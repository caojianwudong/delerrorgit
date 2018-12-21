#ifndef Commondef_h
#define Commondef_h 1

#include <map>
#include <vector>
#include <comutil.h>

enum ModifyStatus
{
    MS_None   = 0,
    MS_Append = 0x1, // 添加
    MS_Remove = 0x2, // 移除
    MS_Modify = 0x3, // 修正
};

/*
  提交数据时，会根据值变化或状态变化进行提交. 
  
    正常提交时以下字段会可能发生变化:
        1. optype : 值变化或状态变化，optype="submit"(IROT_Submit)
        2. ver(移除)    : 值变化时, ver = ver+1;
        3. updatetime: 值变化时, updatetime = now()
        4. projectid : 值变化时, 且Navimap设定的ProjectID非零时，会更新projectid
        5. workid :    提交数据时, 且参数为SP_Editor更新
        6. checkerid : 提交数据时, 且参数为SP_Verifier更新
        7. isdel : 值变化时, 根据设定(数值:0, 字符型:空字符串)

    特殊情况:
        1) 记录删除:    
            对于所有非删除状态的基础表、几何表、扩展表，添加删除标志, 无视状态变化
        2) 状态新增：
            对于扩展表不存在的字段附加Error状态时，会创建新属性, 保存其状态, ver=0
   
     数据库提交类型：
        1. MAJOR_MODIFY: 基础表插入或修改, 适用(SP_Verifier, SP_Editor)
        2. SHAPE_MODIFY: 几何表插入或修改, 适用(SP_Verifier, SP_Editor)
        3. FIELD_MODIFY: 扩展表播入或修改, 适用(SP_Verifier, SP_Editor)
        4. FIELD_REMOVE: 扩展表删除, 适用(SP_Verifier, SP_Editor)
        5. RECORD_REMOVE:记录删除, 适用(SP_Verifier, SP_Editor)
        6. MAJOR_STATUS: 基础表状态修改,适用(SP_Verifier, SP_Toolkit)
        7. SHAPE_STATUS: 几何表状态修改,适用(SP_Verifier, SP_Toolkit)
        8. FIELD_STATUS: 扩展表状态修改,适用(SP_Verifier, SP_Toolkit)
        9. FIELD_FORCE:  扩展表状态新增,适用(SP_Verifier, SP_Toolkit)
*/

enum CommitParams
{
    /*
        有效范围: 质检工具
        特点：保存质检状态且忽略内容变更, 忽略用户ID
    */
    SP_Toolkit,

    /*
        有效范围: 作业员，任务分配工具
        特点：保存内容并重置质检状态, 用户ID设定于workid
    */
     SP_Editor, 

