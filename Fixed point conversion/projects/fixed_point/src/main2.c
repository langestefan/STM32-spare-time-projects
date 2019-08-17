/******************************************************************************
 * File           : Main program
 *****************************************************************************/
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------
void delay(const int d);

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  uint16_t c;

  // --------------------------------------------------------------------------
  // Initialize USART1
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
  // Setup Tx- and Rx pin
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_Init(USART1, &USART_InitStructure);

  USART_Cmd(USART1, ENABLE);
  
  while(1)
  {
    // Transmit information: "Press a key: "
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'P');
    
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'r');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'e');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'s');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'s');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)' ');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'a');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)' ');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'k');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'e');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'y');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)':');

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)' ');

    // Receive data
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){;}
    c = USART_ReceiveData(USART1);
    
    // Make uppercase
    if(c >= (uint16_t)'a' && c <= (uint16_t)'z')
    {
      c -= 32;
    }
    
    // Transmit uppercase and goto next line
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'\n');
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){;}
    USART_SendData(USART1, (uint16_t)'\r');    
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
