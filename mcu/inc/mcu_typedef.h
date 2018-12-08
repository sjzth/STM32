/*!
  ******************************************************************************
  * @file    mcu_types.h
  * @author  ÉÏº£ÐÂÊ±´ï¹¤¿ØÈí¼þ²¿
  * @version V1.0.0
  * @date    2018.9.21
  * @brief   ¸ÃÎÄ¼þ°üº¬Í¨ÓÃÀàÐÍ¶¨Òå¼°²¹³ä
  ******************************************************************************
  */
#ifndef MCU_TYPES_H
#define MCU_TYPES_H
#include "stdint.h"
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef volatile char     vint8_t ;
typedef volatile int      vint16_t;
typedef volatile long     vint32_t;


typedef volatile unsigned char vuint8_t ;
typedef volatile unsigned int  vuint16_t;
typedef volatile unsigned long vuint32_t;

#ifdef __cplusplus
}
#endif

#endif