    /*
        有效范围: 人工质检, 批处理工具
        特点：保存内容及质检测状态, 用户ID设定于checkerid
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
struct ISQLConnector; // 数据库连接式定义
struct ISQLTransact;  // 事务定义
struct IUIDManger;    // ID库图层管理接口
struct IUIDLayer;     // ID库图层访问接口
struct IEMPManager;   // 成果库图层管理接口
struct IEMPLayer;     // 成果库图层访问接口
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
    // 64位整型支持
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
// 图层类型定义
//##ModelId=46B7B83A0167
enum ELayerType
{
	//##ModelId=46B7B83A0169
	ROAD_LAYER		 = 0,				//  道路图层；
	//##ModelId=46B7B83A0177
	SERVICE_LAYER	 = 1,				//  服务图层，POI；
	//##ModelId=46B7B83A0178
	ADMIN_LAYER		 = 2,				//  政区与境界图层；
	//##ModelId=46B7B83A0179
	VS_LAYER		 = 3,				//  表示图层，用于存放注记和符号；
	//##ModelId=46B7B83A0186
	BACKGROUND_LAYER = 4,				//  背景图层包括 植被层 、面状水体层、线状水体层、 岛屿层、 建筑区层、铁路层
	//##ModelId=46B7B83A0187
	GIS_NULL_LAYER   = 5,				//  空图层(无效图层)
	
	EL_LAYER = 6,						//	电子眼图层

	JUNCTION_LAYER = 7,					//  交叉点图层

	TIMELIMIT_LAYER = 8,				//时间限制信息图层

	VEHICLELIMIT_LAYER = 9,				//车辆限制信息图层

	COMPOUND_LAYER = 10,				//统合交叉点图层

	DIRECTION_LAYER = 11,				//方向信息图层

	EXIT_INFO_LAYER = 12,				//高快速出口信息

	JUNCTION_GUIDE_LAYER = 13,			//强制引导信息

	JUNCTION_REFERENCE_LAYER = 14,		//交叉点参照物信息

	JUNCTION_SA_FACILITY_LAYER = 15,	//交叉点服务区设施信息

	JUNCTION_VIEW_LAYER = 16,			//路口放大图信息

	LANE_LAYER = 17,					//车道信息

	TURN_LAYER = 18						//转向信息

};

//## end module%40A1DA6803B9.additionalDeclarations
// 图层类型定义
//##ModelId=46B7B83A0167
enum ETableTypeAttachedByRoad
{
	UNDEFINED_TABLE				= -1,

	ROAD_PROPERTY_TABLE			= 0,	// 道路属性表

	JUNCTION_PROPERTY_TABLE		= 1,	// 交叉点属性表

	COMPOUND_PROPERTY_TABLE		= 2,	// 统合交叉点属性表

	TIMELIMIT_TABLE				= 3,	//  时间限制表

	VEHICLELIMIT_TABLE			= 4,	//  车辆限制表

	TURN_TABLE					= 5,   //  转向表

	DIRECTION_TABLE				= 6,	//  方向表

	LANE_TABLE					= 7,   //  车道表

	JUNCTION_REFERENCE_TABLE	= 8,	//  交叉点参照物表

	JUNCTION_VIDEO_TABLE		= 9,	//  路口3D视频表
	
	JUNCTION_VIEW_TABLE			= 10,	//  路口放大图表
	
	JUNCTION_VRVIEW_TABLE		= 11,	//  路口实景图表
	
	JUNCTION_GUIDE_TABLE		= 12,	//  路口强制诱导表

	NEW_TURN_TABLE				= 13,   //  转向表

	NEW_DIRECTION_TABLE			= 14,	//  方向表

	NEW_LANE_TABLE				= 15,   //  车道表

	EXIT_INFO_TABLE				= 16,

	JUNCTION_SA_FACILITY_TABLE	= 17


};

//////////////////////////////////////////////////////////////////////////
// added at 2013-10-25
const int 	UNKNOWN_TABLE_TYPE				= -1;
const int 	ROAD_BASE_ROAD_TABLE			=1100; // 道路属性表
const int 	ROAD_BASE_JUNCTION_TABLE		=1101; // 交叉点属性表
const int 	ROAD_BASE_COMPOUND_TABLE		=1102; // 统合交叉点属性表
const int 	ROAD_ATTACH_TIME_TABLE			=1203; // 道路时间附属表
const int 	ROAD_ATTACH_VEHICLE_TABLE		=1204; // 道路车辆附属表
const int 	ROAD_ATTACH_TURN_TABLE			=1205; // 道路转向附属表
const int 	ROAD_ATTACH_DIRECTION_TABLE		=1206; // 道路方向附属表
const int 	ROAD_ATTACH_LANE_TABLE			=1207; // 道路车道附属表
const int 	ROAD_ATTACH_REFERENCE_TABLE		=1208; // 道路交叉点参照物附属表
const int 	ROAD_ATTACH_VIDEO_TABLE			=1209; // 道路视频附属表
const int 	ROAD_ATTACH_VIEW_TABLE			=1210; // 道路放大图附属表
const int 	ROAD_ATTACH_VRVIEW_TABLE		=1211; // 道路实景图附属表
const int 	ROAD_ATTACH_GUIDE_TABLE			=1212; // 道路强制引导附属表
const int 	ROAD_ATTACH_NTURN_TABLE			=1213; // 道路新转向附属表
const int 	ROAD_ATTACH_NDIRECTION_TABLE	=1214; // 道路新方向附属表
const int 	ROAD_ATTACH_NLANE_TABLE			=1215; // 道路新车道附属表
const int 	ROAD_ATTACH_EXITINFO_TABLE		=1216; // 道路出口附属表
const int 	ROAD_ATTACH_SA_TABLE			=1217; // 道路服务区附属表
const int	ROAD_ATTACH_FORK_TABLE			=1218; // 道路分岔路附属表

const int 	POI_BASE_POI_TABLE				=2100; // 兴趣点属性表
const int 	POI_ATTACH_TENANT_TABLE			=2201; // 兴趣点租户附属表
const int	POI_ATTACH_FUEL_TABLE			=2202; // 兴趣点燃料附属表

//////////////////////////////////////////////////////////////////////////

// LayerStatusType  Definition
//##ModelId=46B7B83A0196
enum ELayerStatusType 
{
	//##ModelId=46B7B83A0198
	LAYER_INIT,					// 图层对象刚刚建立，还未组织好属性信息；
	//##ModelId=46B7B83A0199
	LAYER_OPENED_WITHOUT_DATA,	// 图层的属性信息已组织完毕，且内存中与数据库中的数据相同，但图层中的地理数据还未被调入内存；
	//##ModelId=46B7B83A01A5
	LAYER_LOADED_AND_SAVED  ,	// 图层已被打开，且内存中含有图层的特征数据,并且这些数据已被保存到数据库中；
	//##ModelId=46B7B83A01A6
	LAYER_LOADED_AND_EDITING 	// 图层已被打开，且内存中含有图层的特征数据,这些数据已被编辑过,但编辑后的数据还未被保存到数据库中；
} ;

//定义点结构
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

//定义点结构
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
