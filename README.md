# pico-ds3231

Kevin Boone, November 2022

## What is this?

This is a simple C driver library for the DS3231 I2C real-time clock,
for the Pi Pico. The library is completely self-contained, in the
`ds3231/` directory. See `main.c` for how to use it.

This isn't the only driver for the DS3231, but it might be the 
simplest. It only supports the time, date, and temperature functions
-- there is not support for alarms or interrupts. 

## Wiring

The DS3231 can be connected to either of the Pico's I2C ports, 
using any of the pins that are supported. The user of library should
specify which port and pins are in use. The defaults used by the
test program are as follows:

    Pico               DS3231 
    ----               --------
    Pin 6 (SDA0)       Data / SDA
    Pin 7 (SCL0)       Clock / SCL
    Pin 36 (3.3V out)  Vcc / +
    Pin 38 (GND)       Gnd / -

To run the test program with different wiring, change the pin assignments
in `config.h`.

## Building the test program

The usual, with the Pico SD:

    mkdir build
    cd build
    PICO_SD_PATH=... cmake ..
    make 

## Using the test program

Copy the UF2 file to the Pico in the usual way, and run a terminal
emulator.  Enter 'get' to see the time, or 'set year month day hour 
minute second' to set it.

Sample output:

    get
    2022-11-27 09:21:00
    temp=20.5000 deg. C


