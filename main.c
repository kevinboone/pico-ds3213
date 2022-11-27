/* =======================================================================
  Test program for DS3231 real-time-clock driver for Pi Pico.
foo
  Copyright (c)2022 Kevin Boone, GPLv3.0
 ======================================================================= */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <pico/stdlib.h>
#include <ds3231/ds3231.h>

#if PICO_ON_DEVICE
#include <hardware/i2c.h>
#endif
#include "config.h"

/* =======================================================================
   readline() is a crude function to read a line of text. The Pico SDK 
     seems to implement gets(), etc., but they don't work for me. 
 ======================================================================= */
#define L 128 
char str [L+1];

char _getchar()
  {
  int c;
  while ((c = getchar_timeout_us (0)) < 0) 
    {
    sleep_ms (10);
    }
  return (char)c;
  }

char *readline() 
  {
#if PICO_ON_DEVICE
  char u, *p;
  for (p=str, u=_getchar(); u!='\r' && p-str<L; u=_getchar()) putchar(*p++=u);
  *p = 0;  
  return str;
#else
  fgets (str, sizeof (str), stdin);
  return str;
#endif
  }
 
/* =======================================================================
  main
 ======================================================================= */
int main ()
  {
  stdio_init_all();

  DS3231 *ds3231 = ds3231_new (I2C_DEV, SDA, SCL, I2C_BAUD);

  while (1)
    {
    readline ();
    printf ("\n");
    if (strncmp (str, "set ", 4) == 0)
      {
      // If the user enters 'set xxx...', read six numbers and use them
      //   to set the date and time on the DS3231
      int year, month, day, hour, min, sec;
      if (sscanf (str + 4, "%d %d %d %d %d %d", 
          &year, &month, &day, &hour, &min, &sec) == 6)
        {
        int ret = ds3231_set_datetime (ds3231, year, month, day, 
           hour, min, sec);
        if (ret != 0)
          printf ("Failed to set date: %s\n", strerror (ret));
        }
      else
        {
        printf ("Enter six numbers: "
                 "year month day hour min sec\n");
        }
      }
    else if (strncmp (str, "get ", 3) == 0)
      {
      // If the user enter 'get', print the current date, time, and
      //   temperature from the DS3231.
      int year, month, day, hour, min, sec;
      ds3231_get_datetime (ds3231, &year, &month, &day, &hour, &min, &sec);
      printf ("%d-%d-%d %02d:%02d:%02d\n", year, month, day,
        hour, min, sec);
      int t = ds3231_get_temp (ds3231);
      // Temperature is in 'millicelcius', so we must divide by 1000
      printf ("temp=%g deg. C\n", t / 1000.0);
      }
    else
      printf 
      ("Enter 'get' to see time, or 'set year month day hour minute second'\n");
    }

  ds3231_destroy (ds3231);
  }


