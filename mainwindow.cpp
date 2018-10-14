#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <network/httprequest.h>
#include <test/test.h>

#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HttpRequest req;
    QMap<QString, QString> params;
    params.insert("name", "Vasya");
    params.insert("email", "ass@hole.com");

    QString response = req.post(
                QUrl("https://drwebber-dev.000webhostapp.com/index.php"),
                params
    );

    ui->textBrowser->setText(response);

    Test test;
    test.testGetRequest();
    test.testPostRequest();
}

MainWindow::~MainWindow()
{
    delete ui;
}
