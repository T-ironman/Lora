#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
#include "delay.h"

void  Adc_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);

#endif
