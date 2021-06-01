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

uint8_t UART2_Available(void){
	//if fifo empty return 0 else return 1
	return ((UART2_FR_R & UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}


//pooling GIVES A WARNING BUT OK 
//$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,499.6,M,48.0,M,,0*5B
// or $GPGLL 
//AND PARSE TILL END
char UART2_Read(void){
	while (UART2_Available() != 1);    //busy waiting // could be replaced by flag "1" so caller of the fn will ignore it..
	
	return ((char)(UART2_DR_R&0xFF));  // &0xFF for data masking to get the data bits only
	
}
