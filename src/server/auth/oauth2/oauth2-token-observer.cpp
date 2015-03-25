#include "oauth2-token-observer.h"
#include "comm-logs.h"
#include "url-query.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
OAuth2TokenObserver::OAuth2TokenObserver(const char *path, HttpMethod method) : PageObserver(path, method){

}

OAuth2TokenObserver::~OAuth2TokenObserver(){

}

void OAuth2TokenObserver::Listen(char *path, UrlQuery &query, void *field, int field_len){

}