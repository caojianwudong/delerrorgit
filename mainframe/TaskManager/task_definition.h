#ifndef TASK_DEFINITION_H
#define TASK_DEFINITION_H


//#define  TASK_TYPE_VIDEO  1   //��Ƶ����
#define  TASK_TYPE_ATTR  2  //��������
#define  TASK_TYPE_XY  3   //λ������



enum TASKTYPE2
{
		TASKTYPE_UNKNOW = 0,//δ֪
		TASKTYPE_VIDEO = 1000,//�����ܼ���Ƶ
		TASKTYPE_FOOT_PRORERTY = 2000,//ƽ�岽����������shape
		TASKTYPE_FOOT_PRORERTYERROR = 2001,//ƽ�����ԸĴ�����shape
		TASKTYPE_FOOT_PRORERTYNEWADD = 2002,//ƽ��������������
		TASKTYPE_FOOT_PRORERTYNEWADDDOOR = 2003,//ƽ������������ַ����
		TASKTYPE_FOOT_PRORERTYMODIFY = 2004,//ƽ�������޸�����
		TASKTYPE_FOOT_PRORERTYMODIFYDOOR = 2005,//ƽ�������޸���ַ����
		TASKTYPE_FOOT_GEOMETRY = 2100,//ƽ�岽����������
		TASKTYPE_FOOT_GEOMETRYERROR = 2101,//�������θĴ�����
		TASKTYPE_CAR_PRORERTY = 3000,//������������shape
		TASKTYPE_CAR_PRORERTYERROR = 3001,//�������ԸĴ�����
		TASKTYPE_CAR_GEOMETRY = 3100,//������������(���ӹ켣����)
		TASKTYPE_CAR_GEOMETRYERROR = 3101,//�������θĴ�����
		TASKTYPE_NET_PRORERTY = 4000,//��ʵ����������shape
		TASKTYPE_NET_PRORERTYERROR = 4001,//��ʵ�����ԸĴ�����shape
		TASKTYPE_NET_GEOMETRY = 4100,//��ʵ�⼸������
		TASKTYPE_NET_GEOMETRYERROR = 4101,//��ʵ�⼸�θĴ�����
		TASKTYPE_COMPLANIT_PRORERTY = 5000,//��Ͷ��������
		TASKTYPE_COMPLANIT_PRORERTYERROR = 5001,//��Ͷ���ԸĴ�����
		TASKTYPE_COMPLANIT_GEOMETRY = 5100,//��Ͷ�������� Ŀǰֻ�����������shape
		TASKTYPE_COMPLANIT_GEOMETRYERROR = 5101,//��Ͷ���θĴ����� shape
		TASKTYPE_IMPORT = 6000,//��������    ����Ҫ�༭�����������Զ��������
		TASKTYPE_AUTODONE = 7000,//�������񹤾��Զ�������� ����Ҫ�༭�����������Զ��������
		TASKTYPE_CROW_PRORERTY = 8000,//�ڰ���������
		TASKTYPE_CROW_PRORERTYERROR = 8001,//�ڰ����ԸĴ�����
		TASKTYPE_CROW_GEOMETRY = 8100,//�ڰ���������
		TASKTYPE_ROADCHANGE_GEOMETRY = 9100,//��·�仯��������
};

enum EDITTYPE{
	EDITTYPE_UNKNOW = 0,
		EDITTYPE_EDIT = 5, //����
		EDITTYPE_CHECK = 6, //У��
		EDITTYPE_MODIFY = 7, //�޸Ĵ���
		EDITTYPE_CONFIRM = 8, //��֤
		EDITTYPE_BATCHTOOL = 51,//�༭������
		EDITTYPE_QCTOOL = 52  // �༭�ʼ�
};

enum TASKSTATE
{
	STATE_UNKNOW = 0, //δռ��δ�ύ
		STATE_OCCUPY = 1, //ռ��
		STATE_COMMIT = 2, //�ύ
		STATE_OVER = 3,//���
		STATE_START = 4, //��ʼ��ҵ��Ŀǰ�����ڷ�����־������ʱ��ͳ��ʱ��
};


enum OPERATETYPE2
{
		OPERATE_NO2 = -1, //��
		OPERATE_UNKNOW2 = 0, //δȷ��
		OPERATE_CONFIRM2 = 1, //ȷ��
		OPERATE_NEW2 = 2, //����
		OPERATE_QUESTION2 = 3, //����
		OPERATE_DELETE2 = 4, //����ɾ�����
		OPERATE_NEW_DELETE2 = 5, //����ɾ��
		OPERATE_CONFIRM_MODIFY2 = 6, //ȷ���޸�
		OPERATE_COLLECT_CONFIRM2 = 7,//��ҵȷ��
		OPERATE_COLLECT_MODIFY2 = 8 ,//��ҵ�޸�
		OPERATE_COLLECT_MOVEPT2 = 9 ,//��ҵ��λ
};

enum LINKTYPE
{
	LINK_FIELDDATA = 0, //��ҵ����
	LINK_ATTACH = 1, //��Ƭ
	LINK_FEATURE = 2, //�������ݶ���poi��Road...��
	LINK_ITEM = 3, //Ҫ�أ��ʼ���������ߣ�
	LINK_BLOCK = 4 //���򣨹���������Զ�������
};

// ģ��mysql��MYSQL_RES�ṹ����ʱ�洢�����
//#include "mysql.h"
struct Field_DB 
{
	CString name;
	int type;
	CString table ;
};
#include <map>
#include <vector>
using namespace std;

typedef std::vector<string>		VT_RES;
typedef std::map<int,VT_RES>	MAP_RES;

namespace _TSGEO
{
	struct SGeoPoint
	{
		double x;
		double y;
		SGeoPoint(double xx,double yy)
		{
			x= xx ;
			y= yy ;
		}
		SGeoPoint()
		{
			x= 0 ;
			y= 0 ;
		}
		void operator = (const  SGeoPoint& pt)
		{
			x = pt.x;
			y = pt.y;
		}
		bool operator == (const  SGeoPoint& pt)
		{
			if(x == pt.x && y == pt.y )
				return true;
			else return false;
		}
		bool operator != (const struct SGeoPoint& pt)
		{
			if(x!=pt.x||y!=pt.y)
				return true;
			else
				return false;
		}
	};
	class SGeoRect
	{
	public:
		double x_min;
		double y_min;
		double x_max;
		double y_max;
		SGeoRect ( double x1,double y1,double x2,double y2 )
		{
			x_min = x1 ;
			x_max = x2 ;
			y_min = y1 ;
			y_max = y2 ;
		}
		SGeoRect ()
		{
			x_min = -1 ;
			x_max = -1 ;
			y_min = -1 ;
			y_max = -1 ;
		}
		void operator = (const SGeoRect& pt) 
		{
			x_min = pt.x_min;
			y_min = pt.y_min;
			x_max = pt.x_max;
			y_max = pt.y_max;
		}
		bool operator == (const SGeoRect& pt) 
		{
			if(x_min == pt.x_min && y_min == pt.y_min && x_max == pt.x_max
				&& y_max == pt.y_max)
				return true;
			else return false;
		}
		bool DpInGeoRect( double x, double y ) 
		{
			if( x>=x_min && x<=x_max&& y>=y_min && y<=y_max )
				return true;
			return false;
		}
		bool DpInGeoRect( SGeoPoint pt ) 
		{
			if( pt.x>=x_min && pt.x<=x_max&& pt.y>=y_min && pt.y<=y_max )
				return true;
			return false;
		}
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
	
}

typedef std::vector<std::string>	VT_CHAR ;

#endif