///********************************************************************************
//* @author: Zhao ChangJiang
//* @email: hebuyijiangnan@gmail.com
//* @date: 24-3-24 下午1:25
//* @version: 1.0
//* @description:
//********************************************************************************/
//#include <stdlib.h>
//#include "Bsp_motor.h"
//
//#define SPEED_RECORD_NUM 15 //速度滤波数组长度
//float speed_Record[SPEED_RECORD_NUM]={0};
//
//float Speed ;//接收编码器计算出的转速
//float set_speed ;//用于pwm输出的速度（duty）
//
//
////电机刹车
//void Motor_break(void) {
//    target_rpm = 0;
//    HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
//    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
//}
//
//
////电机使能
//void Motor_En( uint8_t en){
//    if (en == 0) {
//        HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET);
//    } else if (en == 1) {
//        HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
//    }
//}
///*
// * 进行速度的平均滤波
// * 输入新采样到的速度，存放速度的数组，
// * 返回滤波后的速度
// */
//float Speed_Low_Filter(float new_Spe)
//{
//    static int index = 0;
//    static float sum = 0.0f;
//    sum -= speed_Record[index];
//    speed_Record[index] = new_Spe;
//    sum += new_Spe;
//    index = (index + 1) % SPEED_RECORD_NUM;
//    return sum / SPEED_RECORD_NUM;
//}
//
////控制电机速度
//void motor_speed_set(float Speed)
//{
//    if (Speed == 0)
//    {
//        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
//        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
//        HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
//    }
//    else if (Speed > 0)
//    {
//        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
//        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
//        HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
//        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed);
//    }
//    else if (Speed < 0)
//    {
//        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
//        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
//        HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
//        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,-Speed);
//    }
//}
//
////电机速度控制
//float Get_Speed(void)
//{
//    int16_t zj;
//    float Speed = 0;
//    zj = __HAL_TIM_GetCounter(&htim4);//获取编码器的计数值
//    Speed = (float)zj / (4 * 11 * 30) * 100 * 60;
//    __HAL_TIM_SetCounter(&htim4, 0);
//    return Speed;
//}
//
//// 用于 qsort 的比较函数
//int compare_ints(const void* a, const void* b)
//{
//    int arg1 = *(const int*)a;
//    int arg2 = *(const int*)b;
//
//    if (arg1 < arg2) return -1;
//    if (arg1 > arg2) return 1;
//    return 0;
//}
//
////电机角度控制
//float Get_Angle(void)
//{
//    int16_t zj;
//    float angle = 0;
//    zj = __HAL_TIM_GetCounter(&htim4);//获取编码器的计数值
//    angle = (float)zj / (4 * 11 * 30) * 360;//计算电机的角度
//    return angle;
//}
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if (htim == &htim3)
//    {//10ms中断
//        Speed = Get_Speed();//获取转速
//        Speed = Speed_Low_Filter(Speed);//滤波
//        set_speed = PID_increment(target_rpm, Speed, &PID_Loc);//PID
//        if (set_speed > 7000){
//            set_speed = 7000;
//        }
//        else if (set_speed < -7000) {
//            set_speed = -7000;
//        }//限幅
//        if (set_speed > 500 || set_speed < -500)//死区控制,改善电机异响
//        {
//            motor_speed_set(set_speed);
//        }
//        Printf(USART1, "Speed:%f,%f\n", Speed, target_rpm);//打印当前和目标转速
//    }
//}
