/********************************************************************************
* @author: Zhao ChangJiang
* @email: hebuyijiangnan@gmail.com
* @date: 24-4-12 下午9:40
* @version: 1.0
* @description: 
********************************************************************************/
#include "Bsp_stepmotor.h"

//定义最大速度与设定速度(越小越大)
#define MAXSPEED 150
#define SETSPEED 300
//  3150   3050
uint16_t kRowStep = 2990, kColStep = 3220;//纵一步脉冲   横一步脉冲

uint8_t reset_flag_z = 0;
uint8_t reset_flag_h = 0;

//声明电机（方向）结构体
/*
 * 定时器句柄
 * 对应通道
 * 方向端口
 * */
MotorSeting motorsseting[2] =
        {
                {&htim1,TIM_CHANNEL_1,DIR_GPIO_Port,DIR_Pin},
                {&htim1,TIM_CHANNEL_4,DIR_GPIO_Port,DIR_Pin},
        };

/*
 * 初始化电机速度结构体
 * pluse			    当前脉冲
 * setpluse				设定脉冲
 * transpluse			转变脉冲数
 * transpluse_flag	    转变标志位
 * speed				当前速度
 * maxspeed				最大速度
 * */
Motor motors[2] =
        {
                {0,1,0,0,SETSPEED,MAXSPEED},
                {0,1,0,0,SETSPEED,MAXSPEED},
        };

/**
  *brief  脉冲增加
  *note   None
  *param  电机号
  *retval None
  */
void MOTOR_STEP_PluseAdd(uint8_t motorNum)
{
    motors[motorNum].pluse++;//当前脉冲+1
    Printf(USART1,"motors[%d] pluse:%d\r\n",motorNum,motors[motorNum].pluse);
    if(motors[motorNum].pluse>motors[motorNum].setpluse)//如果大于设定脉冲
    {
        HAL_TIM_Base_Stop_IT(motorsseting[motorNum].htim);//关闭中断并停止计数
        HAL_TIM_PWM_Stop(motorsseting[motorNum].htim,motorsseting[motorNum].Channel);
        motors[motorNum].pluse = motors[motorNum].setpluse = 0;//当前脉冲以及设定脉冲全部清零
//		printf("motors[%d] over:%dms speed: %d\r\n",0,HAL_GetTick(),motors[0].speed);
        Printf(USART1,"motors[%d] over:%dms speed: %d\r\n",motorNum,HAL_GetTick(),motors[motorNum].speed);
    }
}

/**
  *brief  电机计数
  *note   None
  *param  对应定时器
  *retval None
  */
void MOTOR_STEPCONTROL(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        MOTOR_STEP_PluseAdd(0);
    }
//    else if (htim->Instance == TIM2)
//    {
//        MOTOR_STEP_PluseAdd(1);
//    }
}

/**
  *brief  电机设计脉冲数设置
  *note   None
  *param  目标电机号  设定脉冲数
  *retval None
  */
void MOTOR_STEP_PluseSet(uint8_t motorNum,int32_t setpluse)
{
    if(setpluse>=0)//正转
    {
        HAL_GPIO_WritePin(motorsseting[motorNum].GPIOS,motorsseting[motorNum].PINS,GPIO_PIN_RESET);
        motors[motorNum].setpluse=(uint32_t)setpluse;
    }
    else if(setpluse<0)//反转
    {
        HAL_GPIO_WritePin(motorsseting[motorNum].GPIOS,motorsseting[motorNum].PINS,GPIO_PIN_SET);
        motors[motorNum].setpluse=-(uint32_t)setpluse;
    }
    motors[motorNum].speed = SETSPEED;
    MOTOR_STEP_Init(motorNum);
}
/**
  *brief  电机状态是否停止
  *note   None
  *param  None
  *retval 停止 true  否则false
  */
bool MOTOR_STEP_SZOver(void)
{
    if(motors[1].setpluse == 0)
        return true;
    else
        return false;
}
bool MOTOR_STEP_STOver(void)
{
    if(motors[0].pluse == 0)
        return true;
    else
        return false;
}
/**
  *brief  目标电机初始化
  *note   None
  *param  目标电机
  *retval None
  */
void MOTOR_STEP_Init(uint8_t motorNum)
{
    MOTOR_STEP_SpeedSet(motorNum);//速度设定
//    __HAL_TIM_CLEAR_IT(motorsseting[motorNum].htim,TIM_IT_UPDATE ); //清除IT标志位
    HAL_TIM_Base_Start_IT(motorsseting[motorNum].htim);//开始计数
    HAL_TIM_PWM_Start(motorsseting[motorNum].htim,motorsseting[motorNum].Channel);//开始产生脉冲
}


void MOTOR_STEP0_close(void )
{
    HAL_TIM_Base_Stop_IT(motorsseting[0].htim);//关闭中断并停止计数
    HAL_TIM_PWM_Stop(motorsseting[0].htim,motorsseting[0].Channel);
}
/**
  *brief  目标电机速度设定
  *note   SET_AUTORELOAD用于调整自动重载值，即调整周期
  *       SET_COMPARE用于调整比较值，即调整占空比       本程序占空比默认为1/2
  *param  目标电机
  *retval None
  */
void MOTOR_STEP_SpeedSet(uint8_t motorNum)
{
    __HAL_TIM_SET_AUTORELOAD(motorsseting[motorNum].htim,motors[motorNum].speed);
    __HAL_TIM_SET_COMPARE(motorsseting[motorNum].htim,motorsseting[motorNum].Channel,motors[motorNum].speed/2);
}
