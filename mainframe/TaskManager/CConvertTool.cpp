// CConvertTool.cpp: implementation of the CConvertTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CConvertTool.h"

//test,获取ip用
#include   <winsock.h> 
#include   <wsipx.h> 
#include   <wsnwlink.h>
#pragma comment(lib, "ws2_32")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConvertTool::CConvertTool()
{

}

CConvertTool::~CConvertTool()
{

}

// Construction/Destruction
/* 
* Copyright (c) 2010,ｚｙｑ５９４５@126.com
* All rights reserved. 
*  
* 文件名称：Convert.cpp 
* 文件标识：数据类型转换
* 摘    要：主要简化ADO中数据类型的转换 
*  
* 当前版本：1.0 
* 作    者：ｚｙｑ５９４５@126.com（注意把中文字符换成英文字符）
* 完成日期：2010年5月11日 
* 发布Blog：http://blog.csdn.net/zyq5945/
* 
*/ 
//////////////////////////////////////////////////////////////////////
CConvertTool Convert;
CString CConvertTool::ToString(BYTE btValue)
{
	CString strValue;
	strValue.Format(_T("%d"), btValue);
	return strValue;
}

void CConvertTool::bytesTochars( byte *bytes, char *chars, int size)
{
	for ( int i=0; i<size; i++)
	{
		chars[i] = (char) (bytes[i]);
	}
}

void CConvertTool::charsToBytes( char *chars, byte *bytes, int size)
{
	for ( int i=0; i<size; i++)
	{
		bytes[i] = (byte)chars[i];
	}
}

CString CConvertTool::ToString(int iValue)
{
	CString strValue;
	strValue.Format(_T("%d"), iValue);
	return strValue;
}
CString CConvertTool::ToString(unsigned int iValue)
{
	CString strValue;
	strValue.Format(_T("%u"), iValue);
	return strValue;
}
CString CConvertTool::ToString(long lValue)
{
	CString strValue;
	strValue.Format(_T("%d"), lValue);
	return strValue;
}
CString CConvertTool::ToString(unsigned long lValue)
{
	CString strValue;
	strValue.Format(_T("%u"), lValue);
	return strValue;
}
CString CConvertTool::ToString(__int64 i64Value)
{
	CString strValue;
	strValue.Format(_T("%I64d"), i64Value);
	return strValue;
}
CString CConvertTool::ToString(unsigned __int64 i64Value)
{
	CString strValue;
	strValue.Format(_T("%I64u"), i64Value);
	return strValue;
}
CString CConvertTool::ToString(float fltValue)
{
	CString strValue;
	strValue.Format(_T("%f"), fltValue);
	return strValue;
}
CString CConvertTool::ToString(double dblValue)
{
	CString strValue;
	strValue.Format(_T("%f"), dblValue);
	return strValue;
}
// 时间输出格式：2010-05-06 22:07:08
CString CConvertTool::ToString(const COleDateTime& time)
{
	CString strValue;
	strValue = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	return strValue;
}
CString CConvertTool::ToString(const _variant_t& var)
{
	CString strValue;
	switch (var.vt)
	{
	case VT_BSTR: //字符串
	case VT_LPSTR:
	case VT_LPWSTR:
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1:   //无符号字符
	case VT_UI1:
		strValue.Format(_T("%d"), var.bVal);
		break;
	case VT_I2:   //短整型
		strValue.Format(_T("%d"), var.iVal);
		break;
	case VT_UI2:   //无符号短整型
		strValue.Format(_T("%u"), var.uiVal);
		break;
	case VT_INT: //整型
		strValue.Format(_T("%d"), var.intVal);
		break;
	case VT_I4:   //整型
	case VT_I8:   //长整型
		strValue.Format(_T("%d"), var.lVal);
		break; 
	case VT_UINT:   //无符号整型
		strValue.Format(_T("%d"), var.uintVal);
		break;
	case VT_UI4:    //无符号整型
	case VT_UI8:    //无符号长整型
		strValue.Format(_T("%d"), var.ulVal);
		break;
	case VT_VOID:
		strValue.Format(_T("%08x"), var.byref);
		break;
	case VT_R4:   //浮点型
		strValue.Format(_T("%.15lf"), var.fltVal);
		break;
	case VT_R8:   //双精度型
		strValue.Format(_T("%f"), var.dblVal);
		break;
	case VT_DECIMAL: //小数
		strValue.Format(_T("%f"), (double)var);
		break;
	case VT_CY:
		{
			COleCurrency cy = var.cyVal;
			strValue = cy.Format();
		}
		break;
	case VT_BLOB:
	case VT_BLOB_OBJECT:
	case 0x2011:
		strValue = _T("[BLOB]");
		break;
	case VT_BOOL:   //布尔型  
		strValue = var.boolVal ? _T("TRUE") : _T("FALSE");
		break;
	case VT_DATE: //日期型
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt);
			strValue = da.Format(_T("%Y-%m-%d %H:%M:%S"));
		}
		break;
	case VT_NULL://NULL值
	case VT_EMPTY:   //空
		strValue = _T("");
		break;
	case VT_UNKNOWN:   //未知类型
	default:
		strValue = _T("VT_UNKNOW");
		break;
	}
	
	return strValue;
}

