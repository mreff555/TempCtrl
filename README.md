# TEMPCTRL
## A framework for digital temperature control
### by Dan Feerst

## Overview
A PID temperature control deamon implementing heating coil relay control, I2C 2x16 LCD screen controls with adaptibility for as many buttons as you can spare gpio's. Currently the system is implemented with 4 buttons up, down, enter and back. 

Pull requests

I have been really busy with life... and other projects lately.  What to contribute?  Please feel free to submit a pull request.  I am up for bug fixes or features, here are some known areas which need more work.

- I built this off a RPI 4.  I started making arrangements for the older versions but never got around to it.
- Unit testing through docker, which means getting creative with the /proc filesystem
- Still never finished the PID algorithm.

## Dependancies
- wiringPi.h
- wiringPiI2c.h

## Adapting to RPI versions prior to RPI4
Starting with RPI 4, the device driver /dev/gpiomem was created to allow system-wide read/write access (if enabled) to GPIO memory.  This allowed gpio applications to be run without root.  It also makes mapping memory easier since the offset to the first GPIO bank will always be zero.  The earlier raspberry pi's did not have this driver and all mapping had to go through /dev/mem.  This requires root access and the proper offset.  There are alternatives such as writing your own kernel module and rebuilding the kernel.  There is a good article about the /dev/gpiomem module here:

[ARM Assembly Language Using the Raspberry Pi](https://bob.cs.sonoma.edu/IntroCompOrg-RPi/sec-gpio-mem.html)

The LCD screen is implemented leveraging the Wiring PI I2c package.  Other than that the package should comple with c++03.

## Installation
Install is now based on a docker container.  This gives the developer to work on the PI itself if he is a very patient sadomacicist or on any other platform he chooses.  The binary will not run without ELF format so at the moment you will still need to run in the docker environment, unless you are on a linux system.  Unless you are running on a PI, WiringPi libraries will imediately complain and fail because it can't find version info.  Eventually I may implement a work around to allow unit testing.

### Dockerized build (Works on all platforms)

Build the image - This will satisfy all dependancies.

```bash
make build-docker-deps-image
```

Build the binary

```bash
make build
```

If you are on the RPI, the binary will be located in build and can be ran directly, otherwise you will need to execute it through a docker shell.

```bash
make login
cd /root/project_root/build
./tempctrl
```

### Without docker (presumably on an RPI)

```bash
cd build
cmake ..
make
```



## Developer notes 

### PID

![PID diagram](https://upload.wikimedia.org/wikipedia/commons/4/43/PID_en.svg)

A PID is an advanced form of modulating control of analog sources, heating coils being one of the more common uses.  The goal is to bring the substrate up to temperature efficiently fast.  This means with minimal or no overshoot while minimizing the time required to do so. The approach is a negative feedback adjustment based on three calculations of the error at a given time `e(t)`,  Each of these functions have K values.  These K values must be "tuned" for the environment.  Pressure, volume, and most importantly, that material composition.

- Proportional - a push in the opposite direction based on the current linear offset.  This is the simplest approach and often used by itself.  The result is ocillations, which generally start out quite large.  Depending on circumstances, Ocillations may shrink, and may even converge, but it is not guaranteed or remotely efficient.
- Derivative - PID phoenetically rolls off the tounge much easier than PDI, however it makes more sense to discuss the derivative function first.  The derivative looks at the history of error and attempts to reduce rise time.
- Integral - The integral function does nearly the opposite of the derivative.  It looks ahead and tries to prevent overshot

**Transfer Function**

The transfer function tranfers the result of the PID summation into useful functionality.  In the case of a temperature controller this will be a conversion between set point temperature and time, or a frequency for the heating element.
$$
t -->
    \left(
        \frac{1}{\frac{S}{\omega_o} + 1} 
    \right)
    --> T
$$

This video does a really good job of explaining why PID controls are necessary for precision and at a reasonably high level, how they work.  I wish there were videos like this on line when I took Process Controls.  I probably would have remembered more.
[PID example](https://www.youtube.com/watch?v=XfAt6hNV8XM)

### Classes
- bitfield
    - A class utilizing a 64-bit wide data set with convenience functions for setting bits.
- button
    - A class for getting GPIO button information.
- buttonManager
    - Used to manage button subscribler list.  
- buttonPublisher_I
    -  Used to attach publishers to a specific GPIO button
- buttonSubscriber_I
    - Used to update subscriber data
- common
  - Common enumerations and constant expressions
- dataManager
- pidProcessor
- pwmController
- tempdatamanager
- thermocouplereceiver
