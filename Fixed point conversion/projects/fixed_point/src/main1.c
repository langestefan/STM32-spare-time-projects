/******************************************************************************
 * File           : Main program
 *****************************************************************************/
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------
void delay(const int d);

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
int main(void)
{
  // Configure LED3 and LED4 on STM32F0-Discovery
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
	
  // Initialize User_Button on STM32F0-Discovery
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
  
  while(1)
  {
    // Blink LED's
    STM_EVAL_LEDOn(LED3);
    STM_EVAL_LEDOff(LED4);
		STM_EVAL_LEDOn(LED5);

    // Button pressed?
    if(STM_EVAL_PBGetState(BUTTON_USER) == Bit_SET)
    {
      // Delay 0.1 sec.
      delay(SystemCoreClock/8/10);
    }
    else
    {
      // Delay 1 sec.
      delay(SystemCoreClock/8);
    }
    
    // Blink LED's
    STM_EVAL_LEDOff(LED3);
    STM_EVAL_LEDOn(LED4);
		STM_EVAL_LEDOff(LED5);

    // Button pressed?
    if(STM_EVAL_PBGetState(BUTTON_USER) == Bit_SET)
    {
      // Delay 0.1 sec.
      delay(SystemCoreClock/8/10);
    }
    else
    {
      // Delay 1 sec.
      delay(SystemCoreClock/8);      
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

