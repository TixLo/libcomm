#ifndef __COMM_CLIENT_H__
#define __COMM_CLIENT_H__

#include <iostream>
#include <vector>
#include <list>
#include <string.h>
#include "comm-macros.h"
#include "curl/curl.h"

class ClientObserver;

class CurlCmd{
public:
    CurlCmd(){

    }
    ~CurlCmd(){
        if (curl)
            curl_easy_cleanup(curl);

        if (headers)
            curl_slist_free_all(headers);

        if (data)
            delete [] (char*)data;
    }
    COMM_SYNTHESIZE(CURL*, curl, Curl)
    COMM_SYNTHESIZE(std::string, url, Url)
    COMM_SYNTHESIZE(bool, post_action, PostAction)
    COMM_SYNTHESIZE(struct curl_slist*, headers, Headers)

    void SetData(void *data, int len){
        if (!data || len == 0)
            return;

        this->data = (void*)new char[len + 1];
        memset(this->data, 0, len + 1);
        memcpy(this->data, data, len);
    }

    void* GetData(){
        return data;
    }

    int GetDataLength(){
        return len;
    }

private:
    void *data;
    int len;
};

class CommClient{
public:
    CommClient();

    virtual ~CommClient();

    COMM_SYNTHESIZE(std::string, domain, Domain)

    COMM_SYNTHESIZE(std::string, content_type, ContentType)

    COMM_SYNTHESIZE(bool, ssl, SSL)

    COMM_SYNTHESIZE(int, timeout, Timeout)

    void SetObserver(ClientObserver* observer);

    bool Get(std::string url);

    bool Post(std::string url, void *data, int data_len);

    bool AsyncGet(std::string url);

    bool AsyncPost(std::string url, void *data, int data_len);

    void PollingAsyncAction();

    void Recv(char *ptr, int len); 

    void ResetRecvBuf();

    void CallResponse(std::string url, void *data, int len, int code);

protected:
    virtual void SetExtraHeaders(CURL *curl, struct curl_slist **headers);

private:
    bool SyncAction(std::string url, bool post_action, void *data, int data_len);

    bool AsyncAction(std::string url, bool post_action, void *data, int data_len);

    void SetupCurl(CURL *curl,
                   std::string url, 
                   bool post_action, 
                   void *data,
                   int data_len,
                   struct curl_slist **headers);

    ClientObserver *observer;

    std::vector<CurlCmd*> cmds;

    CURLM *multi;

    char *buf;
    int recv_buf_size;
    int buf_size;
};

#endif//__COMM_CLIENT_H__