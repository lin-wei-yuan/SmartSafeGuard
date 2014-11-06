/*******************************************************************************
**		Fliename:ConfigMgr.cpp
**      Description:�����ļ��Ĺ���ȫ��������
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#include "stdafx.h"
#include "ConfigMgr.h"


CConfigMgr::CConfigMgr(CString strFileName)
{
	char buffer[127];
	if((m_fpConfFile = fopen(strFileName,"r")) == 0)
	{
		AfxMessageBox("�����ļ���ʧ�ܣ����������ļ��Ƿ����!");
		exit(0);
	}
	else
	{
		while(fgets(buffer,127,m_fpConfFile))
		{
			m_arrConfigs.Add(CString(buffer));
		}
	}
	if(m_fpConfFile != NULL)
	{
		fclose(m_fpConfFile);
	}
}

CConfigMgr::~CConfigMgr()
{
	if(m_fpConfFile != NULL)
	{
		fclose(m_fpConfFile);
	}
	SaveConfig();
}
/** ��ȡ�������ֵ
	@param name:����������
*/
CString CConfigMgr::GetConfigItem(CString name)
{
	int items = m_arrConfigs.GetSize();
	int i;
	CString strConf;
	for(i = 0;i < items;i ++)
	{
		if(m_arrConfigs[i].Find('#') != 0 && name == m_arrConfigs[i].Left(m_arrConfigs[i].Find('=')))
		{
			strConf = m_arrConfigs[i].Right(m_arrConfigs[i].GetLength() - m_arrConfigs[i].Find('=') - 1);
			strConf.Remove('\n');
			return strConf;
		}
	}
#ifdef __DEBUG__
	AfxMessageBox(CString("��ȡ��") + name + "��ʧ��");
#endif
	return "";
}

/** ����������
	@param item:����������
	@param value:����ֵ
*/
void CConfigMgr::SetConfigItem(CString item, CString value)
{
	int items = m_arrConfigs.GetSize();
	int i;
	CString strConf;
	for(i = 0;i < items;i ++)
	{
		if(m_arrConfigs[i].Find('#') != 0 && item == m_arrConfigs[i].Left(m_arrConfigs[i].Find('=')))
		{
			m_arrConfigs[i] = item + '=' + value + '\n';
			return ;
		}
	}
	m_arrConfigs.Add("\n" + item + '=' + value + '\n');
}

void CConfigMgr::SaveConfig()
{
	m_fpConfFile = fopen("WisdomWellServer.conf","w+");
	
	if(m_fpConfFile == 0)
	{
		AfxMessageBox("�ļ���ʧ�ܣ�");
		exit(0);
	}
	//fputs("#affffffffffffffffffffffffffffffffff",m_fpConfFile);
	int items = m_arrConfigs.GetSize();
	int i;
	for(i = 0;i < items;i ++)
	{
		fputs(m_arrConfigs[i],m_fpConfFile);
	}

	fclose(m_fpConfFile);
	//m_fpConfFile = fopen("WisdomWellServer.conf","r");

}
