/*******************************************************************************
**		Fliename:DataDispatch.cpp
**      Description:����֡����ת�����ַ�
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "DataDispatch.h"
#include "ConfigMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataDispatch::CDataDispatch()
{

}
CDataDispatch::CDataDispatch(BYTE* bytes,int len,CWisdomWellServerDlg *dialog) : m_iLength(len),m_dlgMain(dialog)
{
	memcpy(m_btContent,bytes,len);
	m_btType = m_btContent[0];

}

CDataDispatch::~CDataDispatch()
{

}
/**  �ַ����յ���֡
*/
void CDataDispatch::DispatchFrame()
{//�ϵ� ֡����
	switch(m_btType)
	{
	case UDCODE_TYPE_CTRL:    //�ַ�����֡

		break;
	case UDCODE_TYPE_DATA://weiyuan_change2014��7��22��14:36:37//�����ַ����
		/*m_addrTo = (unsigned short)m_btContent[2] * 256 + (unsigned short) m_btContent[3]; 
		if(m_addrTo != UDCODE_ZIGBEE_PC)
		{
			return;
		}*/ //00 01

		m_btSource = m_btContent[4];
		DispatchData();				//�ַ�����֡
		break;
	case UDCODE_TYPE_EMER:		//�ַ�����
		//m_iLength = 0x02;
		//m_btContent[2]=0x02;
		::SendMessage(this->m_dlgMain->m_hWnd,UM_CAR_RUN_AWAY,0,0);
		break;
	case UDCODE_TYPE_RET:		//�ַ�����֡
		break;
	case UDCODE_TYPE_ROUTE:		//�ַ�·��֡
		break;

	}
}

/** �������ڷַ�����
*/
void CDataDispatch::DispatchData()
{//
	//TWGSTRUCT twg;
	//CARSTATUS cst;
	CDataDispatch d;

  	switch(m_btSource)//weiyuan-change2014��7��22��14:37:20//�б� //8650110-1-switch
	{
	/*
#define		UDCODE_SOURCE_TWG		0x10     //��ʪ�ȡ���ȼ����Ũ������
#define		UDCODE_SOURCE_TEM		0x01	 //�¶�
#define		UDCODE_SOURCE_SIM		0x02	 //ʪ��
#define		UDCODE_SOURCE_AIR		0x03     //��ȼ����Ũ��
#define		UDCODE_SOURCE_PRE		0x04     //ѹ������������
#define		UDCODE_SOURCE_RFID_TOP	0x05     //����RFID����
#define		UDCODE_SOURCE_RFID_BOT	0x06	 //����RFID����
#define		UDCODE_SOURCE_CAR_STAT	0x07	 //��״̬����*/
	case UDCODE_SOURCE_TEM://ok
		m_dlgMain->SetT(m_btContent[5]);
		break;
	case UDCODE_SOURCE_SIM://ok
		m_dlgMain->SetW(m_btContent[5]);
		break;
	case UDCODE_SOURCE_AIR://ok
		m_dlgMain->SetG(m_btContent[5]);
		break;
	case UDCODE_SOURCE_PRE://weight
		m_dlgMain->SetWeight(m_btContent[5]);
		break;
	case UDCODE_SOURCE_RFID_TOP://RFID��
		m_dlgMain->TopRfidTrigger(m_btContent[5]);//RFID��weiyuan
		//m_dlgMain->TopRfidTrigger(CodeToRFID(&m_btContent[5]));//RFID��//�ṹ������������޷�����
		break;
	case UDCODE_SOURCE_RFID_BOT://RFID��
		m_dlgMain->BottomRfidTrigger(m_btContent[5]);//RFID��weiyuan
		//m_dlgMain->BottomRfidTrigger(CodeToRFID(&m_btContent[5]));//RFID��
		break;
	case UDCODE_SOURCE_TWG://ok			//��ʪ�����ݴ���//weiyuan_change2014��7��22��15:22:56
		//twg = CodeToTWGStruct(&m_btContent[5]);//!!
		m_dlgMain->SetTWG(m_btContent[5],m_btContent[6],m_btContent[7],m_btContent[8],m_btContent[9],m_btContent[10]);//m_dlgMain->SetTWG(twg.t,twg.w,twg.g);//!!weiyuan��
		break;
	case UDCODE_SOURCE_CAR_STAT:	//С��״̬//02 09 00 00 07  01 01 01 01
		//cst = CodeToCarStatus(&m_btContent[5]);
		
		//CDialog::OnPaint();
		m_dlgMain->SetCarStatus(m_btContent[5],m_btContent[6],m_btContent[7],m_btContent[8]);//
		//m_dlgMain->SetCarStatus(cst.position,cst.direction,cst.velocity,cst.HarvMon_warn);
		break;
	/**************************************************************************************
	�������Ը��ڵ������
	***************************************************************************************/
	case UDCODE_DEST_TIME://81 
		ResponseTime();	//02 06 00 01 81 00 08
		break;
	case UDCODE_DEST_PASSWORD://82
		ResponsePassword();//02 06 00 01 82 00 08
		break;
	case UDCODE_DEST_YIELD_DAILY:
		ResponseYieldDaily();
		break;
	case UDCODE_DEST_PHONENUM:
		ResponsePhoneNum();
		break;
	case UDCODE_DEST_VMECHINE:
		ResponseVMechine();
		break;
	default:
		break;	
	}
     ResponseTime();	//02 06 00 01 81 00 08
     ResponsePassword();//02 06 00 01 82 00 08
}

