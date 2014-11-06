#include "Option.h"
#include<intrins.h>

//*************************************************
//��������LCD_Busy(void)      �������ܣ�12864�ж��Ƿ�æµ                 
//���ڱ�����
//������&ʱ�䣺
//*************************************************
void LCD_Busy(void)
{
	DataPort=0xff;
	RS=0;
	RW=1;
	E=1;
	while(Busy==1);
	E=0;
}

void LCD_Write_Com(unsigned char com) 
{  
	LCD_Busy();
	RS=0;
	RW=0;
	DataPort=com;
	E=1;
	nop();
	E=0; 
}
/*------------------------------------------------
д�����ݺ���
------------------------------------------------*/
void LCD_Write_Data(unsigned char Data) 
{ 
	LCD_Busy();
	RS=1;
	RW=0;
	DataPort=Data;
	E=1;
	nop();
	E=0; 
}

/*------------------------------------------------
��������
------------------------------------------------*/
void LCD_Clear(void) 
{ 
	
	LCD_Row_Clear(0);
	LCD_Row_Clear(1);
	LCD_Row_Clear(2);
	LCD_Row_Clear(3);
}
/*------------------------------------------------
д���ַ�������			  LCD_Write_String(��y��,�ַ���)
------------------------------------------------*/
void LCD_Write_String(unsigned int y,unsigned char *s) //change version: char --> int
{     
	unsigned char i;
	switch(y)
	{
		case 0:y=0x80;break;
		case 1:y=0x90;break;
		case 2:y=0x88;break;
		case 3:y=0x98;break;
	}
	LCD_Write_Com(0x30);
	LCD_Write_Com(y);
	for(i=0;i<16;i++)
	{
		LCD_Write_Data(*s);
		s++;
	}
}
/*------------------------------------------------
д���ַ�����		LCD_Write_Char(��x��,��y��,�ַ�)
------------------------------------------------*/
void LCD_Write_Char(unsigned int x,unsigned int y,unsigned char Data)  //change version: char --> int
{     
	switch(y)
	{
		case 0:y=0x80;break;
		case 1:y=0x90;break;
		case 2:y=0x88;break;
		case 3:y=0x98;break;
	}
	LCD_Write_Com(0x30);
	LCD_Write_Com(y+x);       
	LCD_Write_Data( Data);  
}
/*------------------------------------------------
��ʼ������
------------------------------------------------*/
void LCD_Init(void) 
{
	RST=1;
	PSB=1;
	LCD_Write_Com(0x30);  /*30---����ָ���*/   
	LCD_Write_Com(0x01);  /*��������ַָ��ָ��00H*/
	LCD_Write_Com(0x06);  /*�����ƶ�����*/
	LCD_Write_Com(0x0c);  /*����ʾ�����α�*/
}

/*------------------------------------------------
�����к���
------------------------------------------------*/
void LCD_Row_Clear(unsigned int row) 
{
	//                    1234567890123456
	LCD_Write_String(row,"                ");
}

