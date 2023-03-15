#include <QDebug>
#include <QFile>
#include <QMargins>
#include <QPageLayout>
#include <QPageSize>
#include <QSize>
#include <QTimer>
#include <QWebEngineSettings>
#include "browser.h"
#include "interceptor.h"

Browser::Browser(const Options& options): QObject (), _options(options)
{
    RequestInterceptor *interceptor = new RequestInterceptor(_options);

    _profile = new QWebEngineProfile();
    _profile->setHttpCacheType(QWebEngineProfile::MemoryHttpCache);
    _profile->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    _profile->setPersistentStoragePath(nullptr);
    _profile->setUrlRequestInterceptor(interceptor);
    if (_options.userAgent.length() > 0) {
        _profile->setHttpUserAgent(_options.userAgent);
    }

    _page = new QWebEnginePage(_profile);
    _page->settings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);
    _page->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);

    _view = new QWebEngineView;
    _view->setPage(_page);
    _view->resize(QSize(_options.width, _options.height));
    connect(_view, &QWebEngineView::loadFinished, this, &Browser::loadFinished);

    //qDebug() << "StoragePath:" << _profile->persistentStoragePath();
    //qDebug() << "isOffTheRecord:" << _profile->isOffTheRecord();
}

Browser::~Browser()
{
    delete _profile;
    delete _page;
    delete _view;
}

void Browser::run()
{
    qDebug() << "Load website";
    _view->load(_options.url);

    // TODO: Investigate whether showing GUI can be avoided?
    qDebug() << "Show browser";
    _view->show();

    QTimer::singleShot(_options.timeout * 1000, this, SLOT(timeout()));
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

void Browser::timeout()
{
    qDebug() << "Timeout";
    screenshot();
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
