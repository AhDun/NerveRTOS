/*********************************************************************************************************
* 文件名称：74HC138.h
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
#ifndef __74HC138_h_
#define __74HC138_h_

sbit A_74HC138 = P1^0;
sbit B_74HC138 = P1^1;
sbit C_74HC138 = P1^2;

void SendByte138(u8 dat);

#endif
