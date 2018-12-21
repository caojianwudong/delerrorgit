// CConvertTool.h: interface for the CConvertTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCONVERT_H__8A951846_6CA6_4976_B09B_755A37DD296F__INCLUDED_)
#define AFX_CCONVERT_H__8A951846_6CA6_4976_B09B_755A37DD296F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <comutil.h>  
#include <string>

//比例尺类型
enum SCALE_TYPE
{
	SCALE_TYPE25000 = 1,  //1:25000
		SCALE_TYPE10000 = 2,  //1:10000
		SCALE_TYPE5000 = 3, //1:5000
		SCALE_TYPE2500 = 4, //1:2500
		SCALE_TYPE1000 = 5,  //1:1000
		SCALE_TYPESMALL = 6, //1:25000分割为100行100列
};

class __declspec(dllexport) CConvertTool  
{
public:  
	//x,y地理坐标,type:比例尺类型，dL:指定比例尺行列位数，1:5000时应为3位，小于这个比例尺时2位即可，这里默认为2位
	static std::string TransCordToGridID(const double &dbGeoLongX,const double &dbGeoLatY, SCALE_TYPE type, int dL=2);
	
	static const char * GetIp();
	static CString Time_tToStr(time_t time);
	static std::string FillZero(UINT iNum, int nDigit);
	static std::string IntToString(int iValue);
	static int TransCordToGridID(const double &dbGeoLongX,const double &dbGeoLatY);
	static double dufenmiaoTodouble( int idu, int ifen, int imiao);
    static CString ToString(BYTE btValue);  
    static CString ToString(int iValue);  
    static CString ToString(unsigned int iValue);  
    static CString ToString(long lValue);  
    static CString ToString(unsigned long lValue);  
    static CString ToString(__int64 i64Value);  
    static CString ToString(unsigned __int64 i64Value);  
    static CString ToString(float fltValue);  
    static CString ToString(double dblValue);  
    static CString ToString(const COleDateTime& time);  
    static CString ToString(const _variant_t& var);  
	static int	   ToInt(const _variant_t &var);
	static double  ToDouble( const _variant_t &var);
	static SYSTEMTIME ToSystemtime(const _variant_t &var);
	static BOOL StringToSYSTEMTIME(LPCTSTR lpszValue, SYSTEMTIME &time);
public:  
    static BYTE ToByte(LPCTSTR lpszValue);  
    static int ToInt(LPCTSTR lpszValue);  
    static unsigned int ToUInt(LPCTSTR lpszValue);  
    static long ToLong(LPCTSTR lpszValue);  
    static unsigned long ToULong(LPCTSTR lpszValue);  
    static __int64 ToInt64(LPCTSTR lpszValue);  
    static unsigned __int64 ToUInt64(LPCTSTR lpszValue);  
    static float ToFloat(LPCTSTR lpszValue);  
    static double ToDouble(LPCTSTR lpszValue);  
    static COleDateTime ToTime(LPCTSTR lpszValue);  
    static _variant_t ToVariant(const COleDateTime& time);  
public:
	/** 
	* int 转 byte 
	* 方法无返回的优点：做内存管理清爽整洁 
	* 如果返回值为 int，float，long，double 等简单类型的话，直接返回即可 
	* 总的来说，这真心是一种很优秀的方法设计模式 
	*/  
	static void int2bytes(int i, byte* bytes, int size = 4);  
	
	// byte 转 int  
	static int bytes2int(byte* bytes, int size = 4);  

	static void short2bytes(short i, byte* bytes, int size=2);

	static short bytes2short(byte* bytes, int size=2);

public:
	static __int64 ToInt64( const _variant_t &var);
	static CString GetCurrentTime();
	static CString Time_tToStr(time_t time, const char *sFormat);
	static CString SYSTEMTIME2CString( SYSTEMTIME &time);
	static void shorts2bytes( short *shorts, byte *bytes, int size);
	static short *bytes2shorts(byte* bytes, int sizebyte);
	static short *ToShortPtr( const _variant_t &var);
	static void  bytesTochars( byte *bytes, char *chars, int size);
	static void charsToBytes( char *chars, byte *bytes, int size);
	static _variant_t ToVariant( short *sz, int size);
	static _variant_t ToVariant( byte *bytes, int sizeByte);
	CConvertTool();
	virtual ~CConvertTool();

};
extern CConvertTool Convert;  

#endif // !defined(AFX_CCONVERT_H__8A951846_6CA6_4976_B09B_755A37DD296F__INCLUDED_)
