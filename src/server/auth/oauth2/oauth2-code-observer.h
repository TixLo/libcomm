#ifndef __OAUTH2_CODE_OBSERVER_H__
#define __OAUTH2_CODE_OBSERVER_H__

#include "page-observer.h"

class UrlQuery;

class OAuth2CodeObserver : public PageObserver{
public:
    OAuth2CodeObserver(const char *path, HttpMethod method);

    virtual ~OAuth2CodeObserver();

    void Listen(char *path, UrlQuery &query, void *field, int field_len);

private:

};

#endif//__OAUTH2_CODE_OBSERVER_H__