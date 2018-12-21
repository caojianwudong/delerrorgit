#ifndef __VIDEO_DEFINITION_H__ 
#define __VIDEO_DEFINITION_H__ 1

#include <vector>
#include <string>
#include <map>
#include <list>

#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

const COLORREF COLOR_CONFIRM = RGB(45,181,45);
const COLORREF COLOR_NEW = RGB(255,137,151);
const COLORREF COLOR_TEXT = RGB(0,0,0);
const COLORREF COLOR_ERR_BACK = RGB(255,0,0);//错误背景
const COLORREF COLOR_ERR_TEXT = RGB(255,0,0);
const COLORREF COLOR_DEL_BACK = RGB(150,150,150); //基础poi删除背景色
const COLORREF COLOR_NEW_DEL_BACK = RGB(192,192,192); //新增删除
const COLORREF COLOR_PARENT_POI_TEXT = RGB(255,255,0); //本点poi前景色
//////////////////////////////////////////////////////////////////////////

const CString FIELD_INDEX = "索引";
const CString FIELD_ID = "点对象编号";
const CString FIELD_NAMEC = "中文正式名称";	
const CString FIELD_NAMEE = "英文正式名称";	
const CString FIELD_FEATCODE = "对象类型代码";	
const CString FIELD_FEATCODE_NAMEC = "对象类型代码中文";	
const CString FIELD_FEATCODE2 = "补充类别";	
const CString FIELD_FEATCODE2_NAMEC = "补充类别中文";	
const CString FIELD_SORTCODE = "系列代码";	
const CString FIELD_SORTCODE_NAMEC = "系列代码中文";	
const CString FIELD_TEL = "电话号码";	
const CString FIELD_GRADE = "等级";
const CString FIELD_AI = "附加信息";	
const CString FIELD_ADDRESS4 = "详细地址乡镇级";	
const CString FIELD_ADDRESS5 = "详细地址村级、除行政区划外的其它区域";	
const CString FIELD_ADDRESS6 = "详细地址大街路巷里";	
const CString FIELD_ADDRESS7 = "详细地址号组";	
const CString FIELD_ADDRESS8 = "详细地址其它";	
const CString FIELD_REMARK = "备注";	
const CString FIELD_NAMEP = "拼音名称";	
const CString FIELD_ADDRESS4P = "详细地址拼音乡镇级";	
const CString FIELD_ADDRESS5P = "详细地址拼音村级、除行政区划外的其它区域";	
const CString FIELD_ADDRESS6P = "详细地址拼音大街路巷里";	
const CString FIELD_ADDRESS7P = "详细地址拼音号组";	
const CString FIELD_ADDRESS8P = "详细地址拼音其它";	
const CString FIELD_NAMES = "简称";	
const CString FIELD_NAMESP = "拼音简称";
const CString FIELD_NAMEC1 = "别名1";	
const CString FIELD_NAMEC2 = "别名2";
const CString FIELD_INFOTYPE = "信息类型"; // 默认 0，疑问2
const CString FIELD_MESHID  = "所属网格代码";

const CString FIELD_OPERATETYPE = "操作类型";
const CString FIELD_DATASOUCE = "数据来源";
const CString FIELD_LINKROADID = "关联道路ID";
const CString FIELD_LINKROADMESH = "关联道路所属格网号";
const CString FIELD_RELATIONTYPE = "与所属POI的关系类型";
const CString FIELD_LINKPOIID = "所属POI的编号";
const CString FIELD_LINKMESHID = "所属POI的格网代码";
const CString FIELD_INPUTDATATYPE = "源数据类型";
const CString FIELD_OUTPUTDATATYPE = "商品化类型";
const CString FIELD_UPDATETIME  = "更新资料的年月";
const CString FIELD_ISRELATED = "是否被关联";
const CString FIELD_ROLE_USERID = "修改人";
const CString FIELD_CHECK_USERID = "校正人";

const CString FIELD_BSCAN = "是否浏览过"; // 没有被浏览过 0，有 1







const CString FIELD_COLLECT_TYPE = "外业标注类型";
const CString FIELD_COLLECT_TEL = "电话";
const CString FIELD_COLLECT_ADDRESS = "地址";
const CString FIELD_COLLECT_GRADE = "POI等级";
const CString FIELD_COLLECT_SELTYPE = "选择类型";
const CString FIELD_FLOOR_COUNT = "楼层数";
const CString FIELD_ROOMNUMBER_PRE = "房间号前缀";
const CString FIELD_ROOMNUMBER = "房间号";
const CString FIELD_POI_TYPE = "POI标示";
const CString FIELD_PAGE_ID = "PageID";
const CString FIELD_LINK_POI = "关联POI";
const CString FIELD_LINK_POI_NAME = "关联POI中文";
const CString FIELD_OWNER_FILE = "所属文件";

