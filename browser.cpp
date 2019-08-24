#include <QDebug>
#include <QSize>
#include <QTimer>
#include <QWebEngineSettings>
#include "browser.h"

Browser::Browser(const Options& options): QObject (), _options(options)
{
    QSize size(_options.width, _options.height);
    _image = new QImage(size, QImage::Format_RGB32);
    _painter = new QPainter(_image);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);

    _view = new QWebEngineView;
    _view->resize(size);

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

void Browser::screenshot()
{
    qDebug() << "Screenshot";
    _view->render(_painter);
    _painter->end();
    _image->save(_options.out);

    emit screenshotFinished();
}
