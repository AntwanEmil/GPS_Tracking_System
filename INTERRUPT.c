#include "tm4c123gh6pm.h" 

void EnableInterrupts() {}
void GPIOF_Handler(void) //handler routine name from startup file
{
	GPIO_PORTF_ICR_R = 0x10;
	GPIO_PORTF_DATA_R |= (1 << 3);//turn_on_LED


}


void switch_inter(void)
{
	GPIO_PORTF_IS_R &= ~0x10; // PF4 is edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x10; // PF4 is not both edges
	GPIO_PORTF_IEV_R &= ~0x10; // PF4 falling edge event
	GPIO_PORTF_ICR_R = 0x10; // clear flag4
	GPIO_PORTF_IM_R |= 0x10; // arm interrupt on PF4
	NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | 0x00A00000; // (g) priority 5
	NVIC_EN0_R = 0x40000000; // (h) enable interrupt 30 in NVIC
	EnableInterrupts(); // (i) Enable global Interrupt flag (I)
}