#ifndef __COMM_OAUTH2_CLIENT_H__
#define __COMM_OAUTH2_CLIENT_H__

#include <iostream>
#include "comm-client.h"
#include "comm-macros.h"

class ClientObserver;

class OAuth2Client : public CommClient{
public:
    OAuth2Client();

    virtual ~OAuth2Client();

    COMM_SYNTHESIZE(std::string, client_id, ClientId)

    COMM_SYNTHESIZE(std::string, redirect_uri, RedirectUri)

    COMM_SYNTHESIZE(std::string, state, State)

    COMM_SYNTHESIZE(std::string, scope, Scope)

    COMM_SYNTHESIZE(std::string, authrize_endpoint, AuthorizeEndPoint)

    COMM_SYNTHESIZE(std::string, token_endpoint, TokenEndPoint)

    bool Authorizing();

    void AuthorizeResponse(void *data, int len, int code);

    void TokenResponse(void *data, int len, int code);

protected:
    virtual void SetExtraHeaders(CURL *curl, struct curl_slist **headers);
    
private:
    std::string access_token;

    std::string code;

    int expires_in;
};

#endif//__COMM_OAUTH2_CLIENT_H__