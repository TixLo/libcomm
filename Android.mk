LOCAL_PATH := $(call my-dir)

######################################
# libComm
######################################
include $(CLEAR_VARS)
LOCAL_MODULE    := libcomm

LOCAL_CFLAGS    := -D_GNU_SOURCE \
                   -D_LARGEFILE_SOURCE \
                   -D_FILE_OFFSET_BITS=64 \
                   -fPIC \
                   -DANDROID \
                   -std=gnu99 \
                   -DHAVE_CONFIG_H \
                   -DBUILD_EXTENSION \
                   -fvisibility=hidden
#                   -DSECURE_DB

LOCAL_SRC_FILES := \
    lib/cJSON/cJSON.c \
    lib/curl/lib/file.c \
    lib/curl/lib/timeval.c \
    lib/curl/lib/base64.c \
    lib/curl/lib/hostip.c \
    lib/curl/lib/progress.c \
    lib/curl/lib/formdata.c \
    lib/curl/lib/cookie.c \
    lib/curl/lib/http.c \
    lib/curl/lib/sendf.c \
    lib/curl/lib/ftp.c \
    lib/curl/lib/url.c \
    lib/curl/lib/dict.c \
    lib/curl/lib/if2ip.c \
    lib/curl/lib/speedcheck.c \
    lib/curl/lib/ldap.c \
    lib/curl/lib/version.c \
    lib/curl/lib/getenv.c \
    lib/curl/lib/escape.c \
    lib/curl/lib/mprintf.c \
    lib/curl/lib/telnet.c \
    lib/curl/lib/netrc.c \
    lib/curl/lib/getinfo.c \
    lib/curl/lib/transfer.c \
    lib/curl/lib/strequal.c \
    lib/curl/lib/easy.c \
    lib/curl/lib/security.c \
    lib/curl/lib/curl_fnmatch.c \
    lib/curl/lib/fileinfo.c \
    lib/curl/lib/ftplistparser.c \
    lib/curl/lib/wildcard.c \
    lib/curl/lib/krb5.c \
    lib/curl/lib/memdebug.c \
    lib/curl/lib/http_chunks.c \
    lib/curl/lib/strtok.c \
    lib/curl/lib/connect.c \
    lib/curl/lib/llist.c \
    lib/curl/lib/hash.c \
    lib/curl/lib/multi.c \
    lib/curl/lib/content_encoding.c \
    lib/curl/lib/share.c \
    lib/curl/lib/http_digest.c \
    lib/curl/lib/md4.c \
    lib/curl/lib/md5.c \
    lib/curl/lib/http_negotiate.c \
    lib/curl/lib/inet_pton.c \
    lib/curl/lib/strtoofft.c \
    lib/curl/lib/strerror.c \
    lib/curl/lib/amigaos.c \
    lib/curl/lib/hostasyn.c \
    lib/curl/lib/hostip4.c \
    lib/curl/lib/hostip6.c \
    lib/curl/lib/hostsyn.c \
    lib/curl/lib/inet_ntop.c \
    lib/curl/lib/parsedate.c \
    lib/curl/lib/select.c \
    lib/curl/lib/tftp.c \
    lib/curl/lib/splay.c \
    lib/curl/lib/strdup.c \
    lib/curl/lib/socks.c \
    lib/curl/lib/ssh.c \
    lib/curl/lib/rawstr.c \
    lib/curl/lib/curl_addrinfo.c \
    lib/curl/lib/socks_gssapi.c \
    lib/curl/lib/socks_sspi.c \
    lib/curl/lib/curl_sspi.c \
    lib/curl/lib/slist.c \
    lib/curl/lib/nonblock.c \
    lib/curl/lib/curl_memrchr.c \
    lib/curl/lib/imap.c \
    lib/curl/lib/pop3.c \
    lib/curl/lib/smtp.c \
    lib/curl/lib/pingpong.c \
    lib/curl/lib/rtsp.c \
    lib/curl/lib/curl_threads.c \
    lib/curl/lib/warnless.c \
    lib/curl/lib/hmac.c \
    lib/curl/lib/curl_rtmp.c \
    lib/curl/lib/openldap.c \
    lib/curl/lib/curl_gethostname.c \
    lib/curl/lib/gopher.c \
    lib/curl/lib/idn_win32.c \
    lib/curl/lib/http_negotiate_sspi.c \
    lib/curl/lib/http_proxy.c \
    lib/curl/lib/non-ascii.c \
    lib/curl/lib/asyn-ares.c \
    lib/curl/lib/asyn-thread.c \
    lib/curl/lib/curl_gssapi.c \
    lib/curl/lib/curl_ntlm.c \
    lib/curl/lib/curl_ntlm_wb.c \
    lib/curl/lib/curl_ntlm_core.c \
    lib/curl/lib/curl_ntlm_msgs.c \
    lib/curl/lib/curl_sasl.c \
    lib/curl/lib/curl_multibyte.c \
    lib/curl/lib/hostcheck.c \
    lib/curl/lib/bundles.c \
    lib/curl/lib/conncache.c \
    lib/curl/lib/pipeline.c \
    lib/curl/lib/dotdot.c \
    lib/curl/lib/x509asn1.c \
    lib/curl/lib/http2.c \
    lib/curl/lib/curl_sasl_sspi.c \
    lib/curl/lib/smb.c \
    lib/curl/lib/curl_sasl_gssapi.c \
    lib/curl/lib/curl_endian.c \
    lib/curl/lib/curl_des.c \
    lib/curl/lib/vtls/openssl.c \
    lib/curl/lib/vtls/gtls.c \
    lib/curl/lib/vtls/vtls.c \
    lib/curl/lib/vtls/nss.c \
    lib/curl/lib/vtls/polarssl.c \
    lib/curl/lib/vtls/polarssl_threadlock.c \
    lib/curl/lib/vtls/axtls.c \
    lib/curl/lib/vtls/cyassl.c \
    lib/curl/lib/vtls/curl_schannel.c \
    lib/curl/lib/vtls/curl_darwinssl.c \
    lib/curl/lib/vtls/gskit \
    lib/libevent/buffer.c \
    lib/libevent/bufferevent.c \
    lib/libevent/bufferevent_filter.c \
    lib/libevent/bufferevent_openssl.c \
    lib/libevent/bufferevent_pair.c \
    lib/libevent/bufferevent_ratelim.c \
    lib/libevent/bufferevent_sock.c \
    lib/libevent/epoll.c \
    lib/libevent/epoll_sub.c \
    lib/libevent/evdns.c \
    lib/libevent/event.c \
    lib/libevent/event_tagging.c \
    lib/libevent/evmap.c \
    lib/libevent/evrpc.c \
    lib/libevent/evthread.c \
    lib/libevent/evthread_pthread.c \
    lib/libevent/evutil.c \
    lib/libevent/evutil_rand.c \
    lib/libevent/http.c \
    lib/libevent/listener.c \
    lib/libevent/log.c \
    lib/libevent/poll.c \
    lib/libevent/select.c \
    lib/libevent/signal.c \
    lib/libevent/strlcpy.c \
    lib/libasyncd/lib/qlibc/src/containers/qlist.c \
    lib/libasyncd/lib/qlibc/src/containers/qlisttbl.c \
    lib/libasyncd/lib/qlibc/src/containers/qhasharr.c \
    lib/libasyncd/lib/qlibc/src/containers/qhashtbl.c \
    lib/libasyncd/lib/qlibc/src/containers/qvector.c \
    lib/libasyncd/lib/qlibc/src/containers/qqueue.c \
    lib/libasyncd/lib/qlibc/src/containers/qstack.c \
    lib/libasyncd/lib/qlibc/src/utilities/qcount.c \
    lib/libasyncd/lib/qlibc/src/utilities/qencode.c \
    lib/libasyncd/lib/qlibc/src/utilities/qfile.c \
    lib/libasyncd/lib/qlibc/src/utilities/qhash.c \
    lib/libasyncd/lib/qlibc/src/utilities/qio.c \
    lib/libasyncd/lib/qlibc/src/utilities/qsocket.c \
    lib/libasyncd/lib/qlibc/src/utilities/qstring.c \
    lib/libasyncd/lib/qlibc/src/utilities/qsystem.c \
    lib/libasyncd/lib/qlibc/src/utilities/qtime.c \
    lib/libasyncd/lib/qlibc/src/internal/qinternal.c \
    lib/libasyncd/lib/qlibc/src/internal/md5/md5c.c \
    lib/libasyncd/lib/qlibc/src/extensions/qconfig.c \
    lib/libasyncd/lib/qlibc/src/extensions/qaconf.c \
    lib/libasyncd/lib/qlibc/src/extensions/qlog.c \
    lib/libasyncd/lib/qlibc/src/extensions/qhttpclient.c \
    lib/libasyncd/lib/qlibc/src/extensions/qdatabase.c \
    lib/libasyncd/src/ad_server.c \
    lib/libasyncd/src/ad_http_handler.c \
    lib/radb/radb.c \
    lib/radb/spmemvfs.c \
    lib/radb/sqlite3.c \
    src/log/log.c \
    src/utils/list.c \
    src/utils/openssl_base64.c \
    src/utils/openssl_aes.c \
    src/utils/openssl_hash.c \
    src/utils/url_parser.c \
    src/utils/netlink.c \
    src/utils/utils.c \
    src/auth/auth.c \
    src/auth/basic/basic.c \
    src/auth/oauth2/oauth2.c \
    src/server/server.c \
    src/server/server_auth.c \
    src/auth/db/auth_db.c \
    src/auth/oauth2/oauth2_rfc6749.c \
    src/auth/oauth2/oauth2_session.c \
    src/client/client.c \
    src/client/basic/basic_client.c \
    src/client/oauth2/oauth2_client.c \
    controlflow.cpp

