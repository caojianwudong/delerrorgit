// CWriteLog.cpp: implementation of the CWriteLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CreateTaskForChangedRoad.h"
#include "CWriteLog.h"
#include <afxsock.h>
#include "winsock.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWriteLog::CWriteLog()
{
	m_strLogPath = "" ;
	m_bCreateLog = false ;
}

CWriteLog::~CWriteLog()
{
	
}

bool CWriteLog::WriteLog( CString msg )
{
	SYSTEMTIME st;
	CString strDate;
	GetLocalTime(&st);
	strDate.Format("\\%d-%d-%d-%d_runlog.log",st.wYear,st.wMonth,st.wDay,st.wHour) ;
	
	CString strFilePathName = m_strLogPath + strDate ;
	if ( !stfile.Open( strFilePathName, CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate))
	{
		return false ;
	}

	stfile.SeekToEnd() ;
	
	CString strTime;
	GetLocalTime( &st );
	strTime.Format("%d-%d-%d %d:%d:%d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds) ;
	
	strTime += "			" + msg ;
	stfile.WriteString(strTime) ;

	stfile.Close() ;
	return true ;
// #ifdef _DEBUG
/*
	if ( m_bCreateLog)
	{
		stfile.SeekToEnd() ;

		SYSTEMTIME st;
		CString strDate,strTime;
		GetLocalTime( &st );
		strTime.Format("%d-%d-%d %d:%d:%d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds) ;

		strTime += "			" + msg ;
		stfile.WriteString(strTime) ;
		return true ;
	}
*/
// #endif

	return false ;
}

void CWriteLog::SetLogPath( CString strLogPath )
{
	m_strLogPath = strLogPath ;
	m_strLogPath.TrimRight( "\\" );
}

bool CWriteLog::CreateLog()
{
/*
	if ( m_bCreateLog == false)
	{
		SYSTEMTIME st;
		CString strDate;
		GetLocalTime(&st);
		strDate.Format("\\%d-%d-%d-%d_runlog.log",st.wYear,st.wMonth,st.wDay,st.wHour) ;

		CString strFilePathName = m_strLogPath + strDate ;
		if ( !stfile.Open( strFilePathName, CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate))
		{
			return false ;
		}
		m_bCreateLog = true ;
	}
*/
	return m_bCreateLog ;
	
}

bool CWriteLog::CloseLog()
{
/*
	if ( m_bCreateLog)
	{
		stfile.Close() ;
		m_bCreateLog = false ;
		return true ;
	}
*/
	return true ;
}

const char* CWriteLog::GetIp()
{
	WSADATA wsaData;  
    char name[155];      //�������ڴ�Ż���������ı���  
	//     char *ip;            //����IP��ַ����  
    PHOSTENT hostinfo;   

    //����MAKEWORD()���Winsocl�汾����ȷֵ����������ļ���Winscok��  
    if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )   
    {   //����Winsock�⣬���WSAStartup()��������ֵΪ0��˵�����سɹ���������Լ�������ִ��  
        if( gethostname ( name, sizeof(name)) == 0)   
        { //����ɹ����������������������name����ָ���Ļ�������  
            if((hostinfo = gethostbyname(name)) != NULL)   
            { //���ǻ�ȡ�������������������ɹ��Ļ���������һ��ָ�룬ָ��hostinfo,hostinfoΪPHOSTENT�͵ı�����  
                m_strIp = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);   
                //inet_addr()�����ѵ�ַ��ת��ΪIP��ַ  
                //����inet_ntoa()����,��hostinfo�ṹ�����е�h_addr_listת��Ϊ��׼��IP��ַ(��202.197.11.12.)  
				//                 printf(" IP��ַ: %s/n",ip);        //���IP��ַ  
            }   
        }   
        WSACleanup();         //ж��Winsock�⣬���ͷ�������Դ  
    } 
	
	return m_strIp ;
}
