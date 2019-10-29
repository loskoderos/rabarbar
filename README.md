# Rabarbar

*Yet another website screenshot tool*

Rabarbar is a simple website screenshot utility based on Qt Web Engine (Chromium).

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

## Building
This app has been built and tested with Qt 5.12 running on Ubuntu 18.04 x64.
~~~
git clone https://github.com/cepa/rabarbar
cd rabarbar
/opt/qt5/5.12.4/gcc_64/bin/qmake
qmake
./rabarbar
~~~
Exact commands depend on your local Qt5 installation details.

## Headless
Rabarbar works in headless mode with Xvfb.
~~~
xvfb-run -a ./rabarbar --url https://google.com --width 1280 --height 1024 --out screenshot.png
~~~

## Notes
- Referer header can be ignored by Chromium due to internal policies, consider this feature experimental.
