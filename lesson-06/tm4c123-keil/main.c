#include "tm4c.h"

#define LED_RED 	(1U << 1) // 00000010
#define LED_BLUE 	(1U << 2) // 00000100
#define LED_GREEN (1U << 3) // 00001000

int main(void) {

/*
    unsigned int a = 0x5A5A5A5A;
    unsigned int b = 0xDEADBEEF;
    unsigned int c;

    c = a | b;   // OR
    c = a & b;   // AND
    c = a ^ b;   // XOR
    c = ~b;      // NOT
    c = a << 1;  // lef-shift
    c = a << 2;
    c = b >> 1;  // right-shift
    c = b >> 3;

    int x = 1024;
    int y = -1024;
    int z;

    z = x >> 3;
    z = y >> 3;
*/

    SYSCTL_RCGCGPIO_R |= (1U << 5);  // enable clock for GPIOF
    GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1, 2, and 3 as outputs
    GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN); // enable digital function on pins 1,2,3
		
		GPIO_PORTF_DATA_R = LED_BLUE; // turn the blue LED on
		while (1) {
			/* turn the red LED on while keeping blue on
				GPIO_PORTF_DATA_R = 00000100 - blue on
				LED_RED						=	00000010 - red on
											---------------
				BITWISE OR RESULT = 00000110 - both blue and red on
			*/
        GPIO_PORTF_DATA_R |= LED_RED; // turn the red LED on while keeping blue on

        int volatile counter = 0;
        while (counter < 1000000) {  // delay loop
            ++counter;
        }

			/* turn the red LED off while keeping blue on
				GPIO_PORTF_DATA_R 	= 00000110 - blue and red on
				~LED_RED						=	00000000 - complement of red
												--------------
				BITWISE AND RESULT 	= 00000100 - both blue and red on
			*/
        GPIO_PORTF_DATA_R &= ~LED_RED; // turn the red LED off while keeping blue on
        counter = 0;
        while (counter < 1000000) {  // delay loop
            ++counter;
        }

    }
    //return 0; // unreachable code
}
