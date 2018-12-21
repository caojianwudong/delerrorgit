//## begin module%36DC32850244.cp preserve=no
//	//////////////////////////////////////////////////////////////////////
//	//
//	//  ���ߣ�
//	//  �������ڣ�
//	//  ����޸����ڣ�
//	//
//	//////////////////////////////////////////////////////////////////////
//## end module%36DC32850244.cp

//## Module: CFeatureSet%36DC32850244; Package specification
//## Subsystem: GIAE Components%372FC3E50277

#ifndef CFeatureSet_h
#define CFeatureSet_h 1

#include "commondef.h"
#include "CFeature.h"

class CLayer ;

//##ModelId=46B7B8400020
typedef std::map<OID, CFeature*>		CFeatureMap ;
//##ModelId=46B7B840002F
typedef CFeatureMap::iterator		CFeatureMapIterator ;

//## begin module%36DC32850244.additionalDeclarations preserve=yes
//## end module%36DC32850244.additionalDeclarations

//## Class: CFeatureSet%36F958E40329
//	CFeatureSet��: ����һ���������󼯺ϡ�
//
//	<<˵��>>
//	�����ʾĳ��ͼ����һ����������ļ��ϡ�������ά��һ�����������ָ���б�
//	a. ����������ķ���
//	   ���� ʹ��GetFeatureCount()��ȡ����������������������ĸ�����
//	   ���� ʹ��GetFeaturePtr(featureID��int)ͨ��FeatureID��ȡ����������ָ�����������ָ�룻
//	   ���� ʹ��GetFirstFeaturePtr()��GetNextFeaturePtr()�Լ��Ͻ��б����������ȡ���������������ָ�룻
//	   ���� ��ȡ���ֵ����������󼯺ϵ�ָ�룻
//	b. �򼯺������ӻ�ժ��������������ͨ��AddFeature()��RemoveFeature()�򼯺��м��롢��Ӽ�����ժ��ĳ����������ע�⣺RemoveFeature()ֻ�ǽ�ָ������Ӽ�����ժ��,������ͼ����ɾ���ö��󡣶����ɾ��������CLayer�ฺ����ɣ�

//##ModelId=46B7B840004E
class __declspec(dllexport) CFeatureSet 
{
  public:
	//##ModelId=46B7B840005D
	  void Release();
	//##ModelId=46B7B840005E
	  bool AddFeature ( OID FeatureID );
    //## Constructors (specified)
      //## Operation: CFeatureSet%920392563
	//##ModelId=46B7B8400060
      CFeatureSet (CLayer* pOwnerLayer, const char* name);

    //## Destructor (specified)
      //## Operation: ~CFeatureSet%920392584
	//##ModelId=46B7B840006D
      ~CFeatureSet ();

	//##ModelId=46B7B840007D
	 void CopyFeatureSet( CFeatureSet * pSet ) ;


    //## Other Operations (specified)
      //## Operation: GetOwnerLayerPtr%920392564
	//##ModelId=46B7B840008D
      CLayer* GetOwnerLayerPtr ();

      //## Operation: GetFeatureSetName%929460947
	//##ModelId=46B7B840009C
      const char* GetFeatureSetName ();

      //## Operation: GetBound%939915311
	//##ModelId=46B7B84000AB
      SGeoRect GetBound ();

      //## Operation: GetFeatureCount%920392565
	//##ModelId=46B7B84000BB
      int GetFeatureCount ();

      //## Operation: GetFeaturePtr%920392569
	//##ModelId=46B7B84000CB
      CFeature* GetFeaturePtr (OID featureID);

	//##ModelId=46B7B84000DA
      CFeature* GetFirstPointFeaturePtr ();

	//##ModelId=46B7B84000DB
      CFeature* GetNextPointFeaturePtr ();

	//##ModelId=46B7B84000EA
      CFeature* GetNextPointFeaturePtr (CFeature* pCurrentFeature);

	//##ModelId=46B7B84000FA
      CFeature* GetFirstArcFeaturePtr ();

	//##ModelId=46B7B8400109
      CFeature* GetNextArcFeaturePtr ();

	//##ModelId=46B7B840010A
      CFeature* GetNextArcFeaturePtr (CFeature* pCurrentFeature);

	//##ModelId=46B7B8400119
      CFeature* GetFirstPolygonFeaturePtr ();

	//##ModelId=46B7B840011A
      CFeature* GetNextPolygonFeaturePtr ();

	//##ModelId=46B7B8400128
      CFeature* GetNextPolygonFeaturePtr (CFeature* pCurrentFeature);

      //## Operation: GetFirstFeaturePtr%920392570
	//##ModelId=46B7B840012A
      CFeature* GetFirstFeaturePtr ();

      //## Operation: GetNextFeaturePtr%920392571
	//##ModelId=46B7B8400138
      CFeature* GetNextFeaturePtr ();

      //## Operation: AddFeature%920392572
	//##ModelId=46B7B8400139
      bool AddFeature (CFeature* pFeature);

      //## Operation: RemoveFeature%920392573
	//##ModelId=46B7B840013B
      bool RemoveFeature (OID featureID);

      //## Operation: RemoveFeature%920392586
	//##ModelId=46B7B8400148
      bool RemoveFeature (CFeature* pFeature);

