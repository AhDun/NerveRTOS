/*------------------------------------------------------------------------------------------------------------------------
 * �ļ����ƣ�System_Uart.h

 * �ļ����ݣ�ϵͳ�����ں�

 * �ļ��汾��1.0.0

 * �ļ����ߣ�����ʵ����

 * ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5 

 * ע    �⣺
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  ���ظ������������
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __System_Uart_h_
#define __System_Uart_h_

/*------------------------------------------------------------------------------------------------------------------------
                                                  �궨����
------------------------------------------------------------------------------------------------------------------------*/
#define UART_DAT_Max 128//���ڻ�������������󳤶�
#define UART_TIMES 5//��Ӧʱ�䣨ms��
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����������
------------------------------------------------------------------------------------------------------------------------*/
extern u8 xdata UART_DAT[UART_DAT_Max];//���ڻ�����
extern u8 xdata UART_XDAT_SP;//UART_DAT_SPָ��
extern u8 xdata UART_SKL;

/*------------------------------------------------------------------------------------------------------------------------
                                                  ����������
------------------------------------------------------------------------------------------------------------------------*/
extern void SUARTAppMain();
extern void AUARTAppMain();
extern void Systme_UART_Handle();
extern void Systme_UART_Input();

extern s16 CMD_COMP(const char* a,const char *b);
extern void UARTCMD_Help(const u8 *a);
extern void UARTSystemCmd();
extern void UARTCMD_OUTUART1();
extern void UARTCMD_QueryRunTime();
extern void UARTCMD_INFO();
extern void UARTCMD_ISP();
extern void UARTCMD_RST();
extern void UARTCMD_OPENTU();
extern void UARTCMD_OFFTU();
extern void UARTCMDError();
extern void UARTCMD_OFFTASK();
extern void UARTCMD_POWERIDL();
extern void UARTCMD_POWERPD();
extern void UARTCMD_POWERLOW();
extern void UARTCMD_POWERHIGH();
extern void UARTCMD_OFFWDT();
extern void UARTCMD_OPENWDT();
extern void UARTCMD_OPENTASKAPP();
extern void UARTCMD_OPENAPP();
extern void UARTCMD_SAU();
extern void UARTCMD_PQueryTask();
extern void UARTCMD_QuerySystemTime();
extern void MonitorOutUART();

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/