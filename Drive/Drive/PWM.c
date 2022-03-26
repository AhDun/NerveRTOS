/*********************************************************************************************************
* �ļ����ƣ�PWM.c
* ժ    Ҫ��
* ��ǰ�汾��1.0.0
* ��    �ߣ�����ʵ����
* ������ڣ�
* ��    �ݣ�
* ע    �⣺
* ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5                                                                 
**********************************************************************************************************
* ȡ���汾��
* ��    �ߣ�
* ������ڣ�
* �޸����ݣ�
* �޸��ļ���
*********************************************************************************************************/


#include"Basic.h"
#include"PWM.h"
#include"Sdelay.h"

/********************************
��������:CPWM
��������:���PWM����
�������:x(Ƶ��)HzValue(ˢ����)
��    ��:
�������:�ߵ͵�ƽ
��    ��:
********************************/
void CPWM(u16 x,u8 HzValue,u8 Spped)
{
	static u2 LHs;
	x *= Spped;
	if(LHs)
	{
		LHs = PWMOUT =  0;//�͵�ƽ
		delay_us(x);//��ʱ
	}
	else
	{
		LHs = PWMOUT =  1;//�ߵ�ƽ
		delay_us(1000000 / HzValue - x);//��ʱ
	}
}
/********************************
��������:PWMInit
��������:Ӳ��PWM��ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWMInit()
{
	P_SW2 |= 0x80;
	/*PWMCFG - ��ǿ�� PWM ���üĴ���*/
	//bit7
//	PWMCFG &= 0x7F;// 15 λ�� PWM �����������������ʱ��Ӳ���Զ�����λ�� 1������ CPU ����ж����󣬴˱�־λ��Ҫ�������
//	PWMCFG |= 0x80;// 15 λ�� PWM �����������������ʱ��Ӳ���Զ�����λ�� 1������ CPU ����ж����󣬴˱�־λ��Ҫ�������
	//bit6
	PWMCFG &= 0xBF;//PWM �� ADC ������
//	PWMCFG |= 0x40;//��PWM �� ADC ������������� PWM ������ĳ��ʱ��㴥�� A/D ת����ʹ�� TADCPH �� TADCPL��������
	/*PWMIF - PWM �жϱ�־�Ĵ���*/
	//Bit
	PWMIF = 0x00;//�������PWM���жϱ�־λ
	/*PWMFDCR - PWM �쳣�����ƼĴ���*/
	//bit7
	PWMFDCR &= 0x7F;//�Ƚ���������ɵͱ��Ϊ�쳣�ź�
//	PWMFDCR |= 0x80;//�Ƚ���������ɸ߱��Ϊ�쳣�ź�
	//bit6
	PWMFDCR &= 0xBF;//�ⲿ�˿� P3.5 �ź��ɵͱ��Ϊ�쳣�ź�
//	PWMFDCR |= 0x40;//�ⲿ�˿� P3.5 �ź��ɸ߱��Ϊ�쳣�ź�
	//bit5
	PWMFDCR &= 0xDF;//�ر� PWM �ⲿ�쳣��⹦��
//	PWMFDCR |= 0x20;//ʹ�� PWM �ⲿ�쳣��⹦��

	//bit4
	PWMFDCR &= 0xEF;//���� WM �ⲿ�쳣ʱ��PWM ������ڲ����κθı�
//	PWMFDCR |= 0x10;//���� WM �ⲿ�쳣ʱ��PWM �����������������Ϊ��������ģʽ����ע��ֻ�� ENCnO=1 ����
	//bit3
	PWMFDCR &= 0xF7;//�ر� PWM �쳣����жϣ�FDIF ��Ȼ�ᱻӲ����λ��
//	PWMFDCR |= 0x08;//ʹ�� PWM �쳣����ж�

	//bit2
	PWMFDCR &= 0xFB;//�Ƚ����� PWM �޹�

//	PWMFDCR |= 0x04;//�趨 PWM �쳣���ԴΪ�Ƚ���������쳣������ INVCMP �趨��

	//bit1
	PWMFDCR &= 0xFD;//P3.5 �ڵ�ƽ�� PWM �޹�
