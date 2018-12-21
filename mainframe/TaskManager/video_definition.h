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
const COLORREF COLOR_ERR_BACK = RGB(255,0,0);//���󱳾�
const COLORREF COLOR_ERR_TEXT = RGB(255,0,0);
const COLORREF COLOR_DEL_BACK = RGB(150,150,150); //����poiɾ������ɫ
const COLORREF COLOR_NEW_DEL_BACK = RGB(192,192,192); //����ɾ��
const COLORREF COLOR_PARENT_POI_TEXT = RGB(255,255,0); //����poiǰ��ɫ
//////////////////////////////////////////////////////////////////////////

const CString FIELD_INDEX = "����";
const CString FIELD_ID = "�������";
const CString FIELD_NAMEC = "������ʽ����";	
const CString FIELD_NAMEE = "Ӣ����ʽ����";	
const CString FIELD_FEATCODE = "�������ʹ���";	
const CString FIELD_FEATCODE_NAMEC = "�������ʹ�������";	
const CString FIELD_FEATCODE2 = "�������";	
const CString FIELD_FEATCODE2_NAMEC = "�����������";	
const CString FIELD_SORTCODE = "ϵ�д���";	
const CString FIELD_SORTCODE_NAMEC = "ϵ�д�������";	
const CString FIELD_TEL = "�绰����";	
const CString FIELD_GRADE = "�ȼ�";
const CString FIELD_AI = "������Ϣ";	
const CString FIELD_ADDRESS4 = "��ϸ��ַ����";	
const CString FIELD_ADDRESS5 = "��ϸ��ַ�弶�����������������������";	
const CString FIELD_ADDRESS6 = "��ϸ��ַ���·����";	
const CString FIELD_ADDRESS7 = "��ϸ��ַ����";	
const CString FIELD_ADDRESS8 = "��ϸ��ַ����";	
const CString FIELD_REMARK = "��ע";	
const CString FIELD_NAMEP = "ƴ������";	
const CString FIELD_ADDRESS4P = "��ϸ��ַƴ������";	
const CString FIELD_ADDRESS5P = "��ϸ��ַƴ���弶�����������������������";	
const CString FIELD_ADDRESS6P = "��ϸ��ַƴ�����·����";	
const CString FIELD_ADDRESS7P = "��ϸ��ַƴ������";	
const CString FIELD_ADDRESS8P = "��ϸ��ַƴ������";	
const CString FIELD_NAMES = "���";	
const CString FIELD_NAMESP = "ƴ�����";
const CString FIELD_NAMEC1 = "����1";	
const CString FIELD_NAMEC2 = "����2";
const CString FIELD_INFOTYPE = "��Ϣ����"; // Ĭ�� 0������2
const CString FIELD_MESHID  = "�����������";

const CString FIELD_OPERATETYPE = "��������";
const CString FIELD_DATASOUCE = "������Դ";
const CString FIELD_LINKROADID = "������·ID";
const CString FIELD_LINKROADMESH = "������·����������";
const CString FIELD_RELATIONTYPE = "������POI�Ĺ�ϵ����";
const CString FIELD_LINKPOIID = "����POI�ı��";
const CString FIELD_LINKMESHID = "����POI�ĸ�������";
const CString FIELD_INPUTDATATYPE = "Դ��������";
const CString FIELD_OUTPUTDATATYPE = "��Ʒ������";
const CString FIELD_UPDATETIME  = "�������ϵ�����";
const CString FIELD_ISRELATED = "�Ƿ񱻹���";
const CString FIELD_ROLE_USERID = "�޸���";
const CString FIELD_CHECK_USERID = "У����";

const CString FIELD_BSCAN = "�Ƿ������"; // û�б������ 0���� 1







const CString FIELD_COLLECT_TYPE = "��ҵ��ע����";
const CString FIELD_COLLECT_TEL = "�绰";
const CString FIELD_COLLECT_ADDRESS = "��ַ";
const CString FIELD_COLLECT_GRADE = "POI�ȼ�";
const CString FIELD_COLLECT_SELTYPE = "ѡ������";
const CString FIELD_FLOOR_COUNT = "¥����";
const CString FIELD_ROOMNUMBER_PRE = "�����ǰ׺";
const CString FIELD_ROOMNUMBER = "�����";
const CString FIELD_POI_TYPE = "POI��ʾ";
const CString FIELD_PAGE_ID = "PageID";
const CString FIELD_LINK_POI = "����POI";
const CString FIELD_LINK_POI_NAME = "����POI����";
const CString FIELD_OWNER_FILE = "�����ļ�";

