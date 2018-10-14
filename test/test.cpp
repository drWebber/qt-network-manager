#include "test.h"

#include <qdebug.h>

Test::Test()
{

}

void Test::testGetRequest()
{
    QString response =
            req.get(QUrl("https://drwebber-dev.000webhostapp.com/index.php"));

    if (!response.isEmpty() && response.contains("Info about client")) {
        qDebug() << "testGetrequest() completed successfully";
    } else {
        qDebug() << "testGetrequest() failed: respose.isEmpty "
                    "or response not contains \"Info about client\"";
    }
}

void Test::testPostRequest()
{
    QMap<QString, QString> params;
    params.insert("name", "Vasya");
    params.insert("email", "ass@hole.com");

    QString response = req.post(
        QUrl("https://drwebber-dev.000webhostapp.com/index.php"),
        params
    );

    if (!response.isEmpty() && response.contains("Welcome Vasya")) {
        qDebug() << "testPostrequest() completed successfully";
    } else {
        qDebug() << "testPostrequest() failed: respose.isEmpty "
                    "or response not contains \"Welcome Vasya\"";
    }

}
