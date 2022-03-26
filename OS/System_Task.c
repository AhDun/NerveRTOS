/*------------------------------------------------------------------------------------------------------------------------
 * �ļ����ƣ�System_Task.c

 * �ļ����ݣ�ϵͳ����API

 * �ļ��汾��1.0.0

 * �ļ����ߣ�����ʵ����

 * ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5 

 * ע    �⣺
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����ͷ�ļ���
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//������
#include "System_Control.h"
#include "System_Task.h"
#include "System_Clock.h"
#include "Timer.h"
/*------------------------------------------------------------------------------------------------------------------------
                                                  ������ʼ����
------------------------------------------------------------------------------------------------------------------------*/
u8 xdata AQSP = NULL;//���������ָ��
u8 xdata BQSP = NULL;//���������ָ��
#ifdef EnableECF
u8 xdata TaskDMax = NULL;//���������
#endif
u8 xdata PlanTaskId = NULL;//��һ��Ҫ���е�����ID
u8 xdata SP0 = NULL;//��ʼ��ջָ��
u8 xdata RunAppID = NULL;//�����������ID
u8 xdata RunAppPy = NULL;//��������������ȼ�
u8 xdata SnLock = NULL; //�����л���
u8 xdata AppRunTimer = NULL;
u16 xdata TPC = NULL;//�����ʼ��ַ
u16 xdata TaskEndAddr = NULL;//�����Զ���ֹʱ�����صĵ�ַ
u8 xdata TimerIRQTouchType  = NULL;//��ʱ���жϴ�������

