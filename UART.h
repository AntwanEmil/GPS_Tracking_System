#ifndef __UART_H__
#define __UART_H__

#include "stdint.h"

void UART_Init (void);
char UART_Read (void);
void uart0_Write(float data);
void uart0_init(void);
char UART0_Read(void);
float read(void);




#endif