//	PWMFDCR |= 0x02;//�趨 PWM �쳣���ԴΪ P3.5 �ڣ��쳣������ INVIO �趨��

	//bit0
//	PWMFDCR &= 0xFE;//PWM �쳣����жϱ�־λ
//	PWMFDCR |= 0x01;//PWM �쳣����жϱ�־λ
	/*PWMCKS - PWM ʱ��ѡ��Ĵ���*/
	//bit4
	PWMCKS &= 0xEF;//PWM ʱ��ԴΪϵͳʱ�Ӿ���Ƶ����Ƶ֮���ʱ��
//	PWMCKS |= 0x10;//PWM ʱ��ԴΪ��ʱ�� 2 ���������
	//bit3 - bit0
	/*
	SELT2 PWM_PS[3:0] PWM ����ʱ��ԴƵ��
		1 xxxx ��ʱ�� 2 ���������
		0 0000 SYSclk/1
		0 0001 SYSclk/2
		0 0010 SYSclk/3
		�� �� ��
		0 x SYSclk/(x+1)
		�� �� ��
		0 1111 SYSclk/16 
	*/
	PWMCKS |= 0x00; 
	/*PWM �������Ĵ���*/
	//Bit
	PWMCH = 0x00;
	//Bit
	PWMCL = 0x00;
	/*PWMCR - PWM ���ƼĴ���*/
	//bit6
//	PWMCR &= 0xBF;//�ر� PWM �����������жϣ�CBIF ��Ȼ�ᱻӲ����λ��
	PWMCR |= 0x40;//ʹ�� PWM �����������ж�
	//bit7
//	PWMCR &= 0x7F;//�ر� PWM ���η�����
	PWMCR |= 0x80;//ʹ�� PWM ���η�������PWM ��������ʼ����

}
/********************************
��������:PWM0Init
��������:PWM0ͨ����ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWM0Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM0HLD - PWM ͨ����ƽ���ֿ��ƼĴ���*/
	//bit1
	PWM0HLD &= 0xFD;//ͨ�� PWM �������
//	PWM0HLD |= 0x02;//ͨ�� PWM ǿ������ߵ�ƽ 
	//bit0
	PWM0HLD &= 0xFE;//ͨ�� PWM �������
//	PWM0HLD |= 0x01;//ͨ�� PWM �������
	/*PWM0T1H - PWM0T1L - PWM0T2H  - PWM0T2L   PWM ��ת�����ü���ֵ�Ĵ���*/	
	PWM0T1H = 0x00;
	PWM0T1L = 0x00;
	PWM0T2H = 0x00;
	PWM0T2L = 0x00;
	/*PWM0CR - PWM0 ͨ�����ƼĴ���*/
	//bit7
//	PWM0CR &= 0x7F;//��Ӧ PWM ͨ���Ķ˿�Ϊ GPIO 
	PWM0CR |= 0x80;//��Ӧ PWM ͨ���Ķ˿�Ϊ PWM ����ڣ��� PWM ���η���������
	//bit6
	PWM0CR &= 0xBF;//ͨ���� PWM ��ʼ��ƽΪ�͵�ƽ
//	PWM0CR |= 0x40;//ͨ���� PWM ��ʼ��ƽΪ�ߵ�ƽ
	//bit4 - bit3 PWM ������ܽ��л�ѡ��
	//bit2
//	PWM0CR &= 0xFB;//�ر�ͨ���� PWM �ж�
	PWM0CR |= 0x04;//ʹ��ͨ���� PWM �ж�
	//bit1
	PWM0CR &= 0xFD;//�ر�ͨ���� PWM �ڵ� 2 ����ת���ж�
//	PWM0CR |= 0x02;//ʹ��ͨ���� PWM �ڵ� 2 ����ת���ж� 
	//bit0
	PWM0CR &= 0xFE;//�ر�ͨ���� PWM �ڵ� 1 ����ת���ж�
//	PWM0CR |= 0x01;//ʹ��ͨ���� PWM �ڵ� 1 ����ת���ж�
}
/********************************
��������:PWM1Init
��������:PWM1ͨ����ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWM1Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM1HLD - PWM ͨ����ƽ���ֿ��ƼĴ���*/
	//bit1
	PWM1HLD &= 0xFD;//ͨ�� PWM �������
