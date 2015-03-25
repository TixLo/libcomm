#ifndef __AUTH_OAUTH2_H__
#define __AUTH_OAUTH2_H__

#include "auth.h"

class CommServer;
class OAuth2AuthorizeObserver;
class OAuth2TokenObserver;
class OAuth2CodeObserver;

#define OAUTH2_AUTHORIZE            "/oauth2/authorize"
#define OAUTH2_TOKEN                "/oauth2/token"
#define OAUTH2_CODE                 "/oauth2/code"

class AuthOAuth2 : public Auth{
public:
    AuthOAuth2();

    virtual ~AuthOAuth2();

    bool AuthorizingHeaders(ad_conn_t *conn);

    void Initialize(CommServer *server);

private:
    OAuth2AuthorizeObserver *authorize_observer;
    OAuth2TokenObserver *token_observer;
    OAuth2CodeObserver *code_observer;
};

#endif//__AUTH_OAUTH2_H__