#include "oauth2-code-observer.h"
#include "oauth2-rfc6749.h"
#include "auth-oauth2.h"
#include "comm-logs.h"
#include "comm-patch.h"
#include "url-query.h"
#include "json/writer.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
OAuth2CodeObserver::OAuth2CodeObserver(OAuth2Rfc6749* rfc6749, const char *path, HttpMethod method) : PageObserver(path, method){
    SetMimeType("application/json;charset=UTF-8");
    SetHeader("Cache-Control", "no-store");
    SetHeader("Pragma", "no-cache");
    this->rfc6749 = rfc6749;
}

OAuth2CodeObserver::~OAuth2CodeObserver(){

}

void OAuth2CodeObserver::Listen(char *path, UrlQuery &query, void *field, int field_len){
    string code = query.ParamForKey("code");
    string state = query.ParamForKey("state");
    string error = query.ParamForKey("error");
    string client_id = query.ParamForKey("client_id");

    if (!error.empty()){
        rfc6749->Unauthorized(this, kInvalidRequest, "", state);
        return;
    }

    if (code.empty()){
        rfc6749->Unauthorized(this, kInvalidRequest, "", state);
        return;
    }

    if (!oauth2->Query(client_id)){
        rfc6749->AccessDenied(this, state);
        return;
    }

    Json::Value root;
    root["code"] = code;
    if (!state.empty()){
        root["state"] = state;
    }

    std::string response = patch::to_string(root);
    SetResponse(200, (void*)response.c_str(), response.length());
}