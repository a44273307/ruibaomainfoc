/************************************************************************************
Copyright,  LCE STUDIO  
�������ƣ�����ͨ�ţ�����Ƶ��18.432MHz��  
����˵��: ����1�ʹ���3��ʼ��,�ַ��������ַ������ͺ���,������9600bps
����汾��1.0 ��2014/06��
����������rob1983
�Ա����̣�http://shop67639654.taobao.com 
************************************************************************************/ 

#include "stc15f2k60s2.h"
#include "intrins.h"
#include "uart.h"
//#include "main.h"
 bit busy4;
 bit busy2;
 bit busy3;
//bit busy4;
//void SendData(unsigned char ch);
//void SendString(char *s);
//void UartInit(void);
//void U3SendData(unsigned char ch);
//void U3SendString(char *s);
//void U2SendData(unsigned char ch);
//void U2SendString(char *s);


/*----------------------------
��ʱ��0��ʼ��
----------------------------*/

void Timer0Init(void)		//2����@24.000MHz
{


	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0X9A;		//���ö�ʱ��ֵ
	TH0 = 0XA9;		//���ö�ʱ��ֵ
//	TL0 = 0x20;		//���ö�ʱ��ֵ
//	TH0 = 0xD1;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	PT0 = 1;
	ET0 = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	EA=1;
}
/*----------------------------
���ڳ�ʼ��
----------------------------*/

void UartInit(void)		//115200@24.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0x8F;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	ES=1;
	//	ES=0;//�رմ���0�ж�
	EA=1;
}
void Uart23Init(void)		//115200@24.000MHz
{
	S3CON = 0x10;		//8λ����,�ɱ䲨����
	S3CON &= 0xBF;		//����3ѡ��ʱ��2Ϊ�����ʷ�����
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0x8F;		//�趨��ʱ��ֵ
	T2H = 0xFD;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	IE2 |= 0x01;                 //ʹ�ܴ���2�ж�
	IE2 |= 0x08;                 //ʹ�ܴ���3�ж�
	EA=1;
	P_SW2 = (P_SW2 & ~2) | (0 & 0x02);	//�л�IO
	//	//IE2&=0xFE�رմ���2
//	IE2&=0xF7;	//�رմ���3
}
void Uart4Init(void)		//9600bps@24.000MHz	.����4
{
	S4CON = 0x10;		//8λ����,�ɱ䲨����
	S4CON |= 0x40;		//����4ѡ��ʱ��4Ϊ�����ʷ�����
	T4T3M |= 0x20;		//��ʱ��4ʱ��ΪFosc,��1T
	T4L = 0x8F;		//�趨��ʱ��ֵ
	T4H = 0xFD;		//�趨��ʱ��ֵ
	T4T3M |= 0x80;		//������ʱ��4	
	S4CON &= ~(1<<5);	//��ֹ���ͨѶ��ʽ
	S4CON &= ~(1<<7);	// 8λ����, 1λ��ʼλ, 1λֹͣλ, ��У��
	IE2   |=  (1<<4);	//�����ж�
	//IE2&=0xEF�رմ���4
	S4CON |=  (1<<4);	//�������
//	P_SW2 &= ~4;		//�л��� P0.2 P0.3
}


/*----------------------------
ͨ������1���ʹ�������
----------------------------*/
//void SendData(unsigned char ch)
//{
//    TI     =   0;  //���㴮�ڷ�������ж������־
//    SBUF   =   ch;
//    while(TI ==0); //�ȴ��������
//}

//void sendbyte1(unsigned char ch)
//{
//    TI     =   0;  //���㴮�ڷ�������ж������־
//    SBUF   =   ch;
//    while(TI ==0); //�ȴ��������
//}


void sendbyte1(unsigned char ch)
{
	int i;
	// EA=0;
    TI     =   0;  //���㴮�ڷ�������ж������־
    SBUF   =   ch;
    while(TI ==0) //�ȴ��������
	{
		// for(i=0;i<2000; i++){
		// 	if(	TI) break;
		// }
		// break;



	}
	EA=1;
}

/*----------------------------
ͨ������2���ʹ�������
----------------------------*/
void sendbyte2(unsigned char ch)
{
   while (busy2);               //�ȴ�ǰ������ݷ������                      //��ȡУ��λP (PSW.
   	busy2 = 1;
    S2BUF = ch;                //д���ݵ�UART2���ݼĴ���
}




/*----------------------------
ͨ������3���ʹ�������
----------------------------*/
void sendbyte3(unsigned char ch)
{
    while (busy3);               //�ȴ�ǰ������ݷ������
	  busy3 = 1;
    S3BUF = ch;                //д���ݵ�UART2���ݼĴ���
}

/*----------------------------
ͨ������4���ʹ�������
----------------------------*/
void sendbyte4(unsigned char ch)
{
    while (busy4);               //�ȴ�ǰ������ݷ������
	  busy4 = 1;
    S4BUF = ch;                //д���ݵ�UART2���ݼĴ���
}
int debug=1;
void PrintString(const char *puts)
{
	if (debug==0)
	{
		return ;
	}
	
    for (; *puts != 0;	puts++)  sendbyte1(*puts); 	//����ֹͣ��0����
}


