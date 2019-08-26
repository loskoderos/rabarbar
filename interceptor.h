#ifndef BROWSER_INTERCEPTOR_H
#define BROWSER_INTERCEPTOR_H

#include <QWebEngineUrlRequestInterceptor>
#include <QWebEngineUrlRequestInfo>
#include "options.h"

class RequestInterceptor : public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT

public:
    RequestInterceptor(const Options &options, QObject *p = Q_NULLPTR);
    void interceptRequest(QWebEngineUrlRequestInfo &info);

private:
    const Options _options;
};

#endif // BROWSER_INTERCEPTOR_H
