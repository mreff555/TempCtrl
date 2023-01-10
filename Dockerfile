#FROM couchbase/centos7-systemd:latest
FROM archlinux:latest
RUN pacman -Sy
RUN pacman -Syu gcc --noconfirm
RUN pacman -Syu make --noconfirm
RUN pacman -Syu python --noconfirm
RUN pacman -Syu python-pip --noconfirm
RUN pacman -Syu git --noconfirm
RUN git clone https://github.com/WiringPi/WiringPi
RUN sed 's/^.*sudo make install/make install/g' -i WiringPi/build
RUN cd WiringPi && /bin/bash build

RUN cd /
RUN git clone https://github.com/mreff555/TempCtrl
RUN cd TempCtrl && make