const CString FIELD_STATE = "POI状态";
const CString FIELD_POSITION = "真位置";
const CString FIELD_LOCATION = "方位";
const CString FIELD_POSITION_DISPLAY = "引导位置";

const CString ERROR_GEO_MISS_NEW = "漏新增";
const CString ERROR_GEO_MISS_CONFIRM = "漏确认";
const CString ERROR_GEO_OVER_NEW = "多新增";
const CString ERROR_GEO_OVER_CONFIRM = "多确认";
const CString ERROR_GEO_MISS_DELETE = "漏删除";
const CString ERROR_GEO_OVER_DELETE = "多删除";

const double SEARCH_DISTANCE = 0.000584089; //搜索其它人制作的POI时的距离，单位度，大约为50米
const double DISTANCE_AUTO_MOVE = 2; //同位置打点自动后移距离

enum TASKTYPE
{
	TASK_TYPE_UNKNOW = 0,  //未知
	TASK_TYPE_VIDEO = 1,   //车调视频
	TASK_TYPE_PIC_FOOT = 2, //步调照片
	TASK_TYPE_XY = 3, //调整位置任务
	TASK_TYPE_PIC_FOOT_COMMON = 20, //步调普通任务
	TASK_TYPE_PIC_FOOT_OUT_NEW = 21, //步调外业新增POI
};

//任务POI类型
enum TASKPOITYPE
{
	TASK_POI_TYPE_UNKNOW = 0, //初始POI（全部POI）
	TASK_POI_TYPE_COMMON = 1, //普通POI(非VIP,非永久)
	TASK_POI_TYPE_VIP    = 2, // VIP(重要永久) POI
};

struct STASKINFO
{
	__int64 id;
	//任务所属的项目id
	int idProject;
	// 任务进度 照片:POI索引 视频:
	double dLastExit;
	int idEditRoleUser;
	//任务类型：1:视频，2:照片
	int iTaskType;
	//任务类型：1:视频，20:步调普通任务，21:步调外业新增POI任务，22：步调外业新增门址点任务，23：步调外业修改POI任务，24：步调外业修改门址点任务)
	int iTaskType2;
	//项目名称
	CString sProName;
	//任务POI 类型 0: 初始值 1 :普通POI 2:vip poi(校正筛选的时候才会修改这个值)
	int taskpoitype;
	STASKINFO()
	{
		id = 0;
		idProject = 0;
		dLastExit = 0;
		idEditRoleUser = 0;
		iTaskType = 0;
		iTaskType2 = 0;
		sProName = "";
		taskpoitype = TASK_POI_TYPE_UNKNOW;
	}
	void clear()
	{
		id = 0;
		idProject = 0;
		dLastExit = 0;
		idEditRoleUser = 0;
		iTaskType = 0;
		iTaskType2 = 0;
		sProName = "";
		taskpoitype = TASK_POI_TYPE_UNKNOW;
	}
};

struct SVIDEOINFO 
{
	int idVideo; //tb_video_file:id
	char sUrl[256];
	int duration;
	char sStartTime[20];
	char sEndTime[20];
	int iLocation;
	
	SVIDEOINFO()
	{
		idVideo = 0;
		sUrl[0] = '\0';
		duration = 0;
		sStartTime[0] = '\0';
		sEndTime[0] = '\0';
		iLocation = -1;
	}
	void clear()
	{
		idVideo = 0;
		sUrl[0] = '\0';
		duration = 0;
		sStartTime[0] = '\0';
		sEndTime[0] = '\0';
		iLocation = -1;
	}
};

struct STCKINFO 
{
	int id;//数据库中tb_tck中的id
	double x;
	double y;
	char sTime[20];
	short angle; //拍摄角度，用于绘制
	double distance; //距离
	double dSecond; //秒数
	int idLinkRoadL;
	int idMeshLinkRoadL;
	int idLinkRoadR;
	int idMeshLinkRoadR;

	STCKINFO()
	{
		id = 0;
		x = 0;
		y = 0;
		sTime[0] = '\0';
		angle = 0;
		distance = -1;
		dSecond = -1;
		idLinkRoadL = 0;
		idLinkRoadR = 0;
		idMeshLinkRoadL = 0;
		idMeshLinkRoadR = 0;
	}
};

struct SPHOTOINFO 
{
	double x;
	double y;
	double dSecond;
	double dDis;
	int idVideo;
	int idRoleUser;
	SPHOTOINFO()
	{
		x = -1;
		y = -1;
		dSecond = -1;
		dDis = -1;
		idVideo = -1;
		idRoleUser = -1;
	}
	void clear()
	{
		x = -1;
		y = -1;
		dSecond = -1;
		dDis = -1;
		idVideo = -1;
		idRoleUser = -1;
	}
};

