/********************************************************************************
  * @file    bsp.h 
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
#ifndef BSP_LAMP_H
#define BSP_LAMP_H

#ifdef __cplusplus
extern "C"
{
 #endif
/*!
    @defgroup LAMP状态定义
    @{
*/
#define BSP_LAMP_OFF      0
#define BSP_LAMP_ON       1
	/*端口定义*/
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
/*! 
    @} 
*/

/** @enum 指示灯名称
  */
typedef enum {
    /* LED */
    LAMP_LED1,          ///< LED灯1
    LAMP_LED2,          ///< LED灯2
}bsp_lamp_id_t;	
extern void bsp_lamp_init(void);
 #ifdef __cplusplus
 }
 #endif	
#endif
