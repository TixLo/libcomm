#ifndef __OAUTH2_AUTHORIZE_OBSERVER_H__
#define __OAUTH2_AUTHORIZE_OBSERVER_H__

#include "page-observer.h"

class UrlQuery;

class OAuth2AuthorizeObserver : public PageObserver{
public:
    OAuth2AuthorizeObserver(const char *path, HttpMethod method);

    virtual ~OAuth2AuthorizeObserver();

    void Listen(char *path, UrlQuery &query, void *field, int field_len);

private:

};

#endif//__OAUTH2_AUTHORIZE_OBSERVER_H__