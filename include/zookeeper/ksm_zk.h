/*
 * @brief C++ interface of zookeeper client based on zookeeper c interface
 * @author zhangqi
 * time 2015-01-14
 */

#ifndef _KSM_ZK_H
#define _KSM_ZK_H

#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

#include <boost/noncopyable.hpp>
#include <zookeeper.h>
//#include <zookeeper.jute.h>
#include <zookeeper_log.h>


//watcher function 
//typedef boost::function<void(zhandle_t*,int,int,const char*,void*)> watcher_fn;

//callback function for string
//typedef boost::function<void(int,const char* ,const void*)> data_completion_t;

//callback function for void
//typedef boost::function<void(int ,const void*)> void_completion_t;

//callback function for stat
//typedef boost::function<void(int,const struct Stat*,const void*)> stat_completion_t;

//callback function for strings
//typedef boost::function<void(int,const struct String_vector*,const void*)> strings_completion_t;

//typedef boost::function<void(int,const char*,int,const struct Stat*,const void*)> data_completion_t;

//typedef void(*watcher_fn)(zhandle_t*,int,int,const char*,void*);

//typedef void(*data_completion_t)(int,const char*,int,const struct Stat*,const void*);

//typedef void(*void_completion_t)(int,const void* );

//typedef void(*stat_completion_t)(int ,const struct Stat*,const void*);

//typedef void(*string_completion_t)(int,const char* , const void*);

//typedef void(*strings_completion_t)(int,const struct String_vector*,const void*);

//typedef void(*strings_stat_completion_t)(int,const struct String_vector*,const struct Stat*,const void*);

//typedef void(*acl_completion_cb)(int,struct ACL_vector*,struct Stat*,const void*);

enum OPERATION
{
	OP_CONNECT=0,
	OP_CLOSE,
	OP_GETZKSTATUS,
	OP_CREATE,
	OP_GETDATA,
	OP_SETDATA,
	OP_GETCHILDREN,
	OP_DELETE,
	OP_ISEXIST,
	

	OP_UNKNOWN
};

struct InputPara
{
	std::string path;
	std::string value;
};

struct OutPara
{
	int ret;
	std::string strout;
};

struct ZK_Para
{
	OPERATION op;
	InputPara inpara;
	OutPara  outpara;
};

typedef struct _zk_ini
{
	std::string 	ip;
	unsigned int 	port;
	std::string 	task_title;
	std::string		result_title;
}zk_ini;

class KSM_ZK : boost::noncopyable
{
public:
	KSM_ZK();
	virtual ~KSM_ZK();

	int readIni(std::string iniFile);
	virtual void InitZK_cb();
	int Connect(const char* hostport);
	int Close();

	int init(std::string iniFile);

	bool IsConnected();
	bool IsExpired();
	zhandle_t* GetZK() const ;

	int HandleEvent(ZK_Para* para);
	
	int CreateNode(const char* path,void* data);

	int GetNodeData(const char* path);

	int SetNodeData(const char* path,void* data);

	int IsExistNode(const char* path);
	
	int GetChildren(const char* path);

	int DeleteNode(const char* path);


	const char* GetErrorString() const ;

//private:

	zk_ini	m_ini;	
	zhandle_t* 	m_zh;
	//std::string m_hostport;
	int m_connected;
	int m_expired;
	char m_errorstring[1024];

	void SetMainWatcher_cb(watcher_fn cb);
	void SetGetChildWatcher_cb(watcher_fn cb);
	void SetGetDataWatcher_cb(watcher_fn cb);	

	void SetCreateNode_cb(string_completion_t cb);
	void SetDeleteNode_cb(void_completion_t cb);
	void SetExistNode_cb(stat_completion_t cb);
	void SetGetData_cb(data_completion_t cb);
	void SetSetData_cb(stat_completion_t cb);
	void SetGetChild_cb(strings_completion_t cb);	
	
	//main watcher function 
	watcher_fn m_mainwatcher_fn;

	//callback function for create node
	string_completion_t m_createnode_fn;

	//callback function for delete node
	void_completion_t m_deletenode_fn;

	//callback function for getdata
	data_completion_t m_getdata_fn;

	//callback function for getchildren
	strings_completion_t m_getchild_fn;

	//callback function for setdata
	stat_completion_t m_setdata_fn;

	//callback function for exists
	stat_completion_t m_existsnode_fn;

	//watcher for exists node
	watcher_fn m_existsnodewatcher_fn;

	watcher_fn m_getchildwatcher_fn;

	watcher_fn m_getdatawatcher_fn;

	stat_completion_t m_existnode_fn;
	
};

struct node_info
{
	KSM_ZK* ksm_zk;
	char* name;
	char* value;
	char  path[1024];
	int value_len;
	node_info()
	{
		ksm_zk = NULL;
		name = NULL;
		value = NULL;
		path[0] = '\0';
		value_len = 0;
	}	
};
	
void df_main_watcher(zhandle_t* zh,int type,int state,const char* path,void* context);

void df_getdatawatcher(zhandle_t* zh,int type,int state,const char* path,void* context);

void df_create_completion(int rc,const char* path,const void* value);

void df_delete_completion(int rc,const void* value);

void df_getdata_completion(int rc,const char* path,int len,const struct Stat* stat,const void* value);

void df_getchild_watcher(zhandle_t* zh,int type,int state,const char* path,void* context);

void df_getchild_completion(int rc,const struct String_vector* strings,const void* data);

void df_setdata_completion(int rc,const struct Stat* stat, const void* data);

void df_existnode_completion(int rc,const struct Stat* stat,const void* data);

//auxiliary function
const char* TypeEvent2String(int type);

const char* State2String(int state);

int contains(const char* child,struct String_vector* children);

char * make_path(int num,...);

struct String_vector* make_copy(const struct String_vector* vect);

int allocate_vector(struct String_vector* v,int32_t len);

void free_vector(struct String_vector* vect);

void free_task_info(struct task_info* task);

struct String_vector* added_and_set(const struct String_vector* current,struct String_vector** previous);

struct String_vector* removed_and_set(const struct String_vector* current,struct String_vector** previous);


#endif	
