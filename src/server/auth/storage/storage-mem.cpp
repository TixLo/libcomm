#include "storage-mem.h"
#include "comm-logs.h"
#include <algorithm>

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
StorageMem::StorageMem() : Storage(){
}

StorageMem::~StorageMem(){
    for(vector<Account*>::const_iterator iter = accounts.begin(); iter != accounts.end(); ++iter){
        if(*iter != 0){
            delete *iter;
        }
    }
    accounts.clear();
}

void StorageMem::AddAccount(string username, string password){
    Account *account = new Account();
    account->username = username;
    account->password = password;

    Evt("add account (%s, %s)", username.c_str(), password.c_str());
    accounts.push_back(account);
}

void StorageMem::RemoveAccount(string username){
    for(vector<Account*>::const_iterator iter = accounts.begin(); iter != accounts.end(); ++iter){
        if(*iter != 0){
            if (!(*iter)->username.compare(username)){
                Evt("remove account (%s)", username.c_str());

                delete *iter;
                accounts.erase(remove(accounts.begin(), accounts.end(), *iter), accounts.end());
                break;
            }
        }
    }
}

bool StorageMem::VerifyAccount(std::string username, std::string password){
    for(vector<Account*>::const_iterator iter = accounts.begin(); iter != accounts.end(); ++iter){
        if(*iter != 0){
            if (!(*iter)->username.compare(username) &&
                !(*iter)->password.compare(password)){
                return true;
            }
        }
    }
    return false;
}
