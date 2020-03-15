/*
 * mcu_os_port.c
 *
 * Created: 27.01.2020 16:24:39
 * Author: Dinar Talibullin
 */ 

#include "mcu_os.h"
#include "stm8s.h"

void mcu_os_timer_init(void)
{
  //init timer for simple sheduler
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV2); // set 8 MHz for CPU
  TIM2_TimeBaseInit(TIM2_PRESCALER_4, 0x7cf);
  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
  TIM2_Cmd(ENABLE);
  enableInterrupts();
 
}

 INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
{
  one_ms_callback();
  TIM2_ClearITPendingBit(TIM2_IT_UPDATE);
}