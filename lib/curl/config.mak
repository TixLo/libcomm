SRC_CURL_SRC = \
    $(top_srcdir)/lib/curl/lib/file.c \
    $(top_srcdir)/lib/curl/lib/timeval.c \
    $(top_srcdir)/lib/curl/lib/base64.c \
    $(top_srcdir)/lib/curl/lib/hostip.c \
    $(top_srcdir)/lib/curl/lib/progress.c \
    $(top_srcdir)/lib/curl/lib/formdata.c \
    $(top_srcdir)/lib/curl/lib/cookie.c \
    $(top_srcdir)/lib/curl/lib/http.c \
    $(top_srcdir)/lib/curl/lib/sendf.c \
    $(top_srcdir)/lib/curl/lib/ftp.c \
    $(top_srcdir)/lib/curl/lib/url.c \
    $(top_srcdir)/lib/curl/lib/dict.c \
    $(top_srcdir)/lib/curl/lib/if2ip.c \
    $(top_srcdir)/lib/curl/lib/speedcheck.c \
    $(top_srcdir)/lib/curl/lib/ldap.c \
    $(top_srcdir)/lib/curl/lib/version.c \
    $(top_srcdir)/lib/curl/lib/getenv.c \
    $(top_srcdir)/lib/curl/lib/escape.c \
    $(top_srcdir)/lib/curl/lib/mprintf.c \
    $(top_srcdir)/lib/curl/lib/telnet.c \
    $(top_srcdir)/lib/curl/lib/netrc.c \
    $(top_srcdir)/lib/curl/lib/getinfo.c \
    $(top_srcdir)/lib/curl/lib/transfer.c \
    $(top_srcdir)/lib/curl/lib/strequal.c \
    $(top_srcdir)/lib/curl/lib/easy.c \
    $(top_srcdir)/lib/curl/lib/security.c \
    $(top_srcdir)/lib/curl/lib/curl_fnmatch.c \
    $(top_srcdir)/lib/curl/lib/fileinfo.c \
    $(top_srcdir)/lib/curl/lib/ftplistparser.c \
    $(top_srcdir)/lib/curl/lib/wildcard.c \
    $(top_srcdir)/lib/curl/lib/krb5.c \
    $(top_srcdir)/lib/curl/lib/memdebug.c \
    $(top_srcdir)/lib/curl/lib/http_chunks.c \
    $(top_srcdir)/lib/curl/lib/strtok.c \
    $(top_srcdir)/lib/curl/lib/connect.c \
    $(top_srcdir)/lib/curl/lib/llist.c \
    $(top_srcdir)/lib/curl/lib/hash.c \
    $(top_srcdir)/lib/curl/lib/multi.c \
    $(top_srcdir)/lib/curl/lib/content_encoding.c \
    $(top_srcdir)/lib/curl/lib/share.c \
    $(top_srcdir)/lib/curl/lib/http_digest.c \
    $(top_srcdir)/lib/curl/lib/md4.c \
    $(top_srcdir)/lib/curl/lib/md5.c \
    $(top_srcdir)/lib/curl/lib/http_negotiate.c \
    $(top_srcdir)/lib/curl/lib/inet_pton.c \
    $(top_srcdir)/lib/curl/lib/strtoofft.c \
    $(top_srcdir)/lib/curl/lib/strerror.c \
    $(top_srcdir)/lib/curl/lib/amigaos.c \
    $(top_srcdir)/lib/curl/lib/hostasyn.c \
    $(top_srcdir)/lib/curl/lib/hostip4.c \
    $(top_srcdir)/lib/curl/lib/hostip6.c \
    $(top_srcdir)/lib/curl/lib/hostsyn.c \
    $(top_srcdir)/lib/curl/lib/inet_ntop.c \
    $(top_srcdir)/lib/curl/lib/parsedate.c \
    $(top_srcdir)/lib/curl/lib/select.c \
    $(top_srcdir)/lib/curl/lib/tftp.c \
    $(top_srcdir)/lib/curl/lib/splay.c \
    $(top_srcdir)/lib/curl/lib/strdup.c \
    $(top_srcdir)/lib/curl/lib/socks.c \
    $(top_srcdir)/lib/curl/lib/ssh.c \
    $(top_srcdir)/lib/curl/lib/rawstr.c \
    $(top_srcdir)/lib/curl/lib/curl_addrinfo.c \
    $(top_srcdir)/lib/curl/lib/socks_gssapi.c \
    $(top_srcdir)/lib/curl/lib/socks_sspi.c \
    $(top_srcdir)/lib/curl/lib/curl_sspi.c \
    $(top_srcdir)/lib/curl/lib/slist.c \
    $(top_srcdir)/lib/curl/lib/nonblock.c \
    $(top_srcdir)/lib/curl/lib/curl_memrchr.c \
    $(top_srcdir)/lib/curl/lib/imap.c \
    $(top_srcdir)/lib/curl/lib/pop3.c \
    $(top_srcdir)/lib/curl/lib/smtp.c \
    $(top_srcdir)/lib/curl/lib/pingpong.c \
    $(top_srcdir)/lib/curl/lib/rtsp.c \
    $(top_srcdir)/lib/curl/lib/curl_threads.c \
    $(top_srcdir)/lib/curl/lib/warnless.c \
    $(top_srcdir)/lib/curl/lib/hmac.c \
    $(top_srcdir)/lib/curl/lib/curl_rtmp.c \
    $(top_srcdir)/lib/curl/lib/openldap.c \
    $(top_srcdir)/lib/curl/lib/curl_gethostname.c \
    $(top_srcdir)/lib/curl/lib/gopher.c \
    $(top_srcdir)/lib/curl/lib/idn_win32.c \
    $(top_srcdir)/lib/curl/lib/http_negotiate_sspi.c \
    $(top_srcdir)/lib/curl/lib/http_proxy.c \
    $(top_srcdir)/lib/curl/lib/non-ascii.c \
    $(top_srcdir)/lib/curl/lib/asyn-ares.c \
    $(top_srcdir)/lib/curl/lib/asyn-thread.c \
    $(top_srcdir)/lib/curl/lib/curl_gssapi.c \
    $(top_srcdir)/lib/curl/lib/curl_ntlm.c \
    $(top_srcdir)/lib/curl/lib/curl_ntlm_wb.c \
    $(top_srcdir)/lib/curl/lib/curl_ntlm_core.c \
    $(top_srcdir)/lib/curl/lib/curl_ntlm_msgs.c \
    $(top_srcdir)/lib/curl/lib/curl_sasl.c \
    $(top_srcdir)/lib/curl/lib/curl_multibyte.c \
    $(top_srcdir)/lib/curl/lib/hostcheck.c \
    $(top_srcdir)/lib/curl/lib/bundles.c \
    $(top_srcdir)/lib/curl/lib/conncache.c \
    $(top_srcdir)/lib/curl/lib/pipeline.c \
    $(top_srcdir)/lib/curl/lib/dotdot.c \
    $(top_srcdir)/lib/curl/lib/x509asn1.c \
    $(top_srcdir)/lib/curl/lib/http2.c \
    $(top_srcdir)/lib/curl/lib/curl_sasl_sspi.c \
    $(top_srcdir)/lib/curl/lib/smb.c \
    $(top_srcdir)/lib/curl/lib/curl_sasl_gssapi.c \
    $(top_srcdir)/lib/curl/lib/curl_endian.c \
    $(top_srcdir)/lib/curl/lib/curl_des.c \
    $(top_srcdir)/lib/curl/lib/vtls/openssl.c \
    $(top_srcdir)/lib/curl/lib/vtls/gtls.c \
    $(top_srcdir)/lib/curl/lib/vtls/vtls.c \
    $(top_srcdir)/lib/curl/lib/vtls/nss.c \
    $(top_srcdir)/lib/curl/lib/vtls/polarssl.c \
    $(top_srcdir)/lib/curl/lib/vtls/polarssl_threadlock.c \
    $(top_srcdir)/lib/curl/lib/vtls/axtls.c \
    $(top_srcdir)/lib/curl/lib/vtls/cyassl.c \
    $(top_srcdir)/lib/curl/lib/vtls/curl_schannel.c \
    $(top_srcdir)/lib/curl/lib/vtls/curl_darwinssl.c \
    $(top_srcdir)/lib/curl/lib/vtls/gskit

SRC_CURL_INCLUDE = \
    -I$(top_srcdir)/lib/curl/include \
    -I$(top_srcdir)/lib/curl/lib \
    -I$(top_srcdir)/lib/curl/lib/vtls

SRC_CURL_CFLAGS = \
    -DHAVE_CONFIG_H \
    -DCURL_HIDDEN_SYMBOL \
    -fvisibility=hidden
    