      //## Operation: RemoveAll%920392578
	//##ModelId=46B7B840014A
      void RemoveAll ();

  protected:
  private:
    // Data Members for Class Attributes

      //## Attribute: m_pOwnerLayer%36F9596903AC
      //	ָ����������󼯺�����ͼ������ָ�롣
      //## begin CFeatureSet::m_pOwnerLayer%36F9596903AC.attr preserve=no  private: CLayer* {UA} 
	//##ModelId=46B7B840014C
      CLayer* m_pOwnerLayer;
      //## end CFeatureSet::m_pOwnerLayer%36F9596903AC.attr

      //## Attribute: m_FeatureSetName%3766957D02A1
      //	�������󼯺����ơ�
      //## begin CFeatureSet::m_FeatureSetName%3766957D02A1.attr preserve=no  private: char[MAX_FEATURESET_NAME_LEN] {UA} 
	//##ModelId=46B7B840015A
      char m_FeatureSetName[MAX_FEATURESET_NAME_LEN] ;
      //## end CFeatureSet::m_FeatureSetName%3766957D02A1.attr

      //## Attribute: m_pPointFeatureSet%36F958F101DD
      //	ָ����������󼯺��������ĵ�״���͵ĵ������������ָ�롣
      //## begin CFeatureSet::m_pPointFeatureSet%36F958F101DD.attr preserve=no  private: CUniFeatureSet* {UA} 
	//##ModelId=46B7B840015C
      CFeatureMap*  m_pPointFeatureSetMap;
      //## end CFeatureSet::m_pPointFeatureSet%36F958F101DD.attr

      //## Attribute: m_pArcFeatureSet%36F958FF0151
      //	ָ����������󼯺�����������״���͵ĵ������������ָ�롣
      //## begin CFeatureSet::m_pArcFeatureSet%36F958FF0151.attr preserve=no  private: CUniFeatureSet* {UA} 
	//##ModelId=46B7B8400168
      CFeatureMap* m_pArcFeatureSetMap;
      //## end CFeatureSet::m_pArcFeatureSet%36F958FF0151.attr

      //## Attribute: m_pPolygonFeatureSet%36F9590B007C
      //	ָ����������󼯺�����������״���͵ĵ������������ָ�롣
      //## begin CFeatureSet::m_pPolygonFeatureSet%36F9590B007C.attr preserve=no  private: CUniFeatureSet* {UA} 
	//##ModelId=46B7B840016D
      CFeatureMap* m_pPolygonFeatureSetMap;
      //## end CFeatureSet::m_pPolygonFeatureSet%36F9590B007C.attr

      //## Attribute: m_pCurrentUniFeatureSet%36DC64D5017C
      //	��ǰ���ڱ����ĵ������������󼯺ϡ�
      //	�ñ�����GetFirstFeaturePtr()��GetNextFeaturePtr()ʹ�ã�ָʾ��ǰ���ڱ����ĵ������������󼯺ϡ�
      //	�ñ����ɹ��캯����ʼ��Ϊ��ֵ������GetFirstFeaturePtr()��GetNextFeaturePtr()����ȡ���޸ġ�
      //## begin CFeatureSet::m_pCurrentUniFeatureSet%36DC64D5017C.attr preserve=no  private: CUniFeatureSet* {UA} 
	//##ModelId=46B7B8400178
      CFeatureMap* m_pCurrentUniFeatureSetMap;
      //## end CFeatureSet::m_pCurrentUniFeatureSet%36DC64D5017C.attr
     
	//##ModelId=46B7B840017D
	  CFeatureMapIterator m_CurrentPointItemPtr;
	//##ModelId=46B7B8400188
      CFeatureMapIterator m_CurrentArcItemPtr;
	//##ModelId=46B7B8400197
      CFeatureMapIterator m_CurrentPolygonItemPtr;

  private: //## implementation
    // Data Members for Associations

      //## Association: GIAE::<unnamed>%36F95B800135
      //## Role: CFeatureSet::<the_CLayer>%36F95B8001FD
      //## begin CFeatureSet::<the_CLayer>%36F95B8001FD.role preserve=no  public: CLayer {n -> 1RFHGN}
      //## end CFeatureSet::<the_CLayer>%36F95B8001FD.role

      //## Association: GIAE::<unnamed>%36F95B8302DE
      //## Role: CFeatureSet::<the_CUniFeatureSet>%36F95B8303CE
      //## begin CFeatureSet::<the_CUniFeatureSet>%36F95B8303CE.role preserve=no  public: CUniFeatureSet {1 -> 3UHN}
      //## end CFeatureSet::<the_CUniFeatureSet>%36F95B8303CE.role

      //## Association: GIAE::<unnamed>%36DC5D74031B
      //## Role: CFeatureSet::<the_CFeature>%36DC5D7901F6
      //## begin CFeatureSet::<the_CFeature>%36DC5D7901F6.role preserve=no  public: CFeature { -> RHN}
      //## end CFeatureSet::<the_CFeature>%36DC5D7901F6.role

};

// Class CFeatureSet 

extern "C"
{
	 __declspec(dllexport) CFeatureSet* CreateFeatureSet( CLayer * pLayer ) ;
}


//## begin module%36DC32850244.epilog preserve=yes
//## end module%36DC32850244.epilog


#endif
