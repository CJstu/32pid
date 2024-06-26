/********************************************************************************
* @author: Zhao ChangJiang
* @email: hebuyijiangnan@gmail.com
* @date: 24-3-29 下午7:15
* @version: 1.0
* @description: 
********************************************************************************/
#include <stdlib.h>
#include "App_cmd.h"
#include "stdio.h"

#define SCB_AIRCR       (*(volatile unsigned long *)0xE000ED0C)  /* Reset control Address Register */
#define SCB_RESET_VALUE 0x05FA0004                               /* Reset value, write to SCB_AIRCR can reset*/

//TODO 应优化全局变量
char CMD_Buffer[50];////////////////////串口1
int CMD_Buffer_Count = 0;//缓存区计数
int CMD_Flag = 0;//缓存区标志

uint8_t usart_cmd_rx_buffer[1];//串口缓存区
/**
  *brief  串口控制台cmd命令
  *note   None
  *param  None
  *retval None
  */
void cmd(void)
{
    if(CMD_Flag)
        CMD_Flag = 0;//清除标志位1
    else
        return;
    if     (!strcmp(CMD_Buffer,"hi"))			            {Printf(USART1,"hiOK\r\n");}
//    else if(!strcmp(CMD_Buffer,"reboot"))	                {reboot();}
//    else if(!strcmp(CMD_Buffer,"stop"))	                    {Motor_break();}
    else if(strstr(CMD_Buffer,"rpm"))	                    {user_set_targetrpm();}
//    else if(strstr(CMD_Buffer,"down"))	                {down();}
//    else if(strstr(CMD_Buffer,"duo"))	                {duo();}
    else
    {
        Printf(USART1,"unknown cmd '%s'\r\n",CMD_Buffer);
    }
    //缓存区清零
    for(int i = CMD_Buffer_Count; i >= 0; i--)
    {
        CMD_Buffer[i] = 0;
    }
    CMD_Buffer_Count = 0;
    CMD_Flag = 0;
    HAL_UART_Receive_IT(&huart1, (uint8_t*)usart_cmd_rx_buffer, 1);   //设置传输
}
/**
  *brief  软件复位
  *note   None
  *param  None
  *retval None
  */
void reboot(void)
{
    printf("\r\n^^^^^^^^^^^^^^^^^^^^^System Rebooting^^^^^^^^^^^^^^^^^^^^^\r\n\r\n\r\n\r\n");
    SCB_AIRCR = SCB_RESET_VALUE;
}
/**
  *brief  帮助：路径选择格式
  *note   None
  *param  None
  *retval None
  */
void help(void)
{
    printf("reboot \r\n");
}

void user_set_targetrpm(void)
{
    char buf_String[50];
    float buf;
    char *token = strtok(CMD_Buffer, " ");
    if (token != NULL){
        strncpy(buf_String, token, sizeof(buf_String) - 1);
        token = strtok(NULL, " ");
        if (token != NULL) {
            buf = atof(token);
            target_rpm = buf;
        }
    }
}