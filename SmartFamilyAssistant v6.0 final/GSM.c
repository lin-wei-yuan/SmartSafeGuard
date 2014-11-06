#include <Option.h>

extern char EnviInfo[6];
extern char Message[250];
extern unsigned char PassWord[7];

extern unsigned char RandPswd[7]; //һ������
extern  void DHT11Read(unsigned char *OneNum, unsigned char *TwoNum);
extern unsigned char Mq2Read(void);
extern unsigned char ReadTemperature(void);
#define buf_max 372//���泤��372
extern  int flag[];

unsigned char rec_buf[buf_max];//���ջ���
unsigned int k=0;

/*----------------------------
    UART1��ʼ��
-----------------------------*/
void InitUART(void)
{
    SCON = 0x50;                //8λ�ɱ䲨����	
	AUXR1= AUXR1 & 0x3F; 
//    AUXR = 0x40;                //��ʱ��1Ϊ1Tģʽ
	AUXR |= 0x40;                //��ʱ��1Ϊ1Tģʽ
    TMOD = 0x20;                //��ʱ��1Ϊģʽ2(8λ�Զ�����)

    TL1 = 0xDC;   //���ò�������װֵ
    TH1 = 0xDC;
    TR1 = 1;                    //��ʱ��1��ʼ����
    ES = 1;                     //ʹ�ܴ����ж�
    EA = 1;
	
}

/*----------------------------
UART �жϷ������
-----------------------------*/
void Uart() interrupt 4 using 1
{

 	ES=0;	 //�ش����ж�
	RI=0;   
	rec_buf[k]=SBUF;
	if(k<buf_max)
		k++;
	else
		k=0;
	ES=1;	 //�������ж�
}

/*----------------------------
���ʹ�������
----------------------------*/
void Uart1Send(unsigned char dat)
{

	ES=0;//�ش��п��ж�	
    SBUF = dat;                 //д���ݵ�UART���ݼĴ���
	while(TI==0);	//��ѯ�����Ƿ����
		TI=0;	//�������һ��־λ
	ES=1;//�����п��ж�	
}

/*----------------------------
�����ַ���
----------------------------*/
void Uart1Sends(unsigned char *at)
{
    uchar cnt=0;								  
	ES=0;//�ش��п��ж�									
	while(*(at+cnt))	//�ж�һ�������Ƿ����			
	{
		SBUF=*(at+cnt);	//��������
		while(TI==0);	//��ѯ�����Ƿ����
		TI=0;	//�������һ��־λ
		cnt++;	//׼������һ������
	}
	ES=1;//�����п��ж�	
}


//������ģ��
void SendMessage(char *number,char *text)
{
	char Message[100]="";	
    Uart1Sends("AT+CMGF=1\r\n");
	DelaySec(1);//��ʱ3��
	Uart1Sends("AT+CSMP=17,167,2,25\r\n");
	DelaySec(1);//��ʱ3��
	Uart1Sends("AT+CSCS=\"UCS2\"\r\n");
	DelaySec(1);//��ʱ3��
	strcpy(Message,"AT+CMGS=\"");//�����ֻ�����
	strcat(Message,number);
	strcat(Message,"\"\r\n");
	Uart1Sends(Message);
	DelaySec(1);//��ʱ3��
	Uart1Sends(text);//�����������
	Uart1Send(0x1a);

}

//��绰����
void CallPhone(char *number)
{
	char Message[20]="";
	strcpy(Message,"ATD");
	strcat(Message,number);//�����ֻ�����
	strcat(Message,";\r\n");//
	Uart1Sends(Message);//��绰ָ���ۺ�
	//LCD_Init();//LCD����
	LCD_Clear();
	//                  1234567890123456
	LCD_Write_String(1,"������...       ");//LCD ��ʾ���ڲ���
	//LCD_Write_String(2,"�� #  �ɹҶϵ绰");//�� # �ҵ绰
	DelaySec(1);//��ʱ1��
}


//GSM_control ���ſ���////////////////////////////////////////////////////////////




   /*****************�жϻ������Ƿ���ָ�����ַ�������******************/
/*����ԭ��:bit hand(unsigned char *a)
/*��������:�жϻ������Ƿ���ָ�����ַ���
/*�������:unsigned char *a ָ�����ַ���
/*�������:bit 1---����    0---������
/*����ģ��:��
/**********************************************************************/
bit hand(uchar *a)
{ 
    if(strstr(rec_buf,a)!=NULL)	  //!=�ǲ�����
       return 1;
    else
       return 0;
}

