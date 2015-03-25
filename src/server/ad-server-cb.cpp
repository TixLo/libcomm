#include "ad-server-cb.h"
#include "comm-server.h"
#include "comm-logs.h"
#include "page-control.h"
#include "page-observer.h"
#include "auth.h"

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////
static int ServeNotImplementedHandler(short event, ad_conn_t *conn, void *userdata) {
    struct trans_server_var *priv = (struct trans_server_var*) userdata;
    if (!priv)
        return AD_CLOSE;

    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE) {
        ad_http_response(conn, 501, "text/html", "Not implemented", 15);
        return AD_CLOSE;
    }
    return AD_OK;
}

static int ServerUnauthorizedHandler(short event, ad_conn_t *conn, void *userdata) {
    struct trans_server_var *priv = (struct trans_server_var*) userdata;
    if (!priv)
        return AD_CLOSE;

    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE) {
        ad_http_response(conn, 401, "text/html", "Unauthorized", 12);
        return AD_CLOSE;
    }
    return AD_OK;
}

static bool AuthorizingHeader(CommServer *server, ad_conn_t *conn){
    std::vector<Auth*> auths = server->GetAuths();
    if (auths.size() == 0) // DO NOT need to authorization
        return true;

    for(vector<Auth*>::const_iterator iter = auths.begin(); iter != auths.end(); ++iter){
        if(*iter != 0){
            Auth *auth = (Auth*)(*iter);
            if (auth->AuthorizingHeaders(conn)){
                return true;
            }
        }
    }
    return false;
}

static int CommonDispatchHandler(HttpMethod method, short event, ad_conn_t *conn, void *userdata){
    CommServer *server = (CommServer*) userdata;
    if (!server)
        return AD_CLOSE;

    PageControl *control = server->GetPageControl();
    if (!control)
        return AD_CLOSE;

    char *path = ad_http_get_path(conn);
    char *query = ad_http_get_query(conn);
    int field_length = ad_http_get_content_length(conn);
    void *field = ad_http_get_content(conn, 0, 0);

    //
    // check authorization
    //
    bool authorized = AuthorizingHeader(server, conn);
    if (!authorized){
        return ServerUnauthorizedHandler(event, conn, userdata);
    }

    //
    // find match observer
    // 
    PageObserver *observer = control->Notify(method, path, query, field, field_length);
    if (!observer){
        return ServeNotImplementedHandler(event, conn, userdata);
    }

    //
    // add header
    //
    map<string, string> headers = observer->GetHeaders();
    map<string, string>::iterator iter;
    for (iter = headers.begin(); iter != headers.end(); ++iter) {
        Log("header : (%s, %s)", iter->first.c_str(), iter->second.c_str());
        ad_http_set_response_header(conn, iter->first.c_str(), iter->second.c_str());
    }
    headers.clear();

    //
    // set response
    //
    ad_http_response(conn, 
                     observer->GetResponseCode(), 
                     observer->GetMimeType().c_str(), 
                     observer->GetResponse(), 
                     observer->GetResponseLength());
    // return ad_http_is_keepalive_request(conn) ? AD_DONE : AD_CLOSE;
    return AD_CLOSE; 
}

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
int ServerGetHandler(short event, ad_conn_t *conn, void *userdata){
    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE && (event & AD_EVENT_READ)) {
        return CommonDispatchHandler(kGet, event, conn, userdata);
    }
    return AD_OK;
}

int ServerPostHandler(short event, ad_conn_t *conn, void *userdata){
    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE && (event & AD_EVENT_READ)) {
        return CommonDispatchHandler(kPost, event, conn, userdata);
    }
    return AD_OK;
}