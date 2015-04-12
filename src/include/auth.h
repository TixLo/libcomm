#ifndef __AUTH_H__
#define __AUTH_H__

#include <iostream>
#include "comm-macros.h"
#include "asyncd.h"

class Storage;

class Auth{
public:
    Auth();

    virtual ~Auth();

    COMM_SYNTHESIZE_RDONLY(std::string, class_name, ClassName)

    virtual bool AuthorizingHeaders(ad_conn_t *conn) = 0;

    virtual void TimePassing(double delta) = 0;

    Storage* GetStorage(){
        return storage;
    }

private:
    Storage *storage;
};

#endif//__AUTH_H__