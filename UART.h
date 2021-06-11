#ifndef __UART_H__
#define __UART_H__

#include "stdint.h"

void UART_Init (void);
char UART_Read (void);
void UART0_Write(uint8_t data);
void uart0_init(void);
char UART0_Read(void);
float read(void);

int data_line (char * data);
uint32_t  parsing (char * Gpsdata, char * latitude, char * longitude, int size);
void swap(char * LA1, char * LO1, char * LA2, char * LO2);


#endif
