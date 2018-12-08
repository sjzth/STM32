/*!
  ******************************************************************************
  * @file    mcu.c
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.07
  * @brief   
  ******************************************************************************
	* @attention
  *
  **/
#include "mcu_port.h"
void bsp_button_init(void)
{
	
}
void bsp_lamp_init(void)
{
   lamp_port_Init(Lamp1);
	 lamp_port_Init(Lamp2);
}
void hal_mcu_init(void)
{
  if (SysTick_Config(48000))
  { 
    /* Capture error */ 
    while (1);
  }
  
}
