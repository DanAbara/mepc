<<<<<<< HEAD
#include <stdint.h>
#include "tm4c.h"
=======
#include "TM4C123GH6PM.h"  // CMSIS-compatible interface
>>>>>>> b99e29d97ea028ae0e69173b74ac5132c41c0e99
#include "delay.h"

#define LED_RED 	(1U << 1) // 00000010
#define LED_BLUE 	(1U << 2) // 00000100
#define LED_GREEN (1U << 3) // 00001000

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t s8;
int16_t s16;
int32_t s32;

int main(void) {
<<<<<<< HEAD
	
	u8a 	= sizeof(u8a);
	u16c 	= sizeof(uint16_t);
	u32e 	= sizeof(uint32_t);
	
	u8a 	= 0xa1U;
	u16c 	= 0xc1c2U;
	u32e	= 0xe1e2e3e4U;
	
	u8b 	= u8a;
	u16d	= u16c;
	u32f 	= u32e;
	
	u16c	= 40000U;
	u16d 	= 30000U;
	u32e	= (uint32_t)u16c + u16d; // explicitly typecast one operand to 32 bits so that compiler performs the computation in 32 bits.
	
	u16c	= 100U;
	s32		= 10 - (int16_t)u16c;
	
	u8a 	= 0xffU; // 0b11111111
	if ((uint8_t)(~u8a) == 0x00U) {
		u8b = 1U;
	}
	
	SYSCTL_RCGCGPIO_R |= (1U << 5);  // enable clock for GPIOF
	SYSCTL_GPIOHBCTL_R |= (1U << 5); // enable High performance bus for GPIOF pg.258
	GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1, 2, and 3 as outputs
	GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN); // enable digital function on pins 1,2,3
	
	// using array indexing method of setting and clearing bits is safer when using interrupt service routines
	GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE; // turn the blue LED on
	while (1) {
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; // turn the red LED on while keeping blue on
		delay(1500000);
		
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0; // using array indexing
		
		delay(750000);
	}
	//return 0; // unreachable code
}
=======
    Point *pp;
    Window *wp;

    p1.x = sizeof(Point);
    p1.y = 0xAAU;

    w.top_left.x = 1U;
    w.bottom_right.y = 2U;

    t.corners[0].x = 1U;
    t.corners[2].y = 2U;

    p2 = p1;
    w2 = w;

    pp = &p1;
    wp = &w2;

    (*pp).x = 1U;

    (*wp).top_left = *pp;

    pp->x = 1U;
    wp->top_left = *pp;

    SYSCTL->RCGCGPIO  |= (1U << 5); /* enable AHB for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable clock for GPIOF */

    /* configure LEDs (digital output) */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    /* turn all LEDs off */
    GPIOF_AHB->DATA_Bits[LED_RED | LED_BLUE | LED_GREEN] = 0U;

    GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE;
    while (1) {
        GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED;
        delay(500000);

        GPIOF_AHB->DATA_Bits[LED_RED] = 0;

        delay(250000);
    }
    //return 0; // unreachable code
}

//............................................................................
// function needed by the library/startup code
_Noreturn void assert_failed(char const * const module, int const id);
_Noreturn void assert_failed(char const * const module, int const id) {
    // TBD: damage control
    (void)module; // avoid the "unused parameter" compiler warning
    (void)id;     // avoid the "unused parameter" compiler warning
    NVIC_SystemReset();
}
>>>>>>> b99e29d97ea028ae0e69173b74ac5132c41c0e99
