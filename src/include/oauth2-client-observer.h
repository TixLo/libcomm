#ifndef __OAUTH2_CLIENT_OBSERVER_H__
#define __OAUTH2_CLIENT_OBSERVER_H__

#include "client-observer.h"
#include <string>

class OAuth2Client;

class OAuth2ClientObserver : public ClientObserver{
public:
    OAuth2ClientObserver();

    virtual ~OAuth2ClientObserver();

    virtual void Response(std::string url, void *data, int len, int code){};

    void AuthorizeResponse(void *data, int len, int code);

    void TokenResponse(void *data, int len, int code);

    void SetOAuth2Client(OAuth2Client* client){
        oauth2_client = client;
    }

private:
    OAuth2Client *oauth2_client;
};

#endif//__OAUTH2_CLIENT_OBSERVER_H__