#ifndef Commondef_h
#define Commondef_h 1

#include <map>
#include <vector>
#include <comutil.h>

enum ModifyStatus
{
    MS_None   = 0,
    MS_Append = 0x1, // ���
    MS_Remove = 0x2, // �Ƴ�
    MS_Modify = 0x3, // ����
};

/*
  �ύ����ʱ�������ֵ�仯��״̬�仯�����ύ. 
  
    �����ύʱ�����ֶλ���ܷ����仯:
        1. optype : ֵ�仯��״̬�仯��optype="submit"(IROT_Submit)
        2. ver(�Ƴ�)    : ֵ�仯ʱ, ver = ver+1;
        3. updatetime: ֵ�仯ʱ, updatetime = now()
        4. projectid : ֵ�仯ʱ, ��Navimap�趨��ProjectID����ʱ�������projectid
        5. workid :    �ύ����ʱ, �Ҳ���ΪSP_Editor����
        6. checkerid : �ύ����ʱ, �Ҳ���ΪSP_Verifier����
        7. isdel : ֵ�仯ʱ, �����趨(��ֵ:0, �ַ���:���ַ���)

    �������:
        1) ��¼ɾ��:    
            �������з�ɾ��״̬�Ļ��������α���չ�����ɾ����־, ����״̬�仯
        2) ״̬������
            ������չ�����ڵ��ֶθ���Error״̬ʱ���ᴴ��������, ������״̬, ver=0
   
     ���ݿ��ύ���ͣ�
        1. MAJOR_MODIFY: �����������޸�, ����(SP_Verifier, SP_Editor)
        2. SHAPE_MODIFY: ���α������޸�, ����(SP_Verifier, SP_Editor)
        3. FIELD_MODIFY: ��չ������޸�, ����(SP_Verifier, SP_Editor)
        4. FIELD_REMOVE: ��չ��ɾ��, ����(SP_Verifier, SP_Editor)
        5. RECORD_REMOVE:��¼ɾ��, ����(SP_Verifier, SP_Editor)
        6. MAJOR_STATUS: ������״̬�޸�,����(SP_Verifier, SP_Toolkit)
        7. SHAPE_STATUS: ���α�״̬�޸�,����(SP_Verifier, SP_Toolkit)
        8. FIELD_STATUS: ��չ��״̬�޸�,����(SP_Verifier, SP_Toolkit)
        9. FIELD_FORCE:  ��չ��״̬����,����(SP_Verifier, SP_Toolkit)
*/

enum CommitParams
{
    /*
        ��Ч��Χ: �ʼ칤��
        �ص㣺�����ʼ�״̬�Һ������ݱ��, �����û�ID
    */
    SP_Toolkit,

    /*
        ��Ч��Χ: ��ҵԱ��������乤��
        �ص㣺�������ݲ������ʼ�״̬, �û�ID�趨��workid
    */
     SP_Editor, 

    /*
        ��Ч��Χ: �˹��ʼ�, ��������
        �ص㣺�������ݼ��ʼ��״̬, �û�ID�趨��checkerid
    */
    SP_Verifier,
};

typedef enum Confirm
{
	IRCF_NoConfirm = 0x0,
	IRCF_ConfirmOK = 0x1,
	IRCF_ReadyForQC = 0x2,
	IRCF_MASK = 0x3,
}Confirm;

typedef enum CheckStatus
{
    IRCS_NoCheck = 0x0,  // 
    IRCS_Error = 0x1,
    IRCS_NoErr = 0x2,
    IRCS_MASK  = 0x3, 
} CheckStatus;

typedef enum OpType
{
    IROT_Init  = 0x0 , 
    IROT_Submit= 0x1,
    IROT_Ready = 0x2,
    IROT_Published = 0x3,
    IROT_MASK = 0x3,
}OpType;

typedef enum GradeLevel
{
    IRGL_General,  
    IRGL_Permanent,
    IRGL_Important,
}GradeLevel;

#define __SetOIDByIndex     SetBigintByIndex
#define __GetOIDByIndex     GetBigintByIndex
#define __SetMeshByIndex    SetBigintByIndex
#define __GetMeshByIndex    GetBigintByIndex

#ifndef __JMETA_TAG
struct jmeta
{
    long jtype;
    BSTR jkey;    
    union {
        double       d;
        jmeta    *   node;
    } jvalue;
};
#endif // __JMETA_TAG

