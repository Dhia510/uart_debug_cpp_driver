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

int uart_write(int ch)
{
	while(!(USART2->SR & 0x0080)){} // Wait until Tx is idle
	USART2->DR = (ch & 0xFF);
	return 1;
}

int uart_read(void)
{
	while(!(USART2->SR & 0x0020)){} // 
	return USART2->DR;
}

/* Redefining low-level library functions to enable direct use 
 *of high-level library functions in the C library*/
namespace std
{
	struct __FILE 
	{int handle;};
	FILE __stdin;
	FILE __stdout;
	FILE __stderr;
	
	int fgetc(FILE *f)
	{
    int c;
	  c = uart_read();
		
    if(c =='\r')
		{
			uart_write(c);
			c = '\n';
		}
		
		uart_write(c);
		return c;	
  }
	
	int fputc(int c, FILE *stream)
	 {
	   return uart_write(c);
	 }
	 
	 int ferror(FILE *stream)
	 {
	  return 1;
	 }
	 
	
	 long int ftell(FILE *stream)
	 {
	 	  return 1;

	 }
	 
	 int fclose(FILE *f)
	 {
	  return 1;
	 } 
	 
	 int fseek(FILE *f, long nPos, int nMode)
	 {
		 return 0;
	 }
	 
	 int fflush(FILE *f)
	 {
	  return 1;
	 }
}