int CConvertTool::ToInt(const _variant_t& var)
{
	int iValue = -1;
	CString strValue;
	switch (var.vt)
	{
	case VT_INT:
		iValue = var.intVal;
		break;
	case VT_NULL:
		iValue = -1;
		break;
	case VT_I1:   //无符号字符
	case VT_UI1:
		iValue = var.bVal;
		break;
	case VT_I2:   //短整型
		iValue = var.iVal;
		break;
	case VT_UI2:   //无符号短整型
		iValue = var.uiVal;
		break;
	case VT_I4:   //整型
	case VT_I8:   //长整型
		iValue = var.lVal;
		break;
	case VT_UINT:   //无符号整型
		iValue = var.uintVal;
		break;
	case VT_UI4:    //无符号整型
	case VT_UI8:    //无符号长整型
		iValue = var.ulVal;
		break;
	case VT_VOID:
		strValue.Format(_T("%08x"), var.byref);
		iValue = atoi( strValue);
		break;
	case VT_R4:   //浮点型
		strValue.Format(_T("%f"), var.fltVal);
		break;
	case VT_R8:   //双精度型
		strValue.Format(_T("%f"), var.dblVal);
		break;
	case VT_DECIMAL: //小数
		strValue.Format(_T("%f"), (double)var);
		iValue = atoi( strValue);
		break;
	case VT_BSTR: //字符串
	case VT_LPSTR:
	case VT_LPWSTR:
		strValue = (LPCTSTR)(_bstr_t)var;
		iValue = atoi( strValue);
		break;
	}
	return iValue;
}

double CConvertTool::ToDouble(const _variant_t& var)
{
	double dValue = 0;
	CString strValue;
	switch (var.vt)
	{
	case VT_R4:   //浮点型
		dValue = var.fltVal; 
		break;
	case VT_R8:   //双精度型
		dValue = var.dblVal;
		break;
	case VT_DECIMAL: //小数
		dValue = (double)var;
		break;
	case VT_NULL:
		dValue = 0;
		break;
	case VT_BSTR: //字符串
	case VT_LPSTR:
	case VT_LPWSTR:
		strValue = (LPCTSTR)(_bstr_t)var;
		dValue = atof( strValue);
		break;
	default:
		CString smsg;
		smsg.Format(_T("var.vt=%d,ToDouble error!"),var.vt);
		AfxMessageBox(smsg);
		break;
	}
	return dValue;
}

SYSTEMTIME CConvertTool::ToSystemtime(const _variant_t &var)
{
	SYSTEMTIME time;
	switch (var.vt)
	{
	case VT_DATE:   
		VariantTimeToSystemTime( (COleDateTime)var, &time);
		break;
	default:
		CString smsg;
		smsg.Format(_T("var.vt=%d,ToTime error!"),var.vt);
		AfxMessageBox(smsg);
		break;
	}

	return time;
}

