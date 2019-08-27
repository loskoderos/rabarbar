#include <QDebug>
#include <QFile>
#include <QMargins>
#include <QPageLayout>
#include <QPageSize>
#include <QSize>
#include <QTimer>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include "browser.h"
#include "interceptor.h"

Browser::Browser(const Options& options): QObject (), _options(options)
{
    RequestInterceptor *interceptor = new RequestInterceptor(_options);

    QWebEngineProfile *profile = new QWebEngineProfile();
    profile->setHttpCacheType(QWebEngineProfile::MemoryHttpCache);
    profile->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    profile->setPersistentStoragePath(nullptr);
    profile->setRequestInterceptor(interceptor);
    if (_options.userAgent.length() > 0) {
        profile->setHttpUserAgent(_options.userAgent);
    }

    QWebEnginePage *page = new QWebEnginePage(profile);
    page->settings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);

    _view = new QWebEngineView;
    _view->setPage(page);
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
        QPageSize pageSize(QPageSize::A4);
        if (_options.pdfPaperSize == "a3") {
            pageSize = QPageSize(QPageSize::A3);
        } else if (_options.pdfPaperSize == "a4") {
            pageSize = QPageSize(QPageSize::A4);
        } else if (_options.pdfPaperSize == "letter") {
            pageSize = QPageSize(QPageSize::Letter);
        } else if (_options.pdfPaperSize == "tabloid") {
            pageSize = QPageSize(QPageSize::Tabloid);
        }
        QPageLayout layout(pageSize,
                           _options.pdfOrientation == "landscape"
                           ? QPageLayout::Landscape : QPageLayout::Portrait,
                           QMarginsF());

        connect(_view->page(), &QWebEnginePage::pdfPrintingFinished, this, &Browser::pdfPrintingFinished);
        _view->page()->printToPdf(_options.out, layout);

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
