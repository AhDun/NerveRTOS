/*********************************************************************************************************
* �ļ����ƣ�PCA.h
* ժ    Ҫ��PCA
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
#ifndef __PCA_h_
#define __PCA_h_

void PCAAppMain();
void PCA0AppMain();
void PCA1AppMain();
void PCA2AppMain();
void PCA3AppMain();

extern u8 xdata cnt;//�洢PCA��ʱ�������
extern u32 xdata Count0[4];//������
extern u32 xdata Count1[4];//������
extern u32 xdata length[4];//����(us) 
                      
void PCAInit();
void PCA0Init();
void PCA1Init();
void PCA2Init();
void PCA3Init();
//void PCAInterrupt() interrupt 7;

#endif