u8 xdata Pstack[TaskMax][MaxStackDepth] = {NULL};//ջ��
taskqueue TaskQueue[TaskQueueMax + 2] = {NULL};//������б�
TASKINFO TaskInfo[TaskMax] = {NULL};//������Ϣ��
u8 xdata TaskInterruptQueue[TaskQueueMax + 2] = {NULL};//�ж��������
u8 stack0[StackBuffer] = {NULL};//ջ������
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskLoad

 * �������ܣ�ע������

 * ���������TaskId(Ӧ��ID) TaskType(��������) PY(�������ȼ�) TaskM(�������) TaskPC(������)

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void TaskLoad(u8 TaskId,u8 TaskType,u8 PY,u16 TaskM,u16 TaskPC) reentrant
{
	System_IMS_Disable;//�ر����ж�
	TaskInfo[TaskId].Py0 = PY;//�������ȼ�
	TaskInfo[TaskId].Py1 = PY;//�������ȼ�
	TaskInfo[TaskId].Type = TaskType;//��������
	TaskInfo[TaskId].TPC = TaskPC;//�����ַ
	/*��TaskType������ʱ�����ж�Ϊ����������*/
	if(TaskType)
	{
		TaskInfo[TaskId].Pa0 = TaskInfo[TaskId].Pa1 = NULL;//������ֵ//������������Ϣ
	}
	/*������ʱ�����ж�Ϊ��ʱ������*/
	else
	{
		TaskInfo[TaskId].Pa0 = TaskInfo[TaskId].Pa1 = TaskM;//������ֵ//��ʱ��������Ϣ
	}
	#ifdef EnableECF
	if(TaskId >= TaskDMax )//��ȡ���ֵ
	{
			TaskDMax  = TaskId;
	}
	#endif
	System_IMS_Enable;//�������ж�
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskRemove

 * �������ܣ�ע������

 * ���������TaskId(Ӧ��ID)

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void TaskRemove(u8 TaskId) reentrant
{
	#ifdef EnableECF
	u8 R0;
	#endif
	System_IMS_Disable;//�ر����ж�
	TaskInfo[TaskId].Py0 = NULL;//�������ȼ�
	TaskInfo[TaskId].Py1 = NULL;//�������ȼ�
	TaskInfo[TaskId].Type = NULL;//��������
	TaskInfo[TaskId].Pa0 = NULL;//������ֵ
	TaskInfo[TaskId].Pa1 = NULL;//������ֵ
	#ifdef EnableECF
	for(R0 = TaskMax;R0 > NULL ;R0--)//���¼������ֵ 
	{
		if(TaskInfo[R0].Py0 == NULL)
		{
			TaskDMax = R0 - 1;
			break;
		}
	}
	#endif
	System_IMS_Enable;//�������ж�
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�MgQueue

 * �������ܣ����й���

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
#ifdef EnableQueueCheck
void MgQueue() reentrant 
{
 	u8 MgQ_F0;
																										/*��������*/
	if(TaskQueue[NULL].ID == NULL && AQSP > NULL || // 1.������ͷ��û�����ݣ�������ָ�������ʱ
		 TaskQueue[AQSP].ID != NULL || // 							 2.������ָ�룬ָ��Ķ������ݣ���Ϊ��ʱ
		 AQSP > TaskQueueMax)//													 3.������ָ����ڶ��еĳ���ʱ
	{
		AQSP = NULL;//���ж���ָ������
		/*���ж���ָ��У׼���Ӻ���ǰ����У׼*/
		for(MgQ_F0 = TaskQueueMax;MgQ_F0 >= NULL;MgQ_F0--)
		{
			/*��ǰ����ָ��ָ������ݲ�Ϊ�㣬��һ��ָ��ָ��ָ������Ϊ��ʱ������*/
			 if(TaskQueue[MgQ_F0].ID != NULL && TaskQueue[MgQ_F0 + 1].ID == NULL)
			 {
				  AQSP = MgQ_F0 + 1;//����ָ�������
				  break;
			 }	
			 /*û�д�������ʱ����������*/
			 else if(MgQ_F0 == NULL)
			 	break;
		}
	}
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskInterruptQueue_write

 * �������ܣ�д�ж��������

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void TaskInterruptQueue_write()
{
	u8 AQISP1;
	for(AQISP1 = NULL;AQISP1 < TaskQueueMax;AQISP1++)
	{
		/*��ָ��ָ��������뵱ǰ��������ID��ͬʱ������ָ��ָ�������Ϊ��ʱ������*/
		if(TaskInterruptQueue[AQISP1] == RunAppID ||TaskInterruptQueue[AQISP1] == 0)//���������һλ
		{
			/*����ǰ��������ID��д�뵽������*/
			TaskInterruptQueue[BQSP] = RunAppID;
			BQSP++;//ָ���һ
			break;//��������
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskQueue_write

 * �������ܣ�д�������

 * ���������TaskID(Ӧ��ID)Py(�������ȼ�)

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void TaskQueue_write(u8 TaskID,u8 Py) reentrant
{
 	u8 AQSP1,AQSP2;//�������
	if(Py > RunAppPy && RunAppID > NULL && ProTime == NULL)
	{
		TaskInterruptQueue_write();//д�뵽�ж����������
		PlanTaskId = TaskID;//������ID���ص�
		RunAppPy = TaskInfo[PlanTaskId].Py1;
		TPC = TaskInfo[PlanTaskId].TPC;
		SnLock = Locking;//�����л���������
		TimerIRQTouchType = Task_Touch;//��ϵͳ�жϴ���������Ϊ���񴥷�
	}
	else
	{
		#ifdef EnableQueueCheck
		MgQueue();//���ж��й���
		#endif
		if(AQSP < TaskQueueMax)//������ָ��С��������е���󳤶�ʱ���ſ���д��
		{
			 AQSP1 = NULL;
			 while(AQSP1 < TaskQueueMax)//������ָ�����������е���󳤶�ʱ��ֹͣд��
			 {
				 if(TaskQueue[AQSP1].Py >= Py)
					AQSP1++;
				 else
				 {
					 for(AQSP2 = AQSP;AQSP2 > AQSP1;AQSP2--)//���������һλ
					 {
						 TaskQueue[AQSP2] = TaskQueue[AQSP2 - 1];
					 }
					 TaskQueue[AQSP1].ID = TaskID;//д��Ӧ��ID
					 TaskQueue[AQSP1].Py = Py;//д���������ȼ�
					 AQSP++;//����ָ���һ
					 break;//�˳�ѭ��
				 }
			 }
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskQueue_read

 * �������ܣ����������

 * �����������

 * �������������ID

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
u8 TaskQueue_read() reentrant
{
 	u8 Aqw_F0,Aqw_temp;
	/*���ж��Ͷ��У���Ϊ��ʱ�������*/
	if(TaskInterruptQueue[NULL] > NULL)
	{
		Aqw_temp = TaskInterruptQueue[NULL];//��������ID
		RunAppPy = TaskInfo[Aqw_temp].Py1;//���������س�ʼ���ȼ�
		/*������ǰ��һλ*/
		for(Aqw_F0 = NULL;Aqw_F0 < BQSP;Aqw_F0++)
		{
			TaskInterruptQueue[Aqw_F0] = TaskInterruptQueue[Aqw_F0 + 1];
		}
		TaskInterruptQueue[Aqw_F0] = NULL;//������һλ
		if(BQSP > NULL)//����
		{
			BQSP--;//����ָ���һ
		}
		return Aqw_temp;//����Ӧ��ID
	}
	else
	{
		#ifdef EnableQueueCheck
		MgQueue();//���ж��й���
		#endif
		/*��������У���Ϊ��*/
		if(TaskQueue[NULL].ID > NULL)
		{
			Aqw_temp = TaskQueue[NULL].ID;//���������װ������ID
			RunAppPy = TaskQueue[NULL].Py;//���������װ�������ʼ���ȼ�
		}
		else
		{
			Task0Time = Task0TimeSize;//����0���¼���
			RunAppPy = NULL;//������ȼ�
			return false;//���ؼ�
		}
		for(Aqw_F0 = NULL;Aqw_F0 < AQSP;Aqw_F0++)//������ǰ��һλ
		{
			TaskQueue[Aqw_F0] = TaskQueue[Aqw_F0 + 1];
		}
		TaskQueue[Aqw_F0].Py = TaskQueue[Aqw_F0].ID = NULL;//������һλ
		if(AQSP > NULL)//����
		{
			AQSP--;//����ָ���һ
		}
		return Aqw_temp;//����Ӧ��ID
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskRPlanTaskId

 * �������ܣ�ˢ�µȴ�Ӧ��Id

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void TaskRPlanTaskId()
{
	PlanTaskId = TaskQueue_read();//��������ж�ȡ����ID
	TPC = TaskInfo[PlanTaskId].TPC;//��������ID��ȡ����ĳ�ʼ��ַ
	/*��ǰ����ĳ�ʼ���ȼ�С��0x0Aʱ�����м�һ*/
	if(TaskInfo[PlanTaskId].Py1 < 0x0A)
	{
		TaskInfo[PlanTaskId].Py1--;
	}
	/*��ǰ����ĳ�ʼ���ȼ�������ʱ���������ȼ�*/
	if(TaskInfo[PlanTaskId].Py1 == NULL)
	{
		TaskInfo[PlanTaskId].Py1 = TaskInfo[PlanTaskId].Py0;
	}
	SnLock = Locking;//�����л���������
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TypeTaskStartup

 * �������ܣ�������������

 * ���������TYPE(����)

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void TypeTaskStartup(u8 TYPE) reentrant 
{
 	u8 TTS_F0;
	#ifdef EnableECF
	for(TTS_F0 = NULL;TTS_F0 <= TaskDMax ; TTS_F0++)//ʹ��for�����б���
	#else
	for(TTS_F0 = NULL;TTS_F0 <= TaskMax ; TTS_F0++)//ʹ��for�����б���
	#endif
	{
		if(TaskInfo[TTS_F0].Type == TYPE && TaskInfo[TTS_F0].Py1 > NULL)//�뵱ǰ�����¼�ID��ͬ
		{
			TaskQueue_write(TTS_F0,TaskInfo[TTS_F0].Py1);//ע��ID
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�OpenTask

 * �������ܣ�������������

 * ���������TaskID(Ӧ��ID)

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void OpenTask(u8 TaskID) reentrant
{
	if(TaskInfo[TaskID].Py1 > NULL)
	{
		TaskQueue_write(TaskID,TaskInfo[TaskID].Py1);//ע��ID
	}
	else
	{
		TaskQueue_write(TaskID,Task_Class_L9);//ע��ID
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�OpenTaskS

 * �������ܣ������ȼ�������������

 * ���������TaskID(Ӧ��ID) Py(�������ȼ�)

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void OpenTaskS(u8 TaskID,u8 Py) reentrant
{
		TaskQueue_write(TaskID,Py);//ע��ID
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskSwitchIf

 * �������ܣ�����IDˢ������

 * �����������

 * ���������0:������ 1:����

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
u2 TaskSwitchIf()
{
		/*�����ǰ���е��������ȼ�С���������ͷ�����ȼ�ʱ���򷵻���*/
		if(RunAppPy < TaskQueue[NULL].Py)
		{
			return true;
		}
		/*�ж���������в�Ϊ��ʱ�������*/
		else if (TaskInterruptQueue[NULL] > NULL)
		{
			/*��ѯ�ж����������ͷ��������ID�����ȼ��������ȼ����ڵ�ǰ������������ȼ����򷵻���*/
			if(RunAppPy < TaskInfo[TaskInterruptQueue[0]].Py1)
				return true;
			else
				return false;//���ؼ�
		}
		else
			return false;//���ؼ�
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�EnableProtection

 * �������ܣ�������������

 * ���������r1(����ʱ��-��λms)

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void EnableProtection(u16 r1)
{
	/*r1ֵ���ص�����ֵ*/
	ProTime = r1;
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�DisableProtection

 * �������ܣ��ر���������

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void DisableProtection()
{
	/*���㱣��ֵ*/
	ProTime = NULL;
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�TaskEnd

 * �������ܣ������������

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void TaskEnd()
{
	TimerIRQTouchType = Task_End_Touch;
	System_Timer_Touch;
	while(true);
}
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/