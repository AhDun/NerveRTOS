/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：UARTApp.c

 * 文件内容：串口功能函数

 * 文件版本：1.0.0

 * 文件作者：麦特实验室

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//基本库
#include "UARTApp.h"
#include "UART.h"
#include "delay_Lib.h"
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：Uart_Outs

 * 函数功能：串口输出字符串

 * 输入参数：*sdata(字符串)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void Uart_Outs(const char *sdata) reentrant
{
	while(1)
	{
	 	if(*sdata == 0)
			break;
		else if(*sdata == '\n')//发送换行指令
		{
			 UartOut(0x0D) ;//将数据送入发送寄存器中，自动发送
			 UartOut(0x0A);//将数据送入发送寄存器中，自动发送
		}
		else
			UartOut(*sdata);//将数据送入发送寄存器中，自动发送
		sdata++;//向后移动一位指针
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：Uart_Outchar

 * 函数功能：串口输出字符

 * 输入参数：sdata(字符串)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void Uart_Outchar(const u8 sdata)
{
	if(sdata == '\n')//发送换行指令
	{
		 UartOut(0x0D) ;//将数据送入发送寄存器中，自动发送
		 UartOut(0x0A);//将数据送入发送寄存器中，自动发送
	}
	else
		UartOut(sdata);//将数据送入发送寄存器中，自动发送
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：Uart_Outbin

 * 函数功能：串口二进制输出

 * 输入参数：sdata(字符)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void Uart_Outbin(const u8 sdata)
{
	u8 xdata OB_F0;
	for(OB_F0 = 0; OB_F0 < 8;OB_F0++)
	{
	 	 if(sdata & (0x80 >>OB_F0))
		 	Uart_Outchar('1');
		 else
		 	Uart_Outchar('0');	
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：Uart_Outnum

 * 函数功能：串口数字输出

 * 输入参数：sdata(数字)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void Uart_Outnum(const u32 sdata) reentrant
{
	 if((sdata / 10000000000) > 0)
	 	UartOut(sdata / 10000000000 + 48);//发送数据到串口1

	 if((sdata % 10000000000 / 1000000000) > 0)
	 	UartOut(sdata % 10000000000 / 1000000000 + 48);//发送数据到串口1

	 if((sdata % 1000000000 / 100000000) > 0)
	 	UartOut(sdata % 1000000000 / 100000000 + 48);//发送数据到串口1

	 if((sdata % 100000000 / 10000000) > 0)
	 	UartOut(sdata % 100000000 / 10000000 + 48);//发送数据到串口1

	 if((sdata % 10000000 / 1000000) > 0)
	 	UartOut(sdata % 10000000 / 1000000 + 48);//发送数据到串口1

	 if((sdata % 1000000 / 100000) > 0)
	 	UartOut(sdata % 1000000 / 100000 + 48);//发送数据到串口1

	 if((sdata % 100000 / 10000) > 0)
	 	UartOut(sdata % 100000 / 10000 + 48);//发送数据到串口1

	 if((sdata % 10000 / 1000) > 0)
	 	UartOut(sdata % 10000 / 1000 + 48);//发送数据到串口1

	 if((sdata % 1000 / 100) > 0)
	 	UartOut(sdata % 1000 / 100 + 48);//发送数据到串口1

	 if((sdata % 100 / 10) > 0)
	 	UartOut(sdata % 100 / 10 + 48);//发送数据到串口1
	
	 UartOut(sdata % 10+ 48);//发送数据到串口1

} 
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/