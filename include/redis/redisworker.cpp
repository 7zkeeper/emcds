/* author 	: zhangqi
 * filename : redisworker.cpp
 * time		: 2015/09/11
 */ 

#include "redisworker.h"
#include "../inifile/inifile.h"

typedef boost::function<void(bool,const std::string&)> conn_callback;

redisworker::redisworker(boost::asio::io_service& ioService,RedisAsyncClient& redisClient)
		: m_ioService(ioService),m_redis(redisClient)
{
}

redisworker::~redisworker()
{
}

void redisworker::readIni(std::string file)
{
	std::string port,worker;
	inifile::IniFile ini;
	ini.open(file.c_str());
	
	ini.getValue("REDIS","redis_ip",m_para.ip);
	ini.getValue("REDIS","redis_port",port);
	ini.getValue("REDIS","get_title",m_para.task_title);
	ini.getValue("REDIS","push_title",m_para.ret_title);
	ini.getValue("REDIS","redis_worker",worker);
	ini.getValue("REDIS","quit_cmd",m_para.quitcmd);
	
	m_para.port = atoi(port.c_str());
	m_para.worker = atoi(worker.c_str());
/*
	m_para.ip = "127.0.0.1";
	m_para.port = 22121;
	m_para.title = "push:title:setusercfg";
	m_para.quitcmd = "wanttoquit";
*/
}

//set tasktitle,but you'd better persistence the result to ini in future
void redisworker::setTaskTitle(std::string title)
{
	m_para.task_title = title;
}

const RedisAsyncClient& redisworker::getRedis() const
{
	return m_redis;
}

void redisworker::init(const pushtask_callback& task_cb)
{
	m_pool.size_controller().resize(m_para.worker);
	m_pushtaskcb = task_cb;
	asynConnect();
}

void redisworker::asynConnect()
{
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(m_para.ip),m_para.port);
	m_redis.asyncConnect(ep,boost::bind(&redisworker::onConnect,this,_1,_2));
}

void redisworker::onConnect(bool connected,const std::string& errmsg)
{
	if(!connected)
	{
		std::cerr<<"Cannot connect to redis: "<<errmsg<<std::endl;
	}
	else
	{
		std::cout<<"Connected to redis."<<std::endl;
		//m_redis.command("BRPOP",m_para.task_title,"push:test2",0,boost::bind(&redisworker::onBrpop,this,_1));
		m_redis.command("BRPOP",m_para.task_title,0,boost::bind(&redisworker::onBrpop,this,_1));
	}
}	

void redisworker::onSet(const RedisValue& value)
{
	if(value.toString() == "OK")
	{
		std::cout<<"SET: success"<<std::endl;
	}
	else
	{
		std::cerr<<"SET: "<<value.toString()<<std::endl;
	}
}

void redisworker::onGet(const RedisValue& value)
{
	std::cout<<value.toString()<<std::endl;
}

//need argument for the cb
void redisworker::onLpush(const RedisValue& value)
{
	if(value.toInt()>0)
	{
	}
	else
	{
	}
}

void redisworker::onBrpop(const RedisValue& value)
{
/*	if(value.isOk())
	{
		std::cout<<value.toArray()[0].toString()<<std::endl;
		std::cout<<value.toArray()[1].toString()<<std::endl;
		m_redis.command("BRPOP",m_para.title,"push:test2",0,boost::bind(&redisworker::onBrpop,this,_1));
		if(value.toArray()[1].toString()  == m_para.quitcmd)
			m_ioService.stop();
	}
	else
	{
		std::cerr<<"BRPOP: error"<<value.toString()<<std::endl;
	}
*/
	m_pool.schedule(boost::bind(&redisworker::task,this,value));
}


void redisworker::onMessage(const std::vector<char>& bufs)
{
	std::string msg(bufs.begin(),bufs.end());
	std::cerr<<"Message: "<<msg<<std::endl;
	
	if(msg == m_para.quitcmd)
		m_ioService.stop();
}	

//the application is for lpush && brpop ,so value is array,if you want to realize new function,
//you should overloac the function.....
void redisworker::task(const RedisValue& value)
{
	if(value.isOk())
	{
		std::cout<<value.toArray()[0].toString()<<std::endl;
		std::cout<<value.toArray()[1].toString()<<std::endl;
		std::string result;
		m_pushtaskcb(value.toArray()[1].toString(),result);
		std::cout << "redisworker::task " << m_para.task_title << std::endl;
		m_redis.command("BRPOP",m_para.task_title,0,boost::bind(&redisworker::onBrpop,this,_1));
		if(value.toArray()[1].toString()  == m_para.quitcmd)
			m_ioService.stop();
	}
	else
	{
		std::cerr<<"BRPOP: error"<<value.toString()<<std::endl;
	}
}

void redisworker::setRetTitle(const std::string rettitle)
{
	m_para.ret_title = rettitle;
}

std::string redisworker::getTaskTitle()
{
	return m_para.task_title;
}

std::string redisworker::getRetTitle()
{
	return m_para.ret_title;
}

void defTaskFunc(const RedisValue& value)
{
	std::cout<<value.toString()<<std::endl;
}

