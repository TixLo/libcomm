#include "auth-basic.h"
#include "comm-logs.h"
#include "storage.h"
#include "util-openssl.h"
#include <string.h>

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
AuthBasic::AuthBasic() : Auth(){
    class_name = "AuthBasic";
}

AuthBasic::~AuthBasic(){
    Evt("Delete AuthBasic");
}

bool AuthBasic::AuthorizingHeaders(ad_conn_t *conn){
    Evt("basic authorizing");
    const char *basic = ad_http_get_request_header(conn, "Authorization");
    if (!basic)
        return false;

    char *realm = strstr((char*)basic, "Basic ");
    if (!realm){
        Evt("invalid realm");
        return false;
    }

    realm += 6;

    Log("realm : %s", realm);

    char *decoded_bytes = NULL;
    int decoded_len = 0;
    UtilOpenssl::Base64Decode(realm, &decoded_bytes,  &decoded_len);
    if (!decoded_bytes){
        Evt("invalid realm");
        return false;
    }

    string decoded_string = decoded_bytes;
    string delimiter = ":";
    string username;
    string password;

    // find username
    size_t pos = decoded_string.find(delimiter);
    if (pos == std::string::npos){
        Evt("invalid realm");
        delete decoded_bytes;
        return false;
    }
    username = decoded_string.substr(0, pos);
    decoded_string.erase(0, pos + delimiter.length());

    // find password
    password = decoded_string;

    Evt("username : %s, password : %s", username.c_str(), password.c_str());
    
    Storage* storage = GetStorage();
    bool valid = storage->VerifyAccount(username, password);
    
    delete decoded_bytes;
    return valid;
}