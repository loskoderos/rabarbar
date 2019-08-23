#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>
#include <QCommandLineParser>

struct Options
{
    QString url;
};

enum OptionsParserResult
{
    OptionsOk,
    OptionsError
};

OptionsParserResult parseOptions(QCommandLineParser &parser, Options &options);

#endif // OPTIONS_H
