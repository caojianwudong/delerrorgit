#ifndef TASK_DEFINITION_H
#define TASK_DEFINITION_H


//#define  TASK_TYPE_VIDEO  1   //视频任务
#define  TASK_TYPE_ATTR  2  //属性任务
#define  TASK_TYPE_XY  3   //位置任务



enum TASKTYPE2
{
		TASKTYPE_UNKNOW = 0,//未知
		TASKTYPE_VIDEO = 1000,//车调密集视频
		TASKTYPE_FOOT_PRORERTY = 2000,//平板步调属性任务shape
		TASKTYPE_FOOT_PRORERTYERROR = 2001,//平板属性改错任务shape
		TASKTYPE_FOOT_PRORERTYNEWADD = 2002,//平板属性新增任务
		TASKTYPE_FOOT_PRORERTYNEWADDDOOR = 2003,//平板属性新增门址任务
		TASKTYPE_FOOT_PRORERTYMODIFY = 2004,//平板属性修改任务
		TASKTYPE_FOOT_PRORERTYMODIFYDOOR = 2005,//平板属性修改门址任务
		TASKTYPE_FOOT_GEOMETRY = 2100,//平板步调几何任务
		TASKTYPE_FOOT_GEOMETRYERROR = 2101,//步调几何改错任务
		TASKTYPE_CAR_PRORERTY = 3000,//车调属性任务shape
		TASKTYPE_CAR_PRORERTYERROR = 3001,//车调属性改错任务
		TASKTYPE_CAR_GEOMETRY = 3100,//车调几何任务(增加轨迹绘制)
		TASKTYPE_CAR_GEOMETRYERROR = 3101,//车调几何改错任务
		TASKTYPE_NET_PRORERTY = 4000,//非实测属性任务shape
		TASKTYPE_NET_PRORERTYERROR = 4001,//非实测属性改错任务shape
		TASKTYPE_NET_GEOMETRY = 4100,//非实测几何任务
		TASKTYPE_NET_GEOMETRYERROR = 4101,//非实测几何改错任务
		TASKTYPE_COMPLANIT_PRORERTY = 5000,//客投属性任务
		TASKTYPE_COMPLANIT_PRORERTYERROR = 5001,//客投属性改错任务
		TASKTYPE_COMPLANIT_GEOMETRY = 5100,//客投几何任务 目前只有这个任务有shape
		TASKTYPE_COMPLANIT_GEOMETRYERROR = 5101,//客投几何改错任务 shape
		TASKTYPE_IMPORT = 6000,//导入任务    不需要编辑器处理，工具自动完成任务
		TASKTYPE_AUTODONE = 7000,//创建任务工具自动完成任务 不需要编辑器处理，工具自动完成任务
		TASKTYPE_CROW_PRORERTY = 8000,//众包属性任务
		TASKTYPE_CROW_PRORERTYERROR = 8001,//众包属性改错任务
		TASKTYPE_CROW_GEOMETRY = 8100,//众包几何任务
		TASKTYPE_ROADCHANGE_GEOMETRY = 9100,//道路变化几何任务
};

enum EDITTYPE{
	EDITTYPE_UNKNOW = 0,
		EDITTYPE_EDIT = 5, //制作
		EDITTYPE_CHECK = 6, //校正
		EDITTYPE_MODIFY = 7, //修改错误
		EDITTYPE_CONFIRM = 8, //验证
		EDITTYPE_BATCHTOOL = 51,//编辑批处理
		EDITTYPE_QCTOOL = 52  // 编辑质检
};

enum TASKSTATE
{
	STATE_UNKNOW = 0, //未占用未提交
		STATE_OCCUPY = 1, //占用
		STATE_COMMIT = 2, //提交
		STATE_OVER = 3,//完成
		STATE_START = 4, //开始作业，目前仅用于发送日志，进行时间统计时用
};


enum OPERATETYPE2
{
		OPERATE_NO2 = -1, //无
		OPERATE_UNKNOW2 = 0, //未确认
		OPERATE_CONFIRM2 = 1, //确认
		OPERATE_NEW2 = 2, //新增
		OPERATE_QUESTION2 = 3, //疑问
		OPERATE_DELETE2 = 4, //存量删除标记
		OPERATE_NEW_DELETE2 = 5, //新增删除
		OPERATE_CONFIRM_MODIFY2 = 6, //确认修改
		OPERATE_COLLECT_CONFIRM2 = 7,//外业确认
		OPERATE_COLLECT_MODIFY2 = 8 ,//外业修改
		OPERATE_COLLECT_MOVEPT2 = 9 ,//外业移位
};

enum LINKTYPE
{
	LINK_FIELDDATA = 0, //外业资料
	LINK_ATTACH = 1, //照片
	LINK_FEATURE = 2, //关联数据对象（poi、Road...）
	LINK_ITEM = 3, //要素（质检项、批处理工具）
	LINK_BLOCK = 4 //区域（规则的网格、自定义区域）
};

// 模拟mysql的MYSQL_RES结构，临时存储结果集
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