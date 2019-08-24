#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QWebEngineView>
#include "options.h"

class Browser : public QObject
{
    Q_OBJECT

public:
    Browser(const Options& options);
    void run();

public slots:
    void loadFinished();
    void delayedShot();

private:
    void screenshot();

    const Options _options;
    QImage *_image;
    QPainter *_painter;
    QWebEngineView *_view;
};

#endif // BROWSER_H