//	PWM1HLD |= 0x02;//ͨ�� PWM ǿ������ߵ�ƽ 
	//bit0
	PWM1HLD &= 0xFE;//ͨ�� PWM �������
//	PWM1HLD |= 0x01;//ͨ�� PWM �������
	/*PWM1T1H - PWM1T1L - PWM1T2H  - PWM1T2L   PWM ��ת�����ü���ֵ�Ĵ���*/	
	PWM1T1H = 0x00;
	PWM1T1L = 0x00;
	PWM1T2H = 0x00;
	PWM1T2L = 0x00;
	/*PWM1CR - PWM1 ͨ�����ƼĴ���*/
	//bit7
//	PWM1CR &= 0x7F;//��Ӧ PWM ͨ���Ķ˿�Ϊ GPIO 
	PWM1CR |= 0x80;//��Ӧ PWM ͨ���Ķ˿�Ϊ PWM ����ڣ��� PWM ���η���������
	//bit6
	PWM1CR &= 0xBF;//ͨ���� PWM ��ʼ��ƽΪ�͵�ƽ
//	PWM1CR |= 0x40;//ͨ���� PWM ��ʼ��ƽΪ�ߵ�ƽ
	//bit4 - bit3 PWM ������ܽ��л�ѡ��
	//bit2
//	PWM1CR &= 0xFB;//�ر�ͨ���� PWM �ж�
	PWM1CR |= 0x04;//ʹ��ͨ���� PWM �ж�
	//bit1
	PWM1CR &= 0xFD;//�ر�ͨ���� PWM �ڵ� 2 ����ת���ж�
//	PWM1CR |= 0x02;//ʹ��ͨ���� PWM �ڵ� 2 ����ת���ж� 
	//bit0
	PWM1CR &= 0xFE;//�ر�ͨ���� PWM �ڵ� 1 ����ת���ж�
//	PWM1CR |= 0x01;//ʹ��ͨ���� PWM �ڵ� 1 ����ת���ж�
}
/********************************
��������:PWM2Init
��������:PWM2ͨ����ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWM2Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM2HLD - PWM ͨ����ƽ���ֿ��ƼĴ���*/
	//bit1
	PWM2HLD &= 0xFD;//ͨ�� PWM �������
//	PWM2HLD |= 0x02;//ͨ�� PWM ǿ������ߵ�ƽ 
	//bit0
	PWM2HLD &= 0xFE;//ͨ�� PWM �������
//	PWM2HLD |= 0x01;//ͨ�� PWM �������
	/*PWM2T1H - PWM2T1L - PWM2T2H  - PWM2T2L   PWM ��ת�����ü���ֵ�Ĵ���*/	
	PWM2T1H = 0x00;
	PWM2T1L = 0x00;
	PWM2T2H = 0x00;
	PWM2T2L = 0x00;
	/*PWM2CR - PWM2 ͨ�����ƼĴ���*/
	//bit7
//	PWM2CR &= 0x7F;//��Ӧ PWM ͨ���Ķ˿�Ϊ GPIO 
	PWM2CR |= 0x80;//��Ӧ PWM ͨ���Ķ˿�Ϊ PWM ����ڣ��� PWM ���η���������
	//bit6
	PWM2CR &= 0xBF;//ͨ���� PWM ��ʼ��ƽΪ�͵�ƽ
//	PWM2CR |= 0x40;//ͨ���� PWM ��ʼ��ƽΪ�ߵ�ƽ
	//bit4 - bit3 PWM ������ܽ��л�ѡ��
	//bit2
//	PWM2CR &= 0xFB;//�ر�ͨ���� PWM �ж�
	PWM2CR |= 0x04;//ʹ��ͨ���� PWM �ж�
	//bit1
	PWM2CR &= 0xFD;//�ر�ͨ���� PWM �ڵ� 2 ����ת���ж�
//	PWM2CR |= 0x02;//ʹ��ͨ���� PWM �ڵ� 2 ����ת���ж� 
	//bit0
	PWM2CR &= 0xFE;//�ر�ͨ���� PWM �ڵ� 1 ����ת���ж�
