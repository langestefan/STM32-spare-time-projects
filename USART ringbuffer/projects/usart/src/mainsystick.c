/******************************************************************************
 * File           : Main program - SysTick
 *****************************************************************************/
#include "stm32f0xx.h"

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------
void initGreenLED(void);

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
int main(void)
{
  initGreenLED();
	
	// Setup SysTick Timer for 5 msec interrupts
  if(SysTick_Config((SystemCoreClock * 0.005)-1))
  { 
    // Error!
    // Do nothing, LED3 will stay off indicating an erronous situation.
    while(1){;}
  }

  while(1);
}

/**
  * @brief  This function initializes the registers for the green LED PC9.
  * @param  None
  * @retval None
  */
void initGreenLED()
{
  RCC->AHBENR    |= RCC_AHBENR_GPIOCEN;      // GPIOC Periph clock enable
  GPIOC->MODER   |= GPIO_MODER_MODER9_0 ;    // PC9 output
  GPIOC->OTYPER  &= ~GPIO_OTYPER_OT_9;       // Push pull mode selected
  GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9;  // Maximum speed
  GPIOC->PUPDR   &= ~GPIO_PUPDR_PUPDR9;      // no pull-up or pull-down
}
