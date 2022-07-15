#ifndef __UART_H
#define __UART_H
#include "stm32f4xx.h"                  // Device header

// Function to initialize uart 
void uart_init(void);
// Function to write
int uart_write(int ch);
// Function to read
int uart_read(void);


#endif
