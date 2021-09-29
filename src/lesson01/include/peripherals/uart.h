#ifndef	_P_UART_H
#define	_P_UART_H

#include "peripherals/base.h"

// baud_register = clock / (8 * baud_rate) - 1
#define BAUD_RATE_9600	    3254
#define BAUD_RATE_19200	    1626
#define BAUD_RATE_38400	    812
#define BAUD_RATE_57600	    541
#define BAUD_RATE_115200	270

//Really 0x7E000000, start of UART Registers
#define UART_BASE   (PBASE + 0x201000)

//Uart Config Registers
#define UART_DR     (UART_BASE + 0x0)
#define UART_FR     (UART_BASE + 0x18)
#define UART_IBRD   (UART_BASE + 0x24)
#define UART_FBRD   (UART_BASE + 0x28)
#define UART_LCRH   (UART_BASE + 0x2c)
#define UART_CR     (UART_BASE + 0x30)

//48 MHz Operating Speed, given in exercise
#define UART_CLK 48000000

#endif  /*_P_UART_H */
