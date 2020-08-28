#include "stm32f10x.h"
#include "usart.h"
#include "adc.h"
int main()
{
	int t = 0;
	int adc_value = 0;
	char str[80];
	LORA_Config_M0_M1(9600,0,0);//��ʼ��Loraģ�飬������빤��ģʽ
	Adc_Init(); //��ʼ��ADC
	while(1)
	{
		adc_value = Get_Adc_Average(ADC_Channel_10,3);
		t++;
		sprintf(str,"hxthxt %u",t);
		Lora_send(str,1);
		sprintf(str,"adc_value %u",adc_value);		
		Lora_send(str,1);
	}
}



