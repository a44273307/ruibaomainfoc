/************************************************************************************
   
程序名称： （晶振频率18.432MHz） 
功能说明: 通过串口3发送“Everything is possible!”  
          波特率9600，数据位8，奇偶效验无，停止位1，数据流控制无  
************************************************************************************/
#include "stc15f2k60s2.h"	    // 单片机STC15F2K60S2头文件,可以不再加入reg51.h
#include <intrins.h>					// 加入此头文件后,可使用_nop_库函数
#include "delay.h"		        // 延时函数头文件
#include "uart.h"		        	// 串行通信函数头文件
#define  uint unsigned int  
#define  uchar unsigned char	
uint weishu1,weishu2,weishu3,weishu4;
uchar buf1[100];
uchar buf2[100];
uchar buf3[100];
uchar buf4[100];

uint temp1,temp2,temp3,temp4;
uint num1,num2,num3,num4;
bit flag_in1,flag_in2,flag_in3,flag_in4,flag_in5;



int  tx,yan_shi,duibi_num; 
char jishu_sendcushu;

uint yanshi_num;
bit start_num,youliao,shangchuan_ok;
bit  saomiao_ok;
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

sbit x0 = P2^0; 
sbit x1 = P2^1;  
sbit x2 = P2^2;  
sbit x3 = P2^3;
sbit x4 = P2^4; 
sbit x5 = P2^5;
sbit x6 = P2^6;
sbit x7 = P2^7; 

/*****************输出*************/
//sbit y0 = P3^2;  
//sbit y1 = P3^3;	
//sbit y2 = P3^4;
//sbit y3 = P3^5;
//sbit y4 = P3^6;
//sbit y5 = P3^7;
//sbit y6 = P4^1;
//sbit y7 = P4^2;

//sbit run_led = P4^7;
sbit y0 = P4^4;  
sbit y1 = P4^3;	
sbit y2 = P4^2;
sbit y3 = P4^1;
sbit y4 = P3^7;
sbit y5 = P5^4;
//sbit y6 = P4^1;
//sbit y7 = P4^2;


#define stop x0
#define air_in x1
#define qg_up x2
#define qg_centre x3
#define qg_down x4
#define start x5 
#define time_in x6
#define sensor x7

#define time_out y0
#define qg1 y1
#define qg2 y2
#define count y5

bit start_num;
void delay_ms(int m)
{
	int x,y;
	for(x=m;x>0;x--)
	for(y=220;y>0;y--);
}


void open_scanner3()
{
	sendbyte3(0x16);
	sendbyte3(0x54);
	sendbyte3(0x0D);
}

void close_scanner3()
{
	sendbyte3(0x16);
	sendbyte3(0x55);
	sendbyte3(0x0D);
}


void printf2(char *puts)
{
	 while(*puts) 
	{
		sendbyte2(*puts);
		puts++;
	}
}

void saomiaoshangchuan()
{
	sendbyte2('B');
	sendbyte2('S');
	sendbyte2(' ');
	for(tx=0;tx<weishu3;tx++)
	{
		sendbyte2(buf3[tx]);
	}
	sendbyte2(';');
}

void saomiaoshangchuan_S1()
{
	sendbyte1('B');
	sendbyte1('S');
	sendbyte1(' ');
	for(tx=0;tx<weishu3;tx++)
	{
		sendbyte1(buf3[tx]);
	}
	sendbyte1(';');
}

void yahe_ok()
{
	sendbyte2('D');
	sendbyte2('A');
	sendbyte2(' ');
	//sendbyte2('L');
//	sendbyte2('1');
//	sendbyte2(',');
//	sendbyte2('0');
//	sendbyte2(',');
	for(tx=0;tx<weishu3;tx++)
	{
		sendbyte2(buf3[tx]);
	}
	sendbyte2(',');
	sendbyte2('0');
	sendbyte2(';');
}


