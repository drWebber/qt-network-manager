#ifndef TEST_H
#define TEST_H

#include <network/cookiejar.h>
#include <network/httprequest.h>

class Test
{
private:
     HttpRequest req;     
     CookieJar jar;

public:
    Test();

    void testGetRequest();
    void testPostRequest();
    void testCookiesJar();
};

#endif // TEST_H
