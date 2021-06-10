#include "tm4c123gh6pm.h"
#include "stdint.h"




void UART_Init(void){
	SYSCTL_RCGCUART_R |= 0x00000002;	//uart1
	SYSCTL_RCGCGPIO_R |= 0x00000004;	//portc

	UART1_CTL_R &= ~0x00000001; //DISABLE UART CONTROL
	
	//Neo-6 Baud rate = 9600;
	UART1_IBRD_R = 104;
	UART1_FBRD_R = 11;
	
	UART1_LCRH_R = 0x00000070;	//no parity one stop & 2 fifos
	UART1_CTL_R |= 0x00000001;	//ENABLE UART AGAIN
	
	
	GPIO_PORTC_AFSEL_R |= 0x30;		//DIGITAL ENABLE of c4-c5
	GPIO_PORTC_DEN_R |= 0x30;
	
	GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) + 0x00220000; //SUITABLE UART PERIFERAL
	GPIO_PORTC_AMSEL_R &= ~0x30;	//disable analog on pin6-7

}


char UART_Read(void){
	while ((UART1_FR_R&0x0010) != 0);    //busy waiting // could be replaced by flag "1" so caller of the fn will ignore it..
	
	return (UART1_DR_R&0xFF);  // &0xFF for data masking to get the data bits only
	
}
void uart0_init(void)
{
	double I_FBRD;
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;; 
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;; 
	UART0_CTL_R &=~ UART_CTL_UARTEN; 	   
	

	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	
	
	UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN); 
	UART0_CTL_R |= (UART_CTL_RXE|UART_CTL_TXE|UART_CTL_UARTEN); 

	 
	GPIO_PORTA_AFSEL_R |= 0x03 ;
  
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0XFFFFF00)|(GPIO_PCTL_PA1_U0TX&GPIO_PCTL_PA0_U0RX); 
	GPIO_PORTA_DEN_R |= 0x03; 	    
}
uint8_t uart0_available(void)
{
	return((UART0_FR_R&UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}



float read(void)
{
	while(uart0_available()!=1)
	{
		return (float)(UART0_DR_R&0xFF);
	}
}


void uart0_Write(float data)
{
	while((UART0_FR_R & UART_FR_TXFF) != 0); 
	UART0_DR_R = data; 
}