BYTE CConvertTool::ToByte(LPCTSTR lpszValue)
{
	BYTE btValue;
	btValue = (BYTE)_ttoi(lpszValue);
	return btValue;
}
int CConvertTool::ToInt(LPCTSTR lpszValue)
{
	int iValue;
	iValue = _ttoi(lpszValue);
	return iValue;
}
unsigned int CConvertTool::ToUInt(LPCTSTR lpszValue)
{
	unsigned int iValue;
	iValue = _ttoi(lpszValue);
	return iValue;
}
long CConvertTool::ToLong(LPCTSTR lpszValue)
{
	long lValue;
	lValue = _ttol(lpszValue);
	return lValue;
}
unsigned long CConvertTool::ToULong(LPCTSTR lpszValue)
{
	unsigned long lValue;
	lValue = _ttol(lpszValue);
	return lValue;
}
__int64 CConvertTool::ToInt64(LPCTSTR lpszValue)
{
	__int64 i64Value;
	i64Value = _ttoi64(lpszValue);
	return i64Value;
}
unsigned __int64 CConvertTool::ToUInt64(LPCTSTR lpszValue)
{
	unsigned __int64 i64Value;
	i64Value = _ttoi64(lpszValue);
	return i64Value;
}
float CConvertTool::ToFloat(LPCTSTR lpszValue)
{
	float fltValue;
#ifdef _MBCS
	fltValue = (float)atof(lpszValue);
#else
	fltValue = (float)wtof(lpszValue);
#endif
	return fltValue;
}
double CConvertTool::ToDouble(LPCTSTR lpszValue)
{
	double dblValue;
#ifdef _MBCS
	dblValue = atof(lpszValue);
#else
	dblValue = wtof(lpszValue);
#endif
	return dblValue;
}
// 时间格式例子：2010-05-06 22:07:08
//				 2010 05 06 22 07 08
//				 2010:05:06 22:07:08
//				 2010-05-06-22-07-08
// 只要是“- :”分割的时间格式都符合
COleDateTime CConvertTool::ToTime(LPCTSTR lpszValue)
{
	unsigned int iArray[6] = {2010, 5, 11, 12, 00, 00};
	int nIndex = 0;
#if _MSC_VER >= 1310  //VC6.0不支持CStringAlt::Tokenize
	CString strTmp;
	int curPos = 0;
	CString strValue(lpszValue);
	
	strTmp = strValue.Tokenize(_T("- :"),curPos);
	while (strTmp != _T("") && nIndex <6)
	{
		iArray[nIndex++] = ToUInt(strTmp);
		strTmp = strValue.Tokenize(_T("- :"), curPos);
	};
#else
	TCHAR tChar[MAX_PATH] = {0};
	TCHAR tCharTmp[MAX_PATH] = {0};
	TCHAR seps[]   = "- :";
	TCHAR *next_token = NULL;
	ASSERT(_tcslen(lpszValue) < MAX_PATH);
	RtlCopyMemory(tChar, lpszValue, _tcslen(lpszValue) * sizeof(TCHAR));
	next_token = _tcstok(tChar, seps);
	while ( next_token != NULL && nIndex <6)
	{
		iArray[nIndex++] = _ttoi(next_token);
		next_token = _tcstok( NULL, seps);
	}
	
#endif
	COleDateTime time(iArray[0], iArray[1], iArray[2],
		iArray[3], iArray[4], iArray[5]);
	return time;
}
_variant_t CConvertTool::ToVariant(const COleDateTime& time)
{
	_variant_t vtVal;
	
	vtVal.vt = VT_DATE;
	vtVal.date = time;
	return vtVal;
}

void CConvertTool::int2bytes(int i, byte* bytes, int size) 
{
    memset(bytes,0,sizeof(byte) *  size);
    bytes[0] = (byte) (0xff & i);
    bytes[1] = (byte) ((0xff00 & i) >> 8);
    bytes[2] = (byte) ((0xff0000 & i) >> 16);
    bytes[3] = (byte) ((0xff000000 & i) >> 24);
}

