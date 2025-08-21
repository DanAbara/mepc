#include "tm4c.h"
#include "delay.h"

#define LED_RED 	(1U << 1) // 00000010
#define LED_BLUE 	(1U << 2) // 00000100
#define LED_GREEN (1U << 3) // 00001000

unsigned fact(unsigned n);

int main(void) {
	unsigned volatile x;
	x = fact(0U);
	x = 2U + 3U*fact(1U);
	(void)fact(5U);
	
	SYSCTL_RCGCGPIO_R |= (1U << 5);  // enable clock for GPIOF
	SYSCTL_GPIOHBCTL_R |= (1U << 5); // enable High performance bus for GPIOF pg.258
	GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1, 2, and 3 as outputs
	GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN); // enable digital function on pins 1,2,3
	
	// using array indexing method of setting and clearing bits is safer when using interrupt service routines
	GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE; // turn the blue LED on
	while (1) {
		// *(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_RED;
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; // turn the red LED on while keeping blue on
		
		delay(1500000);
		
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0; // using array indexing
		
		delay(700000);
	}
	//return 0; // unreachable code
}

unsigned fact(unsigned n) {
	// 0! = 1
	// n! = (n-1)! for n > 0
	if (n == 0U) {
		return 1U;
	}
	else {
		return n * fact(n - 1U);
	}
}