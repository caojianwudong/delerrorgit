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
    char name[155];      //定义用于存放获得主机名的变量  
	//     char *ip;            //定义IP地址变量  
    PHOSTENT hostinfo;   

    //调用MAKEWORD()获得Winsocl版本的正确值，用于下面的加载Winscok库  
    if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )   
    {   //加载Winsock库，如果WSAStartup()函数返回值为0，说明加载成功，程序可以继续往下执行  
        if( gethostname ( name, sizeof(name)) == 0)   
        { //如果成功，将本地主机名存放入由name参数指定的缓冲区中  
            if((hostinfo = gethostbyname(name)) != NULL)   
            { //这是获取主机，如果获得主机名成功的话，将返回一个指针，指向hostinfo,hostinfo为PHOSTENT型的变量。  
                m_strIp = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);   
                //inet_addr()函数把地址串转换为IP地址  
                //调用inet_ntoa()函数,将hostinfo结构变量中的h_addr_list转化为标准的IP地址(如202.197.11.12.)  
				//                 printf(" IP地址: %s/n",ip);        //输出IP地址  
            }   
        }   
        WSACleanup();         //卸载Winsock库，并释放所有资源  
    } 
	
	return m_strIp ;
}
