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
#include "stm32f10x.h"
#include "core_cm3.h"  
#include "bsp_lamp.h"
#include "hal_lamp.h"
hal_lamp_t hal_all_lamp[] = {
    {LAMP_LED1  ,0,0,0,0},
    {LAMP_LED2  ,0,0,0,0}
};
#define LAMP_NUMBER (sizeof(hal_all_lamp) / sizeof(hal_all_lamp[0]))
const uint8_t hal_lamp_amount = LAMP_NUMBER;
GPIO_TypeDef* GPIO_PORT[Lampn] = {Lamp1_GPIO_PORT, Lamp2_GPIO_PORT};
const uint16_t GPIO_PIN[Lampn] = {Lamp1_PIN, Lamp2_PIN};
const uint32_t GPIO_CLK[Lampn] = {Lamp1_GPIO_CLK, Lamp2_GPIO_CLK};	
void lamp_port_Init(Lamp_TypeDef lamp)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  /* Enable the GPIO_LED Clock */
  RCC_APB2PeriphClockCmd(GPIO_CLK[lamp], ENABLE);
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[lamp];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[lamp], &GPIO_InitStructure);
}
void bsp_lamp_init ( void )
{
   lamp_port_Init (Lamp1 );
	lamp_port_Init (Lamp2 );
}
void bsp_set_lamp( bsp_lamp_id_t lamp, uint8_t value )
{
	switch(lamp)
	{
		case LAMP_LED1:
			if(value == BSP_LAMP_OFF)
			   GPIO_PORT[Lamp1]->BSRR = GPIO_PIN[Lamp1]; 
		   else
				GPIO_PORT[Lamp1]->BRR = GPIO_PIN[Lamp1]; 
		break;
		case LAMP_LED2:
			if(value == BSP_LAMP_OFF)
			   GPIO_PORT[Lamp2]->BSRR = GPIO_PIN[Lamp2]; 
		   else
				GPIO_PORT[Lamp2]->BRR = GPIO_PIN[Lamp2]; 
		break;
		default:
			break;
	}
}
