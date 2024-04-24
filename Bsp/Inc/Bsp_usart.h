/********************************************************************************
* @author: Zhao ChangJiang
* @email: hebuyijiangnan@gmail.com
* @date: 24-3-8 上午12:12
* @version: 1.0
* @description: 
********************************************************************************/


#ifndef BANSHOU_BSP_USART_H
#define BANSHOU_BSP_USART_H

#include "main.h"
#include "usart.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"

void Printf(USART_TypeDef* USARTx, char* fmt, ...);

#endif //BANSHOU_BSP_USART_H
