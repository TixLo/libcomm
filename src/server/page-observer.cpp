#include "page-observer.h"
#include "comm-logs.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
PageObserver::PageObserver(const char *path, HttpMethod method){
    this->path = path;
    this->method = method;
    this->response = NULL;
    this->response_len = 0;
    this->mime = "text/plain";
}

PageObserver::~PageObserver(){

}

void PageObserver::SetHeader(string header, string value){
    if (header.empty() || value.empty())
        return;

    headers[header] = value;
}