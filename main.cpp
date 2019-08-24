#include <QApplication>
#include <QDebug>
#include "common.h"
#include "options.h"
#include "browser.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(APP_NAME);
    QApplication::setApplicationVersion(APP_VERSION);

    qDebug() << APP_NAME << APP_VERSION << " - " << APP_DESCRIPTION;

    Options options;
    bool parserResult = parseOptions(QCoreApplication::arguments(), options);
    qDebug() << " url =" << options.url;
    qDebug() << " width =" << options.width;
    qDebug() << " height =" << options.height;
    qDebug() << " delay =" << options.delay;

    if (!parserResult) {
        qDebug() << "Invalid or missing arguments";
        return -1;
    }

    Browser browser(options);
    browser.run();

    return app.exec();
}
