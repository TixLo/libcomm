#include "storage-mem.h"
#include "comm-logs.h"
#include "util.h"
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

    for(vector<OAuth2Session*>::const_iterator iter = sessions.begin(); iter != sessions.end(); ++iter){
        if(*iter != 0){
            delete *iter;
        }
    }
    sessions.clear();
}

void StorageMem::TimePassing(double current_time){
    for(vector<OAuth2Session*>::const_iterator iter = sessions.begin(); iter != sessions.end(); ++iter){
        if(!*iter)
            continue;

        if (!(*iter)->IsExpired(current_time))
            continue;

        Log("remove client_id : %s", (*iter)->GetClientId().c_str());
        sessions.erase(remove(sessions.begin(), sessions.end(), (*iter)), sessions.end());
        break;
    }
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
        if(!*iter)
            continue;

        if (!(*iter)->username.compare(username)){
            Evt("remove account (%s)", username.c_str());

            delete *iter;
            accounts.erase(remove(accounts.begin(), accounts.end(), *iter), accounts.end());
            break;
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

void StorageMem::AddSession(string client_id, 
                            string access_token, 
                            string redirect_uri,
                            int expiration){

    double remaining_time = Util::GetCurrentTime() + expiration * 1000;
    OAuth2Session *session = new OAuth2Session();
    session->SetClientId(client_id);
    session->SetAccessToken(access_token);
    session->SetRedirectUri(redirect_uri);
    session->SetRemainingTime(remaining_time);
    session->SetExpiration(expiration);

    Evt("add session , client_id : %s", client_id.c_str());
    Evt("add session , access_token : %s", access_token.c_str());

    sessions.push_back(session);
}

void StorageMem::RemoveSession(std::string client_id){
    for(vector<OAuth2Session*>::const_iterator iter = sessions.begin(); iter != sessions.end(); ++iter){
        if(!*iter)
            continue;
        
        if (!(*iter)->GetClientId().compare(client_id)){
            Evt("remove client_id (%s)", client_id.c_str());

            delete *iter;
            sessions.erase(remove(sessions.begin(), sessions.end(), *iter), sessions.end());
            break;
        }
    }
}

bool StorageMem::VerifyAccessToken(std::string access_token){
    for(vector<OAuth2Session*>::const_iterator iter = sessions.begin(); iter != sessions.end(); ++iter){
        if(!*iter)
            continue;
        
        if (!(*iter)->GetAccessToken().compare(access_token)){
            return true;
        }
    }
    return false;
}

string StorageMem::GetAccessToken(string client_id){
    for(vector<OAuth2Session*>::const_iterator iter = sessions.begin(); iter != sessions.end(); ++iter){
        if(!*iter)
            continue;
        
        if (!(*iter)->GetClientId().compare(client_id)){
            return (*iter)->GetAccessToken();
        }
    }

    return "";
}