#ifndef SDE_EXPORTS
struct ISQLConnector; // ���ݿ�����ʽ����
struct ISQLTransact;  // ������
struct IUIDManger;    // ID��ͼ�����ӿ�
struct IUIDLayer;     // ID��ͼ����ʽӿ�
struct IEMPManager;   // �ɹ���ͼ�����ӿ�
struct IEMPLayer;     // �ɹ���ͼ����ʽӿ�
#endif


#if 1


typedef int MESH;
typedef int LAYER;
typedef int NAVIMAP;
typedef __int64 OID;

#else

struct OID {
    OID(){}
    OID(const int & a) {};
    OID  operator-() { return 0; }
    OID & operator++() { return *this; }
    OID & operator++(int) { return *this; }
    OID  operator+(int) { return 0; }
//     bool operator<(OID k) const { return true; }
//     bool operator>(OID k) const { return true; }
//     bool operator<=(OID k) const { return true; }
//     bool operator>=(OID k) const { return true; }
//     bool operator!=(OID k) const { return true; }
//    bool operator==(OID k) const { return true; }

    operator __int64() const { return 0; }
};

OID abs(OID & o) { return 0; }



struct MESH{
    MESH(){}
    MESH(const int & a) {};
//     bool operator<(MESH k) const { return true; }
//     bool operator>(MESH k) const { return true; }
//     bool operator<=(MESH k) const { return true; }
//     bool operator>=(MESH k) const { return true; }
//     bool operator!=(MESH k) const { return true; }
 //   bool operator==(MESH k) const { return true; }
    
    operator __int64() const { return 0; }
};

struct LAYER{
    LAYER(){}
     LAYER(const int & a) {};
    bool operator<(LAYER k) const { return true; }
    bool operator>(LAYER k) const { return true; }
    bool operator<=(LAYER k) const { return true; }
    bool operator>=(LAYER k) const { return true; }
    bool operator!=(LAYER k) const { return true; }
    bool operator==(LAYER k) const { return true; }
};

struct NAVIMAP{
    NAVIMAP(){}
     NAVIMAP(const int & a) {};
    bool operator<(NAVIMAP k) const { return true; }
    bool operator>(NAVIMAP k) const { return true; }
    bool operator<=(NAVIMAP k) const { return true; }
    bool operator>=(NAVIMAP k) const { return true; }
    bool operator!=(NAVIMAP k) const { return true; }
    bool operator==(NAVIMAP k) const { return true; }
};

#endif

//##ModelId=46B7B83A00F0
enum FIELDTYPE
{
	//##ModelId=46B7B83A00FB
	FIELD_UNKNOWN = 0,
	//##ModelId=46B7B83A00FC
	FIELD_INT = 1,
	//##ModelId=46B7B83A00FD
    FIELD_DOUBLE = 2,
	//##ModelId=46B7B83A00FE
    FIELD_STRING = 3,
    // 64λ����֧��
    FIELD_BIGINT = 4,
};

//##ModelId=46B7B83A0109
enum	GEOTYPE
{
	//##ModelId=46B7B83A010B
	GEO_POINT = 2,
	//##ModelId=46B7B83A010C
	GEO_POLYLINE = 8, 
	//##ModelId=46B7B83A0119
	GEO_POLYGON = 9,
	//##ModelId=46B7B83A011A
	GEO_ANNOTATION	= 10,
	
	//##ModelId=46B7B83A011B
	GEO_SYMBOL	= 11,

	//##ModelId=46B7B83A011C
	GEO_COMPOUND = 14
};

//##ModelId=46B7B83A0128
enum	GEO_INFOMATION
{
	//##ModelId=46B7B83A012A
	GEO_HAS_TURN_IN_START_JUNCTION = 1,
	//##ModelId=46B7B83A0138
	GEO_HAS_LANE_IN_START_JUNCTION = 2,
	//##ModelId=46B7B83A0139
	GEO_HAS_DIRECTION_IN_START_JUNCTION = 3,
	//##ModelId=46B7B83A013A
	GEO_OWNER_COMPOUNDJUNCTION_IN_START_JUNCTION = 4,

	//##ModelId=46B7B83A013B
	GEO_HAS_TURN_IN_END_JUNCTION = 11,
	//##ModelId=46B7B83A0148
	GEO_HAS_LANE_IN_END_JUNCTION = 12,
	//##ModelId=46B7B83A0149
	GEO_HAS_DIRECTION_IN_END_JUNCTION = 13,
	//##ModelId=46B7B83A014A
	GEO_OWNER_COMPOUNDJUNCTION_IN_END_JUNCTION = 14,

