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
    QByteArray encoding;

private:
    void waitForReply();

private slots:
    void httpFinished();
    void startGetRequest(const QUrl &url);

signals:
    void replyFinished();

public:
    HttpRequest(const QByteArray &encoding = "UTF-8");
    ~HttpRequest() { }

    void setStandardBrowserHeaders();

    QString get(const QUrl &url);
    QString get(const QString &url);
    QString get(const QUrlQuery &urlQuery);

    QString post(const QUrlQuery &urlQuery, const QMap<QString, QString> headers,
                 const QString body);
    QString post(const QUrlQuery &urlQuery, const QPair<QString, QString> header,
                 const QString body);
    QString post(const QUrlQuery &urlQuery, const QString body);

    QList<QNetworkCookie> getCookies();
    void setCookies(QNetworkCookieJar *jar);

    QByteArray getByteResponse() const;
};

#endif // HTTPREQUEST_H
