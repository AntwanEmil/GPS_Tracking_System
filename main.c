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





double atof_m(const char *s){
int i;
int sign;
double value;
double power;
int powersign;
int power2;
for(i = 0; isspace(s[i]); ++i);
/*skip white space*/




sign = (s[i] == '-')? -1 : 1; /*The sign of the number*/



if(s[i] == '-' || s[i] == '+'){
++i;
}




for(value = 0.0; isdigit(s[i]); ++i){
value = value * 10.0 + (s[i] - '0');
}



if(s[i] == '.'){
++i;
}




for(power = 1.0; isdigit(s[i]); ++i){
value = value * 10.0 + (s[i] - '0');
power *= 10.0;
}



if(s[i] == 'e' || s[i] == 'E'){
++i;
}
else{
return sign * value/power;
}



/*The sign following the E*/
powersign = (s[i] == '-')? -1 : 1;



if(s[i] == '-' || s[i] == '+'){
++i;
}



/*The number following the E*/
for(power2 = 0; isdigit(s[i]); ++i){
power2 = power2 * 10 + (s[i] - '0');
}



if(powersign == -1){
while(power2 != 0){
power *= 10;
--power2;
}
}
else{
while(power2 != 0){
power /= 10;
--power2;
}
}



return sign * value/power;
}







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




/*
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
*/




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
lat1_no = atof_m(lat1);
lon1_no = atof_m(lon1);
while (1)
{
size = 0;






while (i<10){
UART0_Write(lat2[i]);
i = i+1;
}
i=0;
UART0_Write('&');
while (i<10){
UART0_Write(lon2[i]);
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
lat2_no =atof_m(lat2);
delay_milli(100);
lon2_no =atof_m(lon2);




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