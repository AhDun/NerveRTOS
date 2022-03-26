/*********************************************************************************************************
* �ļ����ƣ�ADC.h
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
#ifndef __ADC_h_
#define __ADC_h_

#define ADC_P10 0x00
#define ADC_P11	0x01
#define ADC_P12	0x02
#define ADC_P13	0x03
#define ADC_P14	0x04
#define ADC_P15	0x05
#define ADC_P16 0x06
#define ADC_P17 0x07
#define ADC_P00 0x08
#define ADC_P01 0x09
#define ADC_P02 0x0A
#define ADC_P03 0x0B
#define ADC_P04 0x0C
#define ADC_P05 0x0D
#define ADC_P06 0x0E
#define ADC_S 0x0F

extern u8 xdata ADCBusy;

void ADCAppMain();
void delay_ADC();
void ADC_Init();
u16 ADC_Read(u8 ADS);
//void ADCInterrupt() interrupt 5;	

#endif
