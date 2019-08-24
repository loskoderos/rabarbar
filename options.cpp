#include <QCommandLineParser>
#include "options.h"

bool parseOptions(const QStringList &strings, Options &options)
{
    QCommandLineParser parser;

    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.addOptions({
                          {
                              "url",
                              "Website URL address.",
                              "url"
                          },
                          {
                              "width",
                              "Screnshot width.",
                              "width"
                          },
                          {
                              "height",
                              "Screnshot height.",
                              "height"
                          },
                          {
                              "delay",
                              "Wait for n seconds for website after its fully loaded.",
                              "delay"
                          }
                      });

    parser.parse(strings);

    if (parser.isSet("url")) {
        options.url = QUrl::fromUserInput(parser.value("url"));
    }

    if (parser.isSet("width")) {
        options.width = parser.value("width").toInt();
    }

    if (parser.isSet("height")) {
        options.height = parser.value("height").toInt();
    }

    if (parser.isSet("delay")) {
        options.delay = parser.value("delay").toInt();
    }

    return true;
}
