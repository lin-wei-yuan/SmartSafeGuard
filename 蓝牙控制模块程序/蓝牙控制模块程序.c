/************************************************************
����˵����
���������к��������ģ���ҵ����������źſ�ʵ���������Ƽҵ�ȹ���


*************************************************************/
#include <REG51.H>
#include <string.H>
#define uchar unsigned char
#define uint unsigned int
//�����ǰ�����LED�����ã���Px_x�ĳ��Լ���Ӧ�Ľš�
//���������51��Ƭ���ľ����С
int flag;//��־λ Ϊ1��ʾ������ȷ��Ϊ0����
int If_num = 0;//if���Ĵ���

#define num 3
//Motor
unsigned char code FFW[3]={0xf1,0xf3,0xf2}; //1
unsigned char code FFZ[3]={0xf8,0xfc,0xf4}; //2

sbit BUZZ=P0^6;//������
sbit Accept = P0^7;

sbit LED=P0^0;//LED����
sbit XSQ=P0^1; //��ʾ��
sbit WHQ=P0^2; //����
sbit BFQ=P0^3; //������

sbit KZ1=P1^0;//���߿���
sbit KZ2=P1^1; 
sbit KZ3=P2^2; 
sbit KZ4=P3^3; 


#define FOSC_110592M
//#define FOSC_12M

//������GSMģ�鷵������
uchar rec_data[50];
uchar rec_num;
unsigned int  K;
//ע�⣬���۽��յ��źŻ��Ƿ������źţ�������жϷ�������
/*��ʼ�����򣨱���ʹ�ã������޷��շ������γ��򽫻�ʹ�ö�ʱ��1*/
void SerialInti()//��ʼ�����򣨱���ʹ�ã������޷��շ���
{
	TMOD=0x20;//��ʱ��1����ģʽ2:8λ�Զ����ض�ʱ��

#ifdef FOSC_12M		   //��������ݾ����С���ò�ͬ����ֵ��ʼ������
	TH1=0xf3;//װ���ֵ��������2400
	TL1=0xf3;	
#else 	
	TH1=0xfd;//װ���ֵ��������9600
	TL1=0xfd;
#endif //end of SOC_12M
	
	TR1=1;//�򿪶�ʱ��
	SM0=0;//���ô���ͨѶ����ģʽ����10Ϊһ�����ͣ������ʿɱ䣬�ɶ�ʱ��1������ʿ��ƣ�
	SM1=1;//(ͬ��)�ڴ�ģʽ�£���ʱ�����һ�ξͷ���һ��λ������
	REN=1;//���н�������λ��Ҫ������sm0sm1�ٿ���������
	EA=1;//�����ж�
	ES=1;//�����п��ж�	
}

/*����ͨѶ�жϣ��շ���ɽ�������ж�*///�磺+CMTI:"SM",2
void Serial_interrupt() interrupt 4 
{

	uchar temp;
	temp=SBUF;
	rec_data[rec_num++]=temp;
	if(rec_num>=50)
		rec_num=0;
	else
		;
	RI=0;//�����ж��ź����㣬��ʾ����������

}

//���п���������char�����飬������ֹ��/0��ֹͣ
void Uart1Sends(uchar *str)
{
	while(*str!='\0')
	{
		SBUF=*str;
		while(!TI);//�ȴ���������źţ�TI=1������
		TI=0;
		str++;
	}
}
void Uart1BYTE(uchar temp)
{
		SBUF=temp;
		while(!TI);//�ȴ���������źţ�TI=1������
		TI=0;

}

uchar hand(uchar *ptr)
{
	if(strstr(rec_data,ptr)!=NULL)
		return 1;
	else
		return 0;
}

void clear_rec_data()
{
	uchar i;
	for(i=0;i<strlen(rec_data);i++)
	{
		rec_data[i]='0';
	
	}
	rec_num=0;


}
//��ʱ���������1s�ӣ�������ʱ��Ļ���׼...
void DelaySec(int sec)
{
	uint i , j= 0;

	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}

/*******************��ʱ����****************************/
void delay(int time)
{ 
  int i,j;
  
  for(j=0; j <= time; j++)
   for(i =0 ; i <= 120; i++); //for(i =0 ; i <= 120; i++);
}

void Moto_delay(unsigned int t)//���������ʱ����
{                           
   unsigned int k;
   while(t--)
   {
     for(k=0; k<80; k++)
     { }
   }
}
/**********************************************************************
*																	  *
*                       �����������								  *
*																	  *
***********************************************************************/
void Moto() //�������ת��
 { 
   unsigned char motoi;
   unsigned int  motoj;
  	for (motoj=0; motoj<12*num; motoj++)         //ת1*nȦ 
    { 

      for (motoi=0; motoi<3; motoi++)       //һ������ת30��
        {
          if(K==1) 
		  {
		  P2 = FFW[motoi]&0x1f;  //ȡ����
		  Moto_delay(30);                   //����ת��
		  }
		  if(K==2)
		  {
		  P2 = FFZ[motoi]&0x1f;
          Moto_delay(30);                   //����ת��
		  }
        }
     } 
 }

