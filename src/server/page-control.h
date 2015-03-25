#ifndef __PAGE_CONTROL_H__
#define __PAGE_CONTROL_H__

#include "comm-server.h"
#include <vector>
#include <list>

class PageObserver;

class PageControl{
public:
    PageControl();

    ~PageControl();

    /** add CommObserver to listen page data */
    void Attach(PageObserver *observer);

    /** remove CommObserver to listen page data */
    void Detach(PageObserver *observer);

    /** notify all observer */
    PageObserver* Notify(HttpMethod method, char *path, char *query, void *field, int field_len);

private:
    std::vector<PageObserver*> pages;
};

#endif//__PAGE_CONTROL_H__