const CString FIELD_STATE = "POI״̬";
const CString FIELD_POSITION = "��λ��";
const CString FIELD_LOCATION = "��λ";
const CString FIELD_POSITION_DISPLAY = "����λ��";

const CString ERROR_GEO_MISS_NEW = "©����";
const CString ERROR_GEO_MISS_CONFIRM = "©ȷ��";
const CString ERROR_GEO_OVER_NEW = "������";
const CString ERROR_GEO_OVER_CONFIRM = "��ȷ��";
const CString ERROR_GEO_MISS_DELETE = "©ɾ��";
const CString ERROR_GEO_OVER_DELETE = "��ɾ��";

const double SEARCH_DISTANCE = 0.000584089; //����������������POIʱ�ľ��룬��λ�ȣ���ԼΪ50��
const double DISTANCE_AUTO_MOVE = 2; //ͬλ�ô���Զ����ƾ���

enum TASKTYPE
{
	TASK_TYPE_UNKNOW = 0,  //δ֪
	TASK_TYPE_VIDEO = 1,   //������Ƶ
	TASK_TYPE_PIC_FOOT = 2, //������Ƭ
	TASK_TYPE_XY = 3, //����λ������
	TASK_TYPE_PIC_FOOT_COMMON = 20, //������ͨ����
	TASK_TYPE_PIC_FOOT_OUT_NEW = 21, //������ҵ����POI
};

//����POI����
enum TASKPOITYPE
{
	TASK_POI_TYPE_UNKNOW = 0, //��ʼPOI��ȫ��POI��
	TASK_POI_TYPE_COMMON = 1, //��ͨPOI(��VIP,������)
	TASK_POI_TYPE_VIP    = 2, // VIP(��Ҫ����) POI
};

