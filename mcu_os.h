/*
 * mcu_os.h
 *
 * Created: 24.01.2020 14:31:48
 * Author: Dinar Talibullin
 */ 


#ifndef MCU_OS_H_
#define MCU_OS_H_

#include "stm8s.h"
//#include "stdint.h"

#define MCU_OS_TASKS_COUNT 4

void mcu_os_timer_init(void);

void one_ms_callback(void);
void mcu_os_init(void);
int mcu_os_add_task(void (*pt2Func)(void), uint16_t period);



#endif /* MCU_OS_H_ */