//	PWM2CR |= 0x01;//ʹ��ͨ���� PWM �ڵ� 1 ����ת���ж�
}
/********************************
��������:PWM3Init
��������:PWM3ͨ����ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWM3Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM3HLD - PWM ͨ����ƽ���ֿ��ƼĴ���*/
	//bit1
	PWM3HLD &= 0xFD;//ͨ�� PWM �������
//	PWM3HLD |= 0x02;//ͨ�� PWM ǿ������ߵ�ƽ 
	//bit0
	PWM3HLD &= 0xFE;//ͨ�� PWM �������
//	PWM3HLD |= 0x01;//ͨ�� PWM �������
	/*PWM3T1H - PWM3T1L - PWM3T2H  - PWM3T2L   PWM ��ת�����ü���ֵ�Ĵ���*/	
	PWM3T1H = 0x00;
	PWM3T1L = 0x00;
	PWM3T2H = 0x00;
	PWM3T2L = 0x00;
	/*PWM3CR - PWM3 ͨ�����ƼĴ���*/
	//bit7
//	PWM3CR &= 0x7F;//��Ӧ PWM ͨ���Ķ˿�Ϊ GPIO 
	PWM3CR |= 0x80;//��Ӧ PWM ͨ���Ķ˿�Ϊ PWM ����ڣ��� PWM ���η���������
	//bit6
	PWM3CR &= 0xBF;//ͨ���� PWM ��ʼ��ƽΪ�͵�ƽ
//	PWM3CR |= 0x40;//ͨ���� PWM ��ʼ��ƽΪ�ߵ�ƽ
	//bit4 - bit3 PWM ������ܽ��л�ѡ��
	//bit2
//	PWM3CR &= 0xFB;//�ر�ͨ���� PWM �ж�
	PWM3CR |= 0x04;//ʹ��ͨ���� PWM �ж�
	//bit1
	PWM3CR &= 0xFD;//�ر�ͨ���� PWM �ڵ� 2 ����ת���ж�
//	PWM3CR |= 0x02;//ʹ��ͨ���� PWM �ڵ� 2 ����ת���ж� 
	//bit0
	PWM3CR &= 0xFE;//�ر�ͨ���� PWM �ڵ� 1 ����ת���ж�
//	PWM3CR |= 0x01;//ʹ��ͨ���� PWM �ڵ� 1 ����ת���ж�
}
/********************************
��������:PWM4Init
��������:PWM4ͨ����ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWM4Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM4HLD - PWM ͨ����ƽ���ֿ��ƼĴ���*/
	//bit1
	PWM4HLD &= 0xFD;//ͨ�� PWM �������
//	PWM4HLD |= 0x02;//ͨ�� PWM ǿ������ߵ�ƽ 
	//bit0
	PWM4HLD &= 0xFE;//ͨ�� PWM �������
//	PWM4HLD |= 0x01;//ͨ�� PWM �������
	/*PWM4T1H - PWM4T1L - PWM4T2H  - PWM4T2L   PWM ��ת�����ü���ֵ�Ĵ���*/	
	PWM4T1H = 0x00;
	PWM4T1L = 0x00;
	PWM4T2H = 0x00;
	PWM4T2L = 0x00;
	/*PWM4CR - PWM4 ͨ�����ƼĴ���*/
	//bit7
//	PWM4CR &= 0x7F;//��Ӧ PWM ͨ���Ķ˿�Ϊ GPIO 
	PWM4CR |= 0x80;//��Ӧ PWM ͨ���Ķ˿�Ϊ PWM ����ڣ��� PWM ���η���������
	//bit6
	PWM4CR &= 0xBF;//ͨ���� PWM ��ʼ��ƽΪ�͵�ƽ
//	PWM4CR |= 0x40;//ͨ���� PWM ��ʼ��ƽΪ�ߵ�ƽ
	//bit4 - bit3 PWM ������ܽ��л�ѡ��
	//bit2
