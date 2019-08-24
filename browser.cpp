#include <QDebug>
#include <QSize>
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
}

void Browser::run()
{
    qDebug() << "Start browser";
    _view->load(_options.url);

    // TODO: Investigate whether showing GUI can be avoided?
    _view->show();
}
