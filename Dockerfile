FROM archlinux
RUN pacman -Sy
RUN pacman -Sy gcc --noconfirm
RUN pacman -Syu make --noconfirm
RUN pacman -Syu git --noconfirm
RUN pacman -Syu sed --noconfirm

RUN git clone https://github.com/WiringPi/WiringPi
RUN sed 's/^.*sudo make install/make install/g' -i WiringPi/build
RUN cd WiringPi && /bin/bash build

RUN cd /
RUN git clone https://github.com/mreff555/TempCtrl --branch dockerContainers
RUN cd TempCtrl && make