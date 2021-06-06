#include "tm4c123gh6pm.h"
#include "stdint.h"

void portF_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x20;   //enable clock for Port_F
	while ((SYSCTL_RCGCGPIO_R & 0x20) == 0){ }  //allow time for Port_F activation
	GPIO_PORTF_LOCK_R = 0x4C4F434B;  //unlock
	GPIO_PORTF_AFSEL_R = 0;          //used as GPIO
	GPIO_PORTF_PCTL_R = 0;           //not used
	GPIO_PORTF_AMSEL_R = 0;          //not analog
	GPIO_PORTF_CR_R = 0x1F;          //allow changes to all pins
	GPIO_PORTF_DIR_R = 0X0E;         //set pins 1, 2, 3 outputs
	GPIO_PORTF_PUR_R = 0x11;         //enable pull up resistors for switches at pins 0 and 4
	GPIO_PORTF_DEN_R = 0X1F;	       //all pins are digital
	
}

void LED_ON(uint32_t distance){
	if(distance > 100)
	GPIO_PORTF_DATA_R = 0x02;   //turn red led on if distance exceeds 100 meters
}
