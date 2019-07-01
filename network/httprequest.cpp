#include "httprequest.h"

#include <QUrlQuery>
#include <qeventloop.h>
#include <qtextcodec.h>

HttpRequest::HttpRequest(const QByteArray &encoding)
{
    this->encoding = encoding;
}

void HttpRequest::setStandardBrowserHeaders()
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

QString HttpRequest::get(const QUrlQuery &urlQuery)
{
    return get(urlQuery.toString());
}

QString HttpRequest::post(const QUrlQuery &urlQuery, const QMap<QString, QString> headers,
                          const QString body)
{
    request.setUrl(urlQuery.toString());

    QMap<QString, QString>::const_iterator it;
    for (it = headers.begin(); it != headers.end(); ++it) {
        request.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
    }

    QByteArray data;
    if (encoding.contains("UTF-8")) {
        data = body.toUtf8();
    } else {
        data = body.toLocal8Bit();
    }

    reply = manager.post(request, data);
    connect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);

    waitForReply();

    return response;
}

QString HttpRequest::post(const QUrlQuery &urlQuery, QPair<QString, QString> header,
                          const QString body)
{
    return post(urlQuery, QMap<QString, QString>{{header.first, header.second}}, body);
}

QString HttpRequest::post(const QUrlQuery &urlQuery, const QString body)
{
    return post(urlQuery, QMap<QString, QString>(), body);
}

QList<QNetworkCookie> HttpRequest::getCookies()
{
    return cookies;
}

void HttpRequest::setCookies(QNetworkCookieJar *jar)
{
    manager.setCookieJar(jar);
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
        qWarning() << "reply error:" << reply->errorString();
        emit replyFinished();
        return;
    }

    const QVariant redirectionTarget =
            reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    QString contentType = reply->rawHeader("Content-Type");

    QVariant cookieVar = reply->header(QNetworkRequest::SetCookieHeader);
    if (cookieVar.isValid()) {
        cookies.append(cookieVar.value<QList<QNetworkCookie>>());
    }

    byteResponse = reply->readAll();

    if (contentType.contains("windows-1251")) {
        response = QString::fromLocal8Bit(byteResponse);
    } else {
        response = QString(byteResponse);
    }

    if (!redirectionTarget.isNull()) {
        qDebug() << "redirecting to" << redirectionTarget.toUrl();
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
        startGetRequest(redirectedUrl);
        return;
    }

    emit replyFinished();
}
