/******************************************************************************
 * File           : Main program with some bugs in it
 *****************************************************************************/
#include "stm32f0xx.h"
#include "stdint.h"

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------
void         stringCopy(char *dst, const char *src);
unsigned int stringCompare(const char *str1, const char *str2);
unsigned int stringLength(const char *str);
void         delay(const int d);
void 				 initGreenLED(void);

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
int main(void)
{ 
  char str[30] = {0};
  static unsigned int i=0;
  
  // --------------------------------------------------------------------------
  // Find the bug 1
  // Set a breakpoint and observe the value of str
  // --------------------------------------------------------------------------
  // Copy a string into the string buffer
  stringCopy(str, "Happy debugging!");
  
  // --------------------------------------------------------------------------
  // Find the bug 2
  // Set a breakpoint and observe the value of i
  // --------------------------------------------------------------------------
  // Copy a string of three characters in the string buffer
  stringCopy(str, "abc");

  // Compare the two strings
  i = stringCompare(str, "123");

  // --------------------------------------------------------------------------
  // Find the bug 3
  // Set a breakpoint and observe the value of i
  // --------------------------------------------------------------------------
  // Put a string of three characters in the string buffer
  stringCopy(str, "123");
  
  // Get the length of the string
  i = stringLength(str);
  
  
  // --------------------------------------------------------------------------
  // End of excercise
  // --------------------------------------------------------------------------


  i=i; // Prevents compiler warnings (unused variable)

  // Blink the green LED, everything is ok.
  while(1)
  {
    GPIOC->ODR ^= GPIO_ODR_9;          //toggle
    delay(SystemCoreClock / 8 / 10);   //0.1 sec
  }
}

/**
  * @brief  This function copies the src string to the dst string, including 
  *         the string terminator character.
  * @param  src: source string
  *         dst: destination string
  * @retval None
  */
void stringCopy(char *dst, const char *src)
{
  unsigned int i=0;
  
  // Copy characters up to terminating character
  while(src[i] != '\0')
  {
    i++;
    dst[i] = src[i];
  } 
  
  // Add terminating character
  dst[i] = '\0';
}

/**
  * @brief  This function compares the contents of two strings
  * @param  str1: string 1
  *         str2: string 2
  * @retval 0: strings are not equal
  *         1: strings are equal
  */
unsigned int stringCompare(const char *str1, const char *str2)
{
  unsigned int i=0;
  unsigned int ret=1;
  
  // Compare the characters until one string terminates
  while(str1[i] != '\0' && str2[i] != '\0')
  {
    if(str1[i] != str2[i])
    {
      ret=0;
    }
  }
  
  // Verify that both strings are terminated
  if(str1[i] != '\0' || str2[i] != '\0')
  {
    ret=0;
  }
  
  return ret;
}

/**
  * @brief  This function calculate the length of the string str.
  *         The string can be terminated with the following characters:
  *         '\0'
  *         '\n'
  * @param  str: string
  * @retval number of characters  in the string (without the terminating character)
  */
unsigned int stringLength(const char *str)
{
  unsigned int i=0;
  
  // Count the characters in the string
  while(str[i] != '\0' || str[i] != '\n')
  {
    i++;
  }
  
  return i;
}

/**
  * @brief  This function implements a delay.
  *         If the optimization level is set to -O3, this function takes 8
  *         cycles. To create a delay of 1 second, use the following function
  *         call: Delay(SystemCoreClock/8);
  * @param  d: number delay loops (1 loop takes 8/SystemCoreClock sec.)
  * @retval None
  */
#pragma push
#pragma O3
void delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}
#pragma pop

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
