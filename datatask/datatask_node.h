/* author	: zhangqi
 * filename	: datatask_node.h
 * version	: 0.1
 */

#ifndef _DATATASK_NODE_H_
#define _DATATASK_NODE_H_

#include <boost/asio.hpp>

#include "redis/redisworker.h"
#include "zookeeper/ksm_zk.h"
#include "mongodb/em_mongodb.h"
#include "utility/utility.h"

typedef struct _data_task_
{
	std::string key;
	std::string task;
}data_task;

typedef struct _condition_
{
	std::vector<std::string> keyary;
	std::vector<std::string> valueary;
}condition;

typedef enum _task_type_
{
	SET_USER_LOAD = 1000,
	GET_USER_LOAD,

	SET_USER_STOCK = 2000,
	GET_USER_STOCK,

	GET_INCR_USERSTK = 3000,

	UNKNOWN_TASK = 1000000

}task_type;

class datatask_node
{
public:
	datatask_node(boost::asio::io_service& ioService,RedisAsyncClient& rd,std::string iniFile);
//	datatask_node();	
	virtual ~datatask_node();

	virtual int readIni(std::string iniFile);
	virtual int init(std::string iniFile);
	virtual int run();
	virtual void parsepara(std::string redistask,std::string& result);
	virtual int writeResult(std::string value);
	
	virtual void task_work(const std::string& task,std::string& result);
	virtual void deal_task(task_type type,keyvalue kv,std::string& result);
private:
	void updateUserStockCfg(std::string dbcoll,std::string uid,condition value);

	int setArrayInfo(std::string dbcoll,std::string kv,std::string mkey,std::string arrkey,condition value);
	void setUserLoad(keyvalue kv,std::string& result);
	void getUserLoad(keyvalue kv,std::string& result);
	void setUserStock(keyvalue kv,std::string& result);
	void getUserStock(keyvalue kv,std::string& result);
	void getIncrUserStock(keyvalue kv,std::string&result);
	em_mongodb  m_mongodb;
	boost::asio::io_service& m_ioService;
	redisworker m_redis;
	KSM_ZK		m_zookeeper;
};	

#endif
