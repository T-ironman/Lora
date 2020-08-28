#include "delay.h"

/*
 *
 ע�⣺�����������м�Ĳ���u32 i���ܳ���1800���������붨ʱһ���ӣ�����ͨ��forѭ����delay_ms��1000����60�Σ�������ʹ��delay_ms��60000������Ȼ����ͳ����ˡ�
 */
void delay_us(u32 i)
{
    u32 temp;
    SysTick->LOAD=9*i;         //������װ��ֵ, 72MHZʱ
    SysTick->CTRL=0X01;         //ʹ�ܣ����������޶����������ⲿʱ��Դ
    SysTick->VAL=0;                //���������
    do
    {
        temp=SysTick->CTRL;           //��ȡ��ǰ������ֵ
    }
    while((temp&0x01)&&(!(temp&(1<<16))));     //�ȴ�ʱ�䵽��
    SysTick->CTRL=0;    //�رռ�����
    SysTick->VAL=0;        //��ռ�����
}


void delay_ms(u32 i)
{
    u32 temp;
    SysTick->LOAD=9000*i;      //������װ��ֵ, 72MHZʱ
    SysTick->CTRL=0X01;        //ʹ�ܣ����������޶����������ⲿʱ��Դ
    SysTick->VAL=0;            //���������
    do
    {
        temp=SysTick->CTRL;       //��ȡ��ǰ������ֵ
    }
    while((temp&0x01)&&(!(temp&(1<<16))));    //�ȴ�ʱ�䵽��
    SysTick->CTRL=0;    //�رռ�����
    SysTick->VAL=0;        //��ռ�����
}
