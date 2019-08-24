#include <QCoreApplication>
#include <QDebug>
#include "common.h"
#include "options.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);

    Options options;

    parseOptions(QCoreApplication::arguments(), options);
    qDebug() << "url =" << options.url;
    qDebug() << "width =" << options.width;
    qDebug() << "height =" << options.height;
    qDebug() << "delay =" << options.delay;

    return app.exec();
}
