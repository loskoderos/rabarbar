#include <QDebug>
#include "interceptor.h"

RequestInterceptor::RequestInterceptor(const Options &options, QObject *p)
    : QWebEngineUrlRequestInterceptor(p), _options(options)
{
}

void RequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    //qDebug() << "Browser request interceptor" << info.requestUrl();

    if (_options.referer.length() > 0) {
        info.setHttpHeader("Referer", _options.referer.toUtf8());
    }

    // Set some custom header.
    //info.setHttpHeader("X-Custom", "some value");
}
