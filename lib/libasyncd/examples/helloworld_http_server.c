/******************************************************************************
 * libasyncd
 *
 * Copyright (c) 2014 Seungyoung Kim.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include "asyncd/asyncd.h"
#include <pthread.h>

static int command_count = 0;
static ad_conn_t *g_conn = NULL;
void* doSomeThing(void *arg) {
    sleep(3);
    printf("doSomeThig\n");
    ad_http_async_response(g_conn, 200, "text/html", "Hello World", 11);
    g_conn = NULL;
    return NULL;
}

int my_http_get_handler(short event, ad_conn_t *conn, void *userdata) {

    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE && (event & AD_EVENT_READ)) {
        printf("my_http_get_handler\n");
        printf("request header : %s\n", ad_http_get_request_header(conn, "customized"));
        printf("request path : %s\n", ad_http_get_path(conn));
        printf("request query : %s\n", ad_http_get_query(conn));
        int content_length = ad_http_get_content_length(conn);
        int content_buf_length = 0;
        char *content_buf = ad_http_get_content(conn, 0, &content_buf_length);
        printf("content length : %d\n", content_length);
        printf("content buf : (%d)%s\n", content_buf_length, content_buf);

        printf("command_count : %d\n",command_count++);

        // ad_http_response(conn, 200, "text/html", "Hello World", 11);
        // return ad_http_is_keepalive_request(conn) ? AD_DONE : AD_CLOSE;

        // ad_http_response(conn, 200, "text/html", "Hello World", 11);
        // return AD_CLOSE;

        g_conn = conn;
        pthread_t tid = 0;
        pthread_create(&tid, NULL, &doSomeThing, NULL);
        // ad_http_response(conn, 102, "text/html", NULL, 0);
        return AD_ASYNC;
    }
    return AD_OK;
}

int my_http_post_handler(short event, ad_conn_t *conn, void *userdata) {
    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE && (event & AD_EVENT_READ)) {
        printf("my_http_post_handler\n");
        printf("request header : %s\n", ad_http_get_request_header(conn, "customized"));
        printf("request path : %s\n", ad_http_get_path(conn));
        printf("request query : %s\n", ad_http_get_query(conn));
        int content_length = ad_http_get_content_length(conn);
        int content_buf_length = 0;
        char *content_buf = ad_http_get_content(conn, 0, &content_buf_length);
        printf("content length : %d\n", content_length);
        printf("content buf : (%d)%s\n", content_buf_length, content_buf);

        printf("command_count : %d\n",command_count++);

        // ad_http_response(conn, 200, "text/html", "Hello World", 11);
        // return ad_http_is_keepalive_request(conn) ? AD_DONE : AD_CLOSE;

        ad_http_response(conn, 200, "text/html", "Hello World", 11);

        return (g_conn == NULL)? AD_CLOSE : AD_DONE;
    }
    return AD_OK;
}

int my_http_default_handler(short event, ad_conn_t *conn, void *userdata) {
    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE) {
        ad_http_response(conn, 501, "text/html", "Not implemented", 15);
        return AD_CLOSE; // Close connection.
    }
    return AD_OK;
}

int main(int argc, char **argv) {
    ad_log_level(AD_LOG_DEBUG);
    ad_server_t *server = ad_server_new();
    ad_server_set_option(server, "server.port", "8888");
    // ad_server_set_option(server, "server.request_pipelining", "1");
    ad_server_register_hook(server, ad_http_handler, NULL); // HTTP Parser is also a hook.
    ad_server_register_hook_on_method(server, "GET", my_http_get_handler, NULL);
    ad_server_register_hook_on_method(server, "POST", my_http_post_handler, NULL);
    ad_server_register_hook(server, my_http_default_handler, NULL);
    return ad_server_start(server);
}
