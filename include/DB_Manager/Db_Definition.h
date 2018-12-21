#ifndef DB_DEFINITION_H
#define DB_DEFINITION_H

//////////数据库类型编号
const int DB_QCTASK_MYSQL = 1; //质检任务库
const int DB_OKERROR_MYSQL = 2;            //ok错误库
const int DB_LOG_MYSQL = 3 ;			   // 日志数据库
const int DB_POIEDIT_TASK_MYSQL = 4;       //POI编辑任务库
const int DB_FIELDDATA_MYSQL = 5;		//外业资料库
const int DB_ERRORLOG_MYSQL = 6;			//错误库
const int DB_TASK_MYSQL	= 7	;			// 任务库
const int DB_USR_MYSQL = 8;				// 用户管理库
const int DB_POIEDIT_PROJECT_MYSQL = 9;
const int DB_QCTASK_PGSQL = 10; //质检任务库
const int DB_OKERROR_PGSQL = 11;            //ok错误库
const int DB_LOG_PGSQL =12;			   // 日志数据库
const int DB_POIEDIT_TASK_PGSQL = 13;       //POI编辑任务库
const int DB_FIELDDATA_PGSQL = 14;		//外业资料库
const int DB_ERRORLOG_PGSQL =15;			//错误库
const int DB_TASK_PGSQL = 16;			// 任务库
const int DB_USR_PGSQL = 17;				// 用户管理库
const int DB_POIEDIT_PROJECT_PGSQL =18;
const int DB_EXTEND1_MYSQL =19;//扩展1
const int DB_EXTEND2_MYSQL =20;//扩展2
const int DB_EXTEND1_PGSQL =21;//扩展1
const int DB_EXTEND2_PGSQL =22;//扩展2


////////////////数据库类别
const int DB_TYPE_MYSQL = 1;//mysql数据库
const int DB_TYPE_PGSQL = 2;//postgres数据库



///////////////////////////postgres数据库字段类型/////////////////

#endif