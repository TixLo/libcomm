#include "auth.h"
#include "auth-basic.h"
#include "auth-oauth2.h"
#include "comm-logs.h"
#include "storage.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
Auth::Auth() : class_name(""){
    storage = Storage::CreateStorage(kStorageMem);
}

Auth::~Auth(){
    delete storage;
}