#include <QCommandLineParser>
#include "options.h"

bool parseOptions(const QStringList &strings, Options &options)
{
    bool result = true;
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
    } else {
        result = false;
    }

    if (parser.isSet("width")) {
        options.width = parser.value("width").toInt();
    } else {
        result = false;
    }

    if (parser.isSet("height")) {
        options.height = parser.value("height").toInt();
    } else {
        result = false;
    }

    if (parser.isSet("delay")) {
        options.delay = parser.value("delay").toInt();
    } else {
        result = false;
    }

    return result;
}
