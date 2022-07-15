#include "uart.h"

void uart_init(void)
{
	// Enable GPIOA clock
	RCC->AHB1ENR |= 0x01;
	// ENABLE UART2 clock
	RCC->APB1ENR |= 0x20000;
	// Configure PA1 and PA2 for USART2 tx and rx
	GPIOA->AFR[0] |=  0x7700;
	GPIOA->MODER  |=  0x00A0; // Enable alternate function
	USART2->BRR 	 =  0x0683; // Set 9600 baude rate
	USART2->CR1    =  0x000C; // Enable tx and rx 8 bits data
	USART2->CR2    =  0x0000; // 1 bit stop
	USART2->CR3    =  0x0000; // No flow control
	USART2->CR1	  |=  0x2000; // Enable USART2
}
