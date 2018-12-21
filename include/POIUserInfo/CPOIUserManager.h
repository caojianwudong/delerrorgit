// CPOIUserManager.h: interface for the POIUserManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPOIUSERMANAGER_H__EA8BBC85_63F4_426F_ABA7_D80D2C37066E__INCLUDED_)
#define AFX_CPOIUSERMANAGER_H__EA8BBC85_63F4_426F_ABA7_D80D2C37066E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <map>
#include <vector>

#define WM_LOGIN_IN WM_USER + 2001

enum EDITTYPE{
	EDITTYPE_UNKNOW = 0,
	EDITTYPE_EDIT = 5, //制作
	EDITTYPE_CHECK = 6, //校正
	EDITTYPE_MODIFY = 7, //修改错误
    EDITTYPE_CONFIRM = 8, //验证
};

using namespace std;

class POIUser;
class POIUserDB;

class __declspec(dllexport) POIUserManager  
{
public:
	int GetRoleuserid( int idRole, int idUser);
	int GetRoleIdByRoleuserid( int idRoleUser);
	int GetUserIdByRoleuserid( int idRoleUser);
	bool IsCheckUserRole();
	void SetCheckUserRoleFlag( bool bCheck);
	string GetRealName();
	CString GetRoleNameById( int idRole);
	//检测某用户是否有指定权限
	bool CheckUserRole( int idUser, int idRole);
	void AddUserRole( int idUser, int idRole);
	bool GetUserInfoById( int id, string &sUserName, string &sRealName);
	int GetRoleUserId();
	void SetParentHwnd( HWND hwnd);
	int GetUserID();
	int GetUserPost();
	string GetUserName();
	virtual ~POIUserManager();

	static POIUserManager *GetPOIUserManagerPtr();

	CDialog * GetUserLoginDlgPtr();

	POIUser * GetPOIUserPtr();
	POIUserDB * GetPOIUserDBPtr();
	
	void SetCurUser(int nUserID, CString csUserName, CString csRealName, CString csUserPass, int nUserPost);

	void DestoryPOIUserManager();

	bool GetLogin(){return m_nLogin;};

	void SetLogin(bool bFlag){m_nLogin = bFlag;}
	
	int GetEditType(){return m_nEditType;};
	
	void SetEditType(int nType){m_nEditType = nType;}

	void Reset();

private:
	POIUserManager();

	static POIUserManager * m_pPOIUserManager;

	POIUser *m_pCurUser;
	POIUserDB *m_pPOIUserDB;

	CDialog * m_pUserLogin;
	
	bool m_nLogin;	//登录状态

	int m_nEditType;	//编辑类型：与tb_roles中一致

	//projectsmanager:tb_user_roles:某个人拥有的编辑类型
	std::map<int, std::vector<int> > m_mapUserRoles;

	//是否检测已分配编辑或校验权限
	bool m_bCheckUserRole;
};

#endif // !defined(AFX_CPOIUSERMANAGER_H__EA8BBC85_63F4_426F_ABA7_D80D2C37066E__INCLUDED_)