void yahe_ok_S1()
{
	sendbyte1('D');
	sendbyte1('A');
	sendbyte1(' ');
	//sendbyte2('L');
//	sendbyte2('1');
//	sendbyte2(',');
//	sendbyte2('0');
//	sendbyte2(',');
	for(tx=0;tx<weishu3;tx++)
	{
		sendbyte1(buf3[tx]);
	}
	sendbyte1(',');
	sendbyte1('0');
	sendbyte1(';');
}


void cline_shuju()
{ 
	int i;
	for(i=0;i<30;i++)
	buf2[i]== ' ';
}
void io_inint()
{
	P0M1 = 0;	P0M0 = 0;	//设置P0.0~P0.7为准双向口
	P1M1 = 0;	P1M0 = 0;	//设置P1.0~P1.7为准双向口
	P2M1 = 0;	P2M0 = 0;	//设置P2.0~P2.7为准双向口 
	P3M1 = 0;	P3M0 = 0;	//设置P3.0~P3.7为准双向口
	P4M1 = 0;	P4M0 = 0;	//设置P4.0~P4.7为准双向口
	P5M1 = 0;	P5M0 = 0;	//设置P5.0~P5.7为准双向口
}


void key_sensor()
{
	if(!sensor && air_in && !qg_up)
	{
		delay_ms(50);
		if(!sensor && air_in && !qg_up)
		{
			youliao=1;
		}
	}
}

void key()
{
	if(!start)
	{
		delay_ms(50);
		if(!start)
		{
			start_num=1;
		}
	}
}

uint delay_c;


bit xiaya_daowei;
void main()		                                          // 主函数     
{
	
	io_inint();
	Uart23Init();
	
	
	
	
	while(!stop)
	{
		close_scanner3();
		delay_ms(100);
		close_scanner3();
		while(!stop);
	}
	Timer0Init();
	UartInit();
	
	Uart4Init();
////  while(1){
////		open_scanner3();
////		y5 = ~y5;
////		delay_ms(1000);
////		delay_ms(1000);
////		delay_ms(1000);
////		close_scanner3();
////		y5 = ~y5;
////		delay_ms(1000);
////		delay_ms(1000);
////		delay_ms(1000);
////		sendbyte2(2);
////		
////	}
	
	kaishi:
	start_num=0;
	youliao=0;
	y4=1;
	num2=0;
	num3=0;
	num4=0;

	weishu2=0;
	weishu3=0;
	weishu4=0;
	close_scanner3();
	//y5=0;
while(1)
 {
	 key_sensor();
	 while(youliao == 1){
		 open_scanner3();
		 for(delay_c=0;delay_c<100;delay_c++)
		 {
			 delay_ms(100);
			 if(num3==1) break;
		 }
		 if(num3==0){
			 close_scanner3();
			 youliao=0;
		 }
		 if(num3==1){
			 weishu2=0;
			 flag_in2=0;
			 saomiaoshangchuan();
			 saomiaoshangchuan_S1();
			 while(num3){
				 if(num2==1){
					 num2=0;
					 delay_ms(200);
//					 sendbyte2(buf2[0]);
//					 sendbyte2(buf2[1]);
//					 sendbyte2(buf2[2]);
//					 sendbyte2(buf2[3]);
					 
					 if((buf2[0]=='S') && (buf2[1]==' ') && (buf2[2]=='0') && (buf2[3]==',')&&(weishu3>=3)){
						 shangchuan_ok=1;
						 flag_in2=0;
					   num2=0;
						 while(shangchuan_ok){
							 key();
							 if(start_num==1){
								 start_num=0;
								 qg1=0;
								 while(qg_down);
								 time_out=0;
								 qg2=0;
								 count=0;
								 delay_ms(600);
								 count=1;
								 xiaya_daowei=1;
								 while(xiaya_daowei){
									 if(time_in==0){
										 delay_ms(50);
									   if(time_in==0){
											 yahe_ok();
											 yahe_ok_S1();
												 delay_ms(150);
												 qg2=1;
												 delay_ms(150);
												 qg1=1;
												 time_out=1;
												 shangchuan_ok=0;
												 num2=0;
												 num3=0;
												 start_num=0;
												 youliao=0;
											   while(!start);
											   xiaya_daowei=0;
											 goto kaishi;
										 }
										}
								 }	 
						  }
					  }
					 }
					 if((buf2[0]=='S') && (buf2[1]==' ') && (buf2[2]=='1') && (buf2[3]==',')){
						 youliao=0;
						 num3=0;
						 num2=0;
						 goto kaishi;
					 }
				 }
		   }
		 } 
	 }
 }	 
}
	 
	 

	 
	 
