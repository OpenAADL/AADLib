#include <stdio.h>
#include <math.h>
#include "types.h"

float glob_longitude = 1.4;
float glob_latitude = 2.5;
int glob_altitude = 3;

void gps_simulation  (ardupilot_software__gps_position_i* pos)
{
  pos->altitude = glob_altitude;
  pos->latitude = glob_latitude;
  pos->longitude = glob_longitude;

  printf ("[GPS] Simulate latitude %f, longitude %f\n", 
	  pos->latitude, pos->longitude);

}

void gps_backdoor (float yaw)
{
  glob_longitude += sin(yaw)/20.0;
  glob_latitude += cos(yaw)/20.0;
}
