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
typedef enum 
{
  Lamp1 = 0,
  Lamp2 = 1,
  Lamp3 = 2,
  Lamp4 = 3
} Lamp_TypeDef;

typedef enum 
{  
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY = 2,
  BUTTON_RIGHT = 3,
  BUTTON_LEFT = 4,
  BUTTON_UP = 5,
  BUTTON_DOWN = 6,
  BUTTON_SEL = 7
} Button_TypeDef;

extern void lamp_port_Init(Lamp_TypeDef lamp);
#endif
