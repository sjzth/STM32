/*!
  ******************************************************************************
  * @file    mcu_port.c
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.07
  * @brief   mcu端口号映射及初始化（对外开放）
  ******************************************************************************
	* @attention
  *
  **/
#include "mcu_port.h"

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
void STM_SET_LEDOn(Lamp_TypeDef lamp)
{
  GPIO_PORT[lamp]->BSRR = GPIO_PIN[lamp];     
}
void STM_EVAL_LEDOff(Lamp_TypeDef lamp)
{
  GPIO_PORT[lamp]->BRR = GPIO_PIN[lamp];    
}