int CConvertTool::bytes2int(byte* bytes, int size) 
{
    int iRetVal = bytes[0] & 0xFF;
    iRetVal |= ((bytes[1] << 8) & 0xFF00);
    iRetVal |= ((bytes[2] << 16) & 0xFF0000);
    iRetVal |= ((bytes[3] << 24) & 0xFF000000);
    return iRetVal;
}

void CConvertTool::short2bytes(short i, byte* bytes, int size)
{
	memset(bytes,0,sizeof(byte) *  size);
    bytes[0] = (byte) (0xff & i);
    bytes[1] = (byte) ((0xff00 & i) >> 8);
}

short CConvertTool::bytes2short(byte* bytes, int size)
{
	short sRetVal = bytes[0] & 0xFF;
    sRetVal |= ((bytes[1] << 8) & 0xFF00);
	return sRetVal;
}

void CConvertTool::shorts2bytes(short *shorts, byte *bytes, int sizebyte)
{
	memset(bytes,0,sizeof(byte) *  sizebyte);
	for ( int i=0; i<sizebyte/2; i++)
	{
		bytes[i*2] = (byte) (0xff & shorts[i]); //低8位
//AfxMessageBox(ToString(bytes[i*2]));
		bytes[i*2+1] = (byte) ((0xff00 & shorts[i]) >> 8); //高8位，>>向右移动
//AfxMessageBox(ToString(bytes[i*2++]));
	}
}

short *CConvertTool::bytes2shorts(byte* bytes, int sizebyte)
{
	short *sz = new short[sizebyte/2];
	for ( int i=0; i<sizebyte;)
	{
		short sRetVal = bytes[i] & 0xFF;
		sRetVal |= ((bytes[i+1] << 8) & 0xFF00);
		sz[i/2] = sRetVal;
		i+=2;
	}
	
	return sz;
}

short *CConvertTool::ToShortPtr( const _variant_t &var)
{
	if  (var.vt == (VT_ARRAY | VT_UI1)) //对于binary和blob都行
	{
		BYTE	*pByte = NULL;
		::SafeArrayAccessData(var.parray, (void **)&pByte);
		::SafeArrayUnaccessData(var.parray);
		if ( pByte != NULL)
		{
			int size = sizeof(pByte) / sizeof(pByte[0]);
			short *sz = bytes2shorts( pByte, size); //16个车道
			return sz;
		}
	}	
	return NULL;
}

_variant_t CConvertTool::ToVariant( short *sz, int sizeShort)
{
	VARIANT	 varBLOB;
	if ( sz == NULL)
	{
		return varBLOB;
	}

	int sizeByte = sizeShort * 2;
	BYTE *pBuf = new BYTE[sizeByte];
	CConvertTool::shorts2bytes( sz, pBuf, sizeByte);
	
	SAFEARRAY	*psa;
	SAFEARRAYBOUND	rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = sizeByte;
	psa = SafeArrayCreate(VT_UI1, 1, rgsabound);                 //创建SAFEARRAY对象
	for (long i = 0; i < (long)sizeByte; i++)//nLen为BYTE数组大小
		SafeArrayPutElement (psa, &i, pBuf++);          //将pBuf指向的数据保存到SAFEARRAY对象psa中
	varBLOB.vt = VT_ARRAY | VT_UI1;                                   //将varBLOB的类型设置为BYTE类型的数组
	varBLOB.parray = psa; 

	if ( pBuf != NULL)
	{
		delete []pBuf;
		pBuf = NULL;
	}

	return varBLOB;
}

