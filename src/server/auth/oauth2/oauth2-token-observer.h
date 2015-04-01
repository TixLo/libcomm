#ifndef __OAUTH2_TOKEN_OBSERVER_H__
#define __OAUTH2_TOKEN_OBSERVER_H__

#include "page-observer.h"
#include "comm-macros.h"

class UrlQuery;
class OAuth2Rfc6749;

class OAuth2TokenObserver : public PageObserver{
public:
    OAuth2TokenObserver(OAuth2Rfc6749* rfc6749, const char *path, HttpMethod method);

    virtual ~OAuth2TokenObserver();

    void Listen(char *path, UrlQuery &query, void *field, int field_len);

private:
    OAuth2Rfc6749* rfc6749;
};

#endif//__OAUTH2_TOKEN_OBSERVER_H__