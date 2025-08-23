#include <stdint.h>
#include "tm4c_cmsis.h"
#include "delay.h"

#define LED_RED 	(1U << 1) // 00000010
#define LED_BLUE 	(1U << 2) // 00000100
#define LED_GREEN (1U << 3) // 00001000

int16_t x = -1;
uint32_t y = LED_RED | LED_GREEN;

int16_t sqr[] = {
	1*1,
	2*2,
	3*3,
	4*4
};

typedef struct { // packing ensures that the data is stored without skipping any bytes in memory
	uint8_t y;
	uint16_t x;
} Point;

Point p1 = {
	123U,
	0x1234U
};
Point p2;

typedef struct {
	Point top_left;
	Point bottom_right;
} Window;

typedef struct {
	Point corners[3];
} Triangle;

Window w = {
	{ 123U, 0x1234U },
	{ 234U, 0x6789U }
};
	
Window w2;
Triangle t;

int main(void) {
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
	
	// initializing struct pointers
	pp = &p1;
	wp = &w2;
	
	// assessing elements in a struct pointer
	(*pp).x = 1U;
	(*wp).top_left = *pp;
	// or equivalently
	pp->x = 1U;
	wp->top_left = *pp;
	
	SYSCTL->RCGC2 |= (1U << 5);  // enable clock for GPIOF
	SYSCTL->GPIOHSCTL |= (1U << 5); // enable High performance bus for GPIOF pg.258
	GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1, 2, and 3 as outputs
	GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN); // enable digital function on pins 1,2,3
	
	// using array indexing method of setting and clearing bits is safer when using interrupt service routines
	GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE; // turn the blue LED on
	while (1) {
		GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED; // turn the red LED on while keeping blue on
		delay(1800000);
		
		GPIOF_AHB->DATA_Bits[LED_RED] = 0; // using array indexing
		
		delay(750000);
	}
	//return 0; // unreachable code
}