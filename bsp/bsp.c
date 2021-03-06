/********************************************************************************
  * @file    bsp.c 
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
#include "bsp_lamp.h"

void bsp_init(void)
{
    hal_mcu_init();
    bsp_button_init();
    bsp_lamp_init();
}
