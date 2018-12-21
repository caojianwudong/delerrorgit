// CPOIUser.h: interface for the POIUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPOIUSER_H__02F74625_39D2_4357_AC1D_F05B0B94C034__INCLUDED_)
#define AFX_CPOIUSER_H__02F74625_39D2_4357_AC1D_F05B0B94C034__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <map>

using namespace std;

class POIUser  
{
public:
	POIUser();
	virtual ~POIUser();

	string GetUserName(){return m_sUserName;}
	string GetRealName(){return m_sRealName;}
	string GetUserPass(){return m_sUserPass;}
	int GetUserPost(){return m_nUserPost;}
	int GetUserID(){return m_nUserID;}

	void SetUser(int nUserID, CString csUserName, CString csRealName, CString csUserPass, int nUserPost);

private:
	string m_sUserName;
	string m_sRealName;
	string m_sUserPass;
	int m_nUserID;
	int m_nUserPost;

	map<string, int> m_mapEnable;

};

#endif // !defined(AFX_CPOIUSER_H__02F74625_39D2_4357_AC1D_F05B0B94C034__INCLUDED_)
