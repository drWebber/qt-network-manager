#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QMutex>
#include <QNetworkCookieJar>
#include <QSettings>
#include <qnetworkcookie.h>


class CookieJar : public QNetworkCookieJar
{
public:
    CookieJar(QObject *parent = nullptr);
    ~CookieJar();

    virtual QList<QNetworkCookie> cookiesForUrl(const QUrl &url) const;

    virtual bool setCookiesFromUrl(
            const QList<QNetworkCookie> &cookieList, const QUrl &url);
private:
    mutable QMutex mutex;

    void save();
    void load();
};

#endif // COOKIEJAR_H