	//##ModelId=46B7B83A014B
	GEO_POIN_IS_MEET_JUNCTION = 21,

	//##ModelId=46B7B83A0157
	GEO_HAS_NO_INFOMATION = 0
};

//## end module%40A1DA6803B9.additionalDeclarations
// ͼ�����Ͷ���
//##ModelId=46B7B83A0167
enum ELayerType
{
	//##ModelId=46B7B83A0169
	ROAD_LAYER		 = 0,				//  ��·ͼ�㣻
	//##ModelId=46B7B83A0177
	SERVICE_LAYER	 = 1,				//  ����ͼ�㣬POI��
	//##ModelId=46B7B83A0178
	ADMIN_LAYER		 = 2,				//  �����뾳��ͼ�㣻
	//##ModelId=46B7B83A0179
	VS_LAYER		 = 3,				//  ��ʾͼ�㣬���ڴ��ע�Ǻͷ��ţ�
	//##ModelId=46B7B83A0186
	BACKGROUND_LAYER = 4,				//  ����ͼ����� ֲ���� ����״ˮ��㡢��״ˮ��㡢 ����㡢 �������㡢��·��
	//##ModelId=46B7B83A0187
	GIS_NULL_LAYER   = 5,				//  ��ͼ��(��Чͼ��)
	
	EL_LAYER = 6,						//	������ͼ��

	JUNCTION_LAYER = 7,					//  �����ͼ��

	TIMELIMIT_LAYER = 8,				//ʱ��������Ϣͼ��

	VEHICLELIMIT_LAYER = 9,				//����������Ϣͼ��

	COMPOUND_LAYER = 10,				//ͳ�Ͻ����ͼ��

	DIRECTION_LAYER = 11,				//������Ϣͼ��

	EXIT_INFO_LAYER = 12,				//�߿��ٳ�����Ϣ

	JUNCTION_GUIDE_LAYER = 13,			//ǿ��������Ϣ

	JUNCTION_REFERENCE_LAYER = 14,		//������������Ϣ

	JUNCTION_SA_FACILITY_LAYER = 15,	//������������ʩ��Ϣ

	JUNCTION_VIEW_LAYER = 16,			//·�ڷŴ�ͼ��Ϣ

	LANE_LAYER = 17,					//������Ϣ

	TURN_LAYER = 18						//ת����Ϣ

};

//## end module%40A1DA6803B9.additionalDeclarations
// ͼ�����Ͷ���
//##ModelId=46B7B83A0167
enum ETableTypeAttachedByRoad
{
	UNDEFINED_TABLE				= -1,

	ROAD_PROPERTY_TABLE			= 0,	// ��·���Ա�

	JUNCTION_PROPERTY_TABLE		= 1,	// ��������Ա�

	COMPOUND_PROPERTY_TABLE		= 2,	// ͳ�Ͻ�������Ա�

	TIMELIMIT_TABLE				= 3,	//  ʱ�����Ʊ�

	VEHICLELIMIT_TABLE			= 4,	//  �������Ʊ�

	TURN_TABLE					= 5,   //  ת���

	DIRECTION_TABLE				= 6,	//  �����

	LANE_TABLE					= 7,   //  ������

	JUNCTION_REFERENCE_TABLE	= 8,	//  �����������

	JUNCTION_VIDEO_TABLE		= 9,	//  ·��3D��Ƶ��
	
	JUNCTION_VIEW_TABLE			= 10,	//  ·�ڷŴ�ͼ��
	
	JUNCTION_VRVIEW_TABLE		= 11,	//  ·��ʵ��ͼ��
	
	JUNCTION_GUIDE_TABLE		= 12,	//  ·��ǿ���յ���

	NEW_TURN_TABLE				= 13,   //  ת���

	NEW_DIRECTION_TABLE			= 14,	//  �����

	NEW_LANE_TABLE				= 15,   //  ������

	EXIT_INFO_TABLE				= 16,

	JUNCTION_SA_FACILITY_TABLE	= 17


};

