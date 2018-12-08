#ifndef HAL_H
#define HAL_H
#include "mcu_typedef.h"
#include "mcu_interruts.h"
#ifdef __cplusplus
extern "C"
{
 #endif
	
/*! ���������ڱ����ж�״̬��0���������жϣ�1�����ֹ�ж�  */
typedef uint8_t halIntState_t;
/*! �ñ������ڱ��浱ǰ�ж�״̬ �ο� halIntState_t ���� */
extern halIntState_t irq_state;
/*! �����ٽ�״̬������Ϊ halIntState_t ���ͱ��� */
#define HAL_ENTER_CRITICAL_SECTION(x)   st( HAL_DISABLE_INTERRUPTS; x = irq_state; )
/*! �˳��ٽ�״̬������Ϊ halIntState_t ���ͱ��� */
#define HAL_EXIT_CRITICAL_SECTION(x)    st(irq_state = x; if(irq_state==0) HAL_ENABLE_INTERRUPTS; else HAL_DISABLE_INTERRUPTS; )
/*! �����ٽ�״̬������Ϊ��Ҫ�ٽ�״ִ̬�еĴ���� */
#define HAL_CRITICAL_STATEMENT(x)       st( halIntState_t _s; HAL_ENTER_CRITICAL_SECTION(_s); x; HAL_EXIT_CRITICAL_SECTION(_s); )	

extern void hal_init(void);
extern void hal_loop(void);
 #ifdef __cplusplus
 }
 #endif
#endif