//	PWM4CR &= 0xFB;//�ر�ͨ���� PWM �ж�
	PWM4CR |= 0x04;//ʹ��ͨ���� PWM �ж�
	//bit1
	PWM4CR &= 0xFD;//�ر�ͨ���� PWM �ڵ� 2 ����ת���ж�
//	PWM4CR |= 0x02;//ʹ��ͨ���� PWM �ڵ� 2 ����ת���ж� 
	//bit0
	PWM4CR &= 0xFE;//�ر�ͨ���� PWM �ڵ� 1 ����ת���ж�
//	PWM4CR |= 0x01;//ʹ��ͨ���� PWM �ڵ� 1 ����ת���ж�
}
/********************************
��������:PWM5Init
��������:PWM5ͨ����ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWM5Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM5HLD - PWM ͨ����ƽ���ֿ��ƼĴ���*/
	//bit1
	PWM5HLD &= 0xFD;//ͨ�� PWM �������
//	PWM5HLD |= 0x02;//ͨ�� PWM ǿ������ߵ�ƽ 
	//bit0
	PWM5HLD &= 0xFE;//ͨ�� PWM �������
//	PWM5HLD |= 0x01;//ͨ�� PWM �������
	/*PWM5T1H - PWM5T1L - PWM5T2H  - PWM5T2L   PWM ��ת�����ü���ֵ�Ĵ���*/	
	PWM5T1H = 0x00;
	PWM5T1L = 0x00;
	PWM5T2H = 0x00;
	PWM5T2L = 0x00;
	/*PWM5CR - PWM5 ͨ�����ƼĴ���*/
	//bit7
//	PWM5CR &= 0x7F;//��Ӧ PWM ͨ���Ķ˿�Ϊ GPIO 
	PWM5CR |= 0x80;//��Ӧ PWM ͨ���Ķ˿�Ϊ PWM ����ڣ��� PWM ���η���������
	//bit6
	PWM5CR &= 0xBF;//ͨ���� PWM ��ʼ��ƽΪ�͵�ƽ
//	PWM5CR |= 0x40;//ͨ���� PWM ��ʼ��ƽΪ�ߵ�ƽ
	//bit4 - bit3 PWM ������ܽ��л�ѡ��
	//bit2
//	PWM5CR &= 0xFB;//�ر�ͨ���� PWM �ж�
	PWM5CR |= 0x04;//ʹ��ͨ���� PWM �ж�
	//bit1
	PWM5CR &= 0xFD;//�ر�ͨ���� PWM �ڵ� 2 ����ת���ж�
//	PWM5CR |= 0x02;//ʹ��ͨ���� PWM �ڵ� 2 ����ת���ж� 
	//bit0
	PWM5CR &= 0xFE;//�ر�ͨ���� PWM �ڵ� 1 ����ת���ж�
//	PWM5CR |= 0x01;//ʹ��ͨ���� PWM �ڵ� 1 ����ת���ж�
}
/********************************
��������:PWM6Init
��������:PWM6ͨ����ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWM6Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM6HLD - PWM ͨ����ƽ���ֿ��ƼĴ���*/
	//bit1
	PWM6HLD &= 0xFD;//ͨ�� PWM �������
//	PWM6HLD |= 0x02;//ͨ�� PWM ǿ������ߵ�ƽ 
	//bit0
	PWM6HLD &= 0xFE;//ͨ�� PWM �������
//	PWM6HLD |= 0x01;//ͨ�� PWM �������
	/*PWM6T1H - PWM6T1L - PWM6T2H  - PWM6T2L   PWM ��ת�����ü���ֵ�Ĵ���*/	
	PWM6T1H = 0x00;
	PWM6T1L = 0x00;
	PWM6T2H = 0x00;
	PWM6T2L = 0x00;
	/*PWM6CR - PWM6 ͨ�����ƼĴ���*/
	//bit7
//	PWM6CR &= 0x7F;//��Ӧ PWM ͨ���Ķ˿�Ϊ GPIO 
	PWM6CR |= 0x80;//��Ӧ PWM ͨ���Ķ˿�Ϊ PWM ����ڣ��� PWM ���η���������
	//bit6
	PWM6CR &= 0xBF;//ͨ���� PWM ��ʼ��ƽΪ�͵�ƽ
