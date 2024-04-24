/********************************************************************************
* @author: Zhao ChangJiang
* @email: hebuyijiangnan@gmail.com
* @date: 24-4-12 下午9:40
* @version: 1.0
* @description: 
********************************************************************************/


#ifndef INC_32PID_BSP_STEPMOTOR_H
#define INC_32PID_BSP_STEPMOTOR_H
#include "main.h"
#include "tim.h"
#include "stdbool.h"

typedef struct
{
    TIM_HandleTypeDef *htim;
    uint32_t Channel;
    GPIO_TypeDef *GPIOS;
    uint16_t PINS;
}MotorSeting;

typedef struct
{
    uint16_t pluse;
    uint16_t setpluse;
    uint16_t transpluse;
    uint8_t transpluse_flag;
    uint16_t speed;
    uint16_t maxspeed;
}Motor;

void MOTOR_STEP_PluseAdd(uint8_t motorNum);
void MOTOR_STEPCONTROL(TIM_HandleTypeDef *htim);
void MOTOR_STEP_PluseSet(uint8_t motorNum,int32_t setpluse);
void MOTOR_STEP_Init(uint8_t motorNum);
void MOTOR_STEP_SpeedSet(uint8_t motorNum);
bool MOTOR_STEP_SZOver(void);
bool MOTOR_STEP_STOver(void);
void MOTOR_STEP0_close(void );
#endif //INC_32PID_BSP_STEPMOTOR_H
