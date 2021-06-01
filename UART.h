#ifndef __UART_H__
#define __UART_H__

#include "stdint.h"

void UART2_Init (void);
uint8_t UART2_Available(void);
char UART2_Read(void);

#endif
