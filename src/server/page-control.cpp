#include "page-control.h"
#include "page-observer.h"
#include "comm-logs.h"
#include "url-query.h"

#include <algorithm>

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
PageControl::PageControl(){

}

PageControl::~PageControl(){
}

void PageControl::Attach(PageObserver *observer){
    if (!observer)
        return;

    Evt("Attach [%s] observer", observer->GetPath().c_str());
    pages.push_back(observer);
}

void PageControl::Detach(PageObserver *observer){
    if (!observer)
        return;
    Evt("Detach [%s] observer", observer->GetPath().c_str());
    pages.erase(remove(pages.begin(), pages.end(), observer), pages.end());
}

PageObserver* PageControl::Notify(HttpMethod method, char *path, char *query, void *field, int field_len){
    for(vector<PageObserver*>::const_iterator iter = pages.begin(); iter != pages.end(); ++iter){
        if(*iter != 0){
            PageObserver *observer = (PageObserver*)(*iter);
            if (!observer->Equal(method, path))
                continue;

            UrlQuery url_query(query);
            observer->Listen(path, url_query, field, field_len);
            return observer;
        }
    }

    return NULL;
}