//	PWM6CR |= 0x40;//ͨ���� PWM ��ʼ��ƽΪ�ߵ�ƽ
	//bit4 - bit3 PWM ������ܽ��л�ѡ��
	//bit2
//	PWM6CR &= 0xFB;//�ر�ͨ���� PWM �ж�
	PWM6CR |= 0x04;//ʹ��ͨ���� PWM �ж�
	//bit1
	PWM6CR &= 0xFD;//�ر�ͨ���� PWM �ڵ� 2 ����ת���ж�
//	PWM6CR |= 0x02;//ʹ��ͨ���� PWM �ڵ� 2 ����ת���ж� 
	//bit0
	PWM6CR &= 0xFE;//�ر�ͨ���� PWM �ڵ� 1 ����ת���ж�
//	PWM6CR |= 0x01;//ʹ��ͨ���� PWM �ڵ� 1 ����ת���ж�
}
/********************************
��������:PWM7Init
��������:PWM7ͨ����ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void PWM7Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM7HLD - PWM ͨ����ƽ���ֿ��ƼĴ���*/
	//bit1
	PWM7HLD &= 0xFD;//ͨ�� PWM �������
//	PWM7HLD |= 0x02;//ͨ�� PWM ǿ������ߵ�ƽ 
	//bit0
	PWM7HLD &= 0xFE;//ͨ�� PWM �������
//	PWM7HLD |= 0x01;//ͨ�� PWM �������
	/*PWM7T1H - PWM7T1L - PWM7T2H  - PWM7T2L   PWM ��ת�����ü���ֵ�Ĵ���*/	
	PWM7T1H = 0x00;
	PWM7T1L = 0x00;
	PWM7T2H = 0x00;
	PWM7T2L = 0x00;
	/*PWM7CR - PWM7 ͨ�����ƼĴ���*/
	//bit7
//	PWM7CR &= 0x7F;//��Ӧ PWM ͨ���Ķ˿�Ϊ GPIO 
	PWM7CR |= 0x80;//��Ӧ PWM ͨ���Ķ˿�Ϊ PWM ����ڣ��� PWM ���η���������
	//bit6
	PWM7CR &= 0xBF;//ͨ���� PWM ��ʼ��ƽΪ�͵�ƽ
//	PWM7CR |= 0x40;//ͨ���� PWM ��ʼ��ƽΪ�ߵ�ƽ
	//bit4 - bit3 PWM ������ܽ��л�ѡ��
	//bit2
//	PWM7CR &= 0xFB;//�ر�ͨ���� PWM �ж�
	PWM7CR |= 0x04;//ʹ��ͨ���� PWM �ж�
	//bit1
	PWM7CR &= 0xFD;//�ر�ͨ���� PWM �ڵ� 2 ����ת���ж�
//	PWM7CR |= 0x02;//ʹ��ͨ���� PWM �ڵ� 2 ����ת���ж� 
	//bit0
	PWM7CR &= 0xFE;//�ر�ͨ���� PWM �ڵ� 1 ����ת���ж�
//	PWM7CR |= 0x01;//ʹ��ͨ���� PWM �ڵ� 1 ����ת���ж�
}
void PWMInterrupt() interrupt 22
{
 	if(PWMCFG & 0x80)
	{
	   PWMCFG &= 0x7F;
	}
	if(PWMIF & 0x01)
	{
	   PWMIF &= 0xFE;
	}
	if(PWMIF & 0x02)
	{
	   PWMIF &= 0xFD;
	}
	if(PWMIF & 0x04)
	{
	   PWMIF &= 0xFB;
	}
	if(PWMIF & 0x08)
	{
	   PWMIF &= 0xF7;
	}
	if(PWMIF & 0x10)
	{
	   PWMIF &= 0xEF;
	}
	if(PWMIF & 0x20)
	{
	   PWMIF &= 0xDF;
	}
	if(PWMIF & 0x40)
	{
	   PWMIF &= 0xBF;
	}
	if(PWMIF & 0x80)
	{
	   PWMIF &= 0x7F;
	}
}
void PWMFDInterrupt() interrupt 23
{
}
