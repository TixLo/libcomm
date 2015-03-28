#ifndef __OAUTH2_RFC6749_H__
#define __OAUTH2_RFC6749_H__

#include "comm-macros.h"
#include <iostream>
#include <vector>
#include <list>

class UrlQuery;
class PageObserver;

typedef enum{
    kInvalidRequest = 0,
    kUnauthorizedClient,
    kAccessDenied,
    kUnsupportedResponseType,
    kInvalidScope,
    kServerError,
    kTemporarilyUnavailable,
    kErrorMax
}AuthorizationCodeError;

class OAuth2Code{
    COMM_SYNTHESIZE(std::string, redirect_uri, RedirectUri)
    COMM_SYNTHESIZE(std::string, client_id, ClientId)
    COMM_SYNTHESIZE(std::string, code, Code)
    COMM_SYNTHESIZE(double, remaining_time, RemainingTime)
    bool IsExpired(double delta){
        remaining_time -= delta;
        if (remaining_time <= 0)
            return true;
        return false;
    }
};

class OAuth2Rfc6749{
public:
    OAuth2Rfc6749();

    virtual ~OAuth2Rfc6749();

    void AccessDenied(PageObserver *observer, std::string state);

    void Unauthorized(PageObserver *observer, AuthorizationCodeError err);

    void Unauthorized(PageObserver *observer, AuthorizationCodeError err, std::string redirect_uri, std::string state);

    OAuth2Code* Authorize(UrlQuery &query);

    char* GetToken(UrlQuery &query);

    bool CheckToken(std::string access_token);

    void TimePassing(double delta);

private:
    bool VerifyCode(std::string code);

    void RemoveCode(std::string code);

private:
    std::vector<OAuth2Code*> existed_codes;
};

#endif//__OAUTH2_RFC6749_H__