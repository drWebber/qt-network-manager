#include "cookiejar.h"
#include <qdebug.h>

CookieJar::CookieJar(QObject *parent) : QNetworkCookieJar(parent) {
    load();
}

CookieJar::~CookieJar() {
    save();
}

QList<QNetworkCookie> CookieJar::cookiesForUrl(const QUrl &url) const
{
    QMutexLocker lock(&mutex);
    return QNetworkCookieJar::cookiesForUrl(url);
}

bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList,
                                  const QUrl &url)
{
    QMutexLocker lock(&mutex);
    return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}

void CookieJar::save()
{
    QMutexLocker lock(&mutex);
    QList<QNetworkCookie> list = allCookies();
    QByteArray data;
    foreach (QNetworkCookie cookie, list) {
//        if (!cookie.isSessionCookie()) {
            data.append(cookie.toRawForm());
            data.append("\n");
//        }
    }

    QSettings settings;
    settings.setValue("Cookies", data);
}

void CookieJar::load()
{
    QMutexLocker lock(&mutex);
    QSettings settings;
    QByteArray data = (settings.value("Cookies").toByteArray());
    setAllCookies(QNetworkCookie::parseCookies(data));
}