float CDataDispatch::CodeToFloat(BYTE *bts)
{
	float f;
	memcpy((void *)&f,bts,sizeof(f));
	return f;
}

CString CDataDispatch::CodeToCString(BYTE *bts, int len)
{
	int i;
	char chs[1024];
    
	for(i = 0;i < len;i ++)
	{
		chs[i] = bts[i];
	}
	chs[i] = 0;
	return CString(chs);
}

TWGSTRUCT CDataDispatch::CodeToTWGStruct(BYTE *bts)
{
	TWGSTRUCT result;
	memcpy(&result,(void *)bts,sizeof(TWGSTRUCT));
	return result;
}

CARSTATUS CDataDispatch::CodeToCarStatus(BYTE *bts)
{
	CARSTATUS cst;
	memcpy(&cst,(void *)bts,sizeof(CARSTATUS));
	return cst;
}

long CDataDispatch::CodeToRFID(BYTE *bts)
{
	long result;
	memcpy(&result,(void *)bts,sizeof(long));
	return result;
}

/** ����һ������֡
	@param toAddr:����Ŀ���Zigbee�̵�ַ
	@param target:���͵����豸��ʶ
	@param action:����
*/
CDataDispatch* CDataDispatch::CreateControlFrame(unsigned short toAddr, BYTE target, BYTE action)
{
	
	BYTE content[5];
	content[0] = UDCODE_TYPE_CTRL;//0x0
	content[1] = 0x05;
	memcpy(&content[2],&toAddr,sizeof(toAddr));
	content[4] = action;

	return new CDataDispatch(content,5,(CWisdomWellServerDlg *)AfxGetApp()->GetMainWnd()); 
}


/** ����֡������ 

*/
void CDataDispatch::SendFrame()
{
	m_dlgMain->SendFrame(m_btContent,m_iLength);
}
/** ����һ������֡
	@param toAddr:����Ŀ���Zigbee�̵�ַ
	@param type:���͵����豸��ʶ
	@param content:����
	@param contentlen:���ݳ���
*/
CDataDispatch* CDataDispatch::CreateDataFrame(unsigned short toAddr, BYTE type, BYTE *content,int contentlen)
{
	BYTE data[255];
	data[0] = UDCODE_TYPE_DATA;
	data[1] = contentlen + 5;
	memcpy(&data[2],&toAddr,sizeof(toAddr));
	data[4] = type;
	memcpy(&data[5],content,contentlen);

	return new CDataDispatch(data,(int)data[1],(CWisdomWellServerDlg *)AfxGetApp()->GetMainWnd()); 
}

/**  �㲥��ǰʱ��

*/
void CDataDispatch::ResponseTime()//8650110-81//weiyuan-chang2014��7��24��15:32:42 ---ok!!
{
	CUTime t;//CUTime tnow;//CUTime
//	int unixTime = t.GetUnixTime();
	//m_addrTo = 0x0008;//UDCODE_ZIGBEE_BROADCAST;
	m_btContent[0] = UDCODE_TYPE_DATA;
	m_btContent[1] = 0x0B;
	m_iLength = 0x0B;
	m_btContent[2] = 0x00;
	m_btContent[3] = 0x08;
	//memcpy(&m_btContent[2],&m_addrTo,sizeof(m_addrTo));
	m_btContent[4] = UDCODE_DEST_TIME;

    m_btContent[5]=t.m_year%16;//0x15;02 0B 00 00 81 0E 07 18 10 29 05 //0E 2014
    m_btContent[6]=t.m_mon;//0x15;//07  //02 0B 00 00 81 0E 07 18 10 2D 3A
	m_btContent[7]=t.m_day;//0x15;
	m_btContent[8]=t.m_h;//0x15;
	m_btContent[9]=t.m_m;//0x15;
	m_btContent[10]=t.m_s;//0x15;
	//memcpy(&m_btContent[5],&unixTime,sizeof(int));

	this->SendFrame();

	//	sprintf(result,"%4d/%2d/%2d %2d:%2d:%2d",m_year,m_mon,m_day,m_h,m_m,m_s);
	/*  02 09 00 00 81 95 DC D2 53
	ʱ�����ݣ�(0x81)
    //zigbee��������ʱ��//ok
    if(zigbee_rec_out==81)//02 0B 00 00 81 0E 07 18 10 2D 3A
	{   

      //OSMboxPost(RTC_Mbox,(void*)&RTC_data);//�ȴ���zigbee����RTC����RTC_Mbox
	   RTC_Time_Set(recdata[5],recdata[6],recdata[7],recdata[8],recdata[9],recdata[10]);
	   // RTC_Time_Set(0x15,0x8,0x16,0x13,0x12,0x42);
	}//                ��  ��  ��   ʱ   ��    ��
	*/
	
}
/**  Ӧ������
*/

