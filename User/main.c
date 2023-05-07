/************************************************************************************

�������ƣ� ������Ƶ��18.432MHz��
����˵��: ͨ������3���͡�Everything is possible!��
		  ������9600������λ8����żЧ���ޣ�ֹͣλ1��������������
************************************************************************************/
#include "stc15f2k60s2.h" // ��Ƭ��STC15F2K60S2ͷ�ļ�,���Բ��ټ���reg51.h
#include <intrins.h>	  // �����ͷ�ļ���,��ʹ��_nop_�⺯��
#include "delay.h"		  // ��ʱ����ͷ�ļ�
#include "uart.h"		  // ����ͨ�ź���ͷ�ļ�
#define uint unsigned int
#define uchar unsigned char
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
				
// sbit x0 = P4^3;
// sbit x1 = P4^4;
// sbit x2 = P2^0;
// sbit x3 = P2^1;
// sbit x4 = P2^2;
// sbit x5 = P2^3;
// sbit x6 = P2^4;
// sbit x7 = P2^5;
// sbit x10 = P2^6;
// sbit x11 = P2^7;
// sbit x12 = P4^5;
// sbit x13 = P4^6;

sbit x0 = P2 ^ 4;
sbit x1 = P2 ^ 5;

sbit x2 = P2 ^ 6;
sbit x3 = P2 ^ 7;

sbit x4 = P4 ^ 5;
sbit x5 = P4 ^ 6;

sbit x6 = P0 ^ 2;
sbit x7 = P0 ^ 3;

sbit x8 = P0 ^ 4;
sbit x9 = P5 ^ 2;

sbit y0 = P2 ^ 3;
sbit y1 = P2 ^ 2;
sbit y2 = P2 ^ 1;
sbit y3 = P2 ^ 0;
sbit y4 = P4 ^ 4;
sbit y5 = P4 ^ 3;

void printf2(char *puts)
{
	while (*puts)
	{
		sendbyte2(*puts);
		puts++;
	}
}

void io_inint()
{
	P0M1 = 0;
	P0M0 = 0; // ����P0.0~P0.7Ϊ׼˫���
	P1M1 = 0;
	P1M0 = 0; // ����P1.0~P1.7Ϊ׼˫���
	P2M1 = 0;
	P2M0 = 0; // ����P2.0~P2.7Ϊ׼˫���
	P3M1 = 0;
	P3M0 = 0; // ����P3.0~P3.7Ϊ׼˫���
	P4M1 = 0;
	P4M0 = 0; // ����P4.0~P4.7Ϊ׼˫���
	P5M1 = 0;
	P5M0 = 0; // ����P5.0~P5.7Ϊ׼˫���
}

int xinget(int zhi)
{
	if (zhi == 0)
		return x0;
	if (zhi == 1)
		return x1;
	if (zhi == 2)
		return x2;
	if (zhi == 3)
		return x3;
	if (zhi == 4)
		return x4;
	if (zhi == 5)
		return x5;
	if (zhi == 6)
		return x6;
	if (zhi == 7)
		return x7;
	if (zhi == 8)
		return x8;
	if (zhi == 9)
		return x9;
}
void getxin()
{
	int i;
	char datatmp[10];
	for (i = 0; i < 10; i++)
	{
		sprintf(datatmp, "x%d %d\n", i, xinget(i));
		PrintString(datatmp);
	}
}
void delay_ms(int m)
{
	int x, y;
	for (x = m; x > 0; x--)
		for (y = 220; y > 0; y--)
			;
}

int xiugaiflag=0;
int xiugairec=0;
void jisuandianliu(char *p)
{
	char* index;
	int ans;
	index=strstr(p,"setdianliu");
	if(index==0)
	{
		return  ;
	}
	ans=atoi(index+strlen("setdianliu"));
	if(ans==-1)
	{
		return;
	}
	xiugaiflag=1;
	xiugairec=ans;
}
void runningcheck()
{
	if(xiugaiflag==0)
	{
		return ;
	}
	xiugaiflag=0;
	printf("get xiugairec %d",xiugairec);

}
void main()
{
	char shuju[100]="sdsdsd:setdianliu760";
int ans;
	io_inint();
	Uart23Init();

	Timer0Init();
	UartInit();

	Uart4Init();

	while (1)
	{
		delay_ms(100);
		// ans=jisuandianliu(shuju);
		runningcheck();
		// printf("ans %d",ans);
		// PrintString("12345");
		// sendbyte3('a');
	}
}




uint weishu1, weishu2, weishu3, weishu4;
char buf1[100];
char buf2[100];
char buf3[100];
char buf4[100];
char temp1, temp2, temp3, temp4;


int timeleft1, timeleft2, timeleft3, timeleft4;
void chuankou3put(char c)
{
	buf3[weishu3++] = c;
	if (weishu3 > 80)
		weishu3 = 0;
	timeleft3 = 20;
}
void chuankou3jisuan()
{
	// PrintString(buf3);
	jisuandianliu(buf3);
	memset(buf3, 0, sizeof(buf3));
	weishu3 = 0;
}
void chuankou3time()
{
	if (timeleft3 > 0)
	{
		timeleft3--;
		if (timeleft3 == 0) // ����һ��������.
		{
			chuankou3jisuan();
		}
	}
}
void Timer0() interrupt 1
{
	chuankou3time();
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
	if (TI) // �����ж�..
	{
		TI = 0;
	}
}

void uart2(void) interrupt 8
{
	if (S2CON & S2RI)
	{
		S2CON &= ~S2RI;
		temp2 = S2BUF;
	}
	if (S2CON & S2TI)
	{
		// y1=0;
		S2CON &= ~S2TI; // ���S2TIλ
		busy2 = 0;		// ��æ��־
	}
}

void Uart3() interrupt 17 using 1
{
	if (S3CON & S3RI)
	{
		S3CON &= ~S3RI; //??S3RI?
		temp3 = S3BUF;
		chuankou3put(temp3);
	}
	if (S3CON & S3TI)
	{
		S3CON &= ~S3TI; // ���S3TIλ
		busy3 = 0;		// ��æ��־
	}
}

void Uart4() interrupt 18
{
	if (S4CON & S4RI)
	{
		S4CON &= ~S4RI; //??S4RI?
		temp4 = S4BUF;
	}
	if (TI4)
	{
		CLR_TI4();
		busy4 = 0; // ��æ��־
	}
}
