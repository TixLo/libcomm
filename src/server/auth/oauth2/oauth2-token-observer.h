#ifndef __OAUTH2_TOKEN_OBSERVER_H__
#define __OAUTH2_TOKEN_OBSERVER_H__

#include "page-observer.h"

class UrlQuery;

class OAuth2TokenObserver : public PageObserver{
public:
    OAuth2TokenObserver(const char *path, HttpMethod method);

    virtual ~OAuth2TokenObserver();

    void Listen(char *path, UrlQuery &query, void *field, int field_len);

private:

};

#endif//__OAUTH2_TOKEN_OBSERVER_H__