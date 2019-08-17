/*
Authour				 : Mehmet KORAL
Date					 : 05.07.2019
E-mail				 : mehmet.koral96@gmail.com
Explanation	   : This code has developed for testing External Interrupt. 
								 We will be focusing on External interrupt/event controller (EXTI Register)
							   Mainly for The blinking of LED(Green) with the user button on the board
								 PA0	->	User button
								 PD12	->	Green LED
Used documents : dm0007051.pdf(https://www.st.com/resource/en/datasheet/dm00037051.pdf)
								 Reference Manuel(https://www.st.com/resource/en/reference_manual/dm00031020.pdf)
*/

/*
	Many times an important event outside of the processor requires attention and action of the processor 
	while it is executing regular program. The situation where the execution of the regular program is 
	suspended and the processor is forced to take care of the important event is called an interrupt.
*/

#include "stm32f4xx.h"                  	// Device header

void delay(uint16_t milisecond);

void EXTI0_IRQHandler(void) {
	GPIOD->ODR = 1ul << 13;
	EXTI->PR |= 1ul << 0;										//Clear Int flag
}

int main() {
	RCC->AHB1ENR |= 9ul << 0;								//Clock has permitted for GPIOA and GPIOD 
	RCC->AHB2ENR |= 1ul << 14;							//Clock SYSCFG - system configuration controller
	
	NVIC_EnableIRQ(EXTI0_IRQn);							//Enable IRQ for ext. signals, line EXTI0_IRQn
	SYSCFG->EXTICR[0] |= 0x00000000;				//to select the source input for the EXTIx external interrupt.
	
	EXTI->RTSR |= 1ul << 0;									//Set for rissing edge interrupt
	EXTI->IMR |= 1ul << 0;									//Enable Int. for EXTI0
	
	GPIOA->MODER |= 0xA8000000;							//It is already Input for User button
	
	GPIOD->MODER |= 1ul << 24;							//PD14's state changed from input to output
	GPIOD->MODER |= 1ul << 26;
	
	while(1) {
		GPIOD->ODR &= ~(3ul << 12);						//Turn PD12 off
		delay(1000);
		GPIOD->ODR |= 1ul << 12;
		delay(1000);
	}
}

void delay(uint16_t milisecond) {
	uint32_t time = 0;
	time = 8000 * milisecond;
	while(time > 0) time--;
}