/**************************/
/**手动插入***/
enum STATUSINSERT
{
	INSERT_UNKNOW = 0,	//无手动插入
	INSERT_BEFORE = 1,	//在之前插入
	INSERT_BEHIND = 2,	//在之后插入
};

enum OPERATETYPE
{
	OPERATE_NO = -1, //无
	OPERATE_UNKNOW = 0, //未确认
	OPERATE_CONFIRM = 1, //确认
	OPERATE_NEW = 2, //新增
	OPERATE_QUESTION = 3, //疑问
	OPERATE_DELETE = 4, //存量删除标记
	OPERATE_NEW_DELETE = 5, //新增删除
	OPERATE_CONFIRM_MODIFY = 6, //确认修改
	OPERATE_COLLECT_CONFIRM = 7,//外业确认
	OPERATE_COLLECT_MODIFY = 8 ,//外业修改
	OPERATE_COLLECT_MOVEPT = 9 ,//外业移位
};

//poi 来源
enum POISOURCETYPE
{
	SOURCE_POIEDIT = 1,//1:POI编辑器，2:创建任务工具，3:母库，4:emp，5:lcs
    SOURCE_CREATETOOL = 2,
	SOURCE_BASEDB = 3,
	SOURCE_EMP  = 4,
	SOURCE_LCS  = 5
};

enum POILOCATION
{
	LOCATION_UNKNOW = -1, //未知
	LOCATION_LEFT = 0, //poi位于轨迹方向的左侧
	LOCATION_RIGHT = 1 //poi位于轨迹方向的右侧
};

enum TASKSTATE
{
	STATE_UNKNOW = 0, //未占用未提交
	STATE_OCCUPY = 1, //占用
	STATE_COMMIT = 2, //提交
	STATE_OVER = 3,//完成
	STATE_START = 4, //开始作业，目前仅用于发送日志，进行时间统计时用
};

enum PROJECTSTATE
{
	PROJECT_STATE_UNSTART = 0, //未知
	PROJECT_STATE_START = 1, //已开始
	PROJECT_STATE_WAIT = 2, //暂停
	PROJECT_STATE_CLOCK = 3,//锁定
	PROJECT_STATE_OK = 4	//完成
};

enum ACCEPT
{
	ACCEPT_UNKNOW = 0,	//未知状态
	ACCEPT_YES = 1,		//接受
	ACCEPT_NO = 2,		//不接受
	ACCEPT_ANOTHER = 3,	//其他值
	ACCEPT_WAIT = 4		//搁置
};

//TODO::应从数据库中读取
enum ERROR_TYPE
{
	ERROR_TYPE_MISS_NEW = 31, //漏新增
	ERROR_TYPE_MISS_CONFIRM = 32, //,漏确认
	ERROR_TYPE_OVER_NEW = 33,//多新增
	ERROR_TYPE_OVER_CONFIRM = 34, //多确认
	ERROR_TYPE_MISS_DELETE= 35, //漏删除
	ERROR_TYPE_OVER_DELETE = 36, //多删除
	ERROR_TYPE_POSITION = 37, //位置错误
    ERROR_TYPE_LOCATION = 38, //方位错误
	ERROR_TYPE_POSITION_DISPLAY = 39, //引导位置错误
    ERROR_TYPE_REDO  = 40,//返工
};

//错误类别
enum ERROR_CATEGORY
{
	ERROR_CATEGORY_FIELD = 1, //属性错误
	ERROR_CATEGORY_GEO = 2,   //几何错误
	ERROR_CATEGORY_MANUAL = 3,//人工错误(返工)
};

enum FIELD_TYPE
{
	FIELD_INT_TYPE = 1, 
	FIELD_DOUBLE_TYPE = 2,
	FIELD_STRING_TYPE = 3,
};

//错误状态
enum ERRORSTATE
{
	ERROR_STATE_UN_SLOVE = 1, //未解决
	ERROR_STATE_SLOVE = 2, //解决
	ERROR_STATE_CLOSE = 3   //关闭
};

// by hxz
//POI 来源
enum  POI_DATASOUCE
{
	POI_FROM_POIEDIT =1,//POI 编辑器
	POI_FROM_TASKCREATETOOL =2, //创建任务工具
	POI_FROM_BASEDB  = 3 , //母库
	POI_FROM_EMP  = 4, //emp
	POI_FORM_LCS =5   // LCS
};
struct SERROR_FIELD_INFO
{
	int idField;    //字段id
	int idCategory; //错误类别
	int idFieldType; //字段类型
	CString sFieldName;  //字段名称

	SERROR_FIELD_INFO()
	{
		idField = -1;
		idCategory = -1;
		idFieldType = -1;
		sFieldName = "";
	}
};

struct SPOI_IN_VIDEOGEO
{
	double dSecond;
	double dDistance;
	int location; //拍摄方向，左：0,右：1
	SPHOTOINFO *pPhotoSeeInfo; //观测照片信息

