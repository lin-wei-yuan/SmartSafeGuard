#include <Option.h>

extern char EnviInfo[6];
extern char Message[250];
extern unsigned char PassWord[7];
extern unsigned char rec_buf_Uart2[72];
extern int flag[];
void CloseTimer0(void);
void InitTimer(void);
extern  void DHT11Read(unsigned char *OneNum, unsigned char *TwoNum);
extern unsigned char Mq2Read(void);
extern unsigned char ReadTemperature(void);
extern void GSM_control(void);
//���ڲ�����Ϊ9600

int int0_t=100,randseed;
/*************	�û�ϵͳ����	**************/

#define D_TIMER0		125			//ѡ��ʱ��ʱ��, us, 

#define Timer0_Reload		65536-D_TIMER0

/**************** Timer��ʼ������ ******************************/
void InitTimer(void)
{
//	TMOD = 0;		//for STC15Fxxxϵ��	Timer0 as 16bit reload timer.
	TMOD &= 0xF0;		//for STC15Fxxxϵ��	Timer0 as 16bit reload timer.
	TH0 = Timer0_Reload / 256;
	TL0 = Timer0_Reload % 256;
	ET0 = 1;
	TR0 = 1;

	EA  = 1;

}

void CloseTimer0(void)
{	
	ET0 = 0;
	TR0 = 0;
}


 void timer0 (void) interrupt 1
{

 	//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
	unsigned char Tab[] = {'0','1','2','3','4','5','6','7','8','9'}; 
	unsigned char temp,temperature;
	unsigned char wet[2],wet_pc[2]; 
	unsigned char MQ;
	unsigned char Str[22];//="#1234567890abcdefghij";	
	int str_i=0;

	int0_t++;
	randseed++;
	if(randseed > 32760)
	{
	 	randseed = 0;
	}
//	

	if(int0_t>=100)
	{	 
		int0_t=0;
		
		CloseTimer0();
          
    	GSM_control();//������ſ���

		InitTimer();//��ʱ��0��ʼ��Timer0

		ES = 0;                     //�رմ���1�ж�
	

		temp=ReadTemperature()-1;
		temperature=temp;	 
    	EnviInfo[0]=Tab[temp/10]; //ʮλ�¶�
        EnviInfo[1]=Tab[temp%10]; //��λ�¶�

		DHT11Read(&wet[0],&wet[1]);		
		temp=wet[0];
		wet_pc[0]=wet[0];
		wet_pc[1]=wet[1];
		wet[0]=temp/10;
		if(temp/10>9)
		{
		 wet[0]=9;
		}
		EnviInfo[2]=Tab[wet[0]%10];
		EnviInfo[3]=Tab[wet[1]];

		MQ=Mq2Read();
		EnviInfo[4]=Tab[MQ];

		if(MQ==0)
		{
		  strcat(Message,"5B895168007C007C");
		}
		else
		{
		  strcat(Message,"5F025E38007C007C");
		  
		}

		if(MQ==1 && flag[0]!=1)
		{
			flag[0]=1;
			SendMessage("00310038003200370030003700320030003300350033","8B6662A5FF01FF01FF010020002068C06D4B5230537196696C144F536D535EA65F025E38FF0C8BF75C3D5FEB80547CFB5BB64EBA590474063002");
		}
		if(MQ==0 && flag[0]==1 && flag[4]!=1)
		{
			flag[4]=1;
			SendMessage("00310038003200370030003700320030003300350033","8B6662A589E39664FF01FF01FF010020002068C06D4B5230537196696C144F536D535EA65DF27ECF6062590D6B635E38FF0C8BF767E5660E5F025E38539F56E04EE55F7B5E9563929664969060A33002");
		}
		if(wet[0] <= 2)		//��ʪ��
		{

		}
		else
		{
		 
		}


        //IE2 = 0x00;
		//DHT11Read(&wet_pc[0],&wet_pc[1]);
		{//���͵�pc
         //02 0B 00 08 10 00 1B 01 02 01 00  
         //      +    .     .
		Str[0]=0x02;
		Str[1]=0x0B;
		Str[2]=0x00;
		Str[3]=0x08;
		
		Str[4]=0x10;
		
		Str[5]=0x00;//+
			 
		Str[6]=temperature;//   ����
		Str[7]=temperature;// С��
		
		Str[8]=EnviInfo[2]-48;//wet_pc[0];//EnviInfo[2];
		Str[9]=EnviInfo[3]-48;//wet_pc[1];//EnviInfo[3];
		
		Str[10]=EnviInfo[4]-48;//MQ;

		}

		for(str_i=0;str_i<=10;str_i++)
		SendData_serial_2(Str[str_i]);
		//SendString_serial_2(Str);

	   //IE2 = 0x01;                 //ʹ�ܴ���2�ж�

	    ES = 1;                     //ʹ�ܴ���1�ж�	
	}

}
