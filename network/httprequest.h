#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <qurl.h>

#include <QtNetwork/qnetworkreply.h>
#include <QNetworkCookie>

class HttpRequest : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager manager;
    QUrl url;
    QNetworkReply *reply;
    QNetworkRequest request;
    QString response;
    QByteArray byteResponse;
    QList<QNetworkCookie> cookies;

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
    QString get(const QString &url);

    QString post(const QUrl &url, const QUrlQuery &postData,
                 const QByteArray &encoding = "UTF-8");
    QString post(const QString &url, const QUrlQuery &postData,
                 const QByteArray &encoding = "UTF-8");

    QList<QNetworkCookie> getCookies();
    void setCookies(QNetworkCookieJar *jar);

    QByteArray getByteResponse() const;
};

#endif // HTTPREQUEST_H
