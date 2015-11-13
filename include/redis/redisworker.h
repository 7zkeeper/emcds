/* author 	: zhangqi
 * filename : redisworker.h
 * time		: 2015/09/11
 */ 

#include <string>
#include <iostream>
#include <boost/asio/ip/address.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/threadpool.hpp>

#include <redisclient/redisasyncclient.h>

using namespace boost::threadpool;
static const::std::string redistitle = "push:title:setusercfg";

typedef boost::function<void(bool,const std::string&)> conn_callback;
typedef boost::function<void(const RedisValue& value)> task_callback;
typedef boost::function<void(const std::string& task,std::string& ret)> pushtask_callback;
void defTaskFunc(const RedisValue& value);

typedef struct _tag_rediswork_para
{
	std::string 	ip;
	unsigned int 	port;
	unsigned int 	worker;
	std::string		task_title;
	std::string		ret_title;
	std::string 	quitcmd;
}rediswork_para;

class redisworker
{
public:
	redisworker(boost::asio::io_service &ioService,RedisAsyncClient& redisClienti);
	virtual ~redisworker();
	//asynchronous connect to redis,maybe syncchronous is better ....
	void asynConnect();
	//callback for connect
	virtual void onConnect(bool connected,const std::string& errmsg);
	
	//callback for set value,most time it is ture
	virtual void onSet(const RedisValue& value);

	//callback for get value
	virtual void onGet(const RedisValue& value);

	//callback for lpush
	virtual void onLpush(const RedisValue& value);

	//callback for brpop
	virtual void onBrpop(const RedisValue& value);

	//callback
	virtual void onMessage(const std::vector<char>& bufs);

	//function for deal task....
	virtual void task(const RedisValue& value);

	virtual void readIni(std::string file);

	virtual void init(const pushtask_callback& task_cb);
	
	//set task title that read from redis
	void setTaskTitle(std::string title);	

	std::string getTaskTitle();

	//set task function 
	void seTaskFunc(pushtask_callback& task_cb);

	const RedisAsyncClient& getRedis() const;

	void setRetTitle(const std::string rettitle);

	//get result title that write to redis
	std::string getRetTitle();
private:
	boost::asio::io_service& m_ioService;
	RedisAsyncClient& 	m_redis;	
	rediswork_para		m_para;
	task_callback 		m_taskcb;
	pushtask_callback  	m_pushtaskcb;
	pool				m_pool;
};

