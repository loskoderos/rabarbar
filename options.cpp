#include "options.h"

OptionsParserResult parseOptions(QCommandLineParser &parser, Options &options)
{
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.addOptions({
                         {
                              "url",
                              "Website URL address",
                              "url"
                          }
                      });
    parser.parse(QCoreApplication::arguments());
    if (parser.isSet("url")) {
        options.url = parser.value("url");
    }
    return OptionsOk;
}
