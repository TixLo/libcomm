#include "oauth2-client-observer.h"
#include "comm-oauth2-client.h"
#include "comm-logs.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
OAuth2ClientObserver::OAuth2ClientObserver() : ClientObserver(){
    oauth2_client = NULL;
}

OAuth2ClientObserver::~OAuth2ClientObserver(){

}

void OAuth2ClientObserver::AuthorizeResponse(void *data, int len, int code){
    if (oauth2_client)
        oauth2_client->AuthorizeResponse(data, len, code);
}

void OAuth2ClientObserver::TokenResponse(void *data, int len, int code){
    if (oauth2_client)
        oauth2_client->TokenResponse(data, len, code);
}
