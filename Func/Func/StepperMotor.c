/*********************************************************************************************************
* �ļ����ƣ�StepperMotor.c
* ժ    Ҫ�������������
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
#include"StepperMotor.h"

/********************************
��������:Motor42
��������:�����������
�������:AB(����)
����:
�������:
���:
˵��:����˫���Խ����
********************************/
void MOTO42r42(u8 AB)
{
 	switch(AB)
	{
 		case 0:MOTO42A = 1;MOTO42B = 0;MOTO42C = 1;MOTO42D = 1;break;
		case 1:MOTO42A = 1;MOTO42B = 1;MOTO42C = 1;MOTO42D = 0;break;
		case 2:MOTO42A = 0;MOTO42B = 1;MOTO42C = 1;MOTO42D = 1;break;
		case 3:MOTO42A = 1;MOTO42B = 1;MOTO42C = 0;MOTO42D = 1;break;
	}
}
/********************************
��������:SMotor
��������:�����������
�������:AB(����)TW(����ģʽ)
����:
�������:
���:
˵��:�����ļ��Խ����
********************************/
void Motor54(u8 AB,u8 TW)
{
 	switch(TW)
	{
	   case 0://��4��
			switch(AB)
			{
				case 0:MOTO54A = 1;MOTO54B = 0;MOTO54C = 0;MOTO54D = 0;break;
				case 1:MOTO54A = 0;MOTO54B = 1;MOTO54C = 0;MOTO54D = 0;break;
				case 2:MOTO54A = 0;MOTO54B = 0;MOTO54C = 1;MOTO54D = 0;break;
				case 3:MOTO54A = 0;MOTO54B = 0;MOTO54C = 0;MOTO54D = 1;break;
			}
			break;
		case 1://˫4��
			switch(AB)
			{
				case 0:MOTO54A = 1;MOTO54B = 1;MOTO54C = 0;MOTO54D = 0;break;
				case 1:MOTO54A = 0;MOTO54B = 1;MOTO54C = 1;MOTO54D = 0;break;
				case 2:MOTO54A = 0;MOTO54B = 0;MOTO54C = 1;MOTO54D = 1;break;
				case 3:MOTO54A = 1;MOTO54B = 0;MOTO54C = 0;MOTO54D = 1;break;
			}
			break;
		case 2://8��
			switch(AB)
			{
				case 0:MOTO54A = 1;MOTO54B = 0;MOTO54C = 0;MOTO54D = 0;break;
				case 1:MOTO54A = 1;MOTO54B = 1;MOTO54C = 0;MOTO54D = 0;break;
				case 2:MOTO54A = 0;MOTO54B = 1;MOTO54C = 0;MOTO54D = 0;break;
				case 3:MOTO54A = 0;MOTO54B = 1;MOTO54C = 1;MOTO54D = 0;break;
				case 4:MOTO54A = 0;MOTO54B = 0;MOTO54C = 1;MOTO54D = 0;break;
				case 5:MOTO54A = 0;MOTO54B = 0;MOTO54C = 1;MOTO54D = 1;break;
				case 6:MOTO54A = 0;MOTO54B = 0;MOTO54C = 0;MOTO54D = 1;break;
				case 7:MOTO54A = 1;MOTO54B = 0;MOTO54C = 0;MOTO54D = 1;break;
			}
			break;
	}
}
