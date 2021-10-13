#ifndef	_P_TIMER_H
#define	_P_TIMER_H

#include "peripherals/base.h"

#define TIMER_CS        (PBASE+0x00003000)
#define TIMER_CLO       (PBASE+0x00003004)
#define TIMER_CHI       (PBASE+0x00003008)
#define TIMER_C0        (PBASE+0x0000300C)
#define TIMER_C1        (PBASE+0x00003010)
#define TIMER_C2        (PBASE+0x00003014)
#define TIMER_C3        (PBASE+0x00003018)

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)

#define LOCALTIMER_CRL    (LOCALPBASE+0x34)
#define LOCALTIMER_CLR     (LOCALPBASE+0x38)

#define LOCALTIMER_CRL_EN  (1 << 28)
#define LOCALTIMER_CRL_INT_EN (1 << 29)
#define LOCALTIMER_CRL_VALUE  (LOCALTIMER_CRL_EN | LOCALTIMER_CRL_INT_EN)

#define LOCALTIMER_CLR_ACK (1 << 31)

#endif  /*_P_TIMER_H */
