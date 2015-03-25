SRC_CommServer = \
    $(top_srcdir)/src/server/comm-server.cpp \
    $(top_srcdir)/src/server/ad-server-cb.cpp \
    $(top_srcdir)/src/logs/comm-logs.cpp \
    $(top_srcdir)/src/utils/util-openssl.cpp \
    $(top_srcdir)/src/server/page-control.cpp \
    $(top_srcdir)/src/server/page-observer.cpp \
    $(top_srcdir)/src/server/url-query.cpp \
    $(top_srcdir)/src/server/auth/auth.cpp \
    $(top_srcdir)/src/server/auth/basic/auth-basic.cpp \
    $(top_srcdir)/src/server/auth/oauth2/auth-oauth2.cpp \
    $(top_srcdir)/src/server/auth/oauth2/oauth2-authorize-observer.cpp \
    $(top_srcdir)/src/server/auth/oauth2/oauth2-code-observer.cpp \
    $(top_srcdir)/src/server/auth/oauth2/oauth2-token-observer.cpp \
    $(top_srcdir)/src/server/auth/storage/storage.cpp \
    $(top_srcdir)/src/server/auth/storage/storage-mem.cpp \
    $(top_srcdir)/src/client/comm-client.cpp \
    $(top_srcdir)/src/client/comm-basic-client.cpp \
    $(top_srcdir)/src/client/client-observer.cpp

SRC_INCLUDE = \
    -I$(top_srcdir)/src/server \
    -I$(top_srcdir)/src/server/auth \
    -I$(top_srcdir)/src/server/auth/basic \
    -I$(top_srcdir)/src/server/auth/oauth2 \
    -I$(top_srcdir)/src/server/auth/storage \
    -I$(top_srcdir)/src/logs \
    -I$(top_srcdir)/src/utils \
    -I$(top_srcdir)/src/client 