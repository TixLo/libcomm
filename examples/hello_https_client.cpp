#include "comm-client.h"
#include "comm-logs.h"
#include "client-observer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

/////////////////////////////////////////////////////////////////
// Observers
/////////////////////////////////////////////////////////////////
class TestClientObserver : public ClientObserver{
public:
    TestClientObserver() : ClientObserver(){}

    void Response(std::string url, void *data, int len, int code){
        Log("Response , url : %s", url.c_str());
        Log("Response , (%d)data : %s", len, data);
        Log("Response , code : %d", code);
    }
};
/////////////////////////////////////////////////////////////////
// Private
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// Public
/////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
    TestClientObserver *test_observer = new TestClientObserver();

    // create common client
    CommClient *client = new CommClient();

    // set observer for obtaining response from HTTP server
    client->SetObserver(test_observer);

    // set reqeust timeout
    client->SetTimeout(3);

    // enable SSL feature
    client->SetSSL(true);

    // execute get action
    client->Get("https://127.0.0.1:1234/test?p1=123");
    
    // execute post action
    client->Post("https://127.0.0.1:1234/index?p1=123",(void*)"fromClient", 10);

    delete client;
    delete test_observer;
}