LOCAL_SHARED_LIBRARIES := liblog libssl libcrypto libdl libz

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/lib/cJSON \
    $(LOCAL_PATH)/lib/curl/include \
    $(LOCAL_PATH)/lib/curl/lib \
    $(LOCAL_PATH)/lib/curl/lib/vtls \
    $(LOCAL_PATH)/lib/libasyncd/include/asyncd \
    $(LOCAL_PATH)/lib/libasyncd/lib/qlibc/include \
    $(LOCAL_PATH)/lib/libasyncd/lib/qlibc/src/internal \
    $(LOCAL_PATH)/lib/libasyncd/lib/qlibc/src/internal/md5 \
    $(LOCAL_PATH)/lib/libasyncd/lib/qlibc/include/qlibc \
    $(LOCAL_PATH)/lib/libevent/include \
    $(LOCAL_PATH)/lib/libevent/android \
    $(LOCAL_PATH)/lib/libevent \
    $(LOCAL_PATH)/lib/radb \
    $(LOCAL_PATH)/src/log \
    $(LOCAL_PATH)/src/utils \
    $(LOCAL_PATH)/src/server \
    $(LOCAL_PATH)/src/auth \
    $(LOCAL_PATH)/src/client \
    $(LOCAL_PATH)/../../openssl/include \
    $(LOCAL_PATH)/../../zlib
#
# Android L (64 bits)
#
#LOCAL_SRC_FILES += lib/curl/lib/android_64/ifaddrs.c
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/lib/curl/lib/android_64
#LOCAL_CFLAGS += -DANDROID_L

#
# Android KK (32 bits)
#
LOCAL_SRC_FILES += lib/curl/lib/android_32/ifaddrs.c
LOCAL_C_INCLUDES += $(LOCAL_PATH)/lib/curl/lib/android_32

LOCAL_MODULE_TAGS := optional 

include $(BUILD_SHARED_LIBRARY)