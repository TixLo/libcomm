#include "auth-basic-observer.h"
#include "comm-logs.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
AuthBasicObserver::AuthBasicObserver(const char *path, HttpMethod method) : PageObserver(path, method){

}

AuthBasicObserver::~AuthBasicObserver(){

}

void AuthBasicObserver::Unauthorized(){
    SetOnceHeader("WWW-Authenticate", "Basic realm=\"\"");
    SetResponse(401, (void*)"Unauthorized", 12);
}

