#ifndef __CLIENT_OBSERVER_H__
#define __CLIENT_OBSERVER_H__

#include "comm-macros.h"
#include <string>

class ClientObserver{
public:
    ClientObserver();

    virtual ~ClientObserver();

    virtual void Response(std::string url, void *data, int len, int code) = 0;
};

#endif//__CLIENT_OBSERVER_H__