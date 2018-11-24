#include "httprequest.h"

#include <QUrlQuery>
#include <qeventloop.h>

HttpRequest::HttpRequest()
{
    request.setRawHeader("accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8");
    // Сжатие включать не нужно, запрос сам придет на сервер как gzip, deflate
    // request.setRawHeader("accept-encoding", "gzip, deflate");
    request.setRawHeader("accept-language", "en-US,en;q=0.9");
    request.setRawHeader("cache-control", "no-cache");
    request.setRawHeader("pragma", "no-cache");
    request.setRawHeader("upgrade-insecure-requests", "1");
    request.setRawHeader("user-agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36 OPR/56.0.3051.36");
}

QString HttpRequest::get(const QUrl &url)
{
    startGetRequest(url);
    waitForReply();

    disconnect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);
    delete reply;

    return response;
}

QString HttpRequest::get(const QString &url)
{
    return get(QUrl(url));
}

QString HttpRequest::post(const QUrl &url, const QMap<QString, QString> &params)
{
    QUrlQuery postData;
    foreach (QString key, params.keys()) {
        postData.addQueryItem(key, params.value(key));
    }

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");
    reply = manager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);

    waitForReply();

    return response;
}

QString HttpRequest::post(const QString &url,
                          const QMap<QString, QString> &params)
{
    return post(QUrl(url), params);
}

void HttpRequest::startGetRequest(const QUrl &url)
{
    request.setUrl(url);

    reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);
}

QByteArray HttpRequest::getByteResponse() const
{
    return byteResponse;
}

void HttpRequest::waitForReply()
{
    QEventLoop loop;
    connect(this,  SIGNAL(replyFinished()), &loop, SLOT(quit()));
    loop.exec();

    disconnect(this,  SIGNAL(replyFinished()), &loop, SLOT(quit()));
}

void HttpRequest::httpFinished()
{
    if (reply->error()) {
        qDebug() << "reply error";        
        emit replyFinished();
//        reply->deleteLater();
        return;
    }

    const QVariant redirectionTarget =
            reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    QString contentType = reply->rawHeader("Content-Type");
    byteResponse = reply->readAll();
    if (contentType.contains("windows-1251")) {
        response = QString::fromLocal8Bit(byteResponse);
    } else {
        response = QString(byteResponse);
    }

//    reply->deleteLater();

    if (!redirectionTarget.isNull()) {
        qDebug() << "redirecting";
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
        startGetRequest(redirectedUrl);
        return;
    }

    emit replyFinished();
}
