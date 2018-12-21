#ifndef CCAttachFieldsInfo_h
#define CCAttachFieldsInfo_h 1

#include "CFieldsInfo.h"
#include <string>
#include "commondef.h"
#include "CFields.h"
using namespace std;

class __declspec(dllexport) CAttachFieldsInfo: public CFieldsInfo
{
  public:
	  virtual int GetIDIndex() = 0;
	  virtual int GetAttachFeatureIDIndex()=0;
	  virtual int GetAttachFeatureMeshIDIndex()=0;

	  int GetType();
	  const char* GetName();

      CAttachFieldsInfo(int Type);
      ~CAttachFieldsInfo();

  protected:
      int       m_iIndex ;
	  int		m_iAttachFeatureIndex;
	  int		m_iAttachFeatureMeshIndex;

	  int       m_iType;
  	  char		m_szName[256] ;

};


class __declspec(dllexport) CAttachRoadFieldsInfo: public CAttachFieldsInfo
{
public:

	CAttachRoadFieldsInfo(int Type);
	~CAttachRoadFieldsInfo();
public:
	virtual int GetStartRoadIDIndex();
	virtual int GetStartRoadMeshIDIndex();
	virtual int GetEndRoadIDIndex();
	virtual int GetEndRoadMeshIDIndex();

protected:
	int     m_iStartRoadIDIndex ;
	int		m_iStartRoadMeshIDIndex ;
	int     m_iEndRoadIDIndex ;
	int		m_iEndRoadMeshIDIndex ;

};

#endif
