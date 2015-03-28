#include "comm-client.h"
#include "comm-oauth2-client.h"
#include "comm-logs.h"
#include "oauth2-client-observer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

/////////////////////////////////////////////////////////////////
// Observers
/////////////////////////////////////////////////////////////////
class TestClientObserver : public OAuth2ClientObserver{
public:
    TestClientObserver() : OAuth2ClientObserver(){}

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

    // create basic authentication's client
    OAuth2Client *client = new OAuth2Client();

    // set observer for obtaining response from HTTP server
    client->SetObserver(test_observer);

    // set information of OAuth 2.0
    client->SetClientId("tix");
    client->SetRedirectUri("urn:oauth:2.0:oob");
    client->SetState("xyz");
    client->SetScope("profile");
    client->SetAuthorizeEndPoint("http://127.0.0.1:1234/oauth2/authorize");
    client->SetTokenEndPoint("http://127.0.0.1:1234/oauth2/token");

    // set reqeust timeout
    client->SetTimeout(3);

    bool authorized = client->Authorizing();

    // execute get action
    if (authorized){
        client->Get("http://127.0.0.1:1234/test");
    }
    
    delete client;
    delete test_observer;
}
