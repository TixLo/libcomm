#ifndef __PAGE_OBSERVER_H__
#define __PAGE_OBSERVER_H__

#include "comm-server.h"
#include "comm-logs.h"
#include "url-query.h"
#include "comm-macros.h"
#include <string>
#include <stdlib.h>
#include <map>

class PageObserver{
public:
    PageObserver(const char *path, HttpMethod method);

    virtual ~PageObserver();

    bool Equal(HttpMethod input_method, char *input_path){
        return (!path.compare(input_path) && method == input_method);
    }

    void SetHeader(std::string header, std::string value);

    void SetOnceHeader(std::string header, std::string value);

    std::map<std::string, std::string> GetHeaders(){
        return headers;
    }

    std::map<std::string, std::string> GetOnceHeaders(){
        return once_headers;
    }

    COMM_SYNTHESIZE(std::string, path, Path)
    COMM_SYNTHESIZE(std::string, mime, MimeType)
    COMM_SYNTHESIZE(HttpMethod, method, Method)

    void SetResponse(int code){
        SetResponse(code, NULL, 0);
    }

    void SetResponse(int code, void *response, int response_len){
        this->response_code = code;
        if (this->response)
            delete [] this->response;

        if (response){
            this->response = new char[response_len];
            memcpy(this->response, response, response_len);
            this->response_len = response_len;
        }
        else{
            this->response = NULL;
            this->response_len = 0;
        }
    }

    void *GetResponse(){
        return (void*)response;
    }

    int GetResponseLength(){
        return response_len;
    }

    int GetResponseCode(){
        return response_code;
    }

    virtual void Listen(char *path, UrlQuery &query, void *field, int field_len) = 0;

private:
    std::map<std::string, std::string> headers;

    std::map<std::string, std::string> once_headers;

    char *response;

    int response_len;

    int response_code;
};

#endif//__PAGE_OBSERVER_H__