/**************************����������ݺ���****************************/
/*����ԭ��:void clr_buf(void)
/*��������:�����������
/*�������:��
/*�������:��
/*����ģ��:��
/**********************************************************************/
void clr_buf(void)
{
    for(k=0;k<=buf_max;k++)
	{
   	    rec_buf[k]='0';
	}	
	 	k=0;
}

/****************************������ź���*****************************/
/*����ԭ��:void clr_ms(void)
/*��������:�������
/*�������:��
/*�������:��
/*����ģ��:��
/**********************************************************************/
void clr_ms(void)
  {
     //Uart1Sends("AT+CMGDA=6\r\n");

	 Uart1Sends("AT+CMGD=1\r\n");

  }

void GSM_control(void)
{
	int j;
	unsigned char *pos;	    	

	Uart1Sends("AT+CMGR=1\r\n");//���Ͷ�ָ��
	delay_GSM(100);//Delay(50000);//
	Uart1Sends("AT+CMGR=1\r\n");//���Ͷ�ָ��
	
	
	if(strstr(rec_buf,"8BBE7F6E5BC67801FF1A" )!=NULL && flag[1]!=1)//�������룺
	{
		

		flag[1] = 1;              
	 	pos = strstr(rec_buf,"8BBE7F6E5BC67801FF1A");
		if(pos-rec_buf < 309)
		{
		
			

			PassWord[0] = rec_buf[pos-rec_buf+20+3];
			PassWord[1] = rec_buf[pos-rec_buf+20+7];
			PassWord[2] = rec_buf[pos-rec_buf+20+11];
			PassWord[3] = rec_buf[pos-rec_buf+20+15];
			PassWord[4] = rec_buf[pos-rec_buf+20+19];
			PassWord[5] = rec_buf[pos-rec_buf+20+23];
			for(j=0;j<6;j++)
			{
			 	if(PassWord[j]<='9' && PassWord[j]>='0')
				{
				;
				}
				else
				{
					PassWord[j]='0';
				}

			}
			LCD_Write_String(2,"�Ѹ��Ķ�������");
//			LCD_Write_String(3,PassWord);

//			SendString_serial_2(PassWord);
//			strcpy(Message,"66F465395BC678016210529FFF0C65B05BC678014E3AFF1A");	
//			pos = pos+20;		
//			strcat(Message,pos);
//			CloseTimer0();		
//			SendMessage("00310033003100370037003700350035003100330034",Message);				
//			InitTimer();//��ʱ��0��ʼ��Timer0
	
			Delay(50);
			clr_ms();//ɾ������
			Delay(50);
//			InitGSM();//��ʼ��GSM����
			LCD_Row_Clear(2);
//			Delay(10000);
		}

		//��ʼ��GSM����
		Uart1Sends("AT\r\n");
		 Delay(1000);
		 //while(!hand("OK"));
		 clr_buf();	
		 Uart1Sends("AT+CMGF=1\r\n");//�ı���ʽ
		 Delay(1000);
		 //while(!hand("OK"));
	
		 clr_buf();
		 Uart1Sends("AT+CNMI=2,1\r\n");
		 Delay(1000);
		 //while(!hand("OK")); 
		 clr_buf(); 
	
		clr_ms();//ɾ������	
		Delay(1000);
		//while(!hand("OK")); 
		clr_buf();
		Delay(50);
	}


	if(strstr(rec_buf,"751F6210968F673A7801")!=NULL && flag[2]!=1)//���������
	{
		
		flag[2] = 1;
		MakeArandStr();		//��������뵽RandPswd[]
		strcpy(Message,"968F673A78014E3AFF1A");
		for(j=0;j<6;j++)
		{
			switch(RandPswd[j])
			{
			case '0':strcat(Message,"0030");break;
			case '1':strcat(Message,"0031");break;
			case '2':strcat(Message,"0032");break;
			case '3':strcat(Message,"0033");break;
			case '4':strcat(Message,"0034");break;
			case '5':strcat(Message,"0035");break;
			case '6':strcat(Message,"0036");break;
			case '7':strcat(Message,"0037");break;
			case '8':strcat(Message,"0038");break;
			case '9':strcat(Message,"0039");break;
			default:strcat(Message,"0030");break;
				
			}

		}
		
		CloseTimer0();		
		SendMessage("00310038003200370030003700320030003300350033",Message);	//		SendMessage("00310033003100370037003700350035003100330034",Message);				
		InitTimer();//��ʱ��0��ʼ��Timer0

		strcpy(Message,"968F673A78014E3AFF1A");
		Delay(50);
		clr_ms();//ɾ������
		Delay(50);
		
		//��ʼ��GSM����
		//��ʼ��GSM����
		Uart1Sends("AT\r\n");
		 Delay(1000);
		 //while(!hand("OK"));
		 clr_buf();	
		 Uart1Sends("AT+CMGF=1\r\n");//�ı���ʽ
		 Delay(1000);
		 //while(!hand("OK"));
	
		 clr_buf();
		 Uart1Sends("AT+CNMI=2,1\r\n");
		 Delay(1000);
		 //while(!hand("OK")); 
		 clr_buf(); 
	
		clr_ms();//ɾ������	
		Delay(1000);
		//while(!hand("OK")); 
		clr_buf();
		Delay(50);
	}


	if(strstr(rec_buf,"5BB65EAD73AF5883")!=NULL && flag[3]!=1)//�鿴��ͥ����
	{		

		flag[3]=1;
			
		strcpy(Message,"76EE524D76845BB65EAD73AF588360C551B54E3AFF1A");
		for(j=0;j<4;j++)
		{
			
			if(j==0)
			{
				strcat(Message,"007C007C6E295EA6003A");
			}
			if(j==2)
			{
				strcat(Message,"007C007C6E7F5EA6003A");
			}
		 	switch(EnviInfo[j])
			{
			case '0':strcat(Message,"0030");break;
			case '1':strcat(Message,"0031");break;
			case '2':strcat(Message,"0032");break;
			case '3':strcat(Message,"0033");break;
			case '4':strcat(Message,"0034");break;
			case '5':strcat(Message,"0035");break;
			case '6':strcat(Message,"0036");break;
			case '7':strcat(Message,"0037");break;
			case '8':strcat(Message,"0038");break;
			case '9':strcat(Message,"0039");break;
			default:strcat(Message,"0030");break;
				
			}
		}
//----g
		strcat(Message,"007C007C537196696C144F5368C06D4B003A");
//		MQ=Mq2Read();
		if(EnviInfo[4]=='0')
		{
		  strcat(Message,"5B895168007C007C");
		}
		else
		{
		  strcat(Message,"5F025E38007C007C");
		  
		}
		
		CloseTimer0();		
		SendMessage("00310038003200370030003700320030003300350033",Message);
						
		InitTimer();//��ʱ��0��ʼ��Timer0

		strcpy(Message,"76EE524D76845BB65EAD73AF588360C551B54E3AFF1A");
		Delay(50);	
		clr_ms();//ɾ������
		Delay(50);
		
		//��ʼ��GSM����
		//��ʼ��GSM����
		Uart1Sends("AT\r\n");
		 Delay(1000);
		 //while(!hand("OK"));
		 clr_buf();	
		 Uart1Sends("AT+CMGF=1\r\n");//�ı���ʽ
		 Delay(1000);
		 //while(!hand("OK"));
	
		 clr_buf();
		 Uart1Sends("AT+CNMI=2,1\r\n");
		 Delay(1000);
		 //while(!hand("OK")); 
		 clr_buf(); 
	
		clr_ms();//ɾ������	
		Delay(1000);
		//while(!hand("OK")); 
		clr_buf();

		Delay(50);
	}
	
	
	clr_buf();     
	
}

void InitGSM(void)
{

    CloseTimer0();

	 clr_buf();

     Uart1Sends("AT\r\n");

	 while(!hand("OK"));

	 clr_buf();
	 //clr_ms();//ɾ������	
	 Uart1Sends("AT+CMGF=1\r\n");//�ı���ʽ
	 while(!hand("OK"));

	 clr_buf();
	 Uart1Sends("AT+CNMI=2,1\r\n");
	 while(!hand("OK")); 
	 clr_buf(); 

	clr_ms();//ɾ������	
	while(!hand("OK")); 
	clr_buf();
	InitTimer();//��ʱ��0��ʼ��Timer0
}

 void delay_GSM(uint z)		  //1ms��ʱ
{
     uint x,y;
	 for(x=z;x>0;x--)
	    for(y=110;y>0;y--);
}

