#include "printf.h"
#include "timer.h"
#include "irq.h"
#include "mini_uart.h"


void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_vector_init();
	timer_local_init();					//enable local timer
	//timer_init();
	//enable_interrupt_controller(); //Don't need this since we are using the local peripheral interrupt 
	enable_irq();

	while (1){
		uart_send(uart_recv());
	}	
}
