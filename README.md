# Rabarbar

*Yet another website screenshot tool*

Rabarbar is a simple website screenshot utility based on Qt Web Engine (Chromium).

## Usage
~~~
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
user-agent      | no       | Custom browser user agent.
referer         | no       | Custom referer.
pdf-orientation | no       | PDF orientation (portrait, landscape).
pdf-paper-size  | no       | PDF paper size (a3, a4, letter, tabloid).

## Hacking
This app has been built and tested with Qt 5.12 running on Ubuntu 18.04 x64.

## Notes
- Referer header can be ignored by Chromium due to internal policies, consider this feature experimental.
