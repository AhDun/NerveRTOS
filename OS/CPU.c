/*------------------------------------------------------------------------------------------------------------------------
 * �ļ����ƣ�CPU.c

 * �ļ����ݣ�ϵͳ�����ں�

 * �ļ��汾��1.0.0

 * �ļ����ߣ�����ʵ����

 * ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5 

 * ע    �⣺
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����ͷ�ļ���
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//������
#include "System_Task.h"
#include "System_Clock.h"
#include "Timer.h"
#include "System_Control.h"
#include "CPU.h"
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskSwitch

 * �������ܣ������л�

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void TaskSwitch()
{
	u8 TS_F0;
	if(TimerIRQTouchType)
	{
		/*���Ŀ������ID�뵱ǰ����ID��ͬ��������л�*/
		if(PlanTaskId != RunAppID)
		{
			/*��ջ���ص�������*/
			#pragma asm
			POP   stack0+0CH
			POP   stack0+0CH
			POP  	stack0+0CH
			POP  	stack0+0BH
			POP  	stack0+0AH
			POP  	stack0+09H
			POP  	stack0+08H
			POP  	stack0+07H
			POP  	stack0+06H
			POP  	stack0+05H
			POP  	stack0+04H
			POP  	stack0+03H
			POP  	stack0+02H
			POP  	stack0+01H
			POP  	stack0+00H
			POP		stack0+0DH
			POP		stack0+0EH
			#pragma endasm
			/*�������ʱ������*/
			AppRunTimer = NULL;
			/*���TimerTouchType == 1�����ʾΪ���񲢷��Զ���������*/
			if(TimerIRQTouchType == Task_Touch)
			{
				/*�����׼��ջ*/
				for(TS_F0 = NULL;TS_F0 < 15;TS_F0++)
				{
					/*��׼ջ*/
					/*ջ������-----д��---->��չRAM��*/
					Pstack [RunAppID][TS_F0 + 1] = stack0[TS_F0];
				}
				/*������չ��ջ�������ϵ��ʼ��ջָ�룬�Զ�����ջ�ĳ���*/
				for(;(SP - SP0) > NULL;TS_F0++)
				{
					/*������ջ�ص����ʱ������ֹͣд��*/
					if(TS_F0 >= MaxStackDepth)
					{
						break;
					}
					/*�����ջ����*/
					#pragma asm
					POP		stack0+1
					#pragma endasm
					/*��չջ*/
					/*ջ������-----д��---->��չRAM��*/
					Pstack [RunAppID][TS_F0 + 1]  = stack0[1];
				}
				Pstack [RunAppID][NULL] = TS_F0 - 1;//��ջ���ȼ�¼��ջ�صĶ���
			}
			else/*������񲢷��Զ��������У�����������ջ��*/
				RunAppPy = Pstack [RunAppID][NULL] = NULL;
			RunAppID = PlanTaskId;/*ˢ������ID*/
			if(Pstack[RunAppID][NULL] == NULL)//׼������̬
			{
				/*���س�ʼ������ַ��������*/
				stack0 [13] = TPC >> 8;
				stack0 [14]=  TPC & 0x00FF;
				
				if(RunAppID > NULL)
				{
					/*�������Զ����ص�ָ��д�뵽��������*/
					stack0 [16] = TaskEndAddr & 0x00FF;
					stack0 [15] = TaskEndAddr >> 8;
					/*����ѹջ�������������Զ����ص�ָ��ӻ�������д�뵽ջ��*/
					#pragma asm
					PUSH 	stack0 + 10H
					PUSH 	stack0 + 0FH
					#pragma endasm
				}
			}
			else if(Pstack [RunAppID][NULL] > NULL)//�������̬
			{
				/*��չջ*/
				/*�Ա��浽ջ���е�ͷ���ĳ�����Ϣ����ջ��������ѹ��ջ��*/
				for(TS_F0 = Pstack [RunAppID][NULL];TS_F0 > 14;TS_F0--)
				{
					/*��չRAM-----д��---->ջ������*/
					stack0[NULL] = Pstack [RunAppID][TS_F0 + 1] ;
					#pragma asm
					PUSH	stack0
					#pragma endasm
				}
				/*��׼ջ*/
				/*��չRAM-----д��---->ջ������*/
				for(TS_F0 = 0;TS_F0 < 15;TS_F0++)
				{
					stack0 [TS_F0] = Pstack [RunAppID][TS_F0 + 1] ;
				}
			}
			/*��λ�����־λ*/
			TimerIRQTouchType = NULL;
			/*��λ�л���*/
			SnLock = NULL; 
			/*��λˢ����*/
			PlanTaskId = NULL;
			/*����װ�ص������ʱ����*/
			AppRunTimer = 0xFF;
			/*��λ����ʱ��*/
			ProTime = NULL;

			/*�����������ص�ջ*/
			#pragma asm
			MOV 	ACC , stack0+00H
			MOV 	B , stack0+01H
			MOV 	DPH , stack0+02H
			MOV 	DPL , stack0+03H
			MOV 	PSW , stack0+04H
			MOV 	0x00 , stack0+05H
			MOV 	0x01 , stack0+06H
			MOV 	0x02 , stack0+07H
			MOV 	0x03 , stack0+08H
			MOV 	0x04 , stack0+09H
			MOV 	0x05 , stack0+0AH
			MOV 	0x06 , stack0+0BH
			MOV 	0x07 , stack0+0CH
			PUSH	stack0+0EH
			PUSH	stack0+0DH
			RETI
			#pragma endasm
		}
		/*��λ�����־λ*/
		TimerIRQTouchType = NULL;
		/*��λ�л���*/
		SnLock = NULL; 
		/*��λˢ����*/
		PlanTaskId = NULL;
		/*����װ�ص������ʱ����*/
		AppRunTimer = 0xFF;
		/*��λ����ʱ��*/
		ProTime = NULL;
	}
}
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/