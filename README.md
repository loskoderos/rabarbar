# Rabarbar

*Yet another website screenshot tool*

Rabarbar is a simple website screenshot utility based on Qt Web Engine (Chrome).

## Usage
~~~
./rabarbar --url https://cepa.io --width 1280 --height 1024 --delay 3 --out screenshot.png
~~~

Parameter  | Required | Description
---------- | -------- | -----------
url        | yes      | Website URL address.
out        | yes      | Output filename.
width      | yes      | Screenshot width in pixels.
height     | yes      | Screenshot height in pixels.
delay      | no       | Number of seconds to wait before grabbing a shot once the website is fully loaded.
user-agent | no       | Custom browser user agent.

## Hacking
This app has been built and tested with Qt 5.12 running on Ubuntu 18.04 x64.
