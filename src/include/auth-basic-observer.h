#ifndef __AUTH_BASIC_OBSERVER_H__
#define __AUTH_BASIC_OBSERVER_H__

#include "page-observer.h"

class AuthBasicObserver : public PageObserver{
public:
    AuthBasicObserver(const char *path, HttpMethod method);

    virtual ~AuthBasicObserver();

    virtual void Listen(char *path, UrlQuery &query, void *field, int field_len){}

    void Unauthorized();

private:

};

#endif//__AUTH_BASIC_OBSERVER_H__