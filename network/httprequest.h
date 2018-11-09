#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <qurl.h>

#include <QtNetwork/qnetworkreply.h>

class HttpRequest : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager manager;
    QUrl url;
    QNetworkReply *reply;
    QNetworkRequest request;
    QString data;

private:
    void waitForReply();

private slots:
    void httpFinished();
    void startGetRequest(const QUrl &url);

signals:
    void replyFinished();

public:
    HttpRequest();
    ~HttpRequest() { }

    QString get(const QUrl &url);
    QString post(const QUrl &url, const QMap<QString, QString> &params);
};

#endif // HTTPREQUEST_H