_variant_t CConvertTool::ToVariant( byte *bytes, int sizeByte)
{
	_variant_t varBLOB;
	if ( bytes == NULL)
	{
		return varBLOB;
	}

	SAFEARRAY	*psa;
	SAFEARRAYBOUND	rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = sizeByte;
	psa = SafeArrayCreate(VT_UI1, 1, rgsabound);                 //创建SAFEARRAY对象
	for (long i = 0; i < (long)sizeByte; i++)//nLen为BYTE数组大小
		SafeArrayPutElement (psa, &i, bytes++);          //将pBuf指向的数据保存到SAFEARRAY对象psa中
	varBLOB.vt = VT_ARRAY | VT_UI1;                                   //将varBLOB的类型设置为BYTE类型的数组
	varBLOB.parray = psa; 
	
	return varBLOB;
}

double CConvertTool::dufenmiaoTodouble( int idu, int ifen, int imiao)
{
	double d = idu + (ifen * 60 + imiao) / 3600;
	return d;
}

CString CConvertTool::SYSTEMTIME2CString(SYSTEMTIME &time)
{
	TCHAR szDateTime[19] = {0};
	_stprintf(szDateTime, _T("%02d-%02d-%02d %02d:%02d:%02d"), time.wYear,time.wMonth,
			time.wDay, time.wHour,time.wMinute, time.wSecond);
	return szDateTime;
}

