 
 /*************************�˲���Ϊ18B20����������*************************************/
#include<Option.h>



sbit DQ_18B20=P2^0;//P4^2;  //ds18b20 �˿�
	

void Delay1(unsigned int x);
unsigned char ReadTemperature(void);
void Init_DS18B20(void);
unsigned char ReadOneChar(void);
void WriteOneChar(unsigned char dat);
void delay_18B20(unsigned int i);
/************************************************************************/



void Delay1(unsigned int x)		//@11.0592MHz   x ms
{
	unsigned char i, j;
	while(x--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} 
		while (--i);
	}
}

void delay_18B20(unsigned int i)//��ʱ����
{
	while(i--);
}
/***************************************************************************************/
//18b20��ʼ������
void Init_DS18B20(void)
{
	unsigned char x=0;
	DQ_18B20 = 1;    //DQ_18B20��λ
	delay_18B20(80);  //������ʱ
	DQ_18B20 = 0;    //��Ƭ����DQ_18B20����
	delay_18B20(800); //��ȷ��ʱ ���� 480us
	DQ_18B20 = 1;    //��������
	delay_18B20(100);
	x=DQ_18B20;      //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
	delay_18B20(50);
}

//��һ���ֽ�
unsigned char ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ_18B20 = 0; // �������ź�
		dat>>=1;
		DQ_18B20 = 1; // �������ź�
		if(DQ_18B20)
		dat|=0x80;
		delay_18B20(50);
	}
	return(dat);
}

//дһ���ֽ�
void WriteOneChar(unsigned char dat)
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DQ_18B20 = 0;
		DQ_18B20 = dat&0x01;
		delay_18B20(50);
		DQ_18B20 = 1;
		dat>>=1;
	}
	delay_18B20(50);
}

//��ȡ�¶�
unsigned char ReadTemperature(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned char t=0;
	//float tt=0;
	Init_DS18B20();
	WriteOneChar(0xCC); // ����������кŵĲ���
	WriteOneChar(0x44); // �����¶�ת��
	delay_18B20(2000);
	Init_DS18B20();
	WriteOneChar(0xCC); //����������кŵĲ��� 
	WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
	a=ReadOneChar();
	b=ReadOneChar();
	
	b<<=4;
	b+=(a&0xf0)>>4;
	t=b;
	//tt=t*0.0625;
	//t= tt*10+0.5; //�Ŵ�10���������������
	return(t);
}
