#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

void timer_init ( void )
{
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);
}

void handle_timer_irq( void ) 
{
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1);
	printf("Timer interrupt received\n\r");
}

void timer_local_init(void)
{
	put32(LOCALTIMER_CRL, LOCALTIMER_CRL_VALUE | interval); //Enables Local Timer Controls, Interrupt and Timer
}															//Sets the interval as well

void handle_local_timer_irq( void ) 
{
	printf("Local timer interrupt received\n\r");			//IRQ Handler for Local Timer Interrupt
	put32(LOCALTIMER_CLR, LOCALTIMER_CLR_ACK);				//Clear Interrupt Flag in Reload Register
}
