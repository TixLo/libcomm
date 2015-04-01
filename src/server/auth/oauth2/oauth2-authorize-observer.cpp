#include "oauth2-authorize-observer.h"
#include "oauth2-rfc6749.h"
#include "auth-oauth2.h"
#include "comm-logs.h"
#include "comm-server.h"
#include "comm-patch.h"
#include "url-query.h"
#include "json/writer.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////
void OAuth2AuthorizeObserver::SendCodeResponse(string redirect_uri, 
                                               string state, 
                                               string client_id,
                                               OAuth2Code *code_info){
    if (redirect_uri.empty()){
        if (!rfc6749->GetOAuth2()->Query(client_id)){
            rfc6749->AccessDenied(this, state);
            return;
        }

        Json::Value root;

        root["code"] = code_info->GetCode();
        if (!state.empty()){
            root["state"] = state;
        }

        string response = patch::to_string(root);
        SetResponse(200, (void*)response.c_str(), response.length());
        return;
    }
    else{
        string redirect_info = "";

        if (!redirect_uri.compare(OAUTH2_BASIC_REDIRECT_URL)){
            if (CommServer::IsHttps())
                redirect_info += "https://127.0.0.1";
            else
                redirect_info += "http://127.0.0.1";
            redirect_info += ":" + patch::to_string(CommServer::GetInstance()->GetPort());
            redirect_info += OAUTH2_CODE;            
        }
        else{
            redirect_info += redirect_uri;
        }
        redirect_info += "?code=" + code_info->GetCode();

        if (!client_id.empty()){
            redirect_info += "&client_id=" +client_id;
        }

        if (!state.empty()){
            redirect_info += "&state=" +state;
        }

        SetOnceHeader("Location", redirect_info.c_str());
        SetResponse(302);
    }
}

void OAuth2AuthorizeObserver::SendAccessTokenResponse(std::string redirect_uri, 
                                                     std::string state, 
                                                     std::string client_id, 
                                                     OAuth2Code *code_info){
    Json::Value root;
    root["access_token"] = code_info->GetAccessToken();
    root["expires_in"] = OAUTH2_SESSION_EXPIRATION;
    root["state"] = state;
    string response = patch::to_string(root); 
    SetResponse(200, (void*)response.c_str(), response.length());
}

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
OAuth2AuthorizeObserver::OAuth2AuthorizeObserver(OAuth2Rfc6749* rfc6749,const char *path, HttpMethod method) : PageObserver(path, method){
    SetMimeType("application/json;charset=UTF-8");
    SetHeader("Cache-Control", "no-store");
    SetHeader("Pragma", "no-cache");
    this->rfc6749 = rfc6749;
}

OAuth2AuthorizeObserver::~OAuth2AuthorizeObserver(){

}

void OAuth2AuthorizeObserver::Listen(char *path, UrlQuery &query, void *field, int field_len){
    string response_type = query.ParamForKey("response_type");
    string client_id = query.ParamForKey("client_id");
    string redirect_uri = query.ParamForKey("redirect_uri");
    string state = query.ParamForKey("state");
    if (response_type.empty() || client_id.empty()){
        rfc6749->Unauthorized(this, kInvalidRequest, redirect_uri, state);
        return;
    }

    OAuth2Code *code_info = rfc6749->Authorize(query);
    if (!code_info){
        rfc6749->Unauthorized(this, kServerError, redirect_uri, state);
        return;
    }

    Wrn("code : %s", code_info->GetCode().c_str());
    Wrn("access token : %s", code_info->GetAccessToken().c_str());

    if (code_info->GetAccessToken().empty()){
        SendCodeResponse(redirect_uri, state, client_id, code_info);
    }
    else{
        SendAccessTokenResponse(redirect_uri, state, client_id, code_info);
        delete code_info;
    }
}