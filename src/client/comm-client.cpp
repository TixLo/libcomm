#include "comm-client.h"
#include "comm-basic-client.h"
#include "comm-logs.h"
#include "client-observer.h"
#include <algorithm>

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////
static size_t HttpWriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata){
    int len = size * nmemb;
    CommClient *client = (CommClient*)userdata;
    if (!client)
        return len;

    client->Recv(ptr, len);
    return len;    
}

void CommClient::Recv(char *ptr, int len){
    if (recv_buf_size + len > buf_size){
        buf_size += (len > 1024)? len : 1024 ;
        char *new_buf = new char[buf_size];
        memset(new_buf, 0, buf_size);
        memcpy(new_buf, buf, recv_buf_size);
        delete [] buf;
        buf = new_buf;
        Evt("realloc recv buffer size : %d", buf_size);
    }

    memcpy(&buf[recv_buf_size], ptr, len);
    recv_buf_size += len;
}

void CommClient::SetupCurl(CURL *curl,
                           std::string url, 
                           bool post_action, 
                           void *data,
                           int data_len,
                           struct curl_slist **headers_ptr){
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HttpWriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)this);
    curl_easy_setopt(curl, CURLOPT_ENCODING, "gzip, deflate");

    Evt("SetupCurl : %s", url.c_str());
    if (post_action){
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        if (data){
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_len);
        }
        else{
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);            
        }
    }
    else
        curl_easy_setopt(curl, CURLOPT_POST, 0L);

    if (ssl){
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    struct curl_slist *headers = NULL;

    SetExtraHeaders(curl, headers);

    if (!content_type.empty()){
        string buf = "Content-Type: " + content_type;
        headers = curl_slist_append(headers, buf.c_str());
    }

    if (headers){
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    *headers_ptr = headers;
}

bool CommClient::SyncAction(std::string url, bool post_action, void *data, int data_len){
    CURL *curl = NULL;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(!curl) {
        Wrn("can not create curl object");
        return false;
    }

    struct curl_slist *headers = NULL;
    SetupCurl(curl, url, post_action, data, data_len, &headers);

    res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    Evt("http code : %d", http_code);

    if(res != CURLE_OK || http_code != 200){
        if (observer){
            observer->Response(url, (void*)buf, recv_buf_size, http_code);
        }
        ResetRecvBuf();
        return true;
    }

    if (headers)
        curl_slist_free_all(headers);

    curl_easy_cleanup(curl);

    if (observer){
        observer->Response(url, (void*)buf, recv_buf_size, http_code);
    }

    ResetRecvBuf();

    return true;
}

bool CommClient::AsyncAction(std::string url, bool post_action, void *data, int data_len){
    CurlCmd *cmd = new CurlCmd();
    if (!cmd){
        Wrn("out of memory");
        return false;
    }

    cmd->SetCurl(curl_easy_init());
    cmd->SetUrl(url);
    cmd->SetData(data, data_len);
    cmd->SetPostAction(post_action);

    if (cmds.size() == 0){
        struct curl_slist *headers = cmd->GetHeaders();
        SetupCurl(cmd->GetCurl(), url, post_action, data, data_len, &headers);
        curl_multi_add_handle(multi, cmd->GetCurl());
    }

    cmds.push_back(cmd);

    return true;
}

void CommClient::SetExtraHeaders(CURL *curl, struct curl_slist *headers){
    Log("SetExtraHeaders");
}

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
CommClient::CommClient() : domain(""),
                           content_type(""),
                           ssl(false),
                           timeout(10),
                           recv_buf_size(0),
                           buf_size(1024),
                           multi(NULL){
    buf = new char[buf_size];
    multi = curl_multi_init();
}

CommClient::~CommClient(){
    if (buf)
        delete [] buf;

    if (multi)
        curl_multi_cleanup(multi);

    for(vector<CurlCmd*>::const_iterator iter = cmds.begin(); iter != cmds.end(); ++iter){
        if(*iter != 0){
            delete *iter;
        }
    }

    cmds.clear();
}

bool CommClient::Get(std::string url){
    if (url.empty())
        return false;

    return SyncAction(url, false, NULL, 0);
}

bool CommClient::Post(std::string url, void *data, int data_len){
    if (url.empty())
        return false;

    return SyncAction(url, true, data, data_len);
}

bool CommClient::AsyncGet(std::string url){
    if (url.empty())
        return false;

    return AsyncAction(url, false, NULL, 0);
}

bool CommClient::AsyncPost(std::string url, void *data, int data_len){
    if (url.empty())
        return false;

    return AsyncAction(url, true, data, data_len);
}

void CommClient::PollingAsyncAction(){
    int running_handle_count = 0;
    curl_multi_perform(multi, &running_handle_count);
    CURLMsg *msg = curl_multi_info_read(multi, &running_handle_count);
    
    if (!msg)
        return;

    if (msg->msg != CURLMSG_DONE)
        return;

    for(vector<CurlCmd*>::const_iterator iter = cmds.begin(); iter != cmds.end(); ++iter){
        if(*iter != 0){
            CurlCmd *cmd = (CurlCmd*)(*iter);
            if (cmd->GetCurl() == msg->easy_handle){
                int http_code = 0;
                curl_easy_getinfo(cmd->GetCurl(), CURLINFO_RESPONSE_CODE, &http_code);

                if (observer){
                    observer->Response(cmd->GetUrl(), 
                                       (void*)buf, 
                                       recv_buf_size, 
                                       http_code);
                }
                ResetRecvBuf();

                curl_multi_remove_handle(multi, cmd->GetCurl());

                delete cmd;

                cmds.erase(remove(cmds.begin(), cmds.end(), cmd), cmds.end());
                break;
            }
        }
    }

    //
    // next cmd
    //
    if (cmds.size() > 0){
        CurlCmd *cmd = cmds.front();
        Log("next url : %s", cmd->GetUrl().c_str());

        struct curl_slist *headers = cmd->GetHeaders();
        SetupCurl(cmd->GetCurl(), 
                  cmd->GetUrl(), 
                  cmd->GetPostAction(), 
                  cmd->GetData(), 
                  cmd->GetDataLength(), 
                  &headers);

        curl_multi_add_handle(multi, cmd->GetCurl());
    }
}

void CommClient::ResetRecvBuf(){
    memset(buf, 0, buf_size);
    recv_buf_size = 0;
}
