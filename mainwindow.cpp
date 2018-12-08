#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <network/cookiejar.h>
#include <network/httprequest.h>
#include <qnetworkcookie.h>
#include <test/test.h>

#include <qdebug.h>
#include <qurlquery.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HttpRequest req;
    QUrlQuery postData;
    postData.addQueryItem("name", "John");
    postData.addQueryItem("email", "j.doe@gmail.com");

    QString response = req.post(
                QUrl("https://drwebber-dev.000webhostapp.com/index.php"),
                postData
    );

    qDebug() << "req.getCookies()" << req.getCookies();

    CookieJar jar(this);
    qDebug() << jar.setCookiesFromUrl(req.getCookies(),
                          QUrl("https://drwebber-dev.000webhostapp.com"));
    qDebug() << jar.cookiesForUrl(
                    QUrl("https://drwebber-dev.000webhostapp.com"));

    req.setCookies(&jar);
    response = req.get("https://drwebber-dev.000webhostapp.com/index.php");
    ui->textBrowser->setText(response);

    Test test;
    test.testGetRequest();
    test.testPostRequest();
    test.testCookiesJar();
}

MainWindow::~MainWindow()
{
    delete ui;
}
