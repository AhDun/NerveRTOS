/*********************************************************************************************************
* �ļ����ƣ�At24c02App.h
* ժ    Ҫ��дAT24c02/��AT24c02/AT24c02���ַ���/AT24c02д�ַ���/ɾ��AT24c02��������
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
#ifndef __At24c02App_h_
#define __At24c02App_h_

#define I2CIFCON 0 //Ӳ��I2C
//#define I2CIFCON//���I2C


#define At24c02Address 0xA0

#if I2CIFCON
	/*���I2C*/
	#define Start  I2cStart
	#define Stop   I2cStop
	#define SendByte I2cSendByte
	#define ReadByte I2cReadByte
	#define SendOk  I2cSendOk
#else
	/*Ӳ��I2C*/
	#define Start  SI2cStart
	#define Stop   SI2cStop
	#define SendByte SI2cSendByte
	#define ReadByte SI2cReadByte
	#define SendOk  SI2cSendOk
#endif
void delay_At24c02();
void At24c02Write(u8 addr,u8 dat);
u8 At24c02Read(u8 addr);
void outs_At24c02(u8 Flash_p,u8 *fp,u8 n);
void ins_At24c02(u8 Flash_p,u8 *fp,u8 n);
void Del_AT24c02();

#endif
