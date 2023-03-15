FROM ubuntu:22.04
LABEL maintainer "Lukasz Cepowski <lukasz@cepowski.com>"

RUN apt-get update && apt-get install --no-install-recommends -y \
  ca-certificates \
  locales-all \
  build-essential \
  qt6-base-dev \
  qt6-webengine-dev \
  libqt6webenginecore6-bin \
  libqt6opengl6-dev \
  qmake6 \
  xvfb
RUN echo ttf-mscorefonts-installer msttcorefonts/accepted-mscorefonts-eula \
  select true | debconf-set-selections
RUN apt-get install --no-install-recommends -y \
  fonts-freefont-ttf \
  ttf-mscorefonts-installer \
  ttf-xfree86-nonfree
RUN apt-get clean

RUN apt-get install -y
RUN mkdir -p /opt/rabarbar
WORKDIR /opt/rabarbar
COPY . /opt/rabarbar/
RUN qmake6 && make clean && make all

ENTRYPOINT ["/opt/rabarbar/entrypoint.sh"]
