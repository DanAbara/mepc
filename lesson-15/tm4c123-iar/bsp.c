/* Board Support Package */
#include "tm4c_cmsis.h"

__stackless void assert_failed (char const *file, int line) {
  /* TBD: damage control based on application */
  NVIC_SystemReset(); /* provided by CMSIS to reset system */
}

/* As an example, Implement SysTick_Handler to be used instead of the alias */
void SysTick_Handler(void) {
}