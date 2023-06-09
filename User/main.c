/************************************************************************************

程序名称： （晶振频率18.432MHz）
功能说明: 通过串口3发送“Everything is possible!”
		  波特率9600，数据位8，奇偶效验无，停止位1，数据流控制无
************************************************************************************/
#include "stc15f2k60s2.h" // 单片机STC15F2K60S2头文件,可以不再加入reg51.h
#include <intrins.h>	  // 加入此头文件后,可使用_nop_库函数
#include "delay.h"		  // 延时函数头文件
#include "uart.h"		  // 串行通信函数头文件
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
	P0M0 = 0; // 设置P0.0~P0.7为准双向口
	P1M1 = 0;
	P1M0 = 0; // 设置P1.0~P1.7为准双向口
	P2M1 = 0;
	P2M0 = 0; // 设置P2.0~P2.7为准双向口
	P3M1 = 0;
	P3M0 = 0; // 设置P3.0~P3.7为准双向口
	P4M1 = 0;
	P4M0 = 0; // 设置P4.0~P4.7为准双向口
	P5M1 = 0;
	P5M0 = 0; // 设置P5.0~P5.7为准双向口
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
void buildsendshuju(int dianliu)
{
	int dianya=2047;
	char dataxx[100]={0};
	sprintf(dataxx,"AB%04dE%04dC%04dV%04dB10#",dianya,dianliu,4095-dianliu,4095-dianya);
	printf("%s",dataxx);
	print4(dataxx);
}
void runningcheck()
{
	if(xiugaiflag==0)
	{
		return ;
	}
	xiugaiflag=0;
	printf("get xiugairec %d\r\n",xiugairec);
	buildsendshuju(xiugairec);
}
// void jisuan1()
// {
	
// }
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
		if (timeleft3 == 0) // 数据一次收完了.
		{
			chuankou3jisuan();
		}
	}
}

void chuankou1put(char c)
{
	buf1[weishu1++] = c;
	if (weishu1 > 80)
		weishu1 = 0;
	timeleft1 = 20;
}
void chuankou1jisuan()
{
	// PrintString(buf1);
	// jisuandianliu(buf1);
	memset(buf1, 0, sizeof(buf1));
	weishu1 = 0;
}
void chuankou1time()
{
	if (timeleft1 > 0)
	{
		timeleft1--;
		if (timeleft1 == 0) // 数据一次收完了.
		{
			chuankou1jisuan();
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
		chuankou1put(SBUF);
	}
	else
	{
		TI = 0;
	}
	if (TI) // 发送中断..
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
		S2CON &= ~S2TI; // 清除S2TI位
		busy2 = 0;		// 清忙标志
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
		S3CON &= ~S3TI; // 清除S3TI位
		busy3 = 0;		// 清忙标志
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
		busy4 = 0; // 清忙标志
	}
}