//////////////////////////////////////////////////////////////////////////
// added at 2013-10-25
const int 	UNKNOWN_TABLE_TYPE				= -1;
const int 	ROAD_BASE_ROAD_TABLE			=1100; // ��·���Ա�
const int 	ROAD_BASE_JUNCTION_TABLE		=1101; // ��������Ա�
const int 	ROAD_BASE_COMPOUND_TABLE		=1102; // ͳ�Ͻ�������Ա�
const int 	ROAD_ATTACH_TIME_TABLE			=1203; // ��·ʱ�丽����
const int 	ROAD_ATTACH_VEHICLE_TABLE		=1204; // ��·����������
const int 	ROAD_ATTACH_TURN_TABLE			=1205; // ��·ת������
const int 	ROAD_ATTACH_DIRECTION_TABLE		=1206; // ��·��������
const int 	ROAD_ATTACH_LANE_TABLE			=1207; // ��·����������
const int 	ROAD_ATTACH_REFERENCE_TABLE		=1208; // ��·���������︽����
const int 	ROAD_ATTACH_VIDEO_TABLE			=1209; // ��·��Ƶ������
const int 	ROAD_ATTACH_VIEW_TABLE			=1210; // ��·�Ŵ�ͼ������
const int 	ROAD_ATTACH_VRVIEW_TABLE		=1211; // ��·ʵ��ͼ������
const int 	ROAD_ATTACH_GUIDE_TABLE			=1212; // ��·ǿ������������
const int 	ROAD_ATTACH_NTURN_TABLE			=1213; // ��·��ת������
const int 	ROAD_ATTACH_NDIRECTION_TABLE	=1214; // ��·�·�������
const int 	ROAD_ATTACH_NLANE_TABLE			=1215; // ��·�³���������
const int 	ROAD_ATTACH_EXITINFO_TABLE		=1216; // ��·���ڸ�����
const int 	ROAD_ATTACH_SA_TABLE			=1217; // ��·������������
const int	ROAD_ATTACH_FORK_TABLE			=1218; // ��·�ֲ�·������

const int 	POI_BASE_POI_TABLE				=2100; // ��Ȥ�����Ա�
const int 	POI_ATTACH_TENANT_TABLE			=2201; // ��Ȥ���⻧������
const int	POI_ATTACH_FUEL_TABLE			=2202; // ��Ȥ��ȼ�ϸ�����

//////////////////////////////////////////////////////////////////////////

// LayerStatusType  Definition
//##ModelId=46B7B83A0196
enum ELayerStatusType 
{
	//##ModelId=46B7B83A0198
	LAYER_INIT,					// ͼ�����ոս�������δ��֯��������Ϣ��
	//##ModelId=46B7B83A0199
	LAYER_OPENED_WITHOUT_DATA,	// ͼ���������Ϣ����֯��ϣ����ڴ��������ݿ��е�������ͬ����ͼ���еĵ������ݻ�δ�������ڴ棻
	//##ModelId=46B7B83A01A5
	LAYER_LOADED_AND_SAVED  ,	// ͼ���ѱ��򿪣����ڴ��к���ͼ�����������,������Щ�����ѱ����浽���ݿ��У�
	//##ModelId=46B7B83A01A6
	LAYER_LOADED_AND_EDITING 	// ͼ���ѱ��򿪣����ڴ��к���ͼ�����������,��Щ�����ѱ��༭��,���༭������ݻ�δ�����浽���ݿ��У�
} ;

//�����ṹ
//##ModelId=46B7B83A01B5
struct SGeoPoint
{
	//##ModelId=46B7B83A01B7
	double x;
	//##ModelId=46B7B83A01B8
	double y;
	//##ModelId=46B7B83A01C5
	SGeoPoint(double xx,double yy)
	{
		x= xx ;
		y= yy ;
	}
	//##ModelId=46B7B83A01C8
	SGeoPoint()
	{
		x= 0 ;
		y= 0 ;
	}
	//##ModelId=46B7B83A01C9
	void operator = (const  SGeoPoint& pt)
	{
		x = pt.x;
		y = pt.y;
	}
	//##ModelId=46B7B83A01CB
	bool operator == (const  SGeoPoint& pt)
	{
		if(x == pt.x && y == pt.y )
			return true;
		else return false;
	}
	//##ModelId=46B7B83A01D4
	bool operator != (const struct SGeoPoint& pt)
	{
		if(x!=pt.x||y!=pt.y)
			return true;
		else
			return false;
	}
};

//##ModelId=46B7B83A01D6
typedef std::vector<SGeoPoint>			VECTOR_PointArray ;

