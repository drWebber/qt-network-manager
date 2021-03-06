#include "httprequest.h"

#include <qeventloop.h>
#include <qurlquery.h>
#include <qdebug.h>

HttpRequest::HttpRequest(Encoding encoding)
{
    this->encoding = encoding;
}

QString HttpRequest::post(const QString url, const QUrlQuery body, const QUrlQuery headers)
{
    return doRequest(Type::POST, url, body, headers);
}

QString HttpRequest::get(const QString url, const QUrlQuery params, const QUrlQuery headers)
{
    return doRequest(Type::GET, url, params, headers);
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

    if (!redirectionTarget.isNull()) {
        qDebug() << "Redirecting to:" << redirectionTarget.toUrl();
        redirectionUrl = redirectionTarget.toUrl().toString();
    } else {
        redirectionUrl = "";
    }

    emit replyFinished();
}

QString HttpRequest::readResponse() const
{
    QString response = "";

    QByteArray result = reply->readAll();
    if (reply->rawHeader("Content-Type").contains("windows-1251")) {
        response = QString::fromLocal8Bit(result);
    } else {
        response = QString(result);
    }

    return response;
}

QString HttpRequest::doRequest(Type type, const QString url, const QUrlQuery params,
                               const QUrlQuery headers)
{
    foreach (auto header, headers.queryItems()) {
        request.setRawHeader(header.first.toUtf8(), header.second.toUtf8());
    }

    if (type == Type::GET) {
        QUrl _url(url);
        _url.setQuery(params);

        request.setUrl(_url);

        // get request
        reply = manager.get(request);
    } else {
        // post request
        request.setUrl(url);

        if (headers.isEmpty()) {
            request.setHeader(QNetworkRequest::ContentTypeHeader,
                              "application/x-www-form-urlencoded");
        }

        QByteArray body;
        if (encoding == Encoding::UTF_8) {
            body = params.toString().toUtf8();
        } else {
            body = params.toString().toLocal8Bit();
        }

        reply = manager.post(request, body);
    }

    connect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);

    QEventLoop loop;
    connect(this,  SIGNAL(replyFinished()), &loop, SLOT(quit()));
    loop.exec();

    disconnect(this,  SIGNAL(replyFinished()), &loop, SLOT(quit()));
    disconnect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);

    if (!redirectionUrl.isEmpty()) {
        return get(redirectionUrl);
    }

    return readResponse();
}
