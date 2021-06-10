#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "SYSTICK.h"
#include "string.h"
void LCD_Cmd(unsigned char command)
{
GPIO_PORTA_DATA_R  = 0x00; //RS =0, E=0, RW=0
GPIO_PORTB_DATA_R  =command;
GPIO_PORTA_DATA_R  =0x80; //E=1 to secure command
delay_micro(0);
GPIO_PORTA_DATA_R  =0x00;
if(command <4) delay_milli(2); else delay_micro(37); } 
void LCD_init(void){
SYSCTL_RCGCGPIO_R |= 0x01; //PORTA clock
SYSCTL_RCGCGPIO_R |= 0x02;
GPIO_PORTA_DIR_R |=0xE0; //PORTA controls RS,E and R/W
GPIO_PORTA_DEN_R  |=0xE0;
GPIO_PORTB_DIR_R  |=0xFF; //PORTB D0-D7
GPIO_PORTB_DEN_R |=0xFF; //PORTB D0-D7
LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
//LCD_Cmd(0x06); //increments automatically
LCD_Cmd(0x0F); //Turn on display
LCD_Cmd(0x01); //clear display
 
}
 

void LCD_Data(unsigned char data) { 
GPIO_PORTA_DATA_R  =0x20; //RS=1, E=0,RW=0
GPIO_PORTB_DATA_R =data;
GPIO_PORTA_DATA_R |= 0x80;
GPIO_PORTA_DATA_R =0x00;
delay_micro(0);
 
}
void dec_to_str (char* str, uint32_t val,uint32_t digits)
{   

  uint32_t i=1u;

  for(; i<=digits; i++)
  {
    str[digits-i] = (char)((val % 10u) + '0');
    val/=10u;
  }

  str[i-1u] = '\0'; // assuming you want null terminated strings?
}
uint32_t number_digits(uint32_t num)
{
    uint32_t count;
    count=0;
    while(num!=0)
    {
        num=num/10;
        count++;
        
    }
    return count;
}
void LCD_DISTANCE(uint32_t number)
{ char change[10];
	uint32_t y;	
		if(number==0)
	{LCD_Data('0');
	delay_milli(1);
	return;}
	dec_to_str(change,number,number_digits(number));
		for(y=0;y<number_digits(number);y++)
		{
			LCD_Data(change[y]);
			delay_milli(1);
		}
}

void LCD_STRING(char *str)
{
  uint32_t size;
	uint8_t up ;
	uint32_t y;
	
	size=strlen(str);
	up=1;
	for(y=0;y<size;y++)
		{	delay_milli(10);
			LCD_Data(str[y]);
			
			/*if(((y+1)%16==0)&&(up))
			{LCD_Cmd(0xC0);
			up=0;
			}
			else if(((y+1)%16==0)&&(!up))
			{LCD_Cmd(0x80);
			up=1;
			}*/
			
		}
		
}
    
