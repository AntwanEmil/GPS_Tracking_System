#include "tm4c123gh6pm.h" // Device header
#include "stdint.h"
#include "UART.h"
#include "LCD.h"
#include "LED.h"
#include "SYSTICK.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>
#define pi 3.14159265358979323846
void SystemInit() {}
float total_dist;




double deg2rad(double deg) {
return (deg * pi / 180);
}



double rad2deg(double rad) {
return (rad * 180 / pi);
}




double total_distance( float lat1, float lon1, float lat2, float lon2) {
double theta, dist;
if ((lat1 == lat2) && (lon1 == lon2)) {
total_dist = 4;
return 0;
}

else {
theta = lon1 - lon2;
dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
dist = acos(dist);
dist = rad2deg(dist);
dist = dist * 60 * 1.1515;
dist = dist * 16.09344;
if(dist>=1)
{total_dist = total_dist+dist ;
}
return (dist);
}
}





int main() {
///////////////////////////////////////////////////////////////
int size;
float dummy;
float lat1_no, lon1_no, lat2_no, lon2_no;
char data[90];
char lat1[12];
char lon1[12];
char lat2[12];
char lon2[12];
uint8_t i;
size = 0;
total_dist=0;
i=0;
UART_Init();
portF_Init();
systic_init();
LCD_init();
delay_milli(50);
UART0_Init();
i=0;




/*
LCD_Cmd(0x01);//clear
LCD_Cmd(0x80);// start from 1st line
delay_milli(100);
lon1_no = atof("99999.55");
delay_milli(10);
lon1_no=lon1_no*100;
LCD_DISTANCE(lon1_no);
*/



///////////////////////////////////



do {
size = data_line(data);



} while (size == -1);




if (parsing(data, lat1, lon1, size))
{
lat1_no = atof(lat1);
lon1_no = atof(lon1);
while (1)
{
size = 0;






while (i<10){
UART0_Write(lat1[i]);
i = i+1;
}
i=0;
UART0_Write('&');
while (i<10){
UART0_Write(lon1[i]);
i = i+1;
}
i=0;
UART0_Write(' ');





do {
size = data_line(data);
} while (size == -1);




if (parsing(data, lat2, lon2, size))
{
delay_milli(100);
LCD_Cmd(0x01);//clear
LCD_Cmd(0x80);// start from 1st line
LCD_STRING(lat2);
delay_milli(100);
lat2_no =atof(lat2);
delay_milli(100);
lon2_no =atof(lon2);




delay_milli(100);
LCD_Cmd(0x01);//clear
LCD_Cmd(0x80);// start from 1st line
LCD_DISTANCE(lat2_no);
delay_milli(100);






total_distance( lat1_no, lon1_no, lat2_no, lon2_no);
//print dist
LCD_Cmd(0x01);//clears
LCD_Cmd(0x80);// start from 1st line
LCD_STRING("dist=");
delay_milli(100);
LCD_DISTANCE(total_dist);
LED_ON(total_dist);
delay_milli(100);



//swap(lat1, lon1, lat2, lon2);
lat1_no=lat2_no;
lon1_no=lon2_no;

//delay_milli(100);
}



}
}
///////////////////////////////////




}