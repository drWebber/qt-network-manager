#ifndef TEST_H
#define TEST_H

#include <network/httprequest.h>

class Test
{
private:
     HttpRequest req;
public:
    Test();

    void testGetRequest();

    void testPostRequest();
};

#endif // TEST_H
