#include "comm-server.h"
#include "comm-logs.h"
#include "ad-server-cb.h"
#include "page-control.h"
#include "comm-patch.h"
#include "util.h"
#include "auth.h"

#include <string>
#include <algorithm>

///////////////////////////////////////////////////////////////
// global variables
///////////////////////////////////////////////////////////////
static double polling_prev_time = 0;
ServerType CommServer::type = kHttp; 
CommServer* CommServer::instance = NULL;

///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////
static void PollingFunction(void *user_data){
    CommServer* server = (CommServer*)user_data;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 33000;

    fd_set fd_read;
    fd_set fd_write;
    fd_set fd_except;

    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    FD_ZERO(&fd_except);

    switch (select(1, &fd_read, &fd_write, &fd_except, &timeout)){
        case -1:
            break;
        case 0:
            double current_time = Util::GetCurrentTime();

            std::vector<Auth*> auths = server->GetAuths();
            if (auths.size() > 0){
                for(vector<Auth*>::const_iterator iter = auths.begin(); iter != auths.end(); ++iter){
                    if(*iter != 0){
                        (*iter)->TimePassing(current_time - polling_prev_time);
                    }
                }
            }
            break;
    }
    
    polling_prev_time = Util::GetCurrentTime();
}

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
CommServer::CommServer() : server_port(9999),
                           enable_pthread(false),
                           http_server(NULL),
                           cert_file(""),
                           key_file(""){
    page_control = new PageControl();
}

CommServer::~CommServer(){
    delete page_control;
}

void CommServer::SetServerType(ServerType type){
    CommServer::type = type;
    Log("CommServer SetServerType : %d", CommServer::type);
}

CommServer* CommServer::GetInstance(){
    if (!CommServer::instance){
        CommServer::instance = new CommServer();
    }
    return CommServer::instance;
}

bool CommServer::Start(){
    if (server_port <= 1024){
        Err("invalid port : %d", server_port);
        return false;
    }

    if (http_server){
        Err("server was already started");
        return false;
    }

    string port = patch::to_string(server_port);

    http_server = ad_server_new();
    ad_server_set_option(http_server, "server.port", port.c_str());

    if (type == kHttps){
        ad_server_set_option(http_server, "server.enable_ssl", "1");
        ad_server_set_option(http_server, "server.ssl_cert", cert_file.c_str());
        ad_server_set_option(http_server, "server.ssl_pkey", key_file.c_str());
    }

    if (enable_pthread){
        ad_server_set_option(http_server, "server.thread", "1");
    }

    ad_server_register_hook(http_server, ad_http_handler, NULL);
    ad_server_register_hook_on_method(http_server, "GET", ServerGetHandler, this);
    ad_server_register_hook_on_method(http_server, "POST", ServerPostHandler, this);
    ad_set_polling(http_server, 100, PollingFunction, (void*)this);
    ad_server_start(http_server);
    return true;
}

bool CommServer::Stop(){
    if (http_server){
        Log("stop server");
        ad_server_stop(http_server);
    }
    return false;
}

void CommServer::AttachAuth(Auth *auth){
    if (!auth)
        return;

    Evt("Attach [%s] authorization", auth->GetClassName().c_str());
    auths.push_back(auth);
}

void CommServer::DetachAuth(Auth *auth){
    if (!auth)
        return;

    Evt("Detach [%s] authorization", auth->GetClassName().c_str());
    auths.erase(remove(auths.begin(), auths.end(), auth), auths.end());
}
