/******************************************************************************
 * File           : Main program
 *****************************************************************************/
#include "stm32f0xx.h"
#include "usart.h"
#include <stdlib.h>
#include <stdbool.h>

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------
void delay(const int d);
void blinkLed (void);
void setupEVALeds(void);
char getc(void);

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
int main(void)
{
	char c;
	//rx_fifo = (char *)malloc(sizeof(char)* RX_FIFO_SIZE );
	
	// Setup
	setupEVALeds();
  USART_init();
  USART_clearscreen();
  USART_putstr("This is STM32F0 microcontroller lesson 2.\n");
  
  while(1)
  {	
		c = getc();
		if(c != 0)
		{
			USART_putc(c);
		}
  }
}

#pragma push
#pragma O3
void delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}
#pragma pop

void setupEVALeds(void)
{
	// --------------------------------------------------------------------------
  // Setup PC8 (blue LED) and PC9 (green LED)
  // GPIOC Periph clock enable
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;  
  // PC8 and PC9 in output mode
  GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0) ;
  // Push pull mode selected
  GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9) ;
  // Maximum speed setting (even though it is unnecessary)
  GPIOC->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9);
  // Pull-up and pull-down resistors disabled
  GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);
}


void blinkLed (void)
{
	// Blink the green LED
	// Set PC9
	GPIOC->BSRR = GPIO_BSRR_BS_9;
	// Delay ~ 0.1 sec.
	delay(SystemCoreClock/8/10);
	// Reset PC9
	GPIOC->BSRR = GPIO_BSRR_BR_9;
	// Delay ~ 0.1 sec.
	delay(SystemCoreClock/8/10);
}
