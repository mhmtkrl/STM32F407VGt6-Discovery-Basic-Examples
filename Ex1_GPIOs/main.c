/*
Authour				 : Mehmet KORAL
Date					 : 04.07.2019
E-mail				 : mehmet.koral96@gmail.com
Explanation	   : This code was developed for testing GPIO registers. 
							   Mainly for the blinking of LED(Green) with the user button on the board
								 PA0	->	User button
								 PD12	->	Green LED
Used documents : dm0007051.pdf(https://www.st.com/resource/en/datasheet/dm00037051.pdf)
								 Reference Manuel(https://www.st.com/resource/en/reference_manual/dm00031020.pdf)
*/

#include "stm32f4xx.h"                  // Device header

#define UserButton			(GPIOA->IDR & 0x00000001)

int main() {
	/*
		Let's get an idea of ​​the CPU speed of the board
		That document,dm0007051 in section: 2.2.12, informs us what happens after resetting of the device 
		"On reset the 16 MHz internal RC oscillator is selected as the default CPU clock."
		We know anymore CPU's speed! Let's activate clock signals of GPIOS in order to access registers.
		Let's have a look for STM32F40xxx block diagram to detect GPIOs bus line.
		GPIOs can be accessed via AHB1.
		It is time to arrange value of the registers, therefore we should have a look at Reference Manuel for register address
	*/

	RCC->AHB1ENR |= 9ul << 0;								//Clock signals were activated for GPIOA and GPIOD 

	GPIOA->MODER |= 0xA8000000;							//Input mode was activated(Default)
	
	GPIOD->MODER |= 1ul << 24;							//PD14's state was changed from input to output mode
	/*
		Other GPIOA & GPIOB registers(SPEED, TYPE, PULL-UP/PULL-DOWN) can be changed for the specific applications
	*/
	while(1) {
		if(UserButton) {											//If pressed the user button
			GPIOD->ODR |= 1ul << 12;								//Turn PD12 on 
			while(UserButton);						
		}
		GPIOD->ODR &= ~(1ul << 12);									//Turn PD12 off
	}
}
