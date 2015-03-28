#include "comm-server.h"
#include "page-control.h"
#include "page-observer.h"
#include "auth-oauth2.h"
#include "storage.h"

#include <signal.h>

/////////////////////////////////////////////////////////////////
// Observers
/////////////////////////////////////////////////////////////////
//
// TestObserver
//
class TestObserver : public PageObserver{
public:
    TestObserver(const char *path, HttpMethod method) : PageObserver(path, method){}

    void Listen(char *path, UrlQuery &query, void *field, int field_len){
        Log("listener , path : %s", path);
        Log("listener , p1 : %s", query.ParamForKey("p1").c_str());
        Log("listener , p2 : %s", query.ParamForKey("p2").c_str());
        Log("listener , field : %d, %s", field_len, field);

        // set response's customized header
        SetOnceHeader("Custom", "xxx");

        // set response data
        SetResponse(200, (void*)"hello", 5);
    }

private:

};

//
// IndexObserver
//
class IndexObserver : public PageObserver{
public:
    IndexObserver(const char *path, HttpMethod method) : PageObserver(path, method){}

    void Listen(char *path, UrlQuery &query, void *field, int field_len){
        Log("listener , path : %s", path);
        Log("listener , p1 : %s", query.ParamForKey("p1").c_str());
        Log("listener , p2 : %s", query.ParamForKey("p2").c_str());
        Log("listener , field : %d, %s", field_len, field);

        // set response data
        SetResponse(200, (void*)"OK", 2);
    }

private:

};
/////////////////////////////////////////////////////////////////
// Private
/////////////////////////////////////////////////////////////////
static void CtrlSigFunction(int sig){
    CommServer *server = CommServer::GetInstance();
    server->Stop();
}

/////////////////////////////////////////////////////////////////
// Public
/////////////////////////////////////////////////////////////////
int main(int argc, char **argv){
    signal(SIGINT, CtrlSigFunction);

    //
    // set server type
    //
    CommServer::SetServerType(kHttp);

    // get singleton instance of CommServer class
    CommServer *server = CommServer::GetInstance();

    //
    // create basic authentcaion instance
    //
    AuthOAuth2* auth = new AuthOAuth2();

    // initialize OAuth2
    auth->Initialize(server);

    // get storage in Auth
    Storage *storage = auth->GetStorage();

    // add legal account
    storage->AddAccount("tix","123456");

    // get page control
    PageControl *control = server->GetPageControl();

    // set HTTP port
    server->SetPort(1234);

    // attach auth instance to server
    server->AttachAuth(auth);

    //
    // create observers for different url pages
    //
    TestObserver *test_observer = new TestObserver("/test", kGet);
    control->Attach(test_observer);

    IndexObserver *index_observer = new IndexObserver("/index", kPost);
    control->Attach(index_observer);

    server->Start();

    // delete server instance
    delete server;

    // delete observer instances
    delete test_observer;
    delete index_observer;
    delete auth;
}
