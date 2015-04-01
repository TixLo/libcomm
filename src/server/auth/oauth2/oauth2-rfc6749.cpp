#include "oauth2-rfc6749.h"
#include "auth-oauth2.h"
#include "page-observer.h"
#include "comm-logs.h"
#include "comm-server.h"
#include "comm-patch.h"
#include "url-query.h"
#include "json/writer.h"
#include "json/reader.h"
#include "util.h"
#include "util-openssl.h"
#include "storage.h"

#include <algorithm>

#define TOKEN_KEY           "[libcomm-oauth2]"
#define CODE_EXPIRATION     10000 //10s

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////
static const char *authorization_code_map[] = {
    "invalid_request",
    "unauthorized_client",
    "access_denied",
    "unsupported_response_type",
    "invalid_scope",
    "server_error",
    "temporarily_unavailable",
    NULL,
};

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
OAuth2Rfc6749::OAuth2Rfc6749(){
    
}

OAuth2Rfc6749::~OAuth2Rfc6749(){

}

void OAuth2Rfc6749::TimePassing(double delta){
    for(vector<OAuth2Code*>::const_iterator iter = existed_codes.begin(); iter != existed_codes.end(); ++iter){
        if(!*iter)
            continue;

        if (!(*iter)->IsExpired(delta))
            continue;

        // Log("remove code : %s", (*iter)->GetCode().c_str());
        delete (*iter);
        existed_codes.erase(remove(existed_codes.begin(), existed_codes.end(), (*iter)), existed_codes.end());
        break;
    }
}

void OAuth2Rfc6749::RemoveCode(string code){
    for(vector<OAuth2Code*>::const_iterator iter = existed_codes.begin(); iter != existed_codes.end(); ++iter){
        if(!*iter)
            continue;

        if (!(*iter)->GetCode().compare(code)){
            delete (*iter);
            existed_codes.erase(remove(existed_codes.begin(), existed_codes.end(), (*iter)), existed_codes.end());
            break;
        }
    }
}

bool OAuth2Rfc6749::VerifyCode(std::string code){
    for(vector<OAuth2Code*>::const_iterator iter = existed_codes.begin(); iter != existed_codes.end(); ++iter){
        if(!*iter)
            continue;

        if (!(*iter)->GetCode().compare(code)){
            return true;
        }
    }

    return false;
}

void OAuth2Rfc6749::AccessDenied(PageObserver *observer, string state){
    Json::Value root;
    root["error"] = authorization_code_map[kAccessDenied];

    if (!state.empty()){
        root["state"] = state;
    }
    std::string response = patch::to_string(root); 
    observer->SetResponse(403, (void*)response.c_str(), response.length());
}

void OAuth2Rfc6749::Unauthorized(PageObserver *observer, AuthorizationCodeError err){
    Unauthorized(observer, err, "", "");
}

void OAuth2Rfc6749::Unauthorized(PageObserver *observer, 
                                 AuthorizationCodeError err, 
                                 string redirect_uri,
                                 string state){
    string error;
    if (err < kErrorMax)
        error = authorization_code_map[err];

    if (redirect_uri.empty()){
        Json::Value root;
        if (error.empty()){
            root["error"] = "Unauthorized";
        }
        else{
            root["error"] = error;
        }

        if (!state.empty()){
            root["state"] = state;
        }
        std::string response = patch::to_string(root); 
        observer->SetResponse(401, (void*)response.c_str(), response.length());
    }
    else{
        string response = redirect_uri;

        if (error.empty()){
            response += "#error=unauthorized";
        }
        else{
            response += "#error=" + error;
        }

        if (!state.empty()){
            response += "&state=" + state;
        } 

        observer->SetResponse(302, (void*)response.c_str(), response.length());
    }
}

OAuth2Code* OAuth2Rfc6749::Authorize(UrlQuery &query){
    string response_type = query.ParamForKey("response_type");
    string client_id = query.ParamForKey("client_id");
    string redirect_uri = query.ParamForKey("redirect_uri");
    string scope = query.ParamForKey("scope");
    string state = query.ParamForKey("state");

    //
    // generate code
    //
    OAuth2Code *code_info = new OAuth2Code();
    code_info->SetRedirectUri(redirect_uri);
    code_info->SetClientId(client_id);
    code_info->SetRemainingTime(CODE_EXPIRATION);

    // check client_id
    Storage *storage = oauth2->GetStorage();
    string access_token;
    if (storage){
        access_token = storage->GetAccessToken(client_id);
    }

    if (access_token.empty()){
        string t = patch::to_string((long long)Util::GetCurrentTime());
        string pattern = t + "-" + redirect_uri + "-" + client_id;

        char *code = UtilOpenssl::Hash((void*)pattern.c_str(), pattern.length());
        if (!code)
            code_info->SetCode(t); 
        else{
            code_info->SetCode(code);
            delete []code;
        }
        existed_codes.push_back(code_info);
    }
    else{
        code_info->SetAccessToken(access_token);
    }
    return code_info;
}

char* OAuth2Rfc6749::GetToken(UrlQuery &query){
    string grant_type = query.ParamForKey("grant_type");
    string code = query.ParamForKey("code");
    string redirect_uri = query.ParamForKey("redirect_uri");
    string client_id = query.ParamForKey("client_id");

    if (!VerifyCode(code)){
        return NULL;
    }

    // remove code
    RemoveCode(code);

    //
    // generate access_token
    //
    Json::Value root;

    // 1. get current time
    string t = patch::to_string((long long)Util::GetCurrentTime());
    root["current"] = t;

    // 2. add customized information
    root["customized"] = "YourCustomizedData";

    // 3. convert to string
    string uncrypted_access_token;
    {
        uncrypted_access_token = patch::to_string(root);
    }
    Log("uncrypted_access_token : %s", uncrypted_access_token.c_str());

    // 4. AES encrypt
    unsigned char *ciphertext = NULL;
    int ciphertext_len = 0;
    if (UtilOpenssl::AesEncrypt((unsigned char*)TOKEN_KEY, 
                               (unsigned char*)uncrypted_access_token.c_str(),
                               (int)uncrypted_access_token.length(), 
                               &ciphertext, 
                               &ciphertext_len) == false){
        return NULL;
    }

    // 5. base64 encode
    char *access_token = UtilOpenssl::Base64Encode((char*)ciphertext, ciphertext_len);
    if (!access_token){
        free(ciphertext);
        return NULL;
    }

    free(ciphertext);

    return access_token;
}

bool OAuth2Rfc6749::CheckToken(std::string access_token){

    // 1. base64 decode
    unsigned char *ciphertext = NULL;
    int ciphertext_len = 0;
    UtilOpenssl::Base64Decode((char*)access_token.c_str(), (char**)&ciphertext, &ciphertext_len);

    if (ciphertext_len <= 0){
        return false;
    }

    // 2. AES decrypt
    unsigned char *plaintext = NULL;
    int plaintext_len = 0;
    if (!UtilOpenssl::AesDecrypt((unsigned char*)TOKEN_KEY,
                                   ciphertext,
                                   ciphertext_len, 
                                   &plaintext, 
                                   &plaintext_len)){
        delete []ciphertext;
        return false;
    }

    // 3. check JSON format
    string document = (const char*)plaintext;
    Log("plaintext : %s", plaintext);
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(document, root)){
        free(plaintext);
        delete []ciphertext;
        return false;
    }

    // 4. print information of access_token
    Log("customized value : %s", root.get("customized", "").asCString());

    free(plaintext);
    delete []ciphertext;
    return true;
}
