#include<Option.h>


#define FOSC_serial_2   11059200L        //ϵͳƵ��
#define BAUD_serial_2 115200//9600//115200             //���ڲ�����

#define NONE_PARITY     0       //��У��
#define ODD_PARITY      1       //��У��
#define EVEN_PARITY     2       //żУ��
#define MARK_PARITY     3       //���У��
#define SPACE_PARITY    4       //�հ�У��

#define PARITYBIT EVEN_PARITY   //����У��λ

//sfr AUXR  = 0x8e;               //�����Ĵ���
//sfr S2CON = 0x9a;               //UART2 ���ƼĴ���
//sfr S2BUF = 0x9b;               //UART2 ���ݼĴ���
//sfr T2H   = 0xd6;               //��ʱ��2��8λ
//sfr T2L   = 0xd7;               //��ʱ��2��8λ
//sfr IE2   = 0xaf;               //�жϿ��ƼĴ���2

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3

//sfr P_SW2   = 0xBA;             //���蹦���л��Ĵ���2
#define S2_S0 0x01              //P_SW2.0

#define buf_max_Uart2 72//���泤��72
//
unsigned char k_Uart2=0;//,i;
unsigned char rec_buf_Uart2[buf_max_Uart2];//���ջ���

bit busy_serial_2;

void init_serial_2(void);
void SendData_serial_2(BYTE dat);
void SendString_serial_2(char *s);
void send_pc_visit(void);
void send_pc_enter(void);

void init_serial_2()
{
    P_SW2 &= ~S2_S0;            //S2_S0=0 (P1.0/RxD2, P1.1/TxD2)
 // P_SW2 |= S2_S0;             //S2_S0=1 (P4.6/RxD2_2, P4.7/TxD2_2)

#if (PARITYBIT == NONE_PARITY)
    S2CON = 0x50;               //8λ�ɱ䲨����
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S2CON = 0xda;               //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (PARITYBIT == SPACE_PARITY)
    S2CON = 0xd2;               //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif

    T2L = (65536 - (FOSC_serial_2/4/BAUD_serial_2));   //���ò�������װֵ
    T2H = (65536 - (FOSC_serial_2/4/BAUD_serial_2))>>8;
    AUXR = 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
//  IE2 = 0x01;                 //ʹ�ܴ���2�ж�
    IE2 = 0x00;
    EA = 1;



	//SendString_serial_2("1234567890!\r\n");
    //SendString_serial_2("STC15F2K60S2\r\nUart2 Test !\r\n");
   	//SendData_serial_2('a');
//	while(1);
}

/*----------------------------
UART2 �жϷ������
-----------------------------*/
void Uart2() interrupt 8 using 1
{
//    if (S2CON & S2RI)
//    {
//        
//       // P0 = S2BUF;             //P0��ʾ��������
//        //P2 = (S2CON & S2RB8);   //P2.2��ʾУ��λ
//    }
//    if (S2CON & S2TI)
//    {
//        S2CON &= ~S2TI;         //���S2TIλ
//        busy_serial_2 = 0;               //��æ��־
//    }

 	ES=0;	 //�ش����ж�
	S2CON &= ~S2RI;         //���S2RIλ
	rec_buf_Uart2[k_Uart2]=S2BUF;
	if(k_Uart2<buf_max_Uart2)
		k_Uart2++;
	else
		k_Uart2=0;
	ES=1;	 //�������ж�
//		    if(strstr(rec_buf_Uart2,"O")!=NULL)
//	    Uart1Sends("OK");
}

/*----------------------------
���ʹ�������
----------------------------*/
void SendData_serial_2(BYTE dat)
{
	Delay(3);
//    while (busy_serial_2);               //�ȴ�ǰ������ݷ������
    ACC = dat;                  //��ȡУ��λP (PSW.0)
    if (P)                      //����P������У��λ
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON &= ~S2TB8;        //����У��λΪ0
#elif (PARITYBIT == EVEN_PARITY)
        S2CON |= S2TB8;         //����У��λΪ1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON |= S2TB8;         //����У��λΪ1
#elif (PARITYBIT == EVEN_PARITY)
        S2CON &= ~S2TB8;        //����У��λΪ0
#endif
    }

	ES=0;//�ش��п��ж�	
    busy_serial_2 = 1;
    S2BUF = ACC;                //д���ݵ�UART2���ݼĴ���
	while(S2CON & S2TI==0);	//��ѯ�����Ƿ����
		S2CON &= ~S2TI;         //���S2TIλ
	ES=1;//�����п��ж�		
}

/*----------------------------
�����ַ���
----------------------------*/
void SendString_serial_2(char *s)
{
    while (*s)                  //����ַ���������־
    {
        SendData_serial_2(*s++);         //���͵�ǰ�ַ�
    }								  	
}

/*---------------
//���͵�pc	
//�շ�����������+�ɹ���//02 06 00 01 05 01
---------------*/
void send_pc_visit(void)
{
	unsigned char Str[22];	
	int str_i=0;

    //IE2 = 0x00;
	
	{//���͵�pc	
     //�շ�����������//02 06 00 01 05 01  
		Str[0]=0x02;
		Str[1]=0x06;
		Str[2]=0x00;
		Str[3]=0x01;	
		Str[4]=0x05;	
		Str[5]=0x01;	
	}		
	for(str_i=0;str_i<=5;str_i++)
	SendData_serial_2(Str[str_i]);
	//SendString_serial_2(Str);

    //IE2 = 0x01;                 //ʹ�ܴ���2�ж�
}


/*---------------
//���͵�pc	
//�ս��������ɹ���//02 06 00 01 06 01
---------------*/
void send_pc_enter(void)
{
	unsigned char Str2[22];	
	int str_i2=0;

    //IE2 = 0x00;
	
	{//���͵�pc	
     //�շ�����������+�ɹ���//02 06 00 01 06 01  
		Str2[0]=0x02;
		Str2[1]=0x06;
		Str2[2]=0x00;
		Str2[3]=0x01;	
		Str2[4]=0x06;	
		Str2[5]=0x01;	
	}		
	for(str_i2=0;str_i2<=5;str_i2++)
	SendData_serial_2(Str2[str_i2]);
	//SendString_serial_2(Str);

    //IE2 = 0x01;                 //ʹ�ܴ���2�ж�
}