#ifndef __OAUTH2_AUTHORIZE_OBSERVER_H__
#define __OAUTH2_AUTHORIZE_OBSERVER_H__

#include "page-observer.h"
#include "comm-macros.h"

class UrlQuery;
class OAuth2Rfc6749;
class OAuth2Code;

class OAuth2AuthorizeObserver : public PageObserver{
public:
    OAuth2AuthorizeObserver(OAuth2Rfc6749* rfc6749, const char *path, HttpMethod method);

    virtual ~OAuth2AuthorizeObserver();

    void Listen(char *path, UrlQuery &query, void *field, int field_len);
    
private:
    void SendCodeResponse(std::string redirect_uri, 
                          std::string state, 
                          std::string client_id, 
                          OAuth2Code *code_info);

    void SendAccessTokenResponse(std::string redirect_uri, 
                                 std::string state, 
                                 std::string client_id, 
                                 OAuth2Code *code_info);

    OAuth2Rfc6749* rfc6749;
};

#endif//__OAUTH2_AUTHORIZE_OBSERVER_H__