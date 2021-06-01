#include "tm4c123gh6pm.h"
#include "stdint.h"




void UART2_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x00000004;	//uart2
	SYSCTL_RCGCUART_R |= 0x08;	//portD
	UART0_CTL_R &= ~UART_CTL_UARTEN; //DISABLE CONTROL
	
	//Neo-6 Baud rate = 9600;
	UART2_IBRD_R = 520;
	UART2_FBRD_R = 53;
	
	UART2_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);	//no parity one stop & 2 fifos
	UART2_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);	//ENABLE UART AGAIN
	
	
	GPIO_PORTD_AFSEL_R |= 0xC0;		//DIGITAL ENABLE of D6-D7
	GPIO_PORTD_DEN_R |= 0xC0;
	
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000; //SUITABLE UART PERIFERAL
	GPIO_PORTD_AMSEL_R &= ~0xC0;	//disable analog on pin6-7

}
