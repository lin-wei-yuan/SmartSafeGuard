#include<Option.h>

//version 5.9 beta 	 (��ίԱ�ṩ��PC�˳����beta�汾)
//notice:
//		
//		beep �����

unsigned char PassWord[7] = "111111"; //��������
unsigned char RandPswd[7] = "888888"; //һ������
unsigned char Input[7] = "000000"; //������������
char EnviInfo[6]="00000";
//static unsigned int  ErrNum=0;
int flag[10]={0};
              //    12345678901234567890123456789012345678901234567890123456789012345678901234567890
char Message[250];	//�洢��������

//���Խ���flag�Ĳ�ͬ��ֵ��һ�������ڲ�ʵ�ֶ��ģ̬
//   flag��	    	0			 	1	     	   2				3				4				5	  				6				7	8	9	    
//  ��Ӧģ̬������Σ�ձ���	����������      �����������	�鿴��ͥ����	���尲ȫһ��֪ͨ	���˷��ʴ�һ��		������ʴ�һ��



void main()
{
	unsigned int i=0;
	unsigned int  ErrNum=0;
	
	EntranceGuardInit();//�Ž�ϵͳ��ʼ��
//	LCD_Init();//LCD��ʼ��
			
	while(1)
	{
		Beep(500);
		LCD_Clear();
		//CursorON;
		//                  1234567890123456
		LCD_Write_String(0,"�����ܰ�ȫ��ʿ��");
		LCD_Write_String(1,"����������:     ");
		LCD_Write_String(3,"        ��* ͨ��");
		LCD_Write_Char(0,2,' ');
//		while(1)
//		{
		 Beep(500);
//		}//debug
		for(i=0;i<6;i++)
		{	
		    CursorON;
			
			Input[i] = KeyScan();
			LCD_Write_Char(i,2,Input[i]);
			Delay(500);
			LCD_Write_Char(i,2,'*');
			if(i>0)
			{
			LCD_Row_Clear(3);
			LCD_Write_String(3,"        ��# ����");
			}

			//���˸����˲��� 1827072 
			if('*'==Input[i] && i==0)//���˰���*���ż� �����˲���绰
		    {
			    LCD_Row_Clear(1);
				LCD_Row_Clear(2);
				LCD_Row_Clear(3);
				CursorOFF;
				//                  1234567890123456
				LCD_Write_String(1,"�������˵绰��..");
				CloseTimer0();
				
				CallPhone("18270720353");//("13177755134");//���˵绰����
				
				InitTimer();//��ʱ��0��ʼ��Timer0
				//i=0;
				LCD_Write_String(3,"    ��# �Ҷϵ绰");
				while('#'!=Input[i] )
				{
				 Input[i] = KeyScan();
				}

			    LCD_Row_Clear(1);
				LCD_Row_Clear(2);
				LCD_Row_Clear(3);
				CursorOFF;
				//                  1234567890123456
				LCD_Write_String(1,"�Ҷϵ绰...     ");
				Uart1Sends("ATH\r\n");//�ҵ绰
				DelaySec(2);//��ʱ2��

				Delay(1000);
				LCD_Clear();
				
				//                  1234567890123456
				LCD_Write_String(0,"�����ܰ�ȫ��ʿ��");
				LCD_Write_String(1,"����������:     ");
				LCD_Write_String(3,"        ��* ͨ��");
				LCD_Write_Char(0,2,' ');
				i=-1;
			  
	        }  
			
			//���˰���#���ż� ������������ 
			if('#'==Input[i] && i>0)
		    {
			    LCD_Row_Clear(1);
				LCD_Row_Clear(2);
				LCD_Row_Clear(3);
				LCD_Write_String(1,"            ����");
				CursorOFF;
				Delay(1000);
				LCD_Write_String(1,"����������:     ");
				LCD_Write_String(3,"        ��* ͨ��");
				i=-1;
				LCD_Write_Char(0,2,' ');
	        }    

							 
		}

		
		CursorOFF;

		if(0==strcmp(Input,RandPswd) && i>=5)
		{//�������ȷ
			
			strcpy(RandPswd,"******");		  //һ����Ч���ú�ʧЧ
//			LCD_Init();//LCD��ʼ��
			Correct();
			ErrNum=0;
			continue;	
		}
		else
	   	{

	   		if(0!=strcmp(Input,PassWord) && i>=5)
				{//�������
					ErrNum++;
					Error(ErrNum);
					if(ErrNum>=3)	ErrNum=0;
				}
				else
				{
				   Correct();
				   ErrNum=0;
				}
		}
		LCD_Row_Clear(2);
	}
}

