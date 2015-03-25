#ifndef __AD_SERVER_CB_H__
#define __AD_SERVER_CB_H__

#include "asyncd.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int ServerGetHandler(short event, ad_conn_t *conn, void *userdata);

extern int ServerPostHandler(short event, ad_conn_t *conn, void *userdata);

#ifdef __cplusplus
}
#endif

#endif//__AD_SERVER_CB_H__