/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：StringApp.h 

 * 文件内容：

 * 文件版本：1.0.0

 * 文件作者：麦特实验室

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __StringApp_h_
#define __StringApp_h_

/*------------------------------------------------------------------------------------------------------------------------
                                                  函数声明区
------------------------------------------------------------------------------------------------------------------------*/
extern u2 SComp(const char *a,const char *b);
extern void SAa(char *a);
extern void ScC(char *a);
extern void SAa_lookup(char *a,char sdata);
extern void ScC_lookup(char *a,char sdata);
extern u8 SLookup(const char *a,char sdata);
extern u32 ASCII_DEC(const char *a);

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/