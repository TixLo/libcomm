#include "comm-basic-client.h"
#include "comm-logs.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
BasicClient::BasicClient() : username(""), 
                             password(""), 
                             CommClient(){
}

BasicClient::~BasicClient(){

}

void BasicClient::SetExtraHeaders(CURL *curl, struct curl_slist *headers){
    Log("SetExtraHeaders");

    if (!curl)
        return;

    string userpwd = username + ":" + password;
    curl_easy_setopt(curl, CURLOPT_USERPWD, userpwd.c_str());
}

