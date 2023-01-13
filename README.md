# TEMPCTRL
## A framework for digital temperature control
### by Dan Feerst

## Overview
A PIC temperature control deamon implementing heating coil relay control, I2C 2x16 LCD screen controls with adaptibility for as many buttons as you can spare gpio's. Currently the system is implemented with 4 buttons up, down, enter and back. 

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
Once dependancies are satisfied, running *make* from the root directory should do it.

## Developer notes 

### PID
A PID is an advanced form of modulating control of analog sources, heating coils being one of the more common uses.

**Transfer Function**
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

[![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)](https://nodesource.com/products/nsolid)