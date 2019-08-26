#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>
#include <QStringList>
#include <QUrl>

struct Options
{
    QUrl url;
    QString out;
    int width;
    int height;
    int delay;
    QString userAgent;

public:
    Options():
        url(""),
        out(""),
        width(0),
        height(0),
        delay(0),
        userAgent("")
    {}
};

bool parseOptions(const QStringList &strings, Options &options);

#endif // OPTIONS_H
