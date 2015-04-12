#ifndef __COMM_BASIC_CLIENT_H__
#define __COMM_BASIC_CLIENT_H__

#include <iostream>
#include "comm-client.h"
#include "comm-macros.h"

class BasicClient : public CommClient{
public:
    BasicClient();

    virtual ~BasicClient();

    COMM_SYNTHESIZE(std::string, username, Username)

    COMM_SYNTHESIZE(std::string, password, Password)

protected:
    virtual void SetExtraHeaders(CURL *curl, struct curl_slist **headers);
    
private:
};

#endif//__COMM_BASIC_CLIENT_H__