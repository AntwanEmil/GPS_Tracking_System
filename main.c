#include "tm4c123gh6pm.h"
#include "UART.h"
#include "LED.h"
#include "stdint.h"
#include "math.h"
#define PI 3.14159265359


void SystemInit(){}
		
	
	float total_distance(float * total_distance ,float lat1, float long1, float lat2, float long2)
{
	uint32_t R = 6371000;
	double x1, x2, delta_x, delta_y;
  double a, c, d;
	x1 = lat1 * (PI / 180);
  x2 = lat2 * (PI / 180);
  delta_x = (lat2 - lat1) * (PI / 180);
  delta_y = (long2 - long1) * (PI / 180);

  a = (sin(delta_x / 2) * sin(delta_x / 2)) + cos(x1) * cos(x2) * sin(delta_y / 2) * sin(delta_y / 2);
  c = 2 * atan2(sqrt(a), sqrt(1-a));
  d = R * c;
	*total_distance = *total_distance + d; //total_distance must be initiallized by zero in the main !!!!!! 
	
	return d;
}
	
	
	
int main(){

}
