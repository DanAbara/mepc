#include "tm4c.h"
#include "delay.h"

#define LED_RED 	(1U << 1) // 00000010
#define LED_BLUE 	(1U << 2) // 00000100
#define LED_GREEN (1U << 3) // 00001000

int *swap(int *x, int *y) {
	static int tmp[2];
	tmp[0] = *x;
	tmp[1] = *y;
	*x = tmp[1];
	*y = tmp[0];
	return tmp;
}

int main(void) {
	
	SYSCTL_RCGCGPIO_R |= (1U << 5);  // enable clock for GPIOF
	SYSCTL_GPIOHBCTL_R |= (1U << 5); // enable High performance bus for GPIOF pg.258
	GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1, 2, and 3 as outputs
	GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN); // enable digital function on pins 1,2,3
	
	// using array indexing method of setting and clearing bits is safer when using interrupt service routines
	GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE; // turn the blue LED on
	while (1) {
		int x = 1500000;
		int y = 750000;
		int *p = swap(&x, &y);
		
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; // turn the red LED on while keeping blue on
		delay(p[0]);
		
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0; // using array indexing
		
		delay(p[1]);
	}
	//return 0; // unreachable code
}