BOOL CConvertTool::StringToSYSTEMTIME(LPCTSTR lpszValue, SYSTEMTIME &time)
{
    if (!lpszValue)
    {
        return FALSE;
    }
    
    int         nYear   = 0;
    int         nMonth  = 0;
    int         nDay    = 0;
    int         nHour   = 0;
    int         nSecond = 0;
    int         nMinute = 0;
    CString  str     = lpszValue;
	
    _stscanf(str, _T("%d-%d-%d %d:%d:%d"), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	
//     if (nMonth==0 || nDay==0)
//     {
//         _stscanf(str, _T("%d/%d/%d %d:%d:%d"), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
//     }
	
    time.wYear   = nYear;
    time.wMonth  = nMonth;
    time.wDay    = nDay;
    time.wHour   = nHour;
    time.wSecond = nSecond;
    time.wMinute = nMinute;
	
    return TRUE;
}

int CConvertTool::TransCordToGridID(const double &dbGeoLongX,const double &dbGeoLatY)
{
	// 1:2.5W格网编码结构：
	// 1:1000000 行号 + 1:1000000 列号 + 所在比例尺 行号 + 所在比例尺 列号
	// 前两项均为2位，后两项均为3位，不足者在前面补零
	
	// 1 : 1 000 000 地形图图幅编号：
	int nGridIDFirst = -1; // 1:1000000图幅纬度对应的数字码
	int nGridIDSecond = -1; // 1:1000000图幅经度对应的数字码
	
	nGridIDFirst =(int)(dbGeoLatY / 4) + 1;
	nGridIDSecond =(int)(dbGeoLongX / 6) + 31;
	
	// 1 : 25 000 
	int nGridIDThird = -1; // 1:25000图幅纬度对应的数字码
	int nGridIDForth = -1; // 1:25000图幅经度对应的数字码
	
	const double dbGeoLatDValue = (double)1 / 12 ; // 所求比例尺地形图分幅的纬差，1:25000时该值为1/12
	const double dbGeoLongDValue = (double)1 / 8 ;// 所求比例尺地形图分幅的经差，1:25000时该值为1/8
	
	double dbTemp = dbGeoLatY - ((int)dbGeoLatY / 4) * 4 ;
	nGridIDThird = (int)(4 / dbGeoLatDValue) - (int)( dbTemp / dbGeoLatDValue);
	dbTemp = dbGeoLongX - ((int)dbGeoLongX / 6) * 6 ;
	nGridIDForth = (int)( dbTemp / dbGeoLongDValue) + 1;
	
	// 将缺位的编号补全位数
	std::string strGridIDFirst,strGridIDSecond,strGridIDThird,strGridIDForth;
	//strGridIDFirst = FillZero(nGridIDFirst,2);
	strGridIDFirst = IntToString(nGridIDFirst);
	strGridIDSecond = FillZero(nGridIDSecond,2);
	strGridIDThird = FillZero(nGridIDThird,3);
	strGridIDForth = FillZero(nGridIDForth,3);
	if (strGridIDFirst == "" || strGridIDSecond == "" || strGridIDThird == "" || strGridIDForth == "")
	{
		return -1;
	}
	std::string strGridID = strGridIDFirst + strGridIDSecond + strGridIDThird + strGridIDForth;
	return atoi(strGridID.c_str());
}

std::string CConvertTool::IntToString(int iValue)
{
	char  *buffer = new char[200];
	sprintf(buffer,"%d",iValue);
	std::string strValue = buffer;
	delete []buffer;
	return strValue;
}

std::string CConvertTool::FillZero(UINT iNum, int nDigit)
{
	std::string strID;
	char  *buffer = new char[200];
	sprintf(buffer,"%d",iNum);
	strID = buffer;
	delete []buffer;
	
	if (strID.length() > nDigit)
	{
		return "";
	}
	else if (strID.length() == nDigit)
	{
		return strID;
	}
	else 
	{
		int nLackSize = nDigit - strID.length();
		for (std::string::size_type nCount = 0 ; nCount < nLackSize ; nCount++)
		{
			strID.insert(0,'0');
		}
		return strID;
	}
	return "";
}

CString CConvertTool::Time_tToStr(time_t time)
{
	struct tm *local;
	CString stime;
	int nYear, nMonth, nDate, nHour, nMin, nSec;
	local = localtime(&time);
	nYear = local->tm_year + 1900;
	nMonth = local->tm_mon + 1;
	nDate = local->tm_mday;
	nHour = local->tm_hour;
	nMin = local->tm_min;
	nSec = local->tm_sec;
	CTime ptime(nYear, nMonth, nDate, nHour, nMin, nSec);
    return ptime.Format(_T("%Y-%m-%d %H:%M:%S"));
}

CString CConvertTool::Time_tToStr(time_t time, const char *sFormat)
{
	struct tm *local;
	CString stime;
	int nYear, nMonth, nDate, nHour, nMin, nSec;
	local = localtime(&time);
	nYear = local->tm_year + 1900;
	nMonth = local->tm_mon + 1;
	nDate = local->tm_mday;
	nHour = local->tm_hour;
	nMin = local->tm_min;
	nSec = local->tm_sec;
	CTime ptime(nYear, nMonth, nDate, nHour, nMin, nSec);
    return ptime.Format(sFormat);
}

CString CConvertTool::GetCurrentTime()
{
	time_t timeCur = time(NULL);
	return CConvertTool::Time_tToStr( timeCur);
}

//暂时以ip最后一位作为用户id，加上用户登录后再去掉
const char * CConvertTool::GetIp()
{
	
	WORD   wVersionRequested   =   MAKEWORD(1,   1); 
	WSADATA   wsaData; 
	
	if   (WSAStartup(wVersionRequested,   &wsaData))   
		return   0; 
	
	
	char   hostname[256]; 
	int   res   =   gethostname(hostname,   sizeof(hostname)); 
	if   (res   !=   0) 
		return   0; 
	
	hostent*   pHostent   =   gethostbyname(hostname); 
	if   (pHostent==NULL) 
		return   0; 
	
	hostent&   he   =   *pHostent; 
	
	sockaddr_in   sa; 
	
	memcpy   (   &sa.sin_addr.s_addr,   he.h_addr_list[0],he.h_length); 
	WSACleanup(); 
	
	return   inet_ntoa(sa.sin_addr); 
}

//根据地理坐标和比例尺获取格网编号(国家标准)
std::string CConvertTool::TransCordToGridID(const double &dbGeoLongX,const double &dbGeoLatY, SCALE_TYPE type, int dL)
{
	//以下算法以1:1000000(经差6°，纬差4°)为分幅标准，即将1:1000000的地图按指定的比例尺进行分割，这是国家标准分幅算法

	double dbGeoLongDValue; //指定比例尺分幅的经差
	double dbGeoLatDValue; //指定比例尺分幅的纬差
	
	if ( type == SCALE_TYPE25000)
	{
		dbGeoLongDValue = (double)1 / 8; //7′30″
		dbGeoLatDValue = (double)1 / 12;  //5′
		dL = 3; //其实只要两位就行了，但公司不知为什么整成3位，保持一致吧
		//1~48
	}
	else if ( type == SCALE_TYPE10000)
	{
		dbGeoLongDValue = (double)1 / 16; //3′45″
		dbGeoLatDValue = (double)1 / 24; //2′30″
		//1~96
	}
	else if ( type == SCALE_TYPE5000)
	{
		dbGeoLongDValue = (double)1 / 32; //1′52.5″
		dbGeoLatDValue = (double)1 / 48; //1′15″
		dL = 3; //3位才能盛得下,1~192    
	}
	else if ( type == SCALE_TYPE2500)
	{
		dbGeoLongDValue = (double)1 / 64; //
		dbGeoLatDValue = (double)1 / 96; //
		dL = 3; //3位才能盛得下1~384
	}
	else if ( type == SCALE_TYPE1000)
	{
		dbGeoLongDValue = (double)1 / 128; //28.125″
		dbGeoLatDValue = (double)1 / 192; //18.75″
		dL = 3; //3位才能盛得下1~768
	}
	else if ( type == SCALE_TYPESMALL)
	{
		dbGeoLongDValue = (double)1 / 800; //28.125″
		dbGeoLatDValue = (double)1 / 1200; //18.75″
		dL = 4; //4位才能盛得下1~4800
	}
	else
	{
		return "";
	}
	// 格网编码结构：
	// 1:1000000 行号 + 1:1000000 列号 + 所在比例尺 行号 + 所在比例尺 列号
	// 前两项均为2位，后两项的位数视比例尺情况设定，也可自己设定，不足者在前面补零，公司里设定1:25000的后两项为3位，这里均设定为两位，以后有需要再改
	
	// 1 : 1 000 000 地形图图幅编号：
	int nGridIDFirst = -1; // 1:1000000图幅纬度对应的数字码  
	int nGridIDSecond = -1; // 1:1000000图幅经度对应的数字码
	
	nGridIDFirst =(int)(dbGeoLatY / 4) + 1; 
	nGridIDSecond =(int)(dbGeoLongX / 6) + 31;
	
	int nGridIDThird = -1; // 指定比例尺图幅纬度对应的行号
	int nGridIDForth = -1; // 指定比例尺图幅经度对应的列号
	
	double dbTemp = dbGeoLatY - ((int)dbGeoLatY / 4) * 4 ;
	nGridIDThird = (int)(4 / dbGeoLatDValue) - (int)( dbTemp / dbGeoLatDValue);
	dbTemp = dbGeoLongX - ((int)dbGeoLongX / 6) * 6 ;
	nGridIDForth = (int)( dbTemp / dbGeoLongDValue) + 1;
	
	// 将缺位的编号补全位数
	std::string strGridIDFirst,strGridIDSecond,strGridIDThird,strGridIDForth;
	
	strGridIDFirst = IntToString(nGridIDFirst);//中国[1,14]行
	strGridIDSecond = FillZero(nGridIDSecond,2);//中国[43,53]列
	strGridIDThird = FillZero(nGridIDThird,dL);//[1:10000,1:1000000]的行数都是两位
	strGridIDForth = FillZero(nGridIDForth,dL);////以1:1000000为分幅标准，即将1:1000000的地图分割，[1:10000,1:1000000]都列数是两位
	if (strGridIDFirst == "" || strGridIDSecond == "" || strGridIDThird == "" || strGridIDForth == "")
	{
		return "";
	}
	std::string strGridID = strGridIDFirst + strGridIDSecond + strGridIDThird + strGridIDForth;
	return strGridID;
}


__int64 CConvertTool::ToInt64(const _variant_t &var)
{
	CString strValue;
	strValue = (LPCTSTR)(_bstr_t)var;
	return ToInt64( strValue);
}