void main()
{   uchar i = 0;
	SerialInti();
	LED=1;//�ص�
	XSQ=1;//�ر���ʾ��
	BFQ=0;//������������
	Accept=0;
	flag = 0;//û����������	
  TMOD = 0x21;//������ʱ\����������
  EA=1;//�����ж�
  //ET0=1;ET1=1;//��ʱ�� //	Ӱ������	//������	 
  TR0=1;TR1=1;
  EX0=1;//�����ⲿ�ж�0
  EX1=1;//�����ⲿ�ж�1
  //TH0=0xd0;TL0=0xf0;//�ߵͰ�λ  //���ж���Ӱ��
  //TH1=0xE7;TL1=0xE7;
  while(1)
  {//(while(1))
  while(0==Accept);//�ȴ��������ֻ��������ź�
  If_num++;
  delay(100);
  if(If_num%2!=0) 
  {//(if)
  Uart1Sends("Please enter the password:\r\n"); //����������
  clear_rec_data();
  If_num++;
  }
	while(1)
	{	 if(0==Accept)
	     break;
	    delay(50);
		 if(1==KZ2)
         {
         BUZZ=0;
		 delay(300);//��ʱ?��
		 BUZZ=1;
		 delay(300);//��ʱ?��
         }
		 if(1==KZ1)
         {
         LED=!LED;
		 delay(200);//��ʱ?��
         }
		while(hand("abc")) //��ȷ����abc
		{clear_rec_data();
		 BUZZ=0;
		 delay(300);//��ʱ?��
		 BUZZ=1;
		 Uart1Sends("Please enter the command:\r\n"); //������ָ��
		 flag=1;//������ȷ��־
		 break;
		}
		if(1==flag)
		break;
	}
	while(1)
 { 
    if(0==Accept)//||0==If_num%2)
	{
	clear_rec_data();
	break;
	}
	while(hand("opend")) 
	{
		clear_rec_data();
		LED=0;//����
		Uart1Sends("Light is open!\r\n");//���ѿ�����
		break;
	}
	//clear_rec_data();//ɾ���洢��GSMģ�鷵�ص����ݣ��Ա����Ժ�����ж�
	while(hand("openx")) //���SIMģ���Ƿ��յ�SIM��READY
	{
		clear_rec_data();
		XSQ=1;//����ʾ��
		Uart1Sends("The display has been opened!\r\n");//��ʾ���ѿ�����
		break;	
	}
	while(hand("closed")) 
	{
		clear_rec_data();
		LED=1;//�ص�
		Uart1Sends("Light has been shut down!\r\n");//���ѹرգ�
		break;
	}
	//clear_rec_data();//ɾ���洢��GSMģ�鷵�ص����ݣ��Ա����Ժ�����ж�
	while(hand("closex")) //���SIMģ���Ƿ��յ�SIM��READY
	{
		clear_rec_data();
		XSQ=0; //����ʾ��
		Uart1Sends("The display has been shut down!\r\n");//��ʾ���ѹرգ�
		break;	
	}

	while(hand("closec")) //������ָ��GSMģ���Ƿ�ִ��
	{
		clear_rec_data();
	    //�����ѹرգ�
		Uart1Sends("The window is closeing!\r\n");//�����ѹرգ�
		  K=1;
		  Moto();//��ת
		  break;
	}
	while(hand("openc")) //���SIMģ���Ƿ��յ�SIM��
	{
		clear_rec_data();
		 //�����ѿ�����
		Uart1Sends("The window is opening!\r\n");//�����ѿ�����
		K=2;
	    Moto();//��ת										   
		break;
    }

	while(hand("closew")) //�ر�����
	{
		clear_rec_data();
	    WHQ=0;//������
		delay(100);
		WHQ=1;
		Uart1Sends("Atomizer has been shut down!\r\n");//�����ѹرգ�
		break;
	}
	//clear_rec_data();
	while(hand("openw")) //������
	{
		clear_rec_data();
		WHQ=0; //������
		delay(100);
		WHQ=1;
		Uart1Sends("Atomizer has been opened!\r\n");//�����ѿ�����
		break;	
	}
		if(0==Accept)//||0==If_num%2)
		{
		clear_rec_data();
		break;
		}
 }
	   if(0==Accept)//||0==If_num%2)
		{
		clear_rec_data();
		break;
		}
   }//(while(1))
}

void External_one(void) interrupt 0	//�ⲿ�ж� 0
{	
    EA=0;//���ж�
    if(0==INT0)//�����⵽�ϰ���
	{
	  BFQ=1;//���������Ÿߵ�ƽ
	  delay(1);	//������ʱ	 
	}
	if(1==INT0)//���û�м�⵽�ϰ���
	{
	  BFQ=0;//���������ŵ͵�ƽ
	  delay(1);	//������ʱ
	}
	EA=1;//���ж�
}
//
void Time_one(void) interrupt 1	//ʱ���ж� 0
{
   
}

void External_two(void) interrupt 2	//�ⲿ�ж� 1
{
EA=0;//���ж�
    //Uart1Sends("Enter INT1!\r\n");//
    if(0==INT1)//�����⵽�ϰ���
	{
	  BUZZ=0;
	  delay(100);
	  BUZZ=1;
	  delay(100);
	}
	EA=1;//���ж�  
}

void Time_two(void) interrupt 3	//ʱ���ж� 2  //interrupt 4 �Ǵ����ж�
{
  
}