FROM archlinux
LABEL Description="Build environment"
ENV HOME /root
SHELL ["/bin/bash", "-c"]

RUN pacman -Sy --noconfirm gcc \
    make \
    lld \
    git \
    sed \
    cmake

# Install wiring pi
RUN cd ${HOME} && \
    git clone https://github.com/WiringPi/WiringPi && \
    sed 's/^.*sudo make install/make install/g' -i WiringPi/build && \
    cd WiringPi && \
    /bin/bash build

# Project source root directory
RUN mkdir ${HOME}/project_root

RUN echo -e \
    "find_library(WIRINGPI_LIBRARIES NAMES wiringPi)\n"\
    "find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)\n"\
    "\n"\
    "include(FindPackageHandleStandardArgs)\n"\
    "find_package_handle_standard_args(wiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIRS)\n"\
    >> /usr/share/cmake/Modules/FindwiringPi.cmake
