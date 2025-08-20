int main(void) {
	// Set bit 5 of GPIO clockgating register (RCGCGPIO) to enable clocks GPIO-F - pg340
	*((unsigned int *) 0x400FE608U) = 0x20U; 
	
	// Set bits 1,2,3 (PF1, PF2, PF3) as outputs (GPIODIR) - pg663
	*((unsigned int *) 0x40025400U) = 0x0EU; 
	
	// Set bits 1,2,3 to set the digital functions (GPIODEN) - pg683
	*((unsigned int *) 0x4002551CU) = 0x0EU; 
	
	// Blink the LED
	while (1) {
		*((unsigned int *) 0x400253FCU) = 0x02U;
		
		int counter = 0;
		while (counter < 1000000) {
			++counter;
		}
		
		*((unsigned int *) 0x400253FCU) = 0x00U;
		counter = 0;
		while (counter < 1000000) {
			++counter;
		}
	}
	
	return 0;
}
