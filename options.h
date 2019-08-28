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
    int timeout;
    QString userAgent;
    QString referer;
    QString pdfOrientation; // landscape, portrait...
    QString pdfPaperSize;   // a3, a4, letter, tabloid...

public:
    Options():
        url(""),
        out(""),
        width(0),
        height(0),
        delay(1),   // This might be fixed in future.
        timeout(30),
        userAgent(""),
        referer(""),
        pdfOrientation("portrait"),
        pdfPaperSize("a4")
    {}
};

bool parseOptions(const QStringList &strings, Options &options);

#endif // OPTIONS_H
