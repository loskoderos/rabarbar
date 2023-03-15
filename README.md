# Rabarbar

*Yet another website screenshot tool*

Rabarbar is a simple website screenshot utility based on Qt Web Engine (Chromium), created for [Miniature.io](https://miniature.io).

![sample.png](https://github.com/cepa/rabarbar/raw/master/sample.png)

## Usage
~~~
./rabarbar --url https://github.com --width 640 --height 1136 --out sample.png
./rabarbar --url https://cepa.io --width 1280 --height 1024 --out screenshot.png
./rabarbar --url https://cepa.io --width 1280 --height 1024 --out screenshot.pdf --pdf-orientation=landscape --pdf-paper-size=a4
~~~

Parameter       | Required | Description
--------------- | -------- | -----------
url             | yes      | Website URL address.
out             | yes      | Output filename.
width           | yes      | Screenshot width in pixels.
height          | yes      | Screenshot height in pixels.
delay           | no       | Number of seconds to wait before grabbing a shot once the website is fully loaded.
timeout         | no       | Max wait time for a page to be loaded in seconds.
user-agent      | no       | Custom browser user agent.
referer         | no       | Custom referer.
pdf-orientation | no       | PDF orientation (portrait, landscape).
pdf-paper-size  | no       | PDF paper size (a3, a4, letter, tabloid).


## Prerequisites
This app has been built and tested with Qt6 on Ubuntu 22.
~~~
apt-get install qt6-base-dev qt6-webengine-dev libqt6webenginecore6-bin qmake6 xvfb
~~~

## Building
~~~
git clone https://github.com/cepa/rabarbar
cd rabarbar
qmake6
make
./rabarbar --url https://openai.com/ --width 512 --height 512 --out sample.png
~~~

## Headless
Rabarbar works in headless mode with Xvfb.
~~~
xvfb-run -a ./rabarbar --url https://google.com --width 1280 --height 1024 --out screenshot.png
~~~

## Notes
- Referer header can be ignored by Chromium due to internal policies, consider this feature experimental.
- Code may be built with Qt5 however there were some issues reported with QWebEngine on Ubuntu.
