#include <QCoreApplication>
#include <QDebug>
#include "common.h"
#include "options.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);

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

    return app.exec();
}