	SPOI_IN_VIDEOGEO()
	{
		dSecond = -1;
		dDistance = -1;
		location = -1;
		pPhotoSeeInfo = NULL;
	}

	~SPOI_IN_VIDEOGEO()
	{
		if ( NULL != pPhotoSeeInfo)
		{
			delete pPhotoSeeInfo;
			pPhotoSeeInfo = NULL;
		}
	}
};
/*note by hxz 20160918
  tb_poi
*/
struct SPOIINFO 
{
	//数据库中tb_poi的id
	__int64 id; 
	//数据库中tb_poi中的 idinemp
	int idPoi; 
	// 唯一id  对应mysql 中bigint
	__int64 idBase;
	int idMesh;
	double dSecond;
	double dDistance;
	//拍摄方向，左：0,右：1
	int location; 
	// 任务id :task id 
	__int64 idTask;
	double x;
	double y;
	//引导位置经纬度
	double xdisplay;
	double ydisplay;
	short operateType;
	// 中文正式名称
	char nameC[256];
	// 别名1
	char nameC1[256];
	// 别名2
	char nameC2[256];
	// 英文正式名称
	char nameE[256];
	// 简称
	char nameS[256];
	// 拼音名称
	char nameP[256];
	// 简称拼音
	char namesP[256];
	//对象类型代码
	int  featCode;
	// 补充类别
	char featCode2[126];
	//系列代码
	char sortCode[256];
	char tel[126];
	// 详细地址乡镇
	char address4[256];
	// 详细地址村级
	char address5[256];
	// 详细地址大街
	char address6[256];
	// 详细地址号组
	char address7[256];
	// 详细地址其他
	char address8[256];
	char address4P[256];
	char address5P[256];
	char address6P[256];
	char address7P[256];
	char address8P[256];
	//附加信息
	char AI[256];
	//与所属POI的关系类型
	int     relationtype;
	//所属POI的编号
	int     linkpoiid;
	//所属POI的网格代码
	int     linkmeshid;
	//源数据类型
	char inputDataType[126];
	//商品化类型
	short outputDataType;
	// 备注
	char remark[256];
	//更新年月2016-10
	char updatetime[8];
	//是否被关联
	char isrelated[20];
	//等级 0:一般 1:永久 2:重要
	int iGrade; 
	//信息类型：0默认，2疑问点
	int infoType; 
	//修改人
	int  role_user_id;
	//校正人
	int  check_user_id;
	//观测照片信息
	SPHOTOINFO *pPhotoSeeInfo; 
	int idLinkRoad;
	int idMeshLinkRoad;
	//数据来源 1:POI编辑器 2：创建任务工具 3:母库 4 :emp 5:lcs
	int idatasource;
	// poi 类型 0:初始值，1：普通 2:vip （这个值筛选的时候才赋值，所以复制初始化默认值，新增的时候为了保持POI名称列表一致性，赋值从属类型）
	int taskpoitype;
   //////////////////////////////////////////////////////////////////////////
	//poi控制信息
	//poi是否浏览过 false 未浏览(默认值) true 浏览
	bool  bscan;

	SPOIINFO()
	{
		id = 0;
		idPoi = 0;
		idBase = 0;
		idMesh = 0;
		dSecond = -1;
		dDistance = -1;
		location = -1;
		idTask = -1;
		x = 0;
		y = 0;
		xdisplay = 0;
		ydisplay = 0;
		operateType = 0;
		nameC[0] = '\0';
		nameC1[0] = '\0';
		nameC2[0] = '\0';
		nameE[0] = '\0';
		nameS[0] = '\0';
		nameP[0] = '\0';
		namesP[0] = '\0';
		featCode = 0;
		featCode2[0] = '\0';
		sortCode[0] = '\0';
		tel[0] = '\0';
		address4[0] = '\0';
		address5[0] = '\0';
		address6[0] = '\0';
		address7[0] = '\0';
		address8[0] = '\0';
		address4P[0] = '\0';
		address5P[0] = '\0';
		address6P[0] = '\0';
		address7P[0] = '\0';
		address8P[0] = '\0';
		AI[0] = '\0';
		inputDataType[0] = '\0';
		outputDataType = 0;
		remark[0] = '\0';
		iGrade = 0;
		infoType = 0;
		pPhotoSeeInfo = NULL;
		idLinkRoad = 0;
		idMeshLinkRoad = 0;
		idatasource = 0;
		updatetime[0] = '\0';
		updatetime[7] = '\0';
		relationtype = 0;
		linkpoiid = 0;
		linkmeshid = 0;
		isrelated[0]= '\0';
		role_user_id = 0;
		check_user_id = 0;
		taskpoitype = TASK_POI_TYPE_UNKNOW;
		bscan = false;
	}

