/********************************************************************************
* @author: Zhao ChangJiang
* @email: hebuyijiangnan@gmail.com
* @date: 24-3-24 下午1:25
* @version: 1.0
* @description: 
********************************************************************************/


#ifndef INC_32PID_BSP_MOTOR_H
#define INC_32PID_BSP_MOTOR_H

#include "main.h"
#include "tim.h"

void Motor_mode(uint8_t mode);
void Motor_En( uint8_t en);
void Motor_break(void);
void motor_speed_set(float Speed);
int compare_ints(const void* a, const void* b);
//float Speed_Low_Filter(float new_Spe,float *speed_Record);
float Speed_Low_Filter(float new_Spe);
float Get_Speed(void );
float Get_Speed(void );

#endif //INC_32PID_BSP_MOTOR_H
