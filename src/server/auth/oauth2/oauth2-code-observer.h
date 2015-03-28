#ifndef __OAUTH2_CODE_OBSERVER_H__
#define __OAUTH2_CODE_OBSERVER_H__

#include "page-observer.h"
#include "comm-macros.h"

class UrlQuery;
class OAuth2Rfc6749;
class AuthOAuth2;

class OAuth2CodeObserver : public PageObserver{
public:
    OAuth2CodeObserver(OAuth2Rfc6749* rfc6749, const char *path, HttpMethod method);

    virtual ~OAuth2CodeObserver();

    void Listen(char *path, UrlQuery &query, void *field, int field_len);

    void SetOAuth2(AuthOAuth2 *oauth2){
        this->oauth2 = oauth2;
    }

private:
    OAuth2Rfc6749* rfc6749;
    AuthOAuth2 *oauth2;
};

#endif//__OAUTH2_CODE_OBSERVER_H__