uint time,lv_bo;	 
void Timer0() interrupt 1
{
	time++;
	if((!start) && (!start_num)) {
     lv_bo++;
    }
	if(start) {
     lv_bo=0; 
     start_num=0;
    }
	if(lv_bo>=50) {
     start_num=1;
    }
	
		
	if(time>1000)
	{
		time=0;
	//	y5=~y5;
	//	run_led=~run_led;
	}
if(!stop)
 {
	delay_ms(1);
  if(!stop)
	 {
		 
		IAP_CONTR=0x60;
	 }
	}
}

void UARTInterrupt(void) interrupt 4 
{
   if(RI)
    {
	    RI=0;
//			temp1 = SBUF;
//			if(temp1==0x0a)
//			  IAP_CONTR=0x60;
			temp2 = SBUF;
			if(flag_in2==1){
				 buf2[weishu2] = temp2;
				 weishu2++;
				 if(weishu2 >= 80) weishu2=0;
		}
//			 }
		
		if((temp2 == 'B') && (flag_in2==0))
				{
					flag_in2=1;
					weishu2=0;
					num2=1;
				}
			
			
	  }
	else 
    {
	    TI=0;	
		}
if(TI)//发送中断..
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
//	 if(temp2 == ';')
//			 {
//				 flag_in2=0;
//				 num2=1;
//			 }
//			else
//			 {
		if(flag_in2==1){
				 buf2[weishu2] = temp2;
				 weishu2++;
				 if(weishu2 >= 80) weishu2=0;
		}
//			 }
		
		if((temp2 == 'B') && (flag_in2==0))
				{
					flag_in2=1;
					weishu2=0;
					num2=1;
				}
	}
  if (S2CON & S2TI)
    {
			//y1=0;
        S2CON &= ~S2TI;         //清除S2TI位
        busy2 = 0;               //清忙标志
    }  
}

  


void Uart3() interrupt 17 using 1
{
    if (S3CON & S3RI)
    {
        S3CON &= ~S3RI;         //??S3RI?
        temp3 = S3BUF;
				if(flag_in3==1)
				{
					if(temp3 == 0XDE)
					 {
						 flag_in3=0;
						 num3=1;
					 }
					else
					 {
						 buf3[weishu3] = temp3;
						 weishu3++;
						 if(weishu3 >= 80)  weishu3=0;
					 }
				 }
				if((temp3 == 0XAC) && (flag_in3==0))
						{
							flag_in3=1;
							weishu3=0;
						}
   }
if (S3CON & S3TI)
    {
        S3CON &= ~S3TI;         //清除S3TI位
        busy3 = 0;               //清忙标志
    }
}

void Uart4() interrupt 18 
{
    if (S4CON & S4RI)
    {
        S4CON &= ~S4RI;         //??S4RI?
        temp4=S4BUF;
				if(flag_in4==1)
				 {
						if(temp4 ==';')//0x44
						 {
							 flag_in4=0;
							 num4=1;
							 //Y4=0;
						 }
						else
						 {
							 buf4[weishu4] = temp4;
							 weishu4++;
						 }
					}
					if(((temp4 =='B') || (temp4 =='D')) && (flag_in4==0))//0x49
					{
						flag_in4=1;
						weishu4=0;
					}
   }
if(TI4)
	{
		CLR_TI4();
		busy4 = 0;               //清忙标志
	}
}



