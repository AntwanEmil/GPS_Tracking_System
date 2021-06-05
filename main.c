#include "tm4c123gh6pm.h"  // Device header
#include "stdint.h"
#include "UART.h"
#include "LCD.h"
#include "SYSTICK.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define PI 3.14159265359



		
	
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
	
	
void SystemInit(){}	
int main(){
	uint32_t distance;

	systic_init();
	portF_Init();
	LCD_init();
	UART_Init();
	distance=150;	
	LCD_Cmd(0x01);//clear
	LCD_Cmd(0x80);// start from 1st line
	delay_milli(10);

	LCD_STRING("Distance=");
	LED_ON(distance);
	delay_milli(10);
	LCD_DISTANCE(distance);
	delay_milli(10);
	LCD_STRING("m");
		


	
	
//LCD_Data('T');
//delay_milli(10);
//LCD_Data('O');
//delay_milli(10);
//LCD_Data('N');
//delay_milli(10);
//	LCD_Data('Y');
//delay_milli(10);
//	LCD_Cmd(0xC0);// start from 1st line
//delay_milli(10);
//LCD_Data('Z');
//delay_milli(10);
//LCD_Data('A');
//delay_milli(10);
//LCD_Data(' ');
//delay_milli(10);
//LCD_Data(' ');
//delay_milli(10);
//LCD_Data(' ');
//delay_milli(10);
//LCD_Data(' ');
//delay_milli(10);
//LCD_Data('T');
//delay_milli(10);


/*delay_milli(100);
LCD_Data('Z');
delay_milli(10);
UART_Init();
LCD_Data('L');*/
//delay_milli(10);
//LCD_STRING("tony amgad 1 2 3 4 5 6 7 8 9 10 11");
  // LCD_DISTANCE(1000);
    
		//LCD_STRING("tony");


/*for(i=0;i<200;i++){
	c = UART_Read();
	out [i]=c;
	}

	for(i=0;i<200;i=i+1){ 
		LCD_Data(out[i]);
		delay_milli(10);
	}*/

	
	
 /* while(1)
	 { do{
        size = data_line(data);
    } while(size == -1);
	
		LCD_STRING(data);
		
		
				
		delay_milli(1);
	//LCD_Cmd(0x01);//clear
//LCD_Cmd(0x80);// start from 1st line
	
		
	}*/
    
    //parsing(data, lat, lon, size);
}
	
