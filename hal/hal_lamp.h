/********************************************************************************
  * @file    hal_lamp.h 
  * @author  zhaocc
  * @version V1.0.0
  * @date    2018.12.7
  * @brief   ¸ÃÎÄ¼þÎªÏµÍ³²ãµÄÊý¾ÝÀàÐÍ¶¨ÒåºÍº¯ÊýÉùÃ÷
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */ 
#ifndef HAL_LAMP_H
#define HAL_LAMP_H
#include "bsp.h"
#include "bsp_lamp.h"
#include "mcu_typedef.h"
#ifdef __cplusplus
extern "C"
{
 #endif
/** @addtogroup Çý¶¯²ã
  * @{
  */
/** @addtogroup Ö¸Ê¾µÆÇý¶¯
  * @{
  */
/** @addtogroup Ö¸Ê¾µÆ¼òÒ×ÉèÖÃºê¶¨Òå
  * @{
  */	
#define HAL_LAMP_HOLD 0xFFFF
#define HAL_LAMP_OPEN(TIME) TIME,(TIME == HAL_LAMP_HOLD)?0x0000:HAL_LAMP_HOLD
#define HAL_LAMP_CLOSE(TIME) (TIME == HAL_LAMP_HOLD)?0x0000:HAL_LAMP_HOLD,TIME
	
/** 
  * @brief  Ö¸Ê¾µÆ×´Ì¬´æ´¢½á¹¹Ìå¡¢
  */
typedef  struct {
    const bsp_lamp_id_t lamp;            ///< Ö¸Ê¾µÆ
    uint16_t   time;            ///< Éè¶¨Ê±¼ä£º´¥·¢×´Ì¬
    uint16_t   reloadTime;      ///< Éè¶¨Ê±¼ä£º·Ç´¥·¢×´Ì¬
    uint16_t   count_time;      ///< µ¹¼ÆÊ±Ê£ÓàÊ±¼ä£º´¥·¢×´Ì¬
    uint16_t   count_reloadTime;///< µ¹¼ÆÊ±Ê£ÓàÊ±¼ä£º·Ç´¥·¢×´Ì¬
}hal_lamp_t;
extern hal_lamp_t hal_all_lamp[];

/** 
    @brief Ö¸Ê¾µÆ´¥·¢×´Ì¬ÉèÖÃ
    @param lamp_number:²Î¿¼ @ref Ö¸Ê¾µÆÃû³Æ
    @param time,reloadTime:
    @verbatim
    +------------------------------------------+
    |             |       reloadTime           |
    | state table +------+-----------+---------+
    |             | ==0  |>0&&<0xFFFF| ==0xFFFF|
    +-------------+------+-----------+---------+
    |t |   ==0    |  1   |     2     |   3     |
    |i +----------+------+-----------+---------+
    |m |0&&<0xFFFF|  6   |     5     |   6     |
    |e +----------+------+-----------+---------+
    |  |==0xFFFF  |  7   |     8     |   9     |
    +-------------+------+-----------+---------+ 

    1 or 2 or 3  : ³¤Ãð 
    4 or 7 or 9  : ³¤ÁÁ
    5            : µãÁÁtimeÊ±¼ä£¬Ï¨ÃðreloadTime
    6            : µãÁÁtimeÊ±¼ä£¬³¤Ãð
    8            : Ï¨ÃðreloadTimeÊ±¼ä£¬³¤ÁÁ
    @endverbatim
    Í¬Ê±¿É²Î¿¼ @ref Ö¸Ê¾µÆ¼òÒ×ÉèÖÃºê¶¨ÒåÊ¹ÓÃÊ¾Àý
    @verbatim
    hal_lamp_set(xxx,HAL_LAMP_OPEN(HAL_LAMP_HOLD));//³¤ÁÁ
    hal_lamp_set(xxx,HAL_LAMP_CLOSE(HAL_LAMP_HOLD));//³¤Ãð
    hal_lamp_set(xxx,HAL_LAMP_OPEN(1000));//ÁÁÒ»Ãë³¤Ãð
    hal_lamp_set(xxx,HAL_LAMP_CLOSE(2000));//ÃðÁ½Ãë³¤ÁÁ
    hal_lamp_set(xxx,HAL_LAMP_CYCLE(4000,25));//ÖÜÆÚ4Ãë£¬Õ¼¿Õ±È25%ÉÁË¸
    @endverbatim
    
    @return     ÎÞ
    @warning    ¶¨Ê±×î´ó60Ãë
 */
extern void hal_lamp_set(bsp_port_id hal_lamp_amount,uint16_t time,uint16_t reloadtime);
/** 
  * @brief  ÓÃÓÚHAL²ã´¢´æLAMPÖ¸Ê¾µÆ×´Ì¬µÄÊý×é£¨bsp²ãÊµÏÖ£
  * @note 	ÒòÎÞ¶¯Ì¬ÄÚ´æ·ÖÅä£¬ËùÒÔÐèÒªÔÚbsp²ãÉêÇëÄÚ´æ
  */
extern hal_lamp_t hal_all_lamp[];
/** 
  * @brief  ÓÃÓÚ±£´æ´¢´æLAMPÖ¸Ê¾µÆ×´Ì¬Êý×éµÄ³¤¶È£¨bsp²ãÊµÏÖ£
  */
extern const uint8_t hal_lamp_amount;
extern void hal_lamp_loop(uint16_t PastTime);
extern void bsp_set_lamp( bsp_lamp_id_t lamp, uint8_t value );
 #ifdef __cplusplus
 }
 #endif
#endif

