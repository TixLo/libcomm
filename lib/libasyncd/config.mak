SRC_LIBASYNCD_SRC = \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/containers/qlist.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/containers/qlisttbl.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/containers/qhasharr.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/containers/qhashtbl.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/containers/qvector.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/containers/qqueue.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/containers/qstack.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qcount.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qencode.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qfile.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qhash.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qio.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qsocket.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qstring.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qsystem.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/utilities/qtime.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/internal/qinternal.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/internal/md5/md5c.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/extensions/qconfig.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/extensions/qaconf.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/extensions/qlog.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/extensions/qhttpclient.c \
    $(top_srcdir)/lib/libasyncd/lib/qlibc/src/extensions/qdatabase.c \
    $(top_srcdir)/lib/libasyncd/src/ad_server.c \
    $(top_srcdir)/lib/libasyncd/src/ad_http_handler.c

SRC_LIBASYNCD_INCLUDE = \
    -I$(top_srcdir)/lib/libasyncd/include/asyncd \
    -I$(top_srcdir)/lib/libasyncd/lib/qlibc/include \
    -I$(top_srcdir)/lib/libasyncd/lib/qlibc/src/internal \
    -I$(top_srcdir)/lib/libasyncd/lib/qlibc/src/internal/md5 \
    -I$(top_srcdir)/lib/libasyncd/lib/qlibc/include/qlibc \
    -I$(top_srcdir)/lib/libasyncd/lib/qlibc/include
    