include ./config.mak

lib_LTLIBRARIES = libcomm.la

libcomm_la_LDFLAGS = \
                  -lssl \ 
                  -lcrypto \
                  -lpthread \
                  -levent \
                  -levent_openssl \
                  -levent_pthreads \
                  -lm \
                  -lz \
                  -ldl
                
libcomm_la_CFLAGS = -D_LARGEFILE_SOURCE \
                  -D_FILE_OFFSET_BITS=64 \
                  -D_GNU_SOURCE \
                  -g \
                  -DBUILD_DEBUG \
                  -DBUILD_EXTENSION

libcomm_la_CXXFLAGS = $(libcomm_la_CFLAGS)

libcomm_la_SOURCES = $(SRC_CommServer)

libcomm_la_CFLAGS += $(SRC_INCLUDE)

include $(top_srcdir)/lib/libasyncd/config.mak
libcomm_la_SOURCES += $(SRC_LIBASYNCD_SRC)
libcomm_la_CFLAGS += $(SRC_LIBASYNCD_INCLUDE)

include $(top_srcdir)/lib/jsoncpp/config.mak
libcomm_la_SOURCES += $(SRC_LIBJSONCPP_SRC)
libcomm_la_CFLAGS += $(SRC_LIBSONCPP_INCLUDE)

include $(top_srcdir)/lib/curl/config.mak
libcomm_la_SOURCES += $(SRC_CURL_SRC)
libcomm_la_CFLAGS += $(SRC_CURL_INCLUDE)
libcomm_la_CFLAGS += $(SRC_CURL_CFLAGS)

