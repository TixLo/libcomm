#include "oauth2-token-observer.h"
#include "oauth2-rfc6749.h"
#include "auth-oauth2.h"
#include "storage.h"
#include "comm-logs.h"
#include "comm-patch.h"
#include "url-query.h"
#include "json/writer.h"
#include "json/reader.h"
#include <stdlib.h>

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
OAuth2TokenObserver::OAuth2TokenObserver(OAuth2Rfc6749* rfc6749, const char *path, HttpMethod method) : PageObserver(path, method){
    SetMimeType("application/json;charset=UTF-8");
    SetHeader("Cache-Control", "no-store");
    SetHeader("Pragma", "no-cache");
    this->rfc6749 = rfc6749;
}

OAuth2TokenObserver::~OAuth2TokenObserver(){

}

void OAuth2TokenObserver::Listen(char *path, UrlQuery &query, void *field, int field_len){
    UrlQuery field_param((char*)field);

    string grant_type = field_param.ParamForKey("grant_type");
    string code = field_param.ParamForKey("code");
    string redirect_uri = field_param.ParamForKey("redirect_uri");
    string client_id = field_param.ParamForKey("client_id");


    if (grant_type.empty() || code.empty()){
        rfc6749->Unauthorized(this, kInvalidRequest);
        return;
    }

    if (grant_type.compare("authorization_code")){
        rfc6749->Unauthorized(this, kUnsupportedResponseType);
        return;
    }

    Storage *storage = rfc6749->GetOAuth2()->GetStorage();
    if (!storage){
        rfc6749->Unauthorized(this, kServerError);
        return;
    }

    char* token = rfc6749->GetToken(field_param);
    if (!token){
        rfc6749->AccessDenied(this, "");
        return;
    }

    string access_token = token;
    if (client_id.empty()){
        client_id = access_token;
    }

    storage->AddSession(client_id, access_token, redirect_uri, OAUTH2_SESSION_EXPIRATION);

    Json::Value root;
    root["access_token"] = access_token;
    root["expires_in"] = OAUTH2_SESSION_EXPIRATION;
    string response = patch::to_string(root); 
    SetResponse(200, (void*)response.c_str(), response.length());

    delete []token;
}