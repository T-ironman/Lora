#include "usart.h"

void MCU_USRAT_LORA_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStrue;     										
	USART_InitTypeDef USART_InitStrue;   
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_DeInit(USART2);   
	
	
	/*Tx Rx*/
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_AF_PP;    								
	GPIO_InitStrue.GPIO_Pin = GPIO_Pin_2;   								    
	GPIO_InitStrue.GPIO_Speed = GPIO_Speed_50MHz;   						
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_IN_FLOATING;    						
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3;   									
	GPIO_Init(GPIOA,&GPIO_InitStrue);

	
	/**M0 M1**/
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_Out_PP;    						
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_4;   				 //M1	
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_Out_PP;   //M0				
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_5;   									
	GPIO_Init(GPIOA,&GPIO_InitStrue);

	
	/***AUX***/
	GPIO_InitStrue.GPIO_Mode = GPIO_Mode_IN_FLOATING;    						
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_1;   				 //AUX	
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	
	USART_InitStrue.USART_BaudRate = bound;									
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	
	USART_InitStrue.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;						
	USART_InitStrue.USART_Parity=USART_Parity_No;							
	USART_InitStrue.USART_StopBits=USART_StopBits_1;   							
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;  
	
	USART_Init(USART2,&USART_InitStrue);   										
	USART_Cmd(USART2,ENABLE); 													
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
}


void LORA_Config_M0_M1(u32 bound,int M0,int M1) //����Loraģ��Ĵ������
{
/**
	* Lora��MCUͨ��ֻ������Ϊ9600
	*/
	MCU_USRAT_LORA_Init(bound); 
	
/**
	* ���ù���ģʽ
	*/
	if(M0 == 0)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_5); //M0 = 0
	}
	else if(M0 == 1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5); //M0 = 0
	}
	else		
	{}
	if(M1 == 0)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4); //M0 = 0
	}
	else if(M1 == 1)
	{
			GPIO_SetBits(GPIOA,GPIO_Pin_4);  //M1 = 1
	}
	else
	{}

/**
	*�ж�AUX���Ƿ�Ϊ�ߵ�ƽ������״̬
	*/
//	while(1)
//	{
//		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)
//		{
//			delay_ms(10);
//			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)
//			{
//				return true;
//			}
//		}
//	}
}


//Loraģ��ÿ�� time_s �뷢��һ�� str �ַ���
void Lora_send(char* str,int time_s)
{
	for(int t=0;t<strlen(str);t++)
		{
			USART_SendData(USART2,str[t]);         //�򴮿�1��������
			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		}
		for(int i = 0 ;i < time_s; i++ )
			delay_ms(1000);
	
}
