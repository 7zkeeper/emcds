/* 	author	: zhangqi
 *  filename: em_mongodb.h
 *  date	: 2015/09/14
 *  version : 0.1
 */

#ifndef EM_MONGODB_H_
#define EM_MONGODB_H_

#include <iostream>
#include <vector>
#include <map>
#include <boost/thread/mutex.hpp>
#include "mongo/client/dbclient.h"
#include <semaphore.h>


using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONElement;
using mongo::DBClientConnection;
typedef enum _mongo_ret
{
	MDB_RET_SUCCESS = 0,
	MDB_FAIL_INSTANCE = -1,
	MDB_INVALID_URI = -2,
	MDB_FAIL_CONNECT = -3,
	MDB_FAIL_SET = -4,	
	MDB_FAIL_QUERY = -5,
	MDB_ERR_PARA = -6,

	MDB_ERR_INI = -101,
	MDB_ERR_INIPARA = -102,
	MDB_EXISTCONNPOOL = -103,
	MDB_ERR_MUTEX = -104,
	MDB_ERR_SEM = -105
}mongo_ret;


typedef struct _tag_mongodb_para
{
	std::string 	ip;
	unsigned int 	port;
	unsigned int   	timeout;
	unsigned int	connectnum;
}mongodb_para;

class em_mongodb
{
public:
	em_mongodb();
  	em_mongodb(std::string& file);
	virtual ~em_mongodb();

  	int readIni(std::string file);
	int init(std::string file);
	int release();
	int init();
	virtual int connect();

	DBClientConnection* getConn();
	
	int query(std::string dbcoll,mongo::Query cond,std::string& out);
	
	int query(std::string dbcoll,mongo::Query cond,std::vector<BSONObj>& out,int count = 0);

	int insert(std::string dbcoll,mongo::BSONObj valObj);

	int setvalue(std::string dbcoll,mongo::Query cond,BSONObj valObj,bool flag);
	
	void queryincrement(std::string dbcoll,BSONElement last);	

	virtual int incrementfunc(BSONObj obj);
private:
	void releaseconn(DBClientConnection* pconn);

	std::string 	m_iniFile;
	mongodb_para	m_mongodbpara;
	pthread_mutex_t m_jobmux;
	pthread_mutex_t m_dbmux;
	sem_t			m_jobsem;
	boost::mutex 	m_iomux;
	std::map<DBClientConnection* ,bool>	m_connpool;
	mongo::client::GlobalInstance	m_instance;
};


#endif	
