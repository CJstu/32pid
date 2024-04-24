/********************************************************************************
* @author: Zhao ChangJiang
* @email: hebuyijiangnan@gmail.com
* @date: 24-3-24 下午2:24
* @version: 1.0
* @description: 
********************************************************************************/
#include "PID.h"
#include "stdlib.h"

extern int encoder_count;

int Motor_pwm;
float target_rpm = 300.0;//r/min
float Target_Velocity=0.0;
extern float rmp;
//20 1.22 5

//初始化结构体
PID_LocTypeDef PID_Loc =
        {22,
         1.2,
         0,
         0,
         0,
         0,
         0,
         0 };

void Control_function(void)
{
    Target_Velocity =(float )(target_rpm/6000.0*4*11*30);//将目标rpm转化为编码器需要的脉冲计数转化为int类型的
    Motor_pwm = (int)PID_increment(Target_Velocity, encoder_count*1.0, &PID_Loc);
    limit_pwm();
    Set_Pwm(Motor_pwm);
}


//增量式PID
//pidout+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
//setvalue : 设置值（期望值）
//actualvalue: 实际值
float PID_increment(float setvalue, float actualvalue, PID_LocTypeDef *PID)
{
    PID->ek =setvalue-actualvalue;
    PID->out+=PID->kp * (PID->ek-PID->ek1)+ PID->ki*PID->ek + PID->kd*(PID->ek-2*PID->ek1+PID->ek2);
//	PID->out+=PID->kp*PID->ek-PID->ki*PID->ek1+PID->kd*PID->ek2;
    PID->ek2 = PID->ek1;
    PID->ek1 = PID->ek;
    return PID->out;
}


/**
*	函数功能：赋值给PWM寄存器
*	入口参数：PWM
*	返回值：无
*/
void Set_Pwm(int cj_pwm)
{
    int pwm_abs;
    if (cj_pwm < 0)
    {
        Motor_mode(0);
    }
    else
    {
        Motor_mode(1);
    }
    pwm_abs = abs(cj_pwm);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,pwm_abs);
}


//pwm限幅
void limit_pwm(void)
{
    int maxnum = 7000;
    if (Motor_pwm > maxnum)
    {
        Motor_pwm = maxnum;
    }
    else if (Motor_pwm < -maxnum)
    {
        Motor_pwm = -maxnum;
    }
}

//找出数组中最大值和最小值
void Find_Max_Min(int16_t *arr, uint8_t len, int16_t *max, int16_t *min)
{
    uint8_t i;
    *max = arr[0];
    *min = arr[0];
    for (i = 1; i < len; i++)
    {
        if (arr[i] > *max)
        {
            *max = arr[i];
        }
        if (arr[i] < *min)
        {
            *min = arr[i];
        }
    }
}