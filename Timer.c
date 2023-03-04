/* Timer.c
 *
 * Author: panchal pritesh
 *         naren subburaj
 * Date:  10-02-2022
 *
 * this file takes two command timerinit and timer '0' 'delay'
 * timerinit function initialize the  timer2 and timer5
 * timer command takes two arguments first one to select between timer and counter
 * the other argument takes amount of delay for counter in us
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "common.h"
#include "main.h"

TIM_HandleTypeDef htim5;

void ExampleInit(void *data)
{

  /* Place Initialization things here.  This function gets called once
   * at startup.
   */

}

void ExampleTask(void *data)
{

  /* Place your task functionality in this function.  This function
   * will be called repeatedly, as if you placed it inside the main
   * while(1){} loop.
   */

}

ADD_TASK(ExampleTask,  /* This is the name of the function for the task */
	 ExampleInit,  /* This is the initialization function */
	 NULL,         /* This pointer is passed as 'data' to the functions */
	 0,            /* This is the number of milliseconds between calls */
"This is the help text for the task")


ParserReturnVal_t TimerInit(int mode)
{
  if(mode != CMD_INTERACTIVE) return CmdReturnOk;
  GPIOC->MODER |= 0x00000000;    //make gpio port c as input
  RCC->AHB1ENR |= (1<<0);        //turn on the clock of port A
  GPIOA->MODER |= (1<<10);       //make PA5 pin as output 

  RCC->APB1ENR |= (1<<0);        // Enable clock source for timer 2
  RCC->APB1ENR |= (1<<3);        // Enable clock source for timer 5

  TIM2->PSC = 50-1;              // 50 000 000 / 100 = 1us
  TIM2->ARR = 65535-1;           // 65535/1 = 65 ms delay
  TIM2->CNT |= 0;                //set counter to 0          
  TIM2->CR1 |= (1<<0);           //start the timer
  while(!(TIM2->SR & (1<<0)));


  
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 50000-1;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 1000-1;
  //htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_Base_Init(&htim5);
  





  GPIOC->IDR &= ~(1<<13);       //reset PC13 pin
  printf("Press on board switch B1 to stop all timers!\n");
  return CmdReturnOk;
}

ADD_CMD("timerinit",TimerInit,"0 | 1           Control LED")



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  if(htim == &htim5){
      GPIOA->ODR ^= (1<<5);  
  }
  
}


void us_delay(int delay){
      TIM2->CNT = 0;
      TIM2->CR1 |= (1<<0);          //start the timer
      //int j,k;
    
      while(1){
       delay = delay-65535;
      //printf("delay  = %d\n",delay);
     
      if(delay > 65535){
         while(TIM2->CNT < 65534);
      }else{
        if(delay > 0){
          while(TIM2->CNT < delay);  
        }
        
      }  
       if(delay <  0){
        break;
      }
      
      }
      
    

}


void us_delay1(int delay){
      TIM2->CNT = 0;
      //TIM2->CR1 |= (1<<0);          //start the timer
       while(TIM2->CNT < delay); 
}

void ms_delay(uint16_t ms_delay){
  for(uint16_t i = 0; i< ms_delay; i++){ 
    us_delay1(1000);
  }
}



void TIM5_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim5);
}

void timerIntr()
{
 
  HAL_NVIC_SetPriority(TIM5_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(TIM5_IRQn);
  
  HAL_TIM_Base_Start_IT(&htim5);
 
  

}


void counter(int delay)
{
  uint32_t pinState=0;
  while(1){
    
    GPIOA->ODR |= (1<<5);
    ms_delay((int)delay);
    GPIOA->ODR &= ~(1<<5);
    ms_delay((int)delay);

    pinState = ~GPIOC->IDR;
    if(pinState & (1<<13)){
      break;
    }

  }


}


ParserReturnVal_t timer(int mode)
{
  if(mode != CMD_INTERACTIVE) return CmdReturnOk;
  
  uint32_t rc=0;
  uint32_t ITdelay;
  uint32_t opt = 0;

  rc =  fetch_uint32_arg(&opt);
  if(rc) {
   printf("Please select the options 0 for counter 1 for interrupt.\n");
   return CmdReturnBadParameter1;
 }
  rc =  fetch_uint32_arg(&ITdelay);
  if(rc) {
   printf("Please supply the Delay in milliseconds.\n");
   return CmdReturnBadParameter1;
 }
 (opt == 1) ? timerIntr() : counter((int)ITdelay);

   
   
return CmdReturnOk;
}

ADD_CMD("timer",timer,"                Example Command")



ParserReturnVal_t CmdExample(int mode)
{
  if(mode != CMD_INTERACTIVE) return CmdReturnOk;

  /* Put your command implementation here */
  printf("Example Command\n");

  return CmdReturnOk;
}

ADD_CMD("example",CmdExample,"                Example Command")
