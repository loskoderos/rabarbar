#ifndef OPTIONS_H
#define OPTIONS_H

#include <QUrl>
#include <QStringList>

struct Options
{
    QUrl url;
    int width;
    int height;
    int delay;

public:
    Options(): url(""), width(0), height(0), delay(0) {}
};

bool parseOptions(const QStringList &strings, Options &options);

#endif // OPTIONS_H
