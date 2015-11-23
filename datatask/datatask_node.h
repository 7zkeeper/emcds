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

class datatask_node
{
public:
	datatask_node(boost::asio::io_service& ioService,RedisAsyncClient& rd,std::string iniFile);
	
	virtual ~datatask_node();

	virtual int readIni(std::string iniFile);
	
	virtual int init(std::string iniFile);

	virtual int run();

	virtual void parsepara(std::string redistask,std::string& result);

	virtual int writeResult(std::string value);
	
	virtual void task_work(const std::string& task,std::string& result);

	virtual void deal_task(task_type type,keyvalue kv,std::string& result);
	
	virtual void deal_task(task_type type,std::string value,std::string& result);

private:
	void updateUserStockCfg(std::string dbcoll,std::string uid,condition value);

	void dealSetUserStk(std::string redistask,std::string& result);

	void dealSetUserStk(keyvalue ret,std::string& result);
	
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
