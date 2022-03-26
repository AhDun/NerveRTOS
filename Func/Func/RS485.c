/*********************************************************************************************************
* 文件名称：RS485.c
* 摘    要：
* 当前版本：1.0.0
* 作    者：麦特实验室
* 完成日期：
* 内    容：
* 注    意：
* 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5                                                                 
**********************************************************************************************************
* 取代版本：
* 作    者：
* 完成日期：
* 修改内容：
* 修改文件：
*********************************************************************************************************/

#include"Basic.h"
#include"RS485.h"

///********************************
//函数名称:UART3Init
//函数功能:串口3初始化
//输入参数:
//输    入:
//输出参数:
//输    出:
//********************************/
//void UART3Init()
//{
// 	S3CON |= 0x50;//串口3选择定时器3为波特率发生器，启动串行接收器
//	S3CON &= 0x70;//8位数据,可变波特率
//	T3H = (65536-(MainFosc / 12 / 4 / S3Bps)) /256;
//	T3L = (65536-(MainFosc /  12 / 4 / S3Bps)) %256;
//	T4T3M |= 0x08;//允许定时器3运行
//	IE2 |= 0x08;// 串口3中断打开
//	IE2 &= 0xDF;// 关闭定时器3中断
//	EA = 1;
//}
///********************************
//函数名称:UART3Inerrupt
//函数功能:串口3中断服务
//输入参数:
//输    入:
//输出参数:
//输    出:
//********************************/
//void UART3Interrupt() interrupt 17 using 1
//{
//	IE2 &= 0xF7;// 串口3中断关闭
//	if (S3CON & 0x01)//串行接收到停止位的中间时刻时，该位置1
//  	{
//      	S3CON &= 0xFE;//清除S3CON寄存器对应S3RI位
//	  	temp1 = S3BUF;//把串口3缓存SBUF寄存器数据存放到数组temp1中
//	  	uart3_rflage = 1; 		
//   	}
//   	if (S3CON & 0x02)//在停止位开始发送时，该位置1
//   	{
//      	S3CON &= 0xFD;//清除S3CON寄存器对应S3TI位
//   	}
//	IE2 |= 0x08;// 串口3中断打开
//}
/********************************
函数名称:RS485_R
函数功能:RS485设为接收模式
输入参数:
输    入:
输出参数:
输    出:
********************************/
void RS485_R()
{
	RS485_DIR = 0;			
}
/********************************
函数名称:RS485_T
函数功能:串口3中断服务
输入参数:RS485设为发送模式
输    入:
输出参数:
输    出:
********************************/
void RS485_T()
{
	RS485_DIR = 1;	
}
