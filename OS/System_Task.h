/*------------------------------------------------------------------------------------------------------------------------
 * �ļ����ƣ�System_task.h

 * �ļ����ݣ�

 * �ļ��汾��1.0.0

 * �ļ����ߣ�����ʵ����

 * ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5 

 * ע    �⣺
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  ���ظ������������
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __System_Task_h_
#define __System_Task_h_
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����ͷ�ļ���
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//������

/*------------------------------------------------------------------------------------------------------------------------
                                                  ��������������
------------------------------------------------------------------------------------------------------------------------*/
typedef 	unsigned char 	Py_INT;
typedef 	unsigned int  	Type_INT;
typedef 	unsigned int  	TPC_INT;
typedef 	unsigned int  	Pa_INT;
typedef 	unsigned int  	ID_INT;
/*------------------------------------------------------------------------------------------------------------------------
                                                  �궨����
------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------��ֵ---------------------------------------*/
/*******************�����������*********************/
/*���������󳤶�*/
#define TaskQueueMax 32
/*�����������*/
#define TaskMax 32
/*Ӧ�ó�ʱ��ֵ��ms��*/
#define AppRunTimerMax 100
/*Ӧ��0��ʱ��ֵ��ms��*/
#define Task0TimeSize 1000
/*����ջ���ջ��*/
#define MaxStackDepth 50
/*ջ��������С*/
#define StackBuffer 17
/*******************�������Ͷ���*********************/
/*��ʱ����*/
#define Task_Time 0x00
/*��������*/
#define Task_EX0 0x01
#define Task_UART1_RI 0x02
#define Task_UART1_TI 0x03
#define Task_I2C 0x04
#define Task_PCA 0x05
#define Task_PCA0 0x06
#define Task_PCA1 0x07
#define Task_PCA2 0x08
#define Task_PCA3 0x09
#define Task_ADC 0x0A
#define Task_LVDF 0x0B
#define Task_UART1_RIDAT 0x0C
#define Task_CMPL 0x0D
#define Task_CMPH 0x0E
#define Task_PWMCF 0x0F
#define Task_PWM0 0x10
#define Task_PWM1 0x11
#define Task_PWM2 0x12
#define Task_PWM3 0x13
#define Task_PWM4 0x14
#define Task_PWM5 0x15
#define Task_PWM6 0x16
#define Task_PWM7 0x17
#define Task_PWMFD 0x18
#define Task_UART2_RI 0x19
#define Task_UART2_TI 0x1A
#define Task_UART3_RI 0x1B
#define Task_UART3_TI 0x1C
#define Task_UART4_RI 0x1D
#define Task_UART4_TI 0x1E
#define Task_TIME0 0x1F
#define Task_TIME1 0x20
#define Task_TIME2 0x21
#define Task_TIME3 0x22
#define Task_TIME4 0x22
/*������*/
#define Task_NULL 0xFF
/*******************���ȼ�����*********************/
#define Task_Class_L1 0x01//1�����û�����
#define Task_Class_L2 0x02
#define Task_Class_L3 0x03
#define Task_Class_L4 0x04
#define Task_Class_L5 0x05
#define Task_Class_L6 0x06
#define Task_Class_L7 0x07
#define Task_Class_L8 0x08
#define Task_Class_L9 0x09
#define Task_Class_H1 0x0A//10����ϵͳ����
#define Task_Class_H2 0x0B
#define Task_Class_H3 0x0C
#define Task_Class_H4 0x0D
#define Task_Class_H5 0x0E
#define Task_Class_H6 0x0F
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����������
------------------------------------------------------------------------------------------------------------------------*/
extern u8 xdata AQSP;//���������ָ��
extern u8 xdata BQSP;//���������ָ��
extern u8 xdata TaskDMax;//���������
extern u8 xdata SP0;//��ʼ��ջָ��
extern u8 xdata RunAppID;//�����������ID
extern u8 xdata RunAppPy;//��������������ȼ�
extern u8 xdata PlanTaskId;//��һ��Ҫ���е�����ID
extern u16 xdata TPC;//�����ʼ��ַ
extern u8 xdata SnLock; //�����л��� 
extern u16 xdata TaskEndAddr;//�����Զ���ֹʱ�����صĵ�ַ
extern u8 xdata TimerIRQTouchType;//��ʱ���жϴ�������

extern u8 stack0[StackBuffer];//ջ������
extern u8 xdata Pstack[TaskMax][MaxStackDepth];//ջ��
extern u8 xdata TaskInterruptQueue[TaskQueueMax + 2];//�ж����������
/*------------------------------------------------------------------------------------------------------------------------
                                                  �ṹ��������
------------------------------------------------------------------------------------------------------------------------*/


/*������Ϣ��*/
typedef struct
{
	Py_INT 		Py0;//ʵʱ���ȼ�
	Py_INT 		Py1;//��ʼ���ȼ�
	Type_INT 	Type;//��������
	TPC_INT 	TPC;//�����ʼ��ַ
	TPC_INT 	Pa0;//����0
	Pa_INT 		Pa1;//����1
}xdata TASKINFO;
extern TASKINFO TaskInfo[TaskMax];

/*��ͨ������б�*/
typedef struct
{
 	ID_INT 		ID;//Ӧ��ID
	Py_INT 		Py;//���ȼ�
}xdata taskqueue;
extern taskqueue TaskQueue[TaskQueueMax + 2];
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����������
------------------------------------------------------------------------------------------------------------------------*/
extern void TaskLoad(u8 TaskId,u8 TaskType,u8 PY,u16 TaskM,u16 TaskPC) reentrant;
extern void TaskRemove(u8 TaskId) reentrant;
extern void MgQueue() reentrant ;
extern void TaskRPlanTaskId();
extern void TaskInterruptQueue_write();
extern void TaskQueue_write(u8 TaskID,u8 Py) reentrant;
extern u8 TaskQueue_read() reentrant;
extern void TypeTaskStartup(u8 TYPE) reentrant;
extern void OpenTask(u8 TaskID) reentrant;
extern void OpenTaskS(u8 TaskID,u8 Py) reentrant;
extern void TASKSWITCH();
extern u2 TaskSwitchIf();
extern void EnableProtection(u16 r1);
extern void DisableProtection();
extern void TaskEnd();

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/