#ifndef __URL_QUERY_H__
#define __URL_QUERY_H__

#include <string>
#include <map>

class UrlQuery{
public:
    UrlQuery(char *query);

    ~UrlQuery();

    std::string ParamForKey(const char *key);

    void Print();

private:
    void UrlDecode(char* dst, const char* src, int normalize);

    void GetPairToken(char *parameter);

    std::map<std::string,std::string> params;
};

#endif//__URL_QUERY_H__