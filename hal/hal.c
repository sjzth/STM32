/********************************************************************************
  * @file    hal.c 
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.7
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */ 
#include "mcu.h"
#include "bsp.h"	
#include "hal.h"
#include "hal_lamp.h"
halIntState_t irq_state = 0;
void hal_loop(void)
{
    uint16_t PastTime;
    PastTime = hal_mcu_loop();
    hal_lamp_loop(PastTime);
}
void hal_init(void)
{
    bsp_init();
}