	SPOIINFO(SPOIINFO* pPoiInfo)
	{
		if ( pPoiInfo != NULL)
		{
			x = pPoiInfo->x;
			y = pPoiInfo->y;
		}
	}
	
	~SPOIINFO()
	{
		if ( NULL != pPhotoSeeInfo)
		{
			delete pPhotoSeeInfo;
			pPhotoSeeInfo = NULL;
		}
	}

	CString GetValueByFieldName( const char *sName)
	{
		CString sValue = "";
		if ( strcmp( sName, FIELD_NAMEC) == 0)
		{
			return nameC;
		}
		else if ( strcmp( sName, FIELD_NAMEC1) == 0)
		{
			return nameC1;
		}
		else if ( strcmp( sName, FIELD_NAMEC2) == 0)
		{
			return nameC2;
		}
		else if ( strcmp( sName, FIELD_NAMEE) == 0)
		{
			return nameE;
		}
		else if ( strcmp( sName, FIELD_NAMES) == 0)
		{
			return nameS;
		}
		else if ( strcmp( sName, FIELD_NAMEP) == 0)
		{
			return nameP;
		}
		else if ( strcmp( sName, FIELD_FEATCODE) == 0)
		{
			sValue.Format("%d", featCode);
			return sValue;
		}
		else if ( strcmp( sName, FIELD_FEATCODE2) == 0)
		{
			return featCode2;
		}
		else if ( strcmp( sName, FIELD_SORTCODE) == 0)
		{
			return sortCode;
		}
		else if ( strcmp( sName, FIELD_TEL) == 0)
		{
			return tel;
		}
		else if ( strcmp( sName, FIELD_ADDRESS4) == 0)
		{
			return address4;
		}
		else if ( strcmp( sName, FIELD_ADDRESS5) == 0)
		{
			return address5;
		}
		else if ( strcmp( sName, FIELD_ADDRESS6) == 0)
		{
			return address6;
		}
		else if ( strcmp( sName, FIELD_ADDRESS7) == 0)
		{
			return address7;
		}
		else if ( strcmp( sName, FIELD_ADDRESS8) == 0)
		{
			return address8;
		}
		else if ( strcmp( sName, FIELD_ADDRESS4P) == 0)
		{
			return address4P;
		}
		else if ( strcmp( sName, FIELD_ADDRESS5P) == 0)
		{
			return address5P;
		}
		else if ( strcmp( sName, FIELD_ADDRESS6P) == 0)
		{
			return address6P;
		}
		else if ( strcmp( sName, FIELD_ADDRESS7P) == 0)
		{
			return address7P;
		}
		else if ( strcmp( sName, FIELD_ADDRESS8P) == 0)
		{
			return address8P;
		}
		else if ( strcmp( sName, FIELD_AI) == 0)
		{
			return AI;
		}
		else if ( strcmp( sName, FIELD_REMARK) == 0)
		{
			return remark;
		}
		else if ( strcmp( sName, FIELD_GRADE) == 0)
		{
			sValue.Format("%d", iGrade);
			return sValue;
		}
		else if ( strcmp(sName, FIELD_NAMESP) == 0)
		{
			return namesP;
		}

		return "";
	}

	void SetValueByFieldName( const char *sName, const char *sValue)
	{
		if ( strcmp( sName, FIELD_NAMEC) == 0)
		{
			_snprintf( nameC, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_NAMEC1) == 0)
		{
			_snprintf( nameC1, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_NAMEC2) == 0)
		{
			_snprintf( nameC2, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_NAMEE) == 0)
		{
			_snprintf( nameE, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_NAMES) == 0)
		{
			_snprintf( nameS, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_NAMEP) == 0)
		{
			_snprintf( nameP, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_FEATCODE) == 0)
		{
			featCode =atoi( sValue);
		}
		else if ( strcmp( sName, FIELD_FEATCODE2) == 0)
		{
			_snprintf( featCode2, 126, sValue);
		}
		else if ( strcmp( sName, FIELD_TEL) == 0)
		{
			_snprintf( tel, 126, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS4) == 0)
		{
			_snprintf( address4, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS5) == 0)
		{
			_snprintf( address5, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS6) == 0)
		{
			_snprintf( address6, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS7) == 0)
		{
			_snprintf( address7, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS8) == 0)
		{
			_snprintf( address8, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS4P) == 0)
		{
			_snprintf( address4P, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS5P) == 0)
		{
			_snprintf( address5P, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS6P) == 0)
		{
			_snprintf( address6P, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS7P) == 0)
		{
			_snprintf( address7P, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_ADDRESS8P) == 0)
		{
			_snprintf( address8P, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_AI) == 0)
		{
			_snprintf( AI, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_REMARK) == 0)
		{
			_snprintf( remark, 256, sValue);
		}
		else if ( strcmp( sName, FIELD_GRADE) == 0)
		{
			iGrade = atoi( sValue);
		}
		else if ( strcmp( sName,FIELD_NAMESP) == 0)
		{
			_snprintf(namesP,256,sValue);
		}
	}

