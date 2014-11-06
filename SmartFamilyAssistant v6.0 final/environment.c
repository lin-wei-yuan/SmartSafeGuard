#include<Option.h>
//#include "UART.h"
extern char EnviInfo[6];
unsigned char ReadTemperature(void);
void show_environment_data(void);


void delay(unsigned int i);


extern  void DHT11Read(unsigned char *OneNum, unsigned char *TwoNum);
extern unsigned char Mq2Read(void);




void show_environment_data()
{
	
	LCD_Init();//LCD��ʼ��
	
	CursorON;
	//                  1234567890123456
	LCD_Write_String(0,"�����ܼ�ͥ��ʿ��");
	
	
	LCD_Write_String(1,"    �¶�      ��");
	
	
	LCD_Write_Char(4,1,'+');
	LCD_Write_Char(5,1,(unsigned char)EnviInfo[0]);
	LCD_Write_Char(6,1,(unsigned char)EnviInfo[1]);
	
	
	LCD_Write_String(2,"    ʪ��       %");
	
	LCD_Write_Char(5,2,(unsigned char)EnviInfo[2]);
	LCD_Write_Char(6,2,(unsigned char)EnviInfo[3]);
	
	
	if(EnviInfo[4]=='0')
	{
		LCD_Write_String(3,"����Ũ��  ��ȫ  ");
	}
	else
	{
		LCD_Write_String(3,"����Ũ��  Σ��  ");
		//delay(1000);
	}
	
	delay(5000);
	LCD_Init();//LCD��ʼ��
}

