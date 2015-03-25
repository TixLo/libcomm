#ifndef __STORAGE_MEM_H__
#define __STORAGE_MEM_H__

#include "storage.h"
#include <iostream>
#include <vector>
#include <list>

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

    void AddAccount(std::string username, std::string password);

    void RemoveAccount(std::string username);

    bool VerifyAccount(std::string username, std::string password);
private:
    std::vector<Account*> accounts;
};

#endif//__STORAGE_MEM_H__