	//新增POI
	//除了中文名称和电话外的属性
	void Init(SPOIINFO* pPoiInfo)
	{
		if( pPoiInfo != NULL)
		{
			idMesh = pPoiInfo->idMesh;
			idTask = pPoiInfo->idTask;
			x = pPoiInfo->x;
			y = pPoiInfo->y;
			xdisplay = x;//pPoiInfo->xdisplay;
			ydisplay = y;//pPoiInfo->ydisplay;
			
			idLinkRoad = pPoiInfo->idLinkRoad;
			idMeshLinkRoad = pPoiInfo->idMeshLinkRoad;
		
			strcpy( nameC1,pPoiInfo->nameC1);
			strcpy( nameC2,pPoiInfo->nameC2);
			strcpy(nameE ,pPoiInfo->nameE);
			strcpy(nameS , pPoiInfo->nameS);
			strcpy(namesP, pPoiInfo->namesP);

			featCode = pPoiInfo->featCode;
			strcpy(featCode2,pPoiInfo->featCode2);
			strcpy(sortCode,pPoiInfo->sortCode);
	
//			iGrade = pPoiInfo->iGrade;
			
			strcpy(address4,pPoiInfo->address4);
			strcpy(address5,pPoiInfo->address5);
			strcpy(address6,pPoiInfo->address6);
			strcpy(address7,pPoiInfo->address7);
			strcpy(address8,pPoiInfo->address8);
			strcpy(address4P,pPoiInfo->address4P);
			strcpy(address5P,pPoiInfo->address5P);
			strcpy(address6P,pPoiInfo->address6P);
			strcpy(address7P,pPoiInfo->address7P);
			strcpy(address8P,pPoiInfo->address8P);
			strcpy(AI,pPoiInfo->AI);
			
			relationtype = pPoiInfo->relationtype;
			linkpoiid = pPoiInfo->linkpoiid;
			linkmeshid = pPoiInfo->linkmeshid;
			
			strcpy(inputDataType,pPoiInfo->inputDataType);
			outputDataType = pPoiInfo->outputDataType;
			
			strcpy(remark,pPoiInfo->remark);
			strcpy(isrelated,pPoiInfo->isrelated);
			infoType = pPoiInfo->infoType;
			
			dSecond = pPoiInfo->dSecond;
			dDistance = pPoiInfo->dDistance;
			location = pPoiInfo->location;
			taskpoitype = pPoiInfo->taskpoitype ;

			strcpy(updatetime,pPoiInfo->updatetime);


		}
	}

	void Copy(SPOIINFO* pPoiInfo)
	{
		if( pPoiInfo != NULL)
		{
			id = pPoiInfo->id;
			idBase = pPoiInfo->idBase;
			idPoi =  pPoiInfo->idPoi;
			idMesh = pPoiInfo->idMesh;
			idTask = pPoiInfo->idTask;
			operateType = pPoiInfo->operateType;
			idatasource = pPoiInfo->idatasource;

		
		
			x = pPoiInfo->x;
			y = pPoiInfo->y;
			xdisplay = pPoiInfo->xdisplay;
			ydisplay = pPoiInfo->ydisplay;
			
			idLinkRoad = pPoiInfo->idLinkRoad;
			idMeshLinkRoad = pPoiInfo->idMeshLinkRoad;
			strcpy( nameC,pPoiInfo->nameC);
			strcpy( nameC1,pPoiInfo->nameC1);
			strcpy( nameC2,pPoiInfo->nameC2);
			strcpy(nameE ,pPoiInfo->nameE);
			strcpy(nameS , pPoiInfo->nameS);
			strcpy(namesP, pPoiInfo->namesP);
			strcpy(nameP,pPoiInfo->nameP);
			featCode = pPoiInfo->featCode;
			strcpy(featCode2,pPoiInfo->featCode2);
			strcpy(sortCode,pPoiInfo->sortCode);
			strcpy(tel,pPoiInfo->tel);

			iGrade = pPoiInfo->iGrade;

			strcpy(address4,pPoiInfo->address4);
			strcpy(address5,pPoiInfo->address5);
			strcpy(address6,pPoiInfo->address6);
			strcpy(address7,pPoiInfo->address7);
			strcpy(address8,pPoiInfo->address8);
			strcpy(address4P,pPoiInfo->address4P);
			strcpy(address5P,pPoiInfo->address5P);
			strcpy(address6P,pPoiInfo->address6P);
			strcpy(address7P,pPoiInfo->address7P);
			strcpy(address8P,pPoiInfo->address8P);
			strcpy(AI,pPoiInfo->AI);

			relationtype = pPoiInfo->relationtype;
			linkpoiid = pPoiInfo->linkpoiid;
			linkmeshid = pPoiInfo->linkmeshid;

			strcpy(inputDataType,pPoiInfo->inputDataType);
			outputDataType = pPoiInfo->outputDataType;

			strcpy(remark,pPoiInfo->remark);

			strcpy(updatetime,pPoiInfo->updatetime);

			strcpy(isrelated,pPoiInfo->isrelated);
			infoType = pPoiInfo->infoType;
			role_user_id = pPoiInfo->role_user_id;

			dSecond = pPoiInfo->dSecond;
			dDistance = pPoiInfo->dDistance;
			location = pPoiInfo->location;
		}
	}
};

