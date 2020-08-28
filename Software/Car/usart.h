#ifndef USART_H
#define USART_H

#include "stm32f10x.h"
#include "stdbool.h"
#include "delay.h"
#include "string.h"

void MCU_USRAT_LORA_Init(u32 bound);
void LORA_Config_M0_M1(u32 bound,int M0,int M1); //调整Lora模块的传输参数
void Lora_send(char* cmd,int time_s);
#endif
