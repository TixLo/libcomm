#ifndef __AUTH_OAUTH2_H__
#define __AUTH_OAUTH2_H__

#include "auth.h"

class CommServer;
class OAuth2AuthorizeObserver;
class OAuth2TokenObserver;
class OAuth2CodeObserver;
class OAuth2Rfc6749;

#define OAUTH2_BASIC_REDIRECT_URL   "urn:oauth:2.0:oob"
#define OAUTH2_AUTHORIZE            "/oauth2/authorize"
#define OAUTH2_TOKEN                "/oauth2/token"
#define OAUTH2_CODE                 "/oauth2/code"
#define OAUTH2_SESSION_EXPIRATION   60 //seconds

class AuthOAuth2 : public Auth{
public:
    AuthOAuth2();

    virtual ~AuthOAuth2();

    bool AuthorizingHeaders(ad_conn_t *conn);

    void TimePassing(double delta);

    void Initialize(CommServer *server);

    virtual bool Query(std::string client_id){
        return true;
    }

private:
    OAuth2AuthorizeObserver *authorize_observer;
    OAuth2TokenObserver *token_observer;
    OAuth2CodeObserver *code_observer;
    OAuth2Rfc6749 *rfc6749;
};

#endif//__AUTH_OAUTH2_H__