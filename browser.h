#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineView>
#include "options.h"

class Browser : public QObject
{
    Q_OBJECT

public:
    Browser(const Options& options);
    ~Browser();
    void run();

public slots:
    void loadFinished();
    void delayedShot();
    void pdfPrintingFinished();

signals:
    void screenshotFinished();

private:
    void screenshot();

    const Options _options;
    QWebEngineView *_view;
    QWebEnginePage *_page;
    QWebEngineProfile *_profile;
};

#endif // BROWSER_H