struct SERRORPOI 
{
	__int64 errorId; //数据库中tb_error的id
	__int64 taskID;	//任务ID
	__int64 dataID; //数据库中tb_poi中的Id  modify by hxz 20161009 关联成tb_poi 的idbase
	char nameC[256];
	int errField;	//错误字段
	char oldValue[256];	//原值
	char newValue[256];	//正确提示
	int errType;		//错误类型
	int modifyStatus;	//修订状态
	int errStatus;		//错误状态
	char errRemark[256];	//备注
	int findErrUser;	//错误检出人
	int modiErrUser;	//错误变更人
	int location;
	double distance;
	double x;
	double y;
	
	SERRORPOI()
	{
		errorId = 0;
		taskID = 0;
		dataID = 0;
		nameC[0] = '\0';
		errField = 0;
		oldValue[0] = '\0';
		newValue[0] = '\0';
		errType = 0;
		modifyStatus = 0;
		errStatus = 1;
		errRemark[0] = '\0';
		findErrUser = 0;
		modiErrUser = 0;
		location = 0;
		distance = -1;
		x = 0;
		y = 0;
	}
};

//修改补丁结构
struct ModifyPoi
{
	__int64  id;
	__int64  poi_id;
	__int64  task_id;
	int      field_name_id;
	int      bcheck ;
	char oldValue[256];	//原值
	char newValue[256];	//正确提示
	ModifyPoi()
	{
		id = 0;
		poi_id = 0;
		task_id = 0;
		field_name_id = -1;
		bcheck = 0;
		oldValue[0] = '\0';
		newValue[0] = '\0';
	}
};

//定义和文档有出入
// enum COLLECT_TYPE
// {
// 	COLLECT_TYPE_UNKNOW = -1, //未知状态可能是新增加的
// 	COLLECT_TYPE_NORMAL = 0,  //正常
// 	COLLECT_TYPE_NEW = 1,     //新增
// 	COLLECT_TYPE_MODIFY = 2,  //修改
// 	COLLECT_TYPE_DELETE = 3,  //删除
// 	COLLECT_TYPE_MOVE = 4,     //移动
// 	COLLECT_TYPE_NEW_INTER = 5,  //内业新增
// };
// by hxz 20161025
enum COLLECT_TYPE
{
	COLLECT_TYPE_NEW = 1,     //新增
	COLLECT_TYPE_DELETE = 2,  //删除
	COLLECT_TYPE_MODIFY = 3,  //修改
	COLLECT_TYPE_NORMAL = 4,  //正常
	COLLECT_TYPE_MOVE = 5,     //移动
	COLLECT_TYPE_UNKNOW = 6, //未知状态可能是新增加的
	COLLECT_TYPE_NEW_INTER = 7,  //内业新增
};

//POI类型对应关系：例如：普通-0；门址-1
struct tagPOIType 
{
	int nType;
	std::string sType;
	
	//保存到mdb中的类型值
	int nSaveType;
	int nTrans;
	
	tagPOIType()
	{
		nType = -1;
		sType = "";
		nSaveType = -1;
		nTrans = -1;
	};
};
/*note by hxz 20160918  modify
  tb_poi_collection
*/
class SPOI_COLLECTION_INFO
{
public:
	__int64 id; //
	int type; //1:平板 2:稀疏区
	double x;
	double y;
	double xdisplay;
	double ydisplay;
	int    imeshid;
	int    idinemp;
	char   namec[256];
	char   tel[120];
	char   address[1000];
	int    grade;//poi等级
	char   remark[256];
	int    idOwnerFile;

	SPOI_COLLECTION_INFO()
	{
		id = -1;
		type = -1;
		x = -1;
		y = -1;
		xdisplay = -1;
		ydisplay = -1;
		imeshid = -1;
		idinemp = -1;
		namec[0] = '\0';
		tel[0] = '\0';
		address[0] = '\0';
		grade = -1;
		remark[0] = '\0';
		idOwnerFile = -1;
	}

