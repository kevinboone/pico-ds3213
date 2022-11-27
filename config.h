/*===========================================================================

  Configuration for the DS3231 test driver

  Copyright (2)2022 Kevin Boone, GPLv3.0 

===========================================================================*/

#pragma once

#define I2C_DEV 0

#if PICO_ON_DEVICE
#include <hardware/i2c.h>
#define SDA PICO_DEFAULT_I2C_SDA_PIN
#define SCL PICO_DEFAULT_I2C_SCL_PIN
#else
#define SDA 0 
#define SCL 0 
#endif

#define I2C_BAUD 100000