struct STASKINFO
{
	__int64 id;
	//������������Ŀid
	int idProject;
	// ������� ��Ƭ:POI���� ��Ƶ:
	double dLastExit;
	int idEditRoleUser;
	//�������ͣ�1:��Ƶ��2:��Ƭ
	int iTaskType;
	//�������ͣ�1:��Ƶ��20:������ͨ����21:������ҵ����POI����22��������ҵ������ַ������23��������ҵ�޸�POI����24��������ҵ�޸���ַ������)
	int iTaskType2;
	//��Ŀ����
	CString sProName;
	//����POI ���� 0: ��ʼֵ 1 :��ͨPOI 2:vip poi(У��ɸѡ��ʱ��Ż��޸����ֵ)
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
	int id;//���ݿ���tb_tck�е�id
	double x;
	double y;
	char sTime[20];
	short angle; //����Ƕȣ����ڻ���
	double distance; //����
	double dSecond; //����
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
/**�ֶ�����***/
enum STATUSINSERT
{
	INSERT_UNKNOW = 0,	//���ֶ�����
	INSERT_BEFORE = 1,	//��֮ǰ����
	INSERT_BEHIND = 2,	//��֮�����
};

enum OPERATETYPE
{
	OPERATE_NO = -1, //��
	OPERATE_UNKNOW = 0, //δȷ��
	OPERATE_CONFIRM = 1, //ȷ��
	OPERATE_NEW = 2, //����
	OPERATE_QUESTION = 3, //����
	OPERATE_DELETE = 4, //����ɾ�����
	OPERATE_NEW_DELETE = 5, //����ɾ��
	OPERATE_CONFIRM_MODIFY = 6, //ȷ���޸�
	OPERATE_COLLECT_CONFIRM = 7,//��ҵȷ��
	OPERATE_COLLECT_MODIFY = 8 ,//��ҵ�޸�
	OPERATE_COLLECT_MOVEPT = 9 ,//��ҵ��λ
};

//poi ��Դ
enum POISOURCETYPE
{
	SOURCE_POIEDIT = 1,//1:POI�༭����2:�������񹤾ߣ�3:ĸ�⣬4:emp��5:lcs
    SOURCE_CREATETOOL = 2,
	SOURCE_BASEDB = 3,
	SOURCE_EMP  = 4,
	SOURCE_LCS  = 5
};

enum POILOCATION
{
	LOCATION_UNKNOW = -1, //δ֪
	LOCATION_LEFT = 0, //poiλ�ڹ켣��������
	LOCATION_RIGHT = 1 //poiλ�ڹ켣������Ҳ�
};

enum TASKSTATE
{
	STATE_UNKNOW = 0, //δռ��δ�ύ
	STATE_OCCUPY = 1, //ռ��
	STATE_COMMIT = 2, //�ύ
	STATE_OVER = 3,//���
	STATE_START = 4, //��ʼ��ҵ��Ŀǰ�����ڷ�����־������ʱ��ͳ��ʱ��
};

enum PROJECTSTATE
{
	PROJECT_STATE_UNSTART = 0, //δ֪
	PROJECT_STATE_START = 1, //�ѿ�ʼ
	PROJECT_STATE_WAIT = 2, //��ͣ
	PROJECT_STATE_CLOCK = 3,//����
	PROJECT_STATE_OK = 4	//���
};

enum ACCEPT
{
	ACCEPT_UNKNOW = 0,	//δ֪״̬
	ACCEPT_YES = 1,		//����
	ACCEPT_NO = 2,		//������
	ACCEPT_ANOTHER = 3,	//����ֵ
	ACCEPT_WAIT = 4		//����
};

//TODO::Ӧ�����ݿ��ж�ȡ
enum ERROR_TYPE
{
	ERROR_TYPE_MISS_NEW = 31, //©����
	ERROR_TYPE_MISS_CONFIRM = 32, //,©ȷ��
	ERROR_TYPE_OVER_NEW = 33,//������
	ERROR_TYPE_OVER_CONFIRM = 34, //��ȷ��
	ERROR_TYPE_MISS_DELETE= 35, //©ɾ��
	ERROR_TYPE_OVER_DELETE = 36, //��ɾ��
	ERROR_TYPE_POSITION = 37, //λ�ô���
    ERROR_TYPE_LOCATION = 38, //��λ����
	ERROR_TYPE_POSITION_DISPLAY = 39, //����λ�ô���
    ERROR_TYPE_REDO  = 40,//����
};

//�������
enum ERROR_CATEGORY
{
	ERROR_CATEGORY_FIELD = 1, //���Դ���
	ERROR_CATEGORY_GEO = 2,   //���δ���
	ERROR_CATEGORY_MANUAL = 3,//�˹�����(����)
};

enum FIELD_TYPE
{
	FIELD_INT_TYPE = 1, 
	FIELD_DOUBLE_TYPE = 2,
	FIELD_STRING_TYPE = 3,
};

//����״̬
enum ERRORSTATE
{
	ERROR_STATE_UN_SLOVE = 1, //δ���
	ERROR_STATE_SLOVE = 2, //���
	ERROR_STATE_CLOSE = 3   //�ر�
};

// by hxz
//POI ��Դ
enum  POI_DATASOUCE
{
	POI_FROM_POIEDIT =1,//POI �༭��
	POI_FROM_TASKCREATETOOL =2, //�������񹤾�
	POI_FROM_BASEDB  = 3 , //ĸ��
	POI_FROM_EMP  = 4, //emp
	POI_FORM_LCS =5   // LCS
};
struct SERROR_FIELD_INFO
{
	int idField;    //�ֶ�id
	int idCategory; //�������
	int idFieldType; //�ֶ�����
	CString sFieldName;  //�ֶ�����

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
	int location; //���㷽����0,�ң�1
	SPHOTOINFO *pPhotoSeeInfo; //�۲���Ƭ��Ϣ

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
	//���ݿ���tb_poi��id
	__int64 id; 
	//���ݿ���tb_poi�е� idinemp
	int idPoi; 
	// Ψһid  ��Ӧmysql ��bigint
	__int64 idBase;
	int idMesh;
	double dSecond;
	double dDistance;
	//���㷽����0,�ң�1
	int location; 
	// ����id :task id 
	__int64 idTask;
	double x;
	double y;
	//����λ�þ�γ��
	double xdisplay;
	double ydisplay;
	short operateType;
	// ������ʽ����
	char nameC[256];
	// ����1
	char nameC1[256];
	// ����2
	char nameC2[256];
	// Ӣ����ʽ����
	char nameE[256];
	// ���
	char nameS[256];
	// ƴ������
	char nameP[256];
	// ���ƴ��
	char namesP[256];
	//�������ʹ���
	int  featCode;
	// �������
	char featCode2[126];
	//ϵ�д���
	char sortCode[256];
	char tel[126];
	// ��ϸ��ַ����
	char address4[256];
	// ��ϸ��ַ�弶
	char address5[256];
	// ��ϸ��ַ���
	char address6[256];
	// ��ϸ��ַ����
	char address7[256];
	// ��ϸ��ַ����
	char address8[256];
	char address4P[256];
	char address5P[256];
	char address6P[256];
	char address7P[256];
	char address8P[256];
	//������Ϣ
	char AI[256];
	//������POI�Ĺ�ϵ����
	int     relationtype;
	//����POI�ı��
	int     linkpoiid;
	//����POI���������
	int     linkmeshid;
	//Դ��������
	char inputDataType[126];
	//��Ʒ������
	short outputDataType;
	// ��ע
	char remark[256];
	//��������2016-10
	char updatetime[8];
	//�Ƿ񱻹���
	char isrelated[20];
	//�ȼ� 0:һ�� 1:���� 2:��Ҫ
	int iGrade; 
	//��Ϣ���ͣ�0Ĭ�ϣ�2���ʵ�
	int infoType; 
	//�޸���
	int  role_user_id;
	//У����
	int  check_user_id;
	//�۲���Ƭ��Ϣ
	SPHOTOINFO *pPhotoSeeInfo; 
	int idLinkRoad;
	int idMeshLinkRoad;
	//������Դ 1:POI�༭�� 2���������񹤾� 3:ĸ�� 4 :emp 5:lcs
	int idatasource;
	// poi ���� 0:��ʼֵ��1����ͨ 2:vip �����ֵɸѡ��ʱ��Ÿ�ֵ�����Ը��Ƴ�ʼ��Ĭ��ֵ��������ʱ��Ϊ�˱���POI�����б�һ���ԣ���ֵ�������ͣ�
	int taskpoitype;
   //////////////////////////////////////////////////////////////////////////
	//poi������Ϣ
	//poi�Ƿ������ false δ���(Ĭ��ֵ) true ���
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

