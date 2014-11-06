#include "Option.h"

extern unsigned char RandPswd[7] ; //һ������
extern int randseed;	   //Timer0�ļ�����ֵ
	   /*
void Delay(unsigned int time)
{
	unsigned int j;
	for(;time>0;time--)
		for(j=0;j<510;j++);
//		for(j=0;j<110;j++);
}
*/
void Delay(unsigned int time)
{
//	unsigned int j;
//	for(;time>0;time--)
//		for(j=0;j<510;j++);
//		for(j=0;j<110;j++);
	int d;
	for(;time>1;time--)
		for(d=0;d<1000;d++)
		;
}
/*
void delay_moto(int time)
{ 
  int i,j;
  
  for(j=0; j <= time; j++)
  	for(i =0 ; i <= 120; i++);
//   for(i =0 ; i <= 120; i++);
}
 */

void delay_moto(int x)		//@11.0592MHz   x ms
{
	unsigned char i, j;
	while(x--)
	{
	  _nop_();
	  _nop_();
	  _nop_();
	  i = 20;	 //ԭ��11 	����  1.7        ||	 12			 ||	20 			 ||		||		||
	  j = 190;	 //ԭ��190	  ����			 ||	 �仯����	 ||	 Ч���仯����||		||		||
	  do
	  {
		while (--j);
	  } 
	  while (--i);
    }
}

//����������Ӧʱ����
void Beep(unsigned int time)
{
	BeepON;
	BeepON;
	Delay(time);
	BeepOFF;
	BeepOFF;
}


//��ʱ���������1s�ӣ�������ʱ��Ļ���׼...
void DelaySec(int sec)
{
	unsigned int i , j= 0;
	
	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}

/*------------------------------------------------
uS��ʱ����������������� unsigned char t���޷���ֵ
unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
�������� T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
	while(--t);
}

/*------------------------------------------------
mS��ʱ����������������� unsigned char t���޷���ֵ
unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void DelayMs(unsigned char t)
{
	
	while(t--)
	{
		//������ʱ1mS
		DelayUs2x(245);
		DelayUs2x(245);
	}
}
/******************************����ΪӲ�����***********************/

void Go()
{	 //A
    PH1 = 0;  //PH1Ϊ0 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2Ϊ1 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 1;  //PH1Ϊ1 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 1;  //PH1Ϊ1 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 0;
	I01 = 0;
	I11 = 0;
	

	PH2 = 0;  
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);
	
	
}

//�������
void Forward() //��ת
{	 //A
    PH1 = 0;  //PH1Ϊ0 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2Ϊ1 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 1;  //PH1Ϊ1 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 1;  //PH1Ϊ1 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 0;
	I01 = 0;
	I11 = 0;
	

	PH2 = 0;  
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);	
}

void Reverse() //��ת
{	// ��ת��A/B/  AB/  AB   A/B
     //A
    PH1 = 0;  //PH1Ϊ0 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 1;  //PH1Ϊ1 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 0;  //PH1Ϊ0 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2Ϊ1 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 0;   //PH1Ϊ0 ��A��ȦΪ�������
	I01 = 0;
	I11 = 0;
	

	PH2 = 1;  //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);	
}		  \

void Reverse2() //��ת
{	// ��ת��A/B/  AB/  AB   A/B
     //A
    PH1 = 1;  //PH1Ϊ0 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 0;  //PH1Ϊ1 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 0;  //PH1Ϊ0 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2Ϊ1 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 1;   //PH1Ϊ0 ��A��ȦΪ�������
	I01 = 0;
	I11 = 0;
	

	PH2 = 1;  //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);	
}

			void Reverse3() //��ת
{	// ��ת��A/B/  AB/  AB   A/B
     //A
    PH1 = 0;  //PH1Ϊ0 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//0
	PH1 = 1;  //PH1Ϊ1 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 0;   //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;

	delay_moto(speed);
	//B
	PH1 = 1;  //PH1Ϊ0 ��A��ȦΪ�������
    I01 = 0;
	I11 = 0;
	

	PH2 = 1;   //PH2Ϊ1 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;
	           ////
	delay_moto(speed);
	//0
	PH1 = 0;   //PH1Ϊ0 ��A��ȦΪ�������
	I01 = 0;
	I11 = 0;
	

	PH2 = 1;  //PH2Ϊ0 ��B��ȦΪ�������
	I02 = 0;
	I12 = 0;
             
	delay_moto(speed);	
}

void MakeArandStr()
{
	unsigned int r,t,u,p=0;//ȫ�ֱ���
	unsigned char l;
	//t=r;
	t=randseed;
	for(;;)
	{
		r+=29;
		t++;t%=10;//jֻ��0��9
		switch(t)
		{
		case 1:r*=2;break;
		case 2:r+=8;break;
		case 3:r*=1;break;
		case 4:r+=3;break;
		case 5:r*=6;break;
		case 6:r+=4;break;
		case 7:r*=3;break;
		case 8:r+=5;break;
		case 9:r*=7;break;
		case 0:r+=3;break;
		}
		u = r%10;//�����ֻ��1��10֮�����
		switch(u)
		{
		case 1:l='1';break;
		case 2:l='2';break;
		case 3:l='3';break;
		case 4:l='4';break;
		case 5:l='5';break;
		case 6:l='6';break;
		case 7:l='7';break;
		case 8:l='8';break;
		case 9:l='9';break;
		case 0:l='0';break;
		}
		
		RandPswd[p]=l;
		p++;	
		if(p==6)
		{
		  RandPswd[p]='\0'; 
		  p=0;
		  break;
		}	
	}

}

void OpenDoor()
{
	int r=60;	 //old��r=60  n=60
	int n=60;

	while(r--)
	{
		Reverse3();
	}

	Delay(5000);
/*
	if(RED == 0)
	{
//		Delay(100);	
		do
		{
			;
		}
		while(RED == 1)
	
	}
*/
	while(n--)
	{
		if(RED == 0)
		{
		 	Delay(3000);
		}
		Forward();
	}
	
	
	//�˴���Ӻ��⴫����ȷ��
	

/*
	while(1)
	{
//		Reverse();
		Go();
	}
*/
}
/*
char * ShiftUnicode(unsigned char i)
{
	char UnicodeStr[5];
	switch(i)
	{
		case '0':strcpy(UnicodeStr,"0030");break;
		case '1':strcpy(UnicodeStr,"0031");break;
		case '2':strcpy(UnicodeStr,"0032");break;
		case '3':strcpy(UnicodeStr,"0033");break;
		case '4':strcpy(UnicodeStr,"0034");break;
		case '5':strcpy(UnicodeStr,"0035");break;
		case '6':strcpy(UnicodeStr,"0036");break;
		case '7':strcpy(UnicodeStr,"0037");break;
		case '8':strcpy(UnicodeStr,"0038");break;
		case '9':strcpy(UnicodeStr,"0039");break;
		default:strcpy(UnicodeStr,"0038");	
	}
	return UnicodeStr;
}
*/
/******************************����ΪӲ�����***********************/