/*********************************************************************************************************
* �ļ����ƣ�Keyboard.c
* ժ    Ҫ�����������������
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
#include"Keyboard.h"
#include"Sdelay.h"

/********************************
��������:Keyboarddriver
��������:���������������
�������:
��    ��:
�������:��ֵ
��    ��:
********************************/
u8 Keyboarddriver()
{
	u8 keyvalue = 0xFF;
	keyboardIO = 0xF0;//��ɨ��
	if(keyboardIO != 0xF0)
	{
		delay_ms(20);
		if(keyboardIO != 0xF0)//�жϰ����Ƿ񱻰���
		{
			switch(keyboardIO) //�ж���һ�б�����
			{
				case 0xe0:	keyvalue = 0;break;//��һ�б�����
				case 0xd0:	keyvalue = 1;break;//�ڶ��б�����	
				case 0xb0:	keyvalue = 2;break;//�����б�����	
				case 0x70:	keyvalue = 3;break;//�����б����� 
			}
			keyboardIO = 0x0F;//��ɨ��
			switch(keyboardIO) //�ж���һ�б�����
			{
				case 0x0E:	keyvalue = keyvalue;break;//��һ�б�����
				case 0x0D:	keyvalue = keyvalue + 4;break;//�ڶ��б�����		
				case 0x0B:	keyvalue = keyvalue + 8;break;//�����б�����		
				case 0x07:	keyvalue = keyvalue + 12;break;//�����б�����	 
			}
		}
	}
	return keyvalue;
}
