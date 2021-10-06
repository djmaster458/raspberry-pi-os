#include "printf.h"
#include "utils.h"
#include "mini_uart.h"

void kernel_main_el2(void)
{
	uart_init();
	init_printf(0, putc);
	int el = get_el();
	printf("EL2 Main: Exception level: %d \r\n", el);
	return;
}

void kernel_main(void)
{
	int el = get_el();
	printf("EL1 Main: Exception level: %d \r\n", el);

	while (1) {
		uart_send(uart_recv());
	}
}