	void  Copy(SPOI_COLLECTION_INFO *pCollectionInfo)
	{
		if ( pCollectionInfo != NULL)
		{
			type = pCollectionInfo->type;
			x = pCollectionInfo->x;
			y = pCollectionInfo->y;
			xdisplay = pCollectionInfo->xdisplay;
			ydisplay = pCollectionInfo->ydisplay;
			imeshid = pCollectionInfo->imeshid;
			idinemp = pCollectionInfo->idinemp;
			strcpy(namec,pCollectionInfo->namec);
			strcpy(tel,pCollectionInfo->tel);
			strcpy(address,pCollectionInfo->address);
			grade = pCollectionInfo->grade;
			strcpy(remark,pCollectionInfo->remark);
			idOwnerFile = pCollectionInfo->idOwnerFile;
		}
	}

};

/*note by hxz 20160918
  tb_poi_collection_index
*/
class SPOI_COLLECTION_INFO_INDEX : public SPOI_COLLECTION_INFO
{
public:
//	__int64 id; //tb_poi_collection:id
//	char nameC[256]; //
	int iCollectType; //采集类型:新增、删除等
//	char tel[256]; 
//	char address[256];
//	int iGrade;
//	char remark[256];
	int iSelType; //选择类型：餐厅、专营市场等
	int iFloorcount; //楼层数
	int iRoomnumber_pre; //房间号前缀
	int iRoomnumber; //房间号
	int iCollectUser; 
	__int64 iCellinfo; 
	int iCollectionid;
	int iPoiType; //poi类型，相当于等级，外业分的更详细
	__int64 iPoiTimeStamp; //poi唯一标识
	int iPageid; 
	char linkPoiid[256];
	char linkPoinameC[256];
	int idOwnerFile;

	SPOI_COLLECTION_INFO_INDEX()
	{
//		id = 0;
//		nameC[0] = '\0';
		iCollectType = -1;
//		tel[0] = '\0';
//		address[0] = '\0';
//		iGrade = -1;
//		remark[0] = '\0';
		iSelType = -1;
		iFloorcount = -1;
		iRoomnumber_pre = -1;
		iRoomnumber = -1;
		iCollectUser = -1;
		iCellinfo= -1;
		iCollectionid = -1;
		iPoiType = -1;
		iPoiTimeStamp = -1;
		iPageid = -1;
		linkPoiid[0] = '\0';
		linkPoinameC[0] = '\0';
		idOwnerFile = -1;
	}
	void  Copy(SPOI_COLLECTION_INFO_INDEX *pCollectionInfo)
	{
		if ( pCollectionInfo != NULL)
		{
			SPOI_COLLECTION_INFO::Copy((SPOI_COLLECTION_INFO*)pCollectionInfo);

//			strcpy(nameC,pCollectionInfo->nameC);
			iCollectType = pCollectionInfo->iCollectType;
			strcpy(tel,pCollectionInfo->tel);
			strcpy(address,pCollectionInfo->address);
//			iGrade =  pCollectionInfo->iGrade;
			strcpy(remark,pCollectionInfo->remark);
			iSelType = pCollectionInfo->iSelType;
			iFloorcount = pCollectionInfo->iFloorcount;
			iRoomnumber_pre = pCollectionInfo->iRoomnumber_pre;
			iRoomnumber = pCollectionInfo->iRoomnumber;
			iCollectUser = pCollectionInfo->iCollectUser;
			iCellinfo= pCollectionInfo->iCellinfo;
			iCollectionid = pCollectionInfo->iCollectionid;
			iPoiType = pCollectionInfo->iPoiType;
			iPoiTimeStamp = pCollectionInfo->iPoiTimeStamp;
			iPageid = pCollectionInfo->iPageid;
			strcpy(linkPoiid,pCollectionInfo->linkPoiid);
			strcpy(linkPoinameC,pCollectionInfo->linkPoinameC);
			idOwnerFile = pCollectionInfo->idOwnerFile;
		}
	}
};


typedef std::vector<SVIDEOINFO *> VT_SVIDEOINFO;
typedef std::vector<STCKINFO *> VT_STCKINFO;
typedef std::vector<SPOIINFO *> VT_SPOIINFO;
typedef std::vector<std::string> VT_STRING;
typedef std::multimap<double, SPOIINFO *> MAP_POIINFO;
typedef std::multimap<double, STCKINFO *> MAP_TCKINFO;
typedef std::map<int,  > MAP_POIIDINFO;
// typedef std::map<int, int> MapInt;
typedef std::multimap<int, int> MapInt;
typedef std::multimap<int,SERRORPOI*> MAP_ERRORPOI;
typedef std::list<SPOIINFO*> LIST_POIINFO;
// <POI 唯一标识 , 修改记录>
typedef std::multimap<__int64,ModifyPoi*> MAP_MODIFYPOI;
#endif