#ifndef __STORAGE_MEM_H__
#define __STORAGE_MEM_H__

#include "storage.h"
#include "comm-macros.h"
#include <iostream>
#include <vector>
#include <list>

class OAuth2Session{
    COMM_SYNTHESIZE(std::string, access_token, AccessToken)
    COMM_SYNTHESIZE(std::string, redirect_uri, RedirectUri)
    COMM_SYNTHESIZE(std::string, client_id, ClientId)
    COMM_SYNTHESIZE(double, remaining_time, RemainingTime)
    COMM_SYNTHESIZE(int, expiration, Expiration)
    bool IsExpired(double current_time){
        if (remaining_time <= current_time)
            return true;
        return false;
    }
};

class Account{
public:
    Account():username(""), password(""){

    }

    ~Account(){

    }

    std::string username;
    std::string password;
};

class StorageMem : public Storage{
public:
    StorageMem();

    ~StorageMem();

    void TimePassing(double current_time);

    void AddAccount(std::string username, std::string password);

    void RemoveAccount(std::string username);

    bool VerifyAccount(std::string username, std::string password);

    void AddSession(std::string client_id, 
                    std::string access_token, 
                    std::string redirect_uri,
                    int expiration);

    void RemoveSession(std::string client_id);

    bool VerifyAccessToken(std::string access_token);
private:
    std::vector<Account*> accounts;

    std::vector<OAuth2Session*> sessions;
};

#endif//__STORAGE_MEM_H__