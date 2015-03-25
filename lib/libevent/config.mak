SRC_LIBEVENT_SRC = \
    $(top_srcdir)/lib/libevent/buffer.c \
    $(top_srcdir)/lib/libevent/bufferevent.c \
    $(top_srcdir)/lib/libevent/bufferevent_filter.c \
    $(top_srcdir)/lib/libevent/bufferevent_openssl.c \
    $(top_srcdir)/lib/libevent/bufferevent_pair.c \
    $(top_srcdir)/lib/libevent/bufferevent_ratelim.c \
    $(top_srcdir)/lib/libevent/bufferevent_sock.c \
    $(top_srcdir)/lib/libevent/epoll.c \
    $(top_srcdir)/lib/libevent/epoll_sub.c \
    $(top_srcdir)/lib/libevent/evdns.c \
    $(top_srcdir)/lib/libevent/event.c \
    $(top_srcdir)/lib/libevent/event_tagging.c \
    $(top_srcdir)/lib/libevent/evmap.c \
    $(top_srcdir)/lib/libevent/evrpc.c \
    $(top_srcdir)/lib/libevent/evthread.c \
    $(top_srcdir)/lib/libevent/evthread_pthread.c \
    $(top_srcdir)/lib/libevent/evutil.c \
    $(top_srcdir)/lib/libevent/evutil_rand.c \
    $(top_srcdir)/lib/libevent/http.c \
    $(top_srcdir)/lib/libevent/listener.c \
    $(top_srcdir)/lib/libevent/log.c \
    $(top_srcdir)/lib/libevent/poll.c \
    $(top_srcdir)/lib/libevent/select.c \
    $(top_srcdir)/lib/libevent/signal.c \
    $(top_srcdir)/lib/libevent/strlcpy.c


SRC_LIBEVENT_INCLUDE = \
    -I$(top_srcdir)/lib/libevent/include \
    -I$(top_srcdir)/lib/libevent/android
