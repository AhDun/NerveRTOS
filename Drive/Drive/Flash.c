/*********************************************************************************************************
* �ļ����ƣ�Flash.c
* ժ    Ҫ������Flash��/Flash�ֽڶ�/Flash�ֽ�д/Flash��������
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
#include"Flash.h"

/********************************
��������:Flash_Locked
��������:����Flash��
�������:
��    ��:
�������:
��    ��:
********************************/ 
void Flash_Locked()
{
	 IAP_CONTR = 0;//��ֹIAP/IAP����
     IAP_CMD = 0x00;//ȥ��IAP/IAP����
	 IAP_TRIG = 0x00;//��ֹIAP/IAP�����޴���
}
/********************************
��������:Flash_UnLock
��������:���Flash��
�������:
��    ��:
�������:
��    ��:
********************************/ 
void Flash_UnLock()
{
	IAP_TRIG = 0x5A;  //����0x5A������B9h��IAP/IAP�����Ĵ�����ÿ�ζ������
	IAP_TRIG = 0xA5;  //����0x5A��IAP/IAP������������������
}
/********************************
��������:Flash_read
��������:Flash�ֽڶ�
�������:addr(Flash��ַ)
��    ��:
�������:Flash��Ӧ��ַ���ֽ�����
��    ��:
********************************/
u8 Flash_read(u16 addr)
{
	 IAP_CONTR = IAP_CONTR_Data;//��IAP/IAP����
	 IAP_ADDRH = addr >> 8;//�͵�ַ���ֽ�
	 IAP_ADDRL = addr ; //�͵�ַ���ֽ�
	 IAP_CMD   = IAP_CMD_Read;//д�����������
	 Flash_UnLock();//���Flash��
	 _nop_();//�ȴ�Flash��ɲ���
	 addr = IAP_DATA;//��IAP_DATA�Ĵ����е����ݱ�������
     Flash_Locked();//����Flash�� 
	 return addr; //���ض���������
}
/********************************
��������:Flash_write
��������:Flash�ֽ�д
�������:addr(Flash��ַ)dat(д���ֽ�����)
��    ��:
�������:
��    ��:
********************************/ 
void Flash_write(u16 addr,u8 dat)
{
	 IAP_CONTR = IAP_CONTR_Data;//��IAP/IAP����
	 IAP_ADDRH = addr >> 8;//�͵�ַ���ֽ�
	 IAP_ADDRL = addr;//�͵�ַ���ֽ�
	 IAP_CMD  = IAP_CMD_Write;//д��д�������� 
	 IAP_DATA = dat;//д�����ݵ�IAP_DATA�Ĵ���
	 Flash_UnLock();//���Flash��
	 _nop_();//�ȴ�Flash��ɲ���
	 Flash_Locked();//����Flash��
}
/********************************
��������:Flash_erase
��������:Flash��������
�������:addr(Flash��ַ)
��    ��:
�������:
��    ��:
********************************/
void Flash_erase(u16 addr)
{
	 IAP_CONTR = IAP_CONTR_Data;//��IAP/IAP����	 
	 IAP_ADDRH = addr >> 8; //�Ͳ�����ַ���ֽ�
	 IAP_ADDRL = addr; //�Ͳ�����ַ���ֽ�
	 IAP_CMD = IAP_CMD_Erase;//д�������������
	 Flash_UnLock();//���Flash��
	 _nop_();//�ȴ�Flash��ɲ���
	 Flash_Locked();//����Flash��
}
