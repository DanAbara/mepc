#include "tm4c.h"

int main(void) {
    SYSCTL_RCGCGPIO_R = 0x20U;  // enable clock for GPIOF
    GPIO_PORTF_DIR_R = 0x0EU; // set pins 1,2, and 3 as outputs
    GPIO_PORTF_DEN_R = 0x0EU; // enable digital function on pins 1,2, and 3

		GPIO_PORTF_DATA_R = 0x00U; // turn off all LEDs
	
		return 0;
}