	//����POI
	//�����������ƺ͵绰�������
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
	__int64 errorId; //���ݿ���tb_error��id
	__int64 taskID;	//����ID
	__int64 dataID; //���ݿ���tb_poi�е�Id  modify by hxz 20161009 ������tb_poi ��idbase
	char nameC[256];
	int errField;	//�����ֶ�
	char oldValue[256];	//ԭֵ
	char newValue[256];	//��ȷ��ʾ
	int errType;		//��������
	int modifyStatus;	//�޶�״̬
	int errStatus;		//����״̬
	char errRemark[256];	//��ע
	int findErrUser;	//��������
	int modiErrUser;	//��������
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

//�޸Ĳ����ṹ
struct ModifyPoi
{
	__int64  id;
	__int64  poi_id;
	__int64  task_id;
	int      field_name_id;
	int      bcheck ;
	char oldValue[256];	//ԭֵ
	char newValue[256];	//��ȷ��ʾ
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

//������ĵ��г���
// enum COLLECT_TYPE
// {
// 	COLLECT_TYPE_UNKNOW = -1, //δ֪״̬�����������ӵ�
// 	COLLECT_TYPE_NORMAL = 0,  //����
// 	COLLECT_TYPE_NEW = 1,     //����
// 	COLLECT_TYPE_MODIFY = 2,  //�޸�
// 	COLLECT_TYPE_DELETE = 3,  //ɾ��
// 	COLLECT_TYPE_MOVE = 4,     //�ƶ�
// 	COLLECT_TYPE_NEW_INTER = 5,  //��ҵ����
// };
// by hxz 20161025
enum COLLECT_TYPE
{
	COLLECT_TYPE_NEW = 1,     //����
	COLLECT_TYPE_DELETE = 2,  //ɾ��
	COLLECT_TYPE_MODIFY = 3,  //�޸�
	COLLECT_TYPE_NORMAL = 4,  //����
	COLLECT_TYPE_MOVE = 5,     //�ƶ�
	COLLECT_TYPE_UNKNOW = 6, //δ֪״̬�����������ӵ�
	COLLECT_TYPE_NEW_INTER = 7,  //��ҵ����
};

//POI���Ͷ�Ӧ��ϵ�����磺��ͨ-0����ַ-1
struct tagPOIType 
{
	int nType;
	std::string sType;
	
	//���浽mdb�е�����ֵ
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
	int type; //1:ƽ�� 2:ϡ����
	double x;
	double y;
	double xdisplay;
	double ydisplay;
	int    imeshid;
	int    idinemp;
	char   namec[256];
	char   tel[120];
	char   address[1000];
	int    grade;//poi�ȼ�
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
	int iCollectType; //�ɼ�����:������ɾ����
//	char tel[256]; 
//	char address[256];
//	int iGrade;
//	char remark[256];
	int iSelType; //ѡ�����ͣ�������רӪ�г���
	int iFloorcount; //¥����
	int iRoomnumber_pre; //�����ǰ׺
	int iRoomnumber; //�����
	int iCollectUser; 
	__int64 iCellinfo; 
	int iCollectionid;
	int iPoiType; //poi���ͣ��൱�ڵȼ�����ҵ�ֵĸ���ϸ
	__int64 iPoiTimeStamp; //poiΨһ��ʶ
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
// <POI Ψһ��ʶ , �޸ļ�¼>
typedef std::multimap<__int64,ModifyPoi*> MAP_MODIFYPOI;
#endif