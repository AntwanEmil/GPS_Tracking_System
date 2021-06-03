#include "tm4c123gh6pm.h"
#include "UART.h"
#include "stdint.h"


void SystemInit(){}
int main(){
	char c;
	
	UART_Init();
	while(1)
	c = UART_Read();
}
