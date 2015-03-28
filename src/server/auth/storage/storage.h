#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <iostream>
#include "comm-macros.h"

typedef enum{
    kStorageMem = 1
}StorageType;

class Storage{
public:
    Storage(){};

    virtual ~Storage(){};

    static Storage* CreateStorage(StorageType type);

    virtual void TimePassing(double current_time) = 0;

    virtual void AddAccount(std::string username, std::string password) = 0;

    virtual void RemoveAccount(std::string username) = 0;

    virtual bool VerifyAccount(std::string username, std::string password) = 0;

    virtual void AddSession(std::string client_id,
                            std::string access_token,
                            std::string redirect_uri,
                            int expiration) = 0;

    virtual void RemoveSession(std::string client_id) = 0;

    virtual bool VerifyAccessToken(std::string access_token) = 0;
private:
};

#endif//__STORAGE_H__