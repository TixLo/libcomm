#ifndef __COMM_SERVER_H__
#define __COMM_SERVER_H__

#include <iostream>
#include <vector>
#include <list>
#include "asyncd.h"
#include "comm-macros.h"

class PageControl;
class Auth;

using namespace std;

typedef enum {
    kHttp = 1,
    kHttps
}ServerType;

typedef enum {
    kGet = 1,
    kPost,
    kMethodMax
}HttpMethod;

class CommServer{
public:
    CommServer();

    virtual ~CommServer();

    /** get page control to attach and detach observer */
    PageControl *GetPageControl(){
        return page_control;
    }

    /** enable pthread */
    COMM_SYNTHESIZE(bool, enable_pthread, Pthread)

    /** set port number of HTTP server */
    COMM_SYNTHESIZE(unsigned short, server_port, Port)

    /** attach authorization policy */
    void AttachAuth(Auth *auth);

    /** detach authorization policy */
    void DetachAuth(Auth *auth);

    std::vector<Auth*> GetAuths(){
        return auths;
    }

    /** set cert & key file */
    void SetSSL(std::string cert_file, std::string key_file){
        this->cert_file = cert_file;
        this->key_file = key_file;
    }

    /** start server */
    bool Start();

    /** stop server */
    bool Stop();

public:
    static void SetServerType(ServerType type);

    static CommServer* GetInstance();

private:
    static ServerType type;

    static CommServer *instance;

    ad_server_t *http_server;       /** the instance of ad_server_t */

private:
    PageControl *page_control;

    std::string cert_file;

    std::string key_file;

    std::vector<Auth*> auths;
};

#endif//__COMM_SERVER_H__