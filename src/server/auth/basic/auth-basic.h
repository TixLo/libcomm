#ifndef __AUTH_BASIC_H__
#define __AUTH_BASIC_H__

#include "auth.h"

class AuthBasic : public Auth{
public:
    AuthBasic();

    ~AuthBasic();

    bool AuthorizingHeaders(ad_conn_t *conn);

private:

};

#endif//__AUTH_BASIC_H__