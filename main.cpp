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
    QCommandLineParser parser;

    parseOptions(parser, options);
    qDebug() << options.url;

    return app.exec();
}
