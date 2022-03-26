/*********************************************************************************************************
* �ļ����ƣ�GPIO.h
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
#ifndef __GPIO_h_
#define __GPIO_h_

#define PIO 0x00
#define PSIO 0x01
#define XIO 0x02
#define OIO 0x03

#define P0S 100
#define P1S 110
#define P2S 120
#define P3S 130

#define UART1IO 0x06
#define CCPIO 0x04
#define SPIIO 0x02
#define I2CIO 0x14
#define CMPOIO 0x13
#define UART4IO 0x12
#define UART3IO 0x11
#define UART2IO 0x10
#define MCLKOIO 0x23
#define PWM0IO 0x33
#define PWM1IO 0x43
#define PWM2IO 0x53
#define PWM3IO 0x63
#define PWM4IO 0x73
#define PWM5IO 0x83
#define PWM6IO 0x93
#define PWM7IO 0xA3

void IOSW(u8 IOm,u8 Mode);
void IOMode(u8 IOm,u8 Mode);
void IOPU(u8 IOm,u8 Mode);
void IONCS(u8 IOm,u8 Mode);

#endif
