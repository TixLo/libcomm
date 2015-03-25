#include "oauth2-authorize-observer.h"
#include "comm-logs.h"
#include "url-query.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
OAuth2AuthorizeObserver::OAuth2AuthorizeObserver(const char *path, HttpMethod method) : PageObserver(path, method){

}

OAuth2AuthorizeObserver::~OAuth2AuthorizeObserver(){

}

void OAuth2AuthorizeObserver::Listen(char *path, UrlQuery &query, void *field, int field_len){

}