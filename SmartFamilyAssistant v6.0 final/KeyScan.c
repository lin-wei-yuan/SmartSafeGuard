#include "Option.h"
/******************************����ΪӲ�����***********************/

unsigned char BG[4]={0x7f,0xbf,0xdf,0xef};//���尴���ӵ�ɨ��
unsigned char KEY[4][4]={
	{'a','3','2','1'},
	{'b','6','5','4'},
	{'c','9','8','7'},	//������		
//    {'7','c','9','8'},	//�쳣��
	{'d','#','0','*'}
};

unsigned char KeyScan()
{
	unsigned int Delaytime=150;
	unsigned int i;
	while(1)
	{
		for(i=0;i<=3;i++)
		{
			//P1 = BG[i];//����ɨ�� p2
			switch(i)
			{
			 case  0:{P1&=~0x80;P1|=0x7c;}	 break;
			 case  1:{P1&=~0x40;P1|=0xbc;}	 break;
			 case  2:{P1&=~0x20;P1|=0xdc;}	 break;
			 case  3:{P1&=~0x10;P1|=0xec;}	 break;
			 default:;
			}

			if(0==A0)
				Delay(Delaytime);
			if(0==A0)//��������
			{	  
				return KEY[0][i];
			}
			if(0==A1)
				Delay(Delaytime);
			if(0==A1)//��������
			{
				return KEY[1][i];
			}
			//if(0==A2)
			//	Delay(1);//(Delaytime/2);
			if(0==A2)//��������
			{
				return KEY[2][i];
			}
			if(0==A3)
				Delay(Delaytime);
			if(0==A3)//��������
			{
				return KEY[3][i];
			}
		}
	}
}
/******************************����ΪӲ�����***********************/