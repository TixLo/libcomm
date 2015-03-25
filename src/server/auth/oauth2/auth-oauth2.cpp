#include "auth-oauth2.h"
#include "comm-server.h"
#include "page-control.h"
#include "comm-logs.h"
#include "oauth2-authorize-observer.h"
#include "oauth2-token-observer.h"
#include "oauth2-code-observer.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
AuthOAuth2::AuthOAuth2() : Auth(){
    class_name = "AuthOAuth2";

    authorize_observer = new OAuth2AuthorizeObserver(OAUTH2_AUTHORIZE, kGet);
    code_observer = new OAuth2CodeObserver(OAUTH2_CODE, kGet);
    token_observer = new OAuth2TokenObserver(OAUTH2_TOKEN, kPost);
}

AuthOAuth2::~AuthOAuth2(){
    delete authorize_observer;
    delete code_observer;
    delete token_observer;
}

bool AuthOAuth2::AuthorizingHeaders(ad_conn_t *conn){
    Evt("oauth2 authorizing");

    const char *authorization = ad_http_get_request_header(conn, "Authorization");
    const char *method = ad_http_get_method(conn);
    
    Log("authorization : %s", authorization);
    Log("method : %s", method);
    return true;
}

void AuthOAuth2::Initialize(CommServer *server){
    if (!server)
        return;

    PageControl *control = server->GetPageControl();

    control->Attach(authorize_observer);
    control->Attach(code_observer);
    control->Attach(token_observer);
}

