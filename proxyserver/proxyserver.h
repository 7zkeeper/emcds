/* author	: 	zhangqi
 * filename :   proxyserver.h
 * version	:   0.1
 */

#ifndef _PROXY_SERVER_H_
#define _PROXY_SERVER_H_

#include "protobuf/codec.h"
#include "protobuf/dispatcher.h"
#include "protobuf/dataserver.pb.h"
//#include "redis/redisworker.h"
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <boost/bind.hpp>
//#include <boost/asio.hpp>
#include <map>
#include <vector>
#include "Hiredis.h"

using namespace muduo;
using namespace muduo::net;

typedef boost::shared_ptr<dataserver::SetUsrStkCfg> SetusrstkPtr;

typedef boost::shared_ptr<dataserver::GetUsrStkCfg> GetusrstkPtr;

typedef boost::shared_ptr<dataserver::GetIncrStkCfg> IncrstkcfgPtr;

typedef std::map<std::string,TcpConnectionPtr> ConnectionMap;

typedef std::map<std::string,std::string>	TaskConnMap;

const int maxConns = 30;

const size_t maxPacketLen = 512;

const size_t headerLen = 3;

class ProxyServer : boost::noncopyable
{
public:
	ProxyServer(EventLoop* loop,const InetAddress& listenAddr,const InetAddress& redisAddr,std::string servername);	

	~ProxyServer();	

	void init(std::string iniFile);

	void start();

	void setLoginfo(const char* logprop);

	void queue_task(const std::string& task,std::string& result);

private:
	void onClientConnection(const TcpConnectionPtr& conn);

	void onClientMessage(const TcpConnectionPtr& conn,Buffer* buf,Timestamp);

	void onRedisConnection(hiredis::Hiredis* c,int status);

	void onRedisDisconnection(hiredis::Hiredis* c ,int status);

	void onRedisGetResult(hiredis::Hiredis* c ,redisReply* reply);
	
	void onPushTask(hiredis::Hiredis* c,redisReply* reply);

	void onRemoveConnection(const TcpConnectionPtr& conn);

	void onUnknownMessage(const TcpConnectionPtr& conn,const MessagePtr& message,Timestamp); 

	void onSetusrstk(const TcpConnectionPtr& conn,const SetusrstkPtr& message,Timestamp); 

	void onGetusrstk(const TcpConnectionPtr& conn,const GetusrstkPtr& message,Timestamp);

	void onGetIncrusrstk(const TcpConnectionPtr& conn,const IncrstkcfgPtr& message,Timestamp);

	void sendMsgQueue(const MessagePtr& message,std::string title);

	void connsClear();

	void sendRedisBuffer(int id , Buffer* buf);

	void sendRedisString(int id ,const string& msg);

	void sendRedisPacket(int id ,Buffer* buf);
	
	void dealRedisIncrstkcfg(std::string result);
	
	TcpServer m_server;

	ProtobufDispatcher m_dispatcher;

	ProtobufCodec m_codec;

	//redisworker m_redis;	

	hiredis::Hiredis m_redis;

//	boost::asio::io_service& m_ioService;

	std::map<std::string ,std::string > m_taskconns;

	ConnectionMap m_conns;
};

#endif
