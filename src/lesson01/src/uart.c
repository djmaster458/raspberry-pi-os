#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
	while(1) {
		if(get32(UART_FR) & 0x20u) //wait for TX ready
			continue;
		else
			break;
	}
	put32(UART_DR,c); //Put data into data reg
}

char uart_recv ( void )
{
	while(1) {
		if(get32(UART_FR) & 0x10u) //Wait for RX Ready
			continue;
		else
			break;
	}
	return(get32(UART_DR) & 0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init ( void )
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt0 for gpio14, tx
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt0 for gpio15, rx
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	//Assume Using 115200
	//BRDI = CLOCK / (16 * BAUD)
	//BRDF = integer((fractional part of above * 64) + 0.5)
	unsigned int uart_int_divisor = 26; //Page 56 of PrimeCell PL011
	unsigned int uart_fract_divisior = 3;

	put32(UART_IBRD, uart_int_divisor);
	put32(UART_FBRD, uart_fract_divisior);

	put32(UART_LCRH, (3u << 5)); //Set Word Length to 8-bits by Enabling WLEN to 11

	unsigned int uart_cr = 1u | (1u << 8) | (1u << 9); //Enable UART, TX, and RX

	put32(UART_CR, uart_cr);
}