//##ModelId=46B7B83A01E4
class SGeoRect
{
public:
	//##ModelId=46B7B83A01E5
	double x_min;
	//##ModelId=46B7B83A01F4
	double y_min;
	//##ModelId=46B7B83A01F5
	double x_max;
	//##ModelId=46B7B83A01F6
	double y_max;
	//##ModelId=46B7B83A01F7
	SGeoRect ( double x1,double y1,double x2,double y2 )
	{
		x_min = x1 ;
		x_max = x2 ;
		y_min = y1 ;
		y_max = y2 ;
	}
	//##ModelId=46B7B83A0206
	SGeoRect ()
	{
		x_min = -1 ;
		x_max = -1 ;
		y_min = -1 ;
		y_max = -1 ;
	}
	//##ModelId=46B7B83A0207
	void operator = (const SGeoRect& pt) 
	{
		x_min = pt.x_min;
		y_min = pt.y_min;
		x_max = pt.x_max;
		y_max = pt.y_max;
	}
	//##ModelId=46B7B83A0209
	bool operator == (const SGeoRect& pt) 
	{
		if(x_min == pt.x_min && y_min == pt.y_min && x_max == pt.x_max
		   && y_max == pt.y_max)
			return true;
		else return false;
	}
	//##ModelId=46B7B83A0213
	bool DpInGeoRect( double x, double y ) 
	{
		if( x>=x_min && x<=x_max&& y>=y_min && y<=y_max )
			return true;
		return false;
	}
	//##ModelId=46B7B83A0216
	bool DpInGeoRect( SGeoPoint pt ) 
	{
		if( pt.x>=x_min && pt.x<=x_max&& pt.y>=y_min && pt.y<=y_max )
			return true;
		return false;
	}
	//##ModelId=46B7B83A0218
	void	Union ( SGeoRect rect )
	{
		if ( x_min>rect.x_min )
			x_min = rect.x_min ;
		if ( x_max<rect.x_max )
			x_max = rect.x_max ;
		if ( y_min>rect.y_min )
			y_min = rect.y_min ;
		if ( y_max<rect.y_max )
			y_max = rect.y_max ;
	}
};

//�����ṹ
//##ModelId=46B7B83A01B5
struct SGlobeFeatureID
{
	//##ModelId=46B7B83A01B7
	MESH		m_iMeshID ;
	//##ModelId=46B7B83A01B8
	OID		m_iFeatureID ;
	//##ModelId=46B7B83A01C5
	SGlobeFeatureID( MESH mesh_id, OID feature_id )
	{
		m_iMeshID = mesh_id ;
		m_iFeatureID = feature_id ;
	}
	//##ModelId=46B7B83A01C8
	SGlobeFeatureID()
	{
		m_iMeshID = 0 ;
		m_iFeatureID = 0 ;
	}
	//##ModelId=46B7B83A01C9
	void operator = (const  SGlobeFeatureID& globe_feature_id )
	{
		m_iMeshID = globe_feature_id.m_iMeshID ;
		m_iFeatureID = globe_feature_id.m_iFeatureID;
	}
	//##ModelId=46B7B83A01CB
	bool operator == (const  SGlobeFeatureID& globe_feature_id)
	{
		if( m_iMeshID == globe_feature_id.m_iMeshID &&
			m_iFeatureID == globe_feature_id.m_iFeatureID )
			return true;
		else 
			return false;
	}
	//##ModelId=46B7B83A01D4
	bool operator != (const struct SGlobeFeatureID& globe_feature_id )
	{
		if( m_iMeshID != globe_feature_id.m_iMeshID ||
			m_iFeatureID != globe_feature_id.m_iFeatureID )
			return true;
		else 
			return false;
	}
};


#define MAX_FEATURESET_NAME_LEN 256 

#define MAX_ANNOTATION_LEN 40

#define MAX_LAYER_NAME_LEN 256 

#define MAX_ERROR_MSG 1024 

#define MAX_FIELD_NAME_LEN 256 

#define MAX_RELATED_ARCS_OF_POINT_OBJECT 100 

#define MAX_ISLANDS_OF_POLYGON_OBJECT  1000

#define MAX_ARCS_OF_POLYGON_OBJECT  10000

#define MAX_POINTS_OF_ARC_OBJECT	100000

#define MAP_NAME_MAX_LENGTH		256 

#define MAP_DESC_MAX_LENGTH		1024 

#define	MAX_ERROR_MSG_LENGTH	1024 

#define MAX_FILE_PATH_LENGTH	1024

#define	MINI_VALUE				1e-20 

#endif
