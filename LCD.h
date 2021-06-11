#include "stdint.h"
#include "string.h"
void LCD_init(void);
void LCD_Cmd(unsigned char command);
void LCD_Data(unsigned char data);
void dec_to_str (char* str, uint32_t val,uint32_t digits);
uint32_t number_digits(uint32_t num);
void LCD_DISTANCE(uint32_t number);
void LCD_STRING(char *str);
