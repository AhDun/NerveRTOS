/*------------------------------------------------------------------------------------------------------------------------
 * �ļ����ƣ�System_Control.h

 * �ļ����ݣ�

 * �ļ��汾��1.0.0

 * �ļ����ߣ�����ʵ����

 * ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5 

 * ע    �⣺
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  ���ظ������������
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __System_Control_h_
#define __System_Control_h_
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����ͷ�ļ���
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//������
/*ϵͳ�����*/
#include "System_Clock.h"
#include "WDT.h"//���Ź���
#include "Interrupt.h"//�жϿ�
#include "UARTApp.h"//����Ӧ�ÿ�
#include "UART.h"//���ڿ�
#include "Timer.h"//��ʱ����
#include "system_task.h"//ϵͳ�������
#include "Power.h"//��Դ������
#include "System_Control.h"//ϵͳ���ƿ�
#include "system_uart.h"//ϵͳ���ڿ�
#include "delay_Lib.h"//������ʱ�� 
/*------------------------------------------------------------------------------------------------------------------------
                                                  �궨����
------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------�ַ���--------------------------------------*/
/*ϵͳ�����ɹ�����������ַ���*/
#define System_OK_UART "Nerve RTOS Success Start!\n"
/*ϵͳ����ʧ�ܴ���������ַ���*/
#define System_Error_UART "Nerve RTOS Fali Start!\n"
/*----------------------------------��ֵ---------------------------------------*/
/*����ϵͳ�汾*/
#define Systemv 168
/*����ϵͳ�ڲ��汾������λ��*/
#define SystemSvP 0x2165
/*���ó�ʼָ���ֵ*/
#define SP_Init_Va 2
/*���Ź�������ʱ��*/
#define WDT_SingleCycle_Time 1500
/*ϵͳ����ʱ��*/
#define SYS_TEST_Time 2
/*ϵͳ���Եȴ�ʱ��*/
#define SYS_TEST_Wait_Time 4
/*��Ӧ��ID*/
#define Main_AID 0
/*���ÿ��Ź�Ӧ��ID*/
#define RSTWDT_AID 30
/*ϵͳ����������ģʽӦ��ID*/
#define ISP_AID 29
/*���ڽ������Ӧ��ID*/
#define UARTDAEND_AID 28
/*���������Ӧ��ID*/
#define SYS_TEST 27
/*ϵͳ������Ӧ��ID*/
#define MonitorOutUART_AID 26
/*----------------------------------����---------------------------------------*/
/*ָ��ϵͳ��ʱ����ʼ������*/
#define System_Timer_Init {Timer0Init();}
/*ָ��ϵͳ���ڳ�ʼ������*/
#define System_UART_Init {UART1Init();}
/*ָ��ϵͳ���Ź���ʼ������*/
#define System_WDT_Init {WDT_Init();}
/*----------------------------------����---------------------------------------*/
/*����ϵͳ��ʱ���رմ���*/
#define System_Timer_Disable {ET0 = Disable;}
/*����ϵͳ��ʱ����������*/
#define System_Timer_Enable {ET0 = Enable;}
/*�������жϹرմ���*/
#define System_IMS_Disable {EA = Disable;}
/*�������жϿ�������*/
#define System_IMS_Enable {EA = Enable;}
/*����ϵͳ��ʱ���жϼ������*/
#define System_Timer_Touch {TF0 = Enable;}
/*----------------------------------����---------------------------------------*/
/*�����Ƿ�ʹ�ô��ڹ���*/
#define EnableSerialPortDebugging//�����ڹ���
/*�����Ƿ�ʹ�ÿ��Ź����ܹ���*/
#define EnableWDT//�����Ź�����
/*�����Ƿ�ʹ�õ��Լ�鹦��*/
#define EnableECF//�����Լ�鹦��
/*�����Ƿ�ʹ�ö��м�鹦��*/
#define EnableQueueCheck//�����м�鹦��
/*�����Ƿ�ʹ��ϵͳ����ʱ���ʱ*/
#define EnableRunningTime//ϵͳ����ʱ���ʱ
/*------------------------------------------------------------------------------------------------------------------------
                                                  �ṹ��������
------------------------------------------------------------------------------------------------------------------------*/
/*ϵͳ״̬*/
typedef struct 
{
	u8 SystemOk;//ϵͳ���б�־λ
	u8 TaskSwitch;//���������б�־λ
}xdata SystemFlag;
extern SystemFlag Sf;

/*------------------------------------------------------------------------------------------------------------------------
                                                  ����������
------------------------------------------------------------------------------------------------------------------------*/
extern void System_Init();//ϵͳ��ʼ��
extern void OffTask();//�رն�����
extern void OnTask();//����������
extern void Start_Test();//���������
extern u16 Gma(u16 ADD_R0);//��ȡ������ַ

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/