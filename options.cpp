#include <QByteArray>
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
                              "b64-url",
                              "Website URL address (Base64 encoded).",
                              "b64-url"
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
                              "timeout",
                              "Max wait time for a page to be loaded.",
                              "timeout"
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
                          },
                          {
                              "pdf-orientation",
                              "PDF orientation (landscape, portrait).",
                              "pdf-orientation"
                          },
                          {
                              "pdf-paper-size",
                              "PDF orientation (a3, a4, letter, tabloid).",
                              "pdf-paper-size"
                          }
                      });

    parser.parse(strings);

    if (parser.isSet("url")) {
        options.url = QUrl::fromUserInput(parser.value("url"));
    } else if (parser.isSet("b64-url")) {
        options.url = QUrl::fromUserInput(QByteArray::fromBase64(parser.value("b64-url").toUtf8()).data());
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
        options.width = 1024;
    }

    if (parser.isSet("height")) {
        options.height = parser.value("height").toInt();
    } else {
        options.height = 1024;
    }

    if (parser.isSet("delay")) {
        options.delay = parser.value("delay").toInt();
    }

    if (parser.isSet("timeout")) {
        options.timeout = parser.value("timeout").toInt();
    }

    if (parser.isSet("user-agent")) {
        options.userAgent = parser.value("user-agent");
    }

    if (parser.isSet("referer")) {
        options.referer = parser.value("referer");
    }

    if (parser.isSet("pdf-orientation")) {
        options.pdfOrientation = parser.value("pdf-orientation").toLower();
    }

    if (parser.isSet("pdf-paper-size")) {
        options.pdfPaperSize = parser.value("pdf-paper-size").toLower();
    }

    return result;
}