//�Ž�ϵͳ����ǰ�ĳ�ʼ�����Ӳ������
void EntranceGuardInit()  
{	
	LCD_Init();//LCD��ʼ��
	BeepOFF;

	init_serial_2();

	InitUART();//����1��ʼ��
				
	InitTimer();//��ʱ��0��ʼ��Timer0
			
	InitGSM();//��ʼ��GSM����
		
}

//������ȷ�Ļ�
void Correct()
{

	
	//LCD_Init();//LCD��ʼ��
	LCD_Row_Clear(1);
	LCD_Row_Clear(2);
	LCD_Row_Clear(3);
	
	//Moto();
	
	//                  1234567890123456
	LCD_Write_String(1,"��ӭ  ���   ^_^");
	OpenDoor();

//��ʾ�Ҿӻ�������
   show_environment_data();

	Delay(1000);
//	ErrNum=0;
	if(flag[5]==0)
	{
	flag[5]=1;
	send_pc_enter(); //���͵�pc	   Debug:2014��9��19��20:39:16
    //�ս��������ɹ���//02 06 00 01 06 01
	}
}

//�������Ļ�
void Error(unsigned int ErrNum)
{
	unsigned int i=0;
	Beep(BEEPT);
	//LCD_Clear();
	LCD_Init();//LCD��ʼ��
	

	if(ErrNum>=3)//3
	{
		 
		
		//                  1234567890123456
		LCD_Write_String(0,"����  ��    ����");
		LCD_Write_Char(2,0,'3'); 		 
		//                  1234567890123456
		LCD_Write_String(2,"�Զ���ϵ����... ");
					 //18270721101
		MakeArandStr();		//��������뵽RandPswd[]
		strcpy(Message,"8B66544AFF1A5BC678018F93516595198BEF8D858FC74E096B21FF01002089E395015BC678014E3A");
		for(i=0;i<6;i++)
		{
			switch(RandPswd[i])
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
			//strcat(Message,ShiftUnicode(RandPswd[i]));
		}
		// '\0'
		CloseTimer0();
				
		SendMessage("00310038003200370030003700320030003300350033",Message);		
		 //18270721101

		InitTimer();//��ʱ��0��ʼ��Timer0
//		strcpy(Message,"8B66544AFF1A5BC678018F93516595198BEF8D858FC74E096B21FF01002089E395015BC678014E3A");
		Delay(50);

		//LCD_Clear();
    	LCD_Init();//LCD��ʼ��	
		
		CursorON;

		LCD_Write_String(0,"������    ������");
		//                  1234567890123456
		LCD_Write_String(1,"��������������");
		//                  1234567890123456
		//LCD_Write_String(2,RandPswd);	//Test
		CloseTimer0();
				
		
		while(1)
		{
			LCD_Write_Char(0,2,' ');
//			beep=1;
			for(i=0;i<6;i++)
			{	
				Input[i] = KeyScan();
				LCD_Write_Char(i,2,Input[i]);
				Delay(400);
				LCD_Write_Char(i,2,'*');
								
//				SendString_serial_2(Str);	 
			}
			
			if(0==strcmp(Input,RandPswd) && i>=5)
			{//������ȷ
				//                    1234567890123456
				strcpy(RandPswd,"******");		  //һ����Ч���ú�ʧЧ
				CursorOFF;
				LCD_Clear();
				LCD_Row_Clear(1);
				LCD_Row_Clear(2);
//				OpenDoor();//Moto();
				//                  1234567890123456
				LCD_Write_String(1,"����������......");
				//                  1234567890123456
				LCD_Write_String(2,"�����ѽ��      ");
				Delay(5000);
				break;
			}
			else
			{
				;
			}
			LCD_Row_Clear(2);
		}
		//ErrNum=0;	�ֲ�����������Ч
		InitTimer();//��ʱ��0��ʼ��Timer0
	}
	
	else
	{

				

	    //LCD_Clear();
		//LCD_Init();//LCD��ʼ��
		LCD_Row_Clear(1);
		LCD_Row_Clear(2);

		Beep(BEEPT);
		//                  1234567890123456
		LCD_Write_String(1,"�������:     ��");
		LCD_Write_Char(6,1,(unsigned char)('0'+ErrNum));
		//                  1234567890123456
		LCD_Write_String(2,"��  �ν�������  ");	 //����������:   ����
		LCD_Write_Char(1,2,'3'); 

		Delay(5000);	
		Delay(50);

		LCD_Row_Clear(1);
		LCD_Row_Clear(2);
	}
	
//		 Debug:2014��9��19��20:39:16
		if(ErrNum==1&&flag[6]==0)//1
	{	  flag[6]=1;
		  send_pc_visit(); //���͵�pc	
         //�շ�����������//02 06 00 01 05 01
    }				

}
