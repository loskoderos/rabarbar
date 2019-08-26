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
                              "out",
                              "Output filename.",
                              "out"
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
                          },
                          {
                              "user-agent",
                              "Custom browser user agent.",
                              "user-agent"
                          },
                          {
                              "referer",
                              "Custom referer header.",
                              "referer"
                          }
                      });

    parser.parse(strings);

    if (parser.isSet("url")) {
        options.url = QUrl::fromUserInput(parser.value("url"));
    } else {
        result = false;
    }

    if (parser.isSet("out")) {
        options.out = parser.value("out");
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
    }

    if (parser.isSet("user-agent")) {
        options.userAgent = parser.value("user-agent");
    }

    if (parser.isSet("referer")) {
        options.referer = parser.value("referer");
    }

    return result;
}
