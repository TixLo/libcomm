#include "url-query.h"
#include "comm-logs.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////
/**
 * decode a percent-encoded C string with optional path normalization
 *
 * The buffer pointed to by @dst must be at least strlen(@src) bytes.
 * Decoding stops at the first character from @src that decodes to null.
 * Path normalization will remove redundant slashes and slash+dot sequences,
 * as well as removing path components when slash+dot+dot is found. It will
 * keep the root slash (if one was present) and will stop normalization
 * at the first questionmark found (so query parameters won't be normalized).
 *
 * @param dst       destination buffer
 * @param src       source buffer
 * @param normalize perform path normalization if nonzero
 * @return          number of valid characters in @dst
 * @author          Johan Lindh <johan@linkdata.se>
 * @legalese        BSD licensed (http://opensource.org/licenses/BSD-2-Clause)
 * from http://stackoverflow.com/questions/154536/encode-decode-urls-in-c
 */
void UrlQuery::UrlDecode(char* dst, const char* src, int normalize)
{
    char* org_dst = dst;
    int slash_dot_dot = 0;
    char ch, a, b;
    do {
        ch = *src++;
        if (ch == '%' && isxdigit(a = src[0]) && isxdigit(b = src[1])) {
            if (a < 'A') a -= '0';
            else if(a < 'a') a -= 'A' - 10;
            else a -= 'a' - 10;
            if (b < 'A') b -= '0';
            else if(b < 'a') b -= 'A' - 10;
            else b -= 'a' - 10;
            ch = 16 * a + b;
            src += 2;
        }
        if (normalize) {
            switch (ch) {
            case '/':
                if (slash_dot_dot < 3) {
                    /* compress consecutive slashes and remove slash-dot */
                    dst -= slash_dot_dot;
                    slash_dot_dot = 1;
                    break;
                }
                /* fall-through */
            case '?':
                /* at start of query, stop normalizing */
                if (ch == '?')
                    normalize = 0;
                /* fall-through */
            case '\0':
                if (slash_dot_dot > 1) {
                    /* remove trailing slash-dot-(dot) */
                    dst -= slash_dot_dot;
                    /* remove parent directory if it was two dots */
                    if (slash_dot_dot == 3)
                        while (dst > org_dst && *--dst != '/')
                            /* empty body */;
                    slash_dot_dot = (ch == '/') ? 1 : 0;
                    /* keep the root slash if any */
                    if (!slash_dot_dot && dst == org_dst && *dst == '/')
                        ++dst;
                }
                break;
            case '.':
                if (slash_dot_dot == 1 || slash_dot_dot == 2) {
                    ++slash_dot_dot;
                    break;
                }
                /* fall-through */
            default:
                slash_dot_dot = 0;
            }
        }
        *dst++ = ch;
    } while(ch);
}

void UrlQuery::GetPairToken(char *parameter){
    if (!parameter)
        return;

    char *p1 = strstr(parameter, "=");
    if (!p1)
        return;

    char *p2 = p1 + 1;
    *p1 = '\0';

    if (!p2)
        return;

    params[parameter] = p2;
    *p1 = '=';
    return;
}

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
UrlQuery::UrlQuery(char *query){
    if (!query)
        return;

    Log("query : %s", query);
    int len = (strlen(query) + 1);

    char *decode_query = (char*)calloc(len, 1);
    if (!decode_query){
        Wrn("out of memory");
        return;
    }
    // memset(decode_query, 0 ,len);

    UrlDecode(decode_query, query, 0);

    char *token = strtok(decode_query, "&");

    while(token != NULL) {
        Log("[%s]", token);
        GetPairToken(token);
        token = strtok(NULL, "&");
    }

    free(decode_query);
}

UrlQuery::~UrlQuery(){

}

string UrlQuery::ParamForKey(const char *key){
    string value;

    if (!key)
        return value;

    if (params.find(key) == params.end()) {
        return value;
    } else {
        return params[key];
    }
}

void UrlQuery::Print(){
    map<string, string>::iterator iter;
    for (iter = params.begin(); iter != params.end(); ++iter) {
        Log("parameter : (%s, %s)", iter->first.c_str(), iter->second.c_str());
    }
}