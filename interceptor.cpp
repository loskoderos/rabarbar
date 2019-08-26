#include <QDebug>
#include "interceptor.h"

RequestInterceptor::RequestInterceptor(QObject *p)
    : QWebEngineUrlRequestInterceptor(p)
{
}

void RequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    qDebug() << "Browser request interceptor" << info.requestUrl();

    // Set some custom header.
    //info.setHttpHeader("X-Custom", "some value");
}
