#include <stdint.h>
#include "intrinsics.h"
#include "tm4c_cmsis.h"
#include "bsp.h"

int main(void) {
  SYSCTL->RCGC2 |= (1U << 5);  // enable clock for GPIOF
  SYSCTL->GPIOHSCTL |= (1U << 5); // enable High performance bus for GPIOF pg.258
  GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1, 2, and 3 as outputs - 00001110
  GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN); // enable digital function on pins 1,2,3
 
  SysTick->CTRL = (1U << 2) | (1U << 1) | (1U); // ClK source, Interrupt Enable, Counter Enable
  SysTick->LOAD = SYS_CLOCK_HZ/2 - 1U; // half of clock cycle/half a sec. Since the clock starts from initial val of 0, the -1 is used to avoid one extra cycle
  SysTick->VAL = 0U;
    
  __enable_interrupt(); // clear PRIMASK bit to enable CPU receive interrupts
  
  // using array indexing method of setting and clearing bits is safer when using interrupt service routines
  // GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE; // turn the blue LED on
  while (1) {
  }
  //return 0; // unreachable code
}