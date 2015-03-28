#include "comm-oauth2-client.h"
#include "comm-logs.h"
#include "comm-patch.h"
#include "json/reader.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
OAuth2Client::OAuth2Client() : client_id(""), 
                               redirect_uri(""),
                               state(""),
                               scope(""),
                               authrize_endpoint(""),
                               token_endpoint(""), 
                               access_token(""),
                               code(""),
                               CommClient(){
    SetContentType("application/x-www-form-urlencoded");
}

OAuth2Client::~OAuth2Client(){

}

void OAuth2Client::SetExtraHeaders(CURL *curl, struct curl_slist **headers){
    Log("SetExtraHeaders");
    if (!access_token.empty()){
        string buf = "Authorization: Bearer " + access_token;
        Log("buf : %s", buf.c_str());
        *headers = curl_slist_append(*headers, buf.c_str());
    }
}

void OAuth2Client::AuthorizeResponse(void *data, int len, int code){
    if (code != 200){
        CallResponse("", NULL, 0, 401);
        return;
    }

    Log("data : %s", (char*)data);

    string document = (const char*)data;
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(document, root)){
        CallResponse("", NULL, 0, 401);
        return;
    }

    if (!state.empty()){
        if (state.compare(root.get("state", "").asString())){
            CallResponse("", NULL, 0, 401);
            return;
        }
    }
    this->code = root.get("code", "").asString();
}

void OAuth2Client::TokenResponse(void *data, int len, int code){
    if (code != 200){
        CallResponse("", NULL, 0, 401);
        return;
    }

    Log("data : %s", (char*)data);

    string document = (const char*)data;
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(document, root)){
        CallResponse("", NULL, 0, 401);
        return;
    }

    this->access_token = root.get("access_token", "").asString();
}

bool OAuth2Client::Authorizing(){
    //
    // Get Code
    //
    string parameter = authrize_endpoint + "?response_type=code";

    if (!client_id.empty())
        parameter += "&client_id=" + client_id;

    if (!redirect_uri.empty())
        parameter += "&redirect_uri=" + redirect_uri;

    if (!state.empty())
        parameter += "&state=" + state;

    if (!scope.empty())
        parameter += "&scope=" + scope;

    if (!Get(parameter)){
        CallResponse(parameter, NULL, 0, 401);
        return false;
    }

    Log("code : %s", code.c_str());
    if (code.empty()){
        CallResponse(parameter, NULL, 0, 401);
        return false;       
    }

    ResetRecvBuf();
    //
    // Get Access Token
    //
    parameter = "grant_type=authorization_code";
    parameter += "&code=" + code;

    if (!client_id.empty())
        parameter += "&client_id=" + client_id;

    if (!redirect_uri.empty())
        parameter += "&redirect_uri=" + redirect_uri;

    Log("token_endpoint : %s", token_endpoint.c_str());
    Log("Parameter : %s", parameter.c_str());

    if (!Post(token_endpoint,(void*)parameter.c_str(),parameter.length())){
        CallResponse(parameter, NULL, 0, 401);
        return false;
    }

    Log("access_token : %s", access_token.c_str());
    if (access_token.empty()){
        CallResponse(parameter, NULL, 0, 401);
        return false;       
    }

    ResetRecvBuf();
    return true;
}
