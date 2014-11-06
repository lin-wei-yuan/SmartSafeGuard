/*******************************************************************************
**		Fliename:DataDispatch.h
**      Description:����֡����ת�����ַ�
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#if !defined(AFX_DATADISPATCH_H__CD5ED693_2F46_4457_AFD4_D64EE117A17C__INCLUDED_)
#define AFX_DATADISPATCH_H__CD5ED693_2F46_4457_AFD4_D64EE117A17C__INCLUDED_
#include "WisdomWellServerDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		UDCODE_TYPE_CTRL		0x01	//������
#define		UDCODE_TYPE_DATA		0x02    //������
#define		UDCODE_TYPE_RET			0x03	//������
#define		UDCODE_TYPE_ROUTE		0x04	//·����
#define		UDCODE_TYPE_EMER		0xFF	//������

#define		UDCODE_SOURCE_TWG		0x10     //��ʪ�ȡ���ȼ����Ũ������
#define		UDCODE_SOURCE_TEM		0x01	 //�¶�
#define		UDCODE_SOURCE_SIM		0x02	 //ʪ��
#define		UDCODE_SOURCE_AIR		0x03     //��ȼ����Ũ��
#define		UDCODE_SOURCE_PRE		0x04     //ѹ������������
#define		UDCODE_SOURCE_RFID_TOP	0x05     //����RFID����
#define		UDCODE_SOURCE_RFID_BOT	0x06	 //����RFID����
#define		UDCODE_SOURCE_CAR_STAT	0x07	 //��״̬����

#define		UDCODE_DEST_TIME		0x81	 //ʱ������
#define		UDCODE_DEST_PASSWORD	0x82	 //����������
#define		UDCODE_DEST_YIELD_DAILY	0x83	 //�����ղɿ���
#define		UDCODE_DEST_PHONENUM	0x84	 //�����Ͷ��ŵĺ���
#define		UDCODE_DEST_VMECHINE	0x85	 //��������ת��



#define		UDCODE_ZIGBEE_PC			0x0001	//PC��ZigBee��ַ
#define		UDCODE_ZIGBEE_A				0x0002	//ZigBee-A�ˣ���λ��б������ն�1��
#define		UDCODE_ZIGBEE_B				0x0004	//ZigBee-B�ˣ���λ��б������ն�2��
#define		UDCODE_ZIGBEE_WELL_TOP		0x0008	//ZigBee�������ضˣ���λ�ھ��ϳ��ڴ�������ϵͳ����Ϣ�������ģ�
#define		UDCODE_ZIGBEE_WELL_BOTTOM	0x0010	//ZigBee-�������ضˣ���λ�ھ��³��ڴ���
#define		UDCODE_ZIGBEE_BROADCAST		0x0000	//Zigbee�㲥

#define		UDCODE_TARGET_PEDESTRAINDOOR_TOP		0x01	//����������
#define		UDCODE_TARGET_PEDESTRAINDOOR_BOTTOM		0x03	//����������
#define		UDCODE_TARGET_SAFEDOOR_1				0x05	//��ȫ��1
#define		UDCODE_TARGET_SAFEDOOR_2				0x06	//��ȫ��2
#define		UDCODE_TARGET_CARDOOR_TOP				0x02	//���ϳ�����
#define		UDCODE_TARGET_CARDOOR_BOTTOM			0x04	//���³�����
#define		UDCODE_TARGET_MECHINE					0x07	//�����

#define		UDCODE_ACTION_START			0x03	//����
#define		UDCODE_ACTION_STOP			0x04	//ֹͣ
#define		UDCODE_ACTION_OPEN			0x01	//��
#define		UDCODE_ACTION_CLOSE			0x02	//�ر�

typedef struct _TWGStruct//weiyuan-change2014��7��22��14:42:07
{
	char t; //�¶�//float
	char w; //ʪ��
	char g; //��ȼ����Ũ��
}   TWGSTRUCT,*PTWGSTRUCT;

typedef struct _CarStatus
{
	int position;	//��λ�ã� ����0 ��ͨ��һ1 ��ͨ����2 ����3
	char velocity;	//���ٶ�
	int direction;	//0ֹͣ 1���� 2����
	int HarvMon_warn;	//0���� 1�ܳ�
}CARSTATUS,*PCARSTATUS;	//״̬



typedef unsigned short ZIGBEEADDR;

class CDataDispatch  
{
public:
	static CDataDispatch* CreateDataFrame(unsigned short toAddr,BYTE type,BYTE *content,int contentlen);
	void SendFrame();
	static CDataDispatch* CreateControlFrame(unsigned short toAddr,BYTE target,BYTE action);
	void DispatchFrame();
	CDataDispatch();
	CDataDispatch(BYTE* bytes,int len,CWisdomWellServerDlg * dialog);
	virtual ~CDataDispatch();

private:
	void ResponseVMechine();
	void ResponsePhoneNum();
	void ResponseYieldDaily();
	void ResponsePassword();
	void ResponseTime();
	long CodeToRFID(BYTE *bts);
	CARSTATUS CodeToCarStatus(BYTE *bts);
	CWisdomWellServerDlg * m_dlgMain;
	TWGSTRUCT CodeToTWGStruct(BYTE *bts);
	CString CodeToCString(BYTE * bts,int len);
	float CodeToFloat(BYTE* bts);
	void DispatchData();
	BYTE m_btSource;
	ZIGBEEADDR m_addrTo;
	ZIGBEEADDR m_addrFrom;
	BYTE m_btType;
	BYTE m_btContent[1024];
	int m_iLength;
};

#endif // !defined(AFX_DATADISPATCH_H__CD5ED693_2F46_4457_AFD4_D64EE117A17C__INCLUDED_)
