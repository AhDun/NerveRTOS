/*********************************************************************************************************
* �ļ����ƣ�PWM.h
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

#ifndef __PWM_h_
#define __PWM_h_

sbit PWMOUT = P1^0;

void PWMCFAppMain();
void PWM0AppMain();
void PWM1AppMain();
void PWM2AppMain();
void PWM3AppMain();
void PWM4AppMain();
void PWM5AppMain();
void PWM6AppMain();
void PWM7AppMain();
void PWMFDAppMain();

void CPWM(u16 x,u8 HzValue,u8 Spped);
void PWMInit();
void PWM0Init();
void PWM1Init();
void PWM2Init();
void PWM3Init();
void PWM4Init();
void PWM5Init();
void PWM6Init();
void PWM7Init();
//void PWMInterrupt() interrupt 22;
//void PWMFDInterrupt() interrupt 23;

#endif
