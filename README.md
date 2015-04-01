libcomm
===========================================
### Overview
------------
libcomm (Library Communication) is a tiny communication library implemented based on four open source library (curl , libasyncd, openssl, and jsoncpp) with C++. The libcomm contains two part, one is http(s) server and client and the other is authentication.It implements a minimal requirement of **[OAuth 2.0 specifiction - RFC 6749](https://tools.ietf.org/html/rfc6749)**.

Because libcomm is implemented with C++, you can port this library to other platform easily, such as Android.

libcomm's features are below:
  - http(s) server / client
  - authentication
    - basic authentication
    - OAuth 2.0 authorization grant 
      - Authorization Code 
      - Implicit (not supported currently)
      - Resource Owner Password Credentials (not supported currently)
      - Client Credentials (not supported currently)

The project is base on several open source projects and thanks those awesome libraries.
  - curl : http://curl.haxx.se/
  - libasyncd : https://github.com/wolkykim/libasyncd/
  - libevent : https://github.com/libevent/libevent
  - jsoncpp : https://github.com/open-source-parsers/jsoncpp
  - openssl : https://github.com/openssl/openssl

### Build on Ubuntu 
------------
```
  apt-get install libevent-dev libssl-dev
  autogen.sh
  configure
  make
```

### Storage Interface
------------
libcomm create a interface (**[storage.h](https://github.com/TixLo/libcomm/blob/master/src/server/auth/storage/storage.h)**) of storage for storing account and session(OAuth 2.0) information. There is a reference implementation (**[storage-mem.cpp](https://github.com/TixLo/libcomm/blob/master/src/server/auth/storage/storage-mem.cpp)**) to implement this interface. You can implement any storage what you want in according to Storage interface.
```c
  class Storage{
  public:
    Storage(){};

    virtual ~Storage(){};

    static Storage* CreateStorage(StorageType type);

    virtual void TimePassing(double current_time) = 0;

    virtual void AddAccount(std::string username, std::string password) = 0;

    virtual void RemoveAccount(std::string username) = 0;

    virtual bool VerifyAccount(std::string username, std::string password) = 0;

    virtual void AddSession(std::string client_id,
                            std::string access_token,
                            std::string redirect_uri,
                            int expiration) = 0;

    virtual void RemoveSession(std::string client_id) = 0;

    virtual bool VerifyAccessToken(std::string access_token) = 0;

    virtual std::string GetAccessToken(std::string client_id) = 0;
  private:
  };
```

### Simple HTTP Server & Client 
------------
**[hello_http_server.cpp](https://github.com/TixLo/libcomm/blob/master/examples/hello_http_server.cpp)**
* create a observer for listening request data
  ```c
  class TestObserver : public PageObserver{
  public:
    TestObserver(const char *path, HttpMethod method) : PageObserver(path, method){}

    void Listen(char *path, UrlQuery &query, void *field, int field_len){
        Log("listener , path : %s", path);
        Log("listener , p1 : %s", query.ParamForKey("p1").c_str());
        Log("listener , p2 : %s", query.ParamForKey("p2").c_str());
        Log("listener , field : %d, %s", field_len, field);

        // set response's customized header
        SetOnceHeader("Custom", "xxx");

        // set response data
        SetResponse(200, (void*)"hello", 5);
    }

  private:

  };
  ```
* create a http server
  ```c
    // set server type
    CommServer::SetServerType(kHttp);

    // get singleton instance of CommServer class
    CommServer *server = CommServer::GetInstance();

    // get page control
    PageControl *control = server->GetPageControl();

    // set HTTP port
    server->SetPort(1234);
  ```

* attach observer
  ```c
    TestObserver *test_observer = new TestObserver("/test", kGet);
    control->Attach(test_observer);
  ```

* start to listen
  ```c
    server->Start();
  ```

**[hello_http_client.cpp](https://github.com/TixLo/libcomm/blob/master/examples/hello_http_client.cpp)**
* create a observer for listening response
```c
  class TestClientObserver : public ClientObserver{
  public:
    TestClientObserver() : ClientObserver(){}

    void Response(std::string url, void *data, int len, int code){
        Log("Response , url : %s", url.c_str());
        Log("Response , (%d)data : %s", len, data);
        Log("Response , code : %d", code);
    }
  };
```
* creat a http client
```c
    TestClientObserver *test_observer = new TestClientObserver();

    // create common client
    CommClient *client = new CommClient();

    // set observer for obtaining response from HTTP server
    client->SetObserver(test_observer);

    // set reqeust timeout
    client->SetTimeout(3);

    // execute get action
    client->Get("http://127.0.0.1:1234/test?p1=123");
    
    // execute post action
    client->Post("http://127.0.0.1:1234/index?p1=123",(void*)"fromClient", 10);
```

### Simple Basic HTTP Server & Client 
------------
**[http_basic_auth_server.cpp](https://github.com/TixLo/libcomm/blob/master/examples/http_basic_auth_server.cpp)**

**[http_basic_auth_client.cpp](https://github.com/TixLo/libcomm/blob/master/examples/http_basic_auth_client.cpp)**
* basic authentication server - inherit AuthBasicObserver

```c
  class TestObserver : public AuthBasicObserver{
  public:
    TestObserver(const char *path, HttpMethod method) : AuthBasicObserver(path, method){}

    void Listen(char *path, UrlQuery &query, void *field, int field_len){
        Log("listener , path : %s", path);
        Log("listener , p1 : %s", query.ParamForKey("p1").c_str());
        Log("listener , p2 : %s", query.ParamForKey("p2").c_str());
        Log("listener , field : %d, %s", field_len, field);

        // set response's customized header
        SetOnceHeader("Custom", "xxx");

        // set response data
        SetResponse(200, (void*)"hello", 5);
    }

  private:
  };
```
* create basic authentication server and config it.

```c
    AuthBasic* auth = new AuthBasic();

    // get storage in Auth
    Storage *storage = auth->GetStorage();

    // add legal account
    storage->AddAccount("tix","123456");

    //
    // set server type
    //
    CommServer::SetServerType(kHttp);

    // get singleton instance of CommServer class
    CommServer *server = CommServer::GetInstance();

    // get page control
    PageControl *control = server->GetPageControl();
    
    ...
```
* basic authentication client

```c
    TestClientObserver *test_observer = new TestClientObserver();

    // create basic authentication's client
    BasicClient *client = new BasicClient();

    // set observer for obtaining response from HTTP server
    client->SetObserver(test_observer);

    // set username
    client->SetUsername("tix");

    // set password
    client->SetPassword("123456");

    // set reqeust timeout
    client->SetTimeout(3);

    // execute get action
    client->Get("http://127.0.0.1:1234/test?p1=123");
    
    // execute post action
    client->Post("http://127.0.0.1:1234/index?p1=123",(void*)"fromClient", 10);
```

### Simple OAuth2 HTTP Server & Client 
------------
**[http_oauth2_auth_server.cpp](https://github.com/TixLo/libcomm/blob/master/examples/http_oauth2_auth_server.cpp)**

**[http_oauth2_auth_client.cpp](https://github.com/TixLo/libcomm/blob/master/examples/http_oauth2_auth_client.cpp)**
* OAuth 2.0 server

```c
    CommServer::SetServerType(kHttp);

    // get singleton instance of CommServer class
    CommServer *server = CommServer::GetInstance();

    //
    // create basic authentcaion instance
    //
    AuthOAuth2* auth = new AuthOAuth2();

    // initialize OAuth2
    auth->Initialize(server);

    // get page control
    PageControl *control = server->GetPageControl();

    // set HTTP port
    server->SetPort(1234);

    // attach auth instance to server
    server->AttachAuth(auth);
    
    ...
```
* OAuth 2.0 client - inherit OAuth2ClientObserver class

```c
class TestClientObserver : public OAuth2ClientObserver{
public:
    TestClientObserver() : OAuth2ClientObserver(){}

    void Response(std::string url, void *data, int len, int code){
        Log("Response , url : %s", url.c_str());
        Log("Response , (%d)data : %s", len, data);
        Log("Response , code : %d", code);
    }
};
```
* OAuth 2.0 client - config OAuth 2.0 information 

```c
    TestClientObserver *test_observer = new TestClientObserver();

    // create basic authentication's client
    OAuth2Client *client = new OAuth2Client();

    // set observer for obtaining response from HTTP server
    client->SetObserver(test_observer);

    // set information of OAuth 2.0
    client->SetClientId("tix");
    client->SetRedirectUri("urn:oauth:2.0:oob");
    client->SetState("xyz");
    client->SetScope("profile");
    client->SetAuthorizeEndPoint("http://127.0.0.1:1234/oauth2/authorize");
    client->SetTokenEndPoint("http://127.0.0.1:1234/oauth2/token");

    // set reqeust timeout
    client->SetTimeout(3);

    bool authorized = client->Authorizing();

    // execute get action
    if (authorized){
        client->Get("http://127.0.0.1:1234/test");
    }
```

### Other Samples 
------------
**[hello_http_async_client.cpp](https://github.com/TixLo/libcomm/blob/master/examples/hello_http_async_client.cpp)**

**[hello_https_client.cpp](https://github.com/TixLo/libcomm/blob/master/examples/hello_https_client.cpp)**

**[hello_https_server.cpp](https://github.com/TixLo/libcomm/blob/master/examples/hello_https_server.cpp)**


## License
------------
See the **[LICENSE](https://github.com/TixLo/libcomm/blob/master/LICENSE)** file for details. In summary, libcomm is licensed under the MIT license.

## Contact me
------------
Any comments please send me a mail to tixlo.tw@gmail.com
