#ifndef __BSP_H__
#define __BSP_H__

#define SYS_CLOCK_HZ 16000000U // 16MHz clock/oscillator - 16million cycles per second

#define LED_RED   (1U << 1) // 00000010
#define LED_BLUE  (1U << 2) // 00000100
#define LED_GREEN (1U << 3) // 00001000

#endif // __BSP_H__