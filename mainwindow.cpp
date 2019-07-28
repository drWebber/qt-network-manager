#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qnetworkcookie.h>

#include <qdebug.h>
#include <qurlquery.h>

#include <network/httprequest.h>
#include <QMultiMap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HttpRequest req;
    QString result = req.get("https://google.by");
    qDebug() << "result.size:" << result.size();
    ui->textBrowser->setText(result);

    QUrlQuery params;
    params.addQueryItem("userId", "1");
    QString response = req.get("https://jsonplaceholder.typicode.com/posts", params);
    qDebug() << "GET response:" << response;

    QUrlQuery body;
    body.addQueryItem("name", "John");
    body.addQueryItem("surname", "Doe");

    response = req.post("https://jsonplaceholder.typicode.com/posts", body);

    ui->textBrowser->setText(response);
}

MainWindow::~MainWindow()
{
    delete ui;
}