void CDataDispatch::ResponsePassword()//8650110-82//weiyuan-chang2014��7��24��15:32:42//�����������
{
	CConfigMgr mgr;
	CString passwd = mgr.GetConfigItem("Password");//mgr.GetConfigItem("password");//m_strPassword
    //CString passwd = m_dlgMain->m_confMgr.GetConfigItem(CString("Password"));

	
	//m_addrTo = 0x0008;//(unsigned short)m_btContent[5] * 256 + (unsigned short) m_btContent[6];
	m_btContent[0] = UDCODE_TYPE_DATA;
	m_btContent[1] = 0x0B;//passwd.GetLength() + 5;
	m_iLength = 11;//passwd.GetLength() + 5;
	m_btContent[2] = 0x00;
	m_btContent[3] = 0x08;
	//memcpy(&m_btContent[2],&m_addrTo,sizeof(m_addrTo));
	m_btContent[4] = UDCODE_DEST_PASSWORD;
	memcpy(&m_btContent[5],passwd,passwd.GetLength());
	this->SendFrame();
	/*
    ����������
BYTE0	BTYE1	BYTE2	BYTE3	BYTE4	BYTE5	BYTE6
0x02	0x07	PC-Zigbee�̵�ַ	0x82	ԴZigbee�̵�ַ

	�������ݣ�(0x82)
    if(zigbee_rec_out==82)//02 06 01 01 82 35 36 37 38 39 30 
	{   
          official_password[0]=recdata[5];
          official_password[1]=recdata[6];
          official_password[2]=recdata[7];
          official_password[3]=recdata[8];
          official_password[4]=recdata[9];
          official_password[5]=recdata[10];
     }
	*/
} 

/** Ӧ��ǰ�ղ���
*/

void CDataDispatch::ResponseYieldDaily()
{
	CModel m("yield");
	char sql[255];
	CUTime t;
	CUTime tMor(t.m_year,t.m_mon,t.m_day,0,0,0);
	sprintf(sql,"SELECT SUM(CWeight) from Car where CTime>%d",tMor.GetUnixTime());
	MYSQL_RES *res = m.Query(sql);
	MYSQL_ROW row;
	float dYield;
	if(res != 0)
	{
		row = mysql_fetch_row(res);
		
		dYield = atof(row[0]);
		m_addrTo = (unsigned short)m_btContent[5] * 256 + (unsigned short) m_btContent[6];
		m_btContent[0] = UDCODE_TYPE_DATA;
		m_btContent[1] = 0x09;
		m_iLength = 0x09;
		memcpy(&m_btContent[2],&m_addrTo,sizeof(m_addrTo));
		m_btContent[4] = UDCODE_DEST_YIELD_DAILY;
		memcpy(&m_btContent[5],&dYield,sizeof(float));
	}
}

/** Ӧ��GSM����
*/

void CDataDispatch::ResponsePhoneNum()
{
	CString phNum = m_dlgMain->m_confMgr.GetConfigItem(CString("PhoneNum"));
	
	m_addrTo = (unsigned short)m_btContent[5] * 256 + (unsigned short) m_btContent[6];
	m_btContent[0] = UDCODE_TYPE_DATA;
	m_btContent[1] = phNum.GetLength() + 5;
	m_iLength = phNum.GetLength() + 5;
	memcpy(&m_btContent[2],&m_addrTo,sizeof(m_addrTo));
	m_btContent[4] = UDCODE_DEST_PHONENUM;
	memcpy(&m_btContent[5],phNum,phNum.GetLength());
	this->SendFrame();
}

/** Ӧ������ת��
*/
void CDataDispatch::ResponseVMechine()
{
	CString vMechine = m_dlgMain->m_confMgr.GetConfigItem(CString("VMechine"));
	
	int v = atoi(vMechine);
	m_addrTo = (unsigned short)m_btContent[5] * 256 + (unsigned short) m_btContent[6];
	m_btContent[0] = UDCODE_TYPE_DATA;
	m_btContent[1] = 0x09;
	m_iLength = 0x09;
	memcpy(&m_btContent[2],&m_addrTo,sizeof(m_addrTo));
	m_btContent[4] = UDCODE_DEST_VMECHINE;
	memcpy(&m_btContent[5],&v,sizeof(int));
	
	this->SendFrame();
}
