#include <QDebug>
#include <QFile>
#include <QSize>
#include <QTimer>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include "browser.h"
#include "interceptor.h"

Browser::Browser(const Options& options): QObject (), _options(options)
{
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);

    QWebEngineProfile::defaultProfile()->setRequestInterceptor(new RequestInterceptor(options));
    if (_options.userAgent.length() > 0) {
        QWebEngineProfile::defaultProfile()->setHttpUserAgent(_options.userAgent);
    }

    _view = new QWebEngineView;
    _view->resize(QSize(_options.width, _options.height));
    connect(_view, &QWebEngineView::loadFinished, this, &Browser::loadFinished);
}

void Browser::run()
{
    qDebug() << "Start browser";
    _view->load(_options.url);

    // TODO: Investigate whether showing GUI can be avoided?
    _view->show();
}

void Browser::loadFinished()
{
    qDebug() << "Load finished";
    if (_options.delay == 0) {
        screenshot();
    } else {
        QTimer::singleShot(_options.delay * 1000, this, SLOT(delayedShot()));
    }
}

void Browser::delayedShot()
{
    qDebug() << "Delayed shot";
    screenshot();
}

void Browser::pdfPrintingFinished()
{
    qDebug() << "PDF printing finished";
    emit screenshotFinished();
}

void Browser::screenshot()
{
    qDebug() << "Save screenshot to" << _options.out;

    if (_options.out.endsWith(".pdf", Qt::CaseInsensitive)) {
        connect(_view->page(), &QWebEnginePage::pdfPrintingFinished, this, &Browser::pdfPrintingFinished);
        _view->page()->printToPdf(_options.out);

    } else {
        QSize size(_options.width, _options.height);
        QImage *image = new QImage(size, QImage::Format_RGB32);
        QPainter *painter = new QPainter(image);

        _view->render(painter);
        painter->end();
        image->save(_options.out);

        emit screenshotFinished();
    }
}
