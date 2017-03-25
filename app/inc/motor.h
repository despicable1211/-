#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x_gpio.h"

void left_motor_pwm_init(u16 arr,u16 psc);
void left_motor_gpio_init(void);

#endif