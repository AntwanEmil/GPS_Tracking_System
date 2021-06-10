#include "tm4c123gh6pm.h"  // Device header
#include "stdint.h"
#include "UART.h"
#include "LCD.h"
#include "SYSTICK.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#define PI 3.14159265359
void SystemInit() {}








int main() {
	///////////////////////////////////////////////////////////////
	uint32_t size;
	float lat1_no, lon1_no, lat2_no, lon2_no;
	float total_dist;
	char data[90];
	char lat1[9];
	char lon1[10];
	char lat2[9];
	char lon2[10];
	int i;
	int y;
	//uint32_t size;
	uint32_t temp;
	//char data[100];
  //	char lat[10]; 
  //	char lon[10];
	  ////////////////////////////////////////////////////////////
	size = 0;
	total_dist = 0;
	UART_Init();
	////////////////////////////////////////////////////////////
	systic_init();
	//portF_Init();
	//switch_inter();
	LCD_init();






	LCD_Cmd(0x01);//clear
	LCD_Cmd(0x80);// start from 1st line
	delay_milli(100);
	lon1_no = atof("123548");
	delay_milli(10);
	LCD_DISTANCE(lon1_no);

	//in=fopen ("map.txt","w");
	//fprintf(buffer_out,100,"%d,%d",3,2);
	//fwrite(buffer_out,sizeof(char),strlen(buffer_out),in);



	///////////////////////////////////

	do {
		size = data_line(data);

	} while (size == -1);


	if (parsing(data, lat1, lon1, size))
	{
		while (1)
		{
			//uint32_t size;
			size = 0;

			/*
			LCD_Cmd(0x01);//clear
			LCD_Cmd(0x80);// start from 1st line
			delay_milli(10);
			LCD_STRING(lat1);
			*/

			lat1_no = atof(lat1);
			lon1_no = atof(lon1);

			/*
			LCD_Cmd(0x01);//clear
			LCD_Cmd(0x80);// start from 1st line
			delay_milli(100);
			LCD_DISTANCE(lat1_no);
			*/

			do {
				size = data_line(data);
			} while (size == -1);


			if (parsing(data, lat2, lon2, size))
			{
				lat2_no = atof(lat2);
				lon2_no = atof(lon2);

				///////
				/*
				LCD_DISTANCE(lat1_no);
				delay_milli(100);
				LCD_Cmd(0x01);//clear
				LCD_Cmd(0x80);// start from 1st line
				LCD_DISTANCE(lon1_no);
				delay_milli(100);
				LCD_Cmd(0x01);//clear
				LCD_Cmd(0x80);// start from 1st lin
				LCD_DISTANCE(lon2_no);
				delay_milli(100);
				LCD_Cmd(0x01);//clear
				LCD_Cmd(0x80);// start from 1st line
				LCD_DISTANCE(lat2_no);
				delay_milli(100);
				LCD_Cmd(0x01);//clear
				LCD_Cmd(0x80);// start from 1st line
				*/


				total_distance(&total_dist, lat1_no, lon1_no, lat2_no, lon2_no);
				//print dist
				LCD_Cmd(0x01);//clears
				LCD_Cmd(0x80);// start from 1st line
				LCD_STRING("dist=");
				delay_milli(100);
				LCD_DISTANCE(total_dist);
				delay_milli(100);

				swap(lat1, lon1, lat2, lon2);
				//delay_milli(100);
			}

		}
	}
	///////////////////////////////////


}





