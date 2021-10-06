#include "arm/sysregs.h"

#include "mm.h"

.section ".text.boot"

.globl _start
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF		// Check processor id
	cbz	x0, master		// Hang for all non-primary CPU
	b	proc_hang

proc_hang: 
	b 	proc_hang

master:
	ldr	x0, =SCTLR_VALUE_MMU_DISABLED
	msr	sctlr_el1, x0		

	ldr	x0, =HCR_VALUE
	msr	hcr_el2, x0

	ldr	x0, =SCR_VALUE
	msr	scr_el3, x0

	ldr	x0, =SPSR_VALUE_EL2		//Get EL2 Status Register Value
	msr	spsr_el3, x0			//Copy EL2 Status into EL3 Status Register

	adr	x0, el2_entry			//Get EL2 Entry function address	
	msr	elr_el3, x0				//Link from EL3 to EL2

	eret						//Go to EL2

el2_entry:
	adr	x0, bss_begin			//Clear the EL's stack
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	mov	sp, #LOW_MEMORY

	bl	kernel_main_el2		//Show EL2 using kernel main el2

	// goes to EL1

	ldr	x0, =SPSR_VALUE_EL1	   //Load Status of EL1
	msr	spsr_el2, x0		   //Copy to EL2 status

	adr	x0, el1_entry		  //Get EL1 Entry function address
	msr	elr_el2, x0			  //Link EL2 to EL1

	eret					 //Go to EL1
	
el1_entry:			
	mov	sp, #LOW_MEMORY
	
	bl	kernel_main      //start user main
	b 	proc_hang		// should never come here
