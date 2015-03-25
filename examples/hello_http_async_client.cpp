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

    // execute get action
    client->AsyncGet("http://127.0.0.1:1234/test?p1=123");
    
    // execute post action
    client->AsyncPost("http://127.0.0.1:1234/index?p1=123",(void*)"fromClient", 10);

    //
    // waiting 5 seconds to polling async-action
    //
    for (int i=0 ; i<5; i++){
        sleep(1);
        client->PollingAsyncAction();
    }

    delete client;
    delete test_observer;
}
