#include "tm4c123gh6pm.h"
#include "stdint.h"
void systic_init(void){
    NVIC_ST_CTRL_R=0;
    NVIC_ST_RELOAD_R=0x00FFFFFF;
    NVIC_ST_CURRENT_R=0;
    NVIC_ST_CTRL_R = 0x05;
}
	void delay(uint32_t time){
        NVIC_ST_RELOAD_R = time-1;
      NVIC_ST_CURRENT_R = 0;
      while((NVIC_ST_CTRL_R&0X00010000)==0){};
}
	void delay_micro(uint32_t time){
 unsigned long i;
    for(i=0;i<time;i++)
    delay(80);
}
void delay_milli(uint32_t time){
 unsigned long i;
    for(i=0;i<time;i++)
    delay_micro(1000);

}
 
