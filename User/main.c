/************************************************************************************
   
�������ƣ� ������Ƶ��18.432MHz�� 
����˵��: ͨ������3���͡�Everything is possible!��  
          ������9600������λ8����żЧ���ޣ�ֹͣλ1��������������  
************************************************************************************/
#include "stc15f2k60s2.h"	    // ��Ƭ��STC15F2K60S2ͷ�ļ�,���Բ��ټ���reg51.h
#include <intrins.h>					// �����ͷ�ļ���,��ʹ��_nop_�⺯��
#include "delay.h"		        // ��ʱ����ͷ�ļ�
#include "uart.h"		        	// ����ͨ�ź���ͷ�ļ�
#define  uint unsigned int  
#define  uchar unsigned char	
#include <stdio.h>
#include <string.h>
uint weishu1,weishu2,weishu3,weishu4;
uchar buf1[100];
uchar buf2[100];
uchar buf3[100];
uchar buf4[100];
uint temp1,temp2,temp3,temp4;




//sbit x0 = P4^3;
//sbit x1 = P4^4; 
//sbit x2 = P2^0; 
//sbit x3 = P2^1;  
//sbit x4 = P2^2;  
//sbit x5 = P2^3;
//sbit x6 = P2^4; 
//sbit x7 = P2^5;
//sbit x10 = P2^6;
//sbit x11 = P2^7; 
//sbit x12 = P4^5;
//sbit x13 = P4^6;

sbit x0 = P2^4; 
sbit x1 = P2^5; 


sbit x2 = P2^6;  
sbit x3 = P2^7;

sbit x4 = P4^5; 
sbit x5 = P4^6;

sbit x6 = P0^2;
sbit x7 = P0^3; 

sbit x8 = P0^4; 
sbit x9 = P5^2;




sbit y0 = P2^3;  
sbit y1 = P2^2;	
sbit y2 = P2^1;
sbit y3 = P2^0;
sbit y4 = P4^4;
sbit y5 = P4^3;



void printf2(char *puts)
{
	 while(*puts) 
	{
		sendbyte2(*puts);
		puts++;
	}
}

void io_inint()
{
	P0M1 = 0;	P0M0 = 0;	//����P0.0~P0.7Ϊ׼˫���
	P1M1 = 0;	P1M0 = 0;	//����P1.0~P1.7Ϊ׼˫���
	P2M1 = 0;	P2M0 = 0;	//����P2.0~P2.7Ϊ׼˫��� 
	P3M1 = 0;	P3M0 = 0;	//����P3.0~P3.7Ϊ׼˫���
	P4M1 = 0;	P4M0 = 0;	//����P4.0~P4.7Ϊ׼˫���
	P5M1 = 0;	P5M0 = 0;	//����P5.0~P5.7Ϊ׼˫���
}




int xinget(int zhi)
{
	if(zhi==0) return x0;
	if(zhi==1) return x1;
	if(zhi==2) return x2;
	if(zhi==3) return x3;
	if(zhi==4) return x4;
	if(zhi==5) return x5;
	if(zhi==6) return x6;
	if(zhi==7) return x7;
	if(zhi==8) return x8;
	if(zhi==9) return x9;
}
void getxin()
{
	int i;
	char datatmp[10];
	for(i=0;i<10;i++)
	{
		sprintf(datatmp,"x%d %d\n",i,xinget(i));
		PrintString(datatmp);
	}
}
void delay_ms(int m)
{
	int x,y;
	for(x=m;x>0;x--)
	for(y=220;y>0;y--);
}

void main()		                                       
{
	
	io_inint();
	Uart23Init();
	
	
	Timer0Init();
	UartInit();
	
	Uart4Init();
	while (1)
	{
		delay_ms(100);
		PrintString("12345");
		sendbyte3('a');	
	}
}
	 
	 

	 
	 
uint time,lv_bo;
void Timer0() interrupt 1
{
	
}
char buffxxx[100]="";
char buffweizhi=0;
void dealrecI(char c)
{
	
}
void UARTInterrupt(void) interrupt 4
{
	char downstr;
	if (RI)
	{
		RI = 0;
		
	}
	else
	{
		TI = 0;
	}
	if (TI) //�����ж�..
	{
		TI = 0;
	}
}

void uart2(void ) interrupt 8 
{
  if (S2CON & S2RI)
	{
		S2CON &= ~S2RI;         
		temp2 = S2BUF;
	}
  if (S2CON & S2TI)
    {
			//y1=0;
        S2CON &= ~S2TI;         //���S2TIλ
        busy2 = 0;               //��æ��־
    }  
}

  


void Uart3() interrupt 17 using 1
{
    if (S3CON & S3RI)
    {
        S3CON &= ~S3RI;         //??S3RI?
        temp3 = S3BUF;
				
   }
if (S3CON & S3TI)
    {
        S3CON &= ~S3TI;         //���S3TIλ
        busy3 = 0;               //��æ��־
    }
}

void Uart4() interrupt 18 
{
    if (S4CON & S4RI)
    {
        S4CON &= ~S4RI;         //??S4RI?
        temp4=S4BUF;
   }
if(TI4)
	{
		CLR_TI4();
		busy4 = 0;               //��æ��־
	}
}



