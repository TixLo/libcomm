#include "auth-oauth2.h"
#include "comm-server.h"
#include "page-control.h"
#include "comm-logs.h"
#include "oauth2-authorize-observer.h"
#include "oauth2-token-observer.h"
#include "oauth2-code-observer.h"
#include "oauth2-rfc6749.h"
#include "storage.h"
#include "util.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
AuthOAuth2::AuthOAuth2() : Auth(){
    class_name = "AuthOAuth2";

    rfc6749 = new OAuth2Rfc6749();
    rfc6749->SetOAuth2(this);
    
    authorize_observer = new OAuth2AuthorizeObserver(rfc6749, OAUTH2_AUTHORIZE, kGet);
    code_observer = new OAuth2CodeObserver(rfc6749, OAUTH2_CODE, kGet);
    token_observer = new OAuth2TokenObserver(rfc6749, OAUTH2_TOKEN, kPost);
}

AuthOAuth2::~AuthOAuth2(){
    delete rfc6749;
    delete authorize_observer;
    delete code_observer;
    delete token_observer;
}

bool AuthOAuth2::AuthorizingHeaders(ad_conn_t *conn){
    const char *authorization = ad_http_get_request_header(conn, "Authorization");
    const char *content_type = ad_http_get_request_header(conn, "Content-Type");
    const char *method = ad_http_get_method(conn);
    char *query = ad_http_get_query(conn);
    char *path = ad_http_get_path(conn);

    Evt("oauth2 authorizing, path : %s", path);

    if (!content_type || strcmp(content_type, "application/x-www-form-urlencoded")){
        Wrn("Incorrect Content-Type : %s", content_type);
        return false;
    }

    if (!strcmp(path, OAUTH2_AUTHORIZE) || 
        !strcmp(path, OAUTH2_TOKEN) || 
        !strcmp(path, OAUTH2_CODE)){
        return true;
    }

    Evt("authorization : %s", authorization);

    if (!authorization){
        return false;
    }
    
    //
    // check "Authorization: Bearer "header
    //
    const char *bearer = strstr(authorization,"Bearer ");
    if (bearer){
        bearer += 7;
        Storage *storage = GetStorage();

        if (!rfc6749->CheckToken(bearer)){
            return false;
        }
        
        if (storage->VerifyAccessToken(bearer)){
            return true;
        }
    }

    return false;
}

void AuthOAuth2::TimePassing(double delta){
    rfc6749->TimePassing(delta);
    GetStorage()->TimePassing(Util::GetCurrentTime());
}

void AuthOAuth2::Initialize(CommServer *server){
    if (!server)
        return;

    PageControl *control = server->GetPageControl();

    control->Attach(authorize_observer);
    control->Attach(code_observer);
    control->Attach(token_observer);
}

