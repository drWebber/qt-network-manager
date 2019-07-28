#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qurlquery.h>



class HttpRequest : public QObject
{
    Q_OBJECT
public:
    enum Encoding {UTF_8, WINDOWS_1251};
    HttpRequest(Encoding encoding = Encoding::UTF_8);

    QString post(const QString url,
                 const QUrlQuery body = QUrlQuery(),
                 const QUrlQuery headers = QUrlQuery());
    QString get(const QString url, const QUrlQuery params = QUrlQuery(),
                const QUrlQuery headers = QUrlQuery());

private:
    enum Type {GET, POST};
    QNetworkRequest request;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    Encoding encoding;

    QString readResponse() const;
    QString doRequest(Type type, const QString url, const QUrlQuery params,
                      const QUrlQuery headers);

private slots:
    void httpFinished();
signals:
    void replyFinished();

};

#endif // HTTPREQUEST_H
