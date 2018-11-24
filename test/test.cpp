#include "test.h"

#include <qdebug.h>
#include <qurlquery.h>

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

    QUrlQuery postData;
    postData.addQueryItem("name", "Vasya");
    postData.addQueryItem("email", "ass@hole.com");
    QString response = req.post(
        QUrl("https://drwebber-dev.000webhostapp.com/index.php"),
        postData
    );

    if (!response.isEmpty() && response.contains("Welcome Vasya")) {
        qDebug() << "testPostrequest() completed successfully";
    } else {
        qDebug() << "testPostrequest() failed: respose.isEmpty "
                    "or response not contains \"Welcome Vasya\"";
    }

}

void Test::testCookiesJar()
{
    // Перед исполнением testCookiesJar обязательно должен быть исполенен
    // testPostRequest(), чтобы в req появились куки
    if(jar.setCookiesFromUrl(req.getCookies(),
                             QUrl("https://drwebber-dev.000webhostapp.com"))) {
        qDebug() << "#1 testCookiesJar() completed successfully";
    } else {
        qDebug() << "#1 testCookiesJar() failed: unable to setCookiesFromUrl";
    }

    if(jar.cookiesForUrl(
                QUrl("https://drwebber-dev.000webhostapp.com")).size() == 1) {
        qDebug() << "#2 testCookiesJar() completed successfully";
    } else {
        qDebug() << "#2 testCookiesJar() failed: unable to load cookiesForUrl";
    }
}
