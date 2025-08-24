/* Board Support Package */
#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "bsp.h"

/* on-board LEDs */
#define LED_RED		(1U << 1)
#define LED_BLUE	(1U << 2)
#define LED_GREEN	(1U << 3)

static uint32_t volatile l_tickCtr;

void BSP_init(void) {
	/* board specific settings moved from background - main() */
	SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
	SYSCTL->RCGCGPIO  |= (1U << 5); /* enable Run mode for GPIOF */
	GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN); /* set pins 1,2,3 as output pins */
	GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN); /* enable digital functions for pins 1,2,3 */
	SystemCoreClockUpdate();

	/* Use SysTick_Config() instead of Systick->LOAD/VAL/CTRL etc.*/
	SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);
	
	__enable_irq(); // interrupt handler called via different process of preemption
}

void SysTick_Handler(void) {
	++l_tickCtr;
}

uint32_t BSP_tickCtr(void) {
	uint32_t tickCtr;
	
	__disable_irq();
	tickCtr = l_tickCtr;
	__enable_irq();
	
	return tickCtr;
}

void BSP_delay(uint32_t ticks) {
	/* Calls BSP_tickCtr() until the 'ticks' elapses.
	* No interrupts during the running of this function because it
	* calls BSP_tickCtr() which has interrupts disabled. So it polls 
	* until the the while condition below is false, then it returns,
	* after which the interrupt occurs and l_tickCtr is incremented.
	*/
	uint32_t start = BSP_tickCtr();
	while ((BSP_tickCtr() - start) < ticks) {
	}
}

void BSP_ledRedOn(void) {
	GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED;
}

void BSP_ledRedOff(void) {
	GPIOF_AHB->DATA_Bits[LED_RED] = 0U;
}

void BSP_ledBlueOn(void) {
	GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE;
}

void BSP_ledBlueOff(void) {
	GPIOF_AHB->DATA_Bits[LED_BLUE] = 0U;
}

void BSP_ledGreenOn(void) {
	GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
}

void BSP_ledGreenOff(void) {
	GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;
}

__attribute__((naked)) void assert_failed(char const *file, int line) {
	/* TBD: damage control */
	NVIC_SystemReset(); /* reset the system */
}