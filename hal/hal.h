#ifndef HAL_H
#define HAL_H
#include "mcu_typedef.h"
#include "mcu_interruts.h"
#ifdef __cplusplus
extern "C"
{
 #endif
	
/*! 该类型用于保存中断状态，0代表允许中断，1代表禁止中断  */
typedef uint8_t halIntState_t;
/*! 该变量用于保存当前中断状态 参考 halIntState_t 类型 */
extern halIntState_t irq_state;
/*! 进入临界状态，输入为 halIntState_t 类型变量 */
#define HAL_ENTER_CRITICAL_SECTION(x)   st( HAL_DISABLE_INTERRUPTS; x = irq_state; )
/*! 退出临界状态，输入为 halIntState_t 类型变量 */
#define HAL_EXIT_CRITICAL_SECTION(x)    st(irq_state = x; if(irq_state==0) HAL_ENABLE_INTERRUPTS; else HAL_DISABLE_INTERRUPTS; )
/*! 单行临界状态，输入为需要临界状态执行的代码块 */
#define HAL_CRITICAL_STATEMENT(x)       st( halIntState_t _s; HAL_ENTER_CRITICAL_SECTION(_s); x; HAL_EXIT_CRITICAL_SECTION(_s); )	

extern void hal_init(void);
extern void hal_loop(void);
 #ifdef __cplusplus
 }
 #endif
#endif
