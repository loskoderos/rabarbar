#include <QApplication>
#include <QDebug>
#include "common.h"
#include "options.h"
#include "browser.h"

void safeExit()
{
    qDebug() << "Exit";
    QApplication::exit();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(APP_NAME);
    QApplication::setApplicationVersion(APP_VERSION);

    qDebug() << APP_NAME << APP_VERSION << " - " << APP_DESCRIPTION;

    Options options;
    bool parserResult = parseOptions(QCoreApplication::arguments(), options);
    qDebug() << " url =" << options.url;
    qDebug() << " out =" << options.out;
    qDebug() << " width =" << options.width;
    qDebug() << " height =" << options.height;
    qDebug() << " delay =" << options.delay;
    qDebug() << " timeout =" << options.timeout;

    if (!parserResult) {
        qDebug() << "Invalid or missing arguments";
        return -1;
    }

    Browser browser(options);
    QObject::connect(&browser, &Browser::screenshotFinished, safeExit);

    browser.run();
    return app.exec();
}
