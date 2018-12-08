/********************************************************************************
  * @file    mcu_port.h 
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
#ifndef MCU_PORT_H
#define MCU_PORT_H
#include "stm32f10x.h"
#include "core_cm3.h"
#ifdef __cplusplus
extern "C"
{
#endif
	/*¶Ë¿Ú¶¨Òå*/
#define Lampn                             2
#define Lamp1_PIN                         GPIO_Pin_8
#define Lamp1_GPIO_PORT                   GPIOA
#define Lamp1_GPIO_CLK                    RCC_APB2Periph_GPIOA  
  
#define Lamp2_PIN                         GPIO_Pin_2
#define Lamp2_GPIO_PORT                   GPIOD
#define Lamp2_GPIO_CLK                    RCC_APB2Periph_GPIOD 
	

typedef enum 
{
  Lamp1 = 0,
  Lamp2 = 1
} Lamp_TypeDef;

extern void lamp_port_Init(Lamp_TypeDef lamp);
extern void STM_SET_LEDOn(Lamp_TypeDef lamp);
extern void STM_EVAL_LEDOff(Lamp_TypeDef lamp);
#ifdef __cplusplus
}
#endif	
 
#endif
