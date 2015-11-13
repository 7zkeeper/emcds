/* author	: 	zhangqi
 * filename :   proxyserver.cpp
 * version	:   0.1
 */

#include "proxyserver.h"
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <muduo/base/Logging.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define PROXYSERVER 	"proxyserver"
#define LOGFILE			"serverlog.properties"
using namespace log4cxx;
using namespace log4cxx::helpers;
using namespace boost::property_tree;

std::string redisReplyToString(const redisReply* reply);

ProxyServer::ProxyServer(EventLoop* loop,const InetAddress& listenAddr,	const InetAddress& redisAddr,std::string servername)
		: m_server(loop,listenAddr,servername.c_str()),
		  m_dispatcher(boost::bind(&ProxyServer::onUnknownMessage,this,_1,_2,_3)),
		  m_codec(boost::bind(&ProtobufDispatcher::onProtobufMessage,&m_dispatcher,_1,_2,_3)),
		  m_redis(loop,redisAddr)
{
	m_dispatcher.registerMessageCallback<dataserver::GetIncrStkCfg>(
		boost::bind(&ProxyServer::onGetIncrusrstk,this,_1,_2,_3));
	m_server.setConnectionCallback(
		boost::bind(&ProxyServer::onClientConnection,this,_1));
	m_server.setMessageCallback(
		boost::bind(&ProtobufCodec::onMessage,&m_codec,_1,_2,_3));
	m_redis.setConnectCallback(
		boost::bind(&ProxyServer::onRedisConnection,this,_1,_2));
	m_redis.setDisconnectCallback(
		boost::bind(&ProxyServer::onRedisDisconnection,this,_1,_2));
}
	
void ProxyServer::start()
{
	m_redis.connect();
	m_server.start();
}

void ProxyServer::onClientConnection(const TcpConnectionPtr& conn)
{
	LOG_TRACE << "Client " << conn->peerAddress().toIpPort() << " -> "
			<< conn->localAddress().toIpPort() << " is " 
			<< (conn->connected() ? "online" : "offline");
	
	std::string connname(conn->name().c_str());
	if(conn->connected())
	{
		m_conns[connname] = conn;
	//	m_redis.command(boost::bind(&ProxyServer::onRedisGetResult,this,_1,_2),"BRPOP test 0");
	}
	else
	{
		LOG_INFO << "connname offline " << connname;
		m_conns.erase(connname);
	}	
			
}
	
void ProxyServer::onUnknownMessage(const TcpConnectionPtr& conn,const MessagePtr& message,Timestamp)
{
	conn->shutdown();
	m_conns.erase(std::string(conn->name().c_str()));
}


void ProxyServer::sendRedisString(int id ,const string& msg)
{
	assert(msg.size() <= maxPacketLen);					
	Buffer buf;
	buf.append(msg);
	sendRedisPacket(id,&buf);
}

void ProxyServer::sendRedisPacket(int id ,Buffer* buf)
{
	size_t len = buf->readableBytes();
	LOG_DEBUG << "sendRedisPacket " << len;
	assert(len <= maxPacketLen);
	uint8_t header[headerLen] = {
		static_cast<uint8_t>(len),
		static_cast<uint8_t>(id & 0xFF),
		static_cast<uint8_t>((id & 0xFF00) >> 8)
	};
	buf->prepend(header,headerLen);
}
	
void ProxyServer::onGetIncrusrstk(const TcpConnectionPtr& conn,const IncrstkcfgPtr& message,Timestamp)
{
	LOG_INFO << "onGetIncrusrstk protobuf received...";
	std::string taskid = message->taskid();
	int64_t id = message->incrementid();
	std::string ret = "";
	LOG_INFO << "taskid " <<taskid << " id " << id;
	m_redis.command(boost::bind(&ProxyServer::onPushTask,this,_1,_2),"lpush test %s",taskid.c_str());
	m_taskconns[taskid] = std::string(conn->name().c_str());
}

void ProxyServer::onClientMessage(const TcpConnectionPtr& conn,Buffer* buf,Timestamp)
{
	if(!conn->getContext().empty())
	{
		int id = boost::any_cast<int>(conn->getContext());
		sendRedisBuffer(id,buf);
	}
	else
	{
		buf->retrieveAll();
	}
}

void ProxyServer::sendRedisBuffer(int id , Buffer* buf)
{
	while(buf->readableBytes() > maxPacketLen)
	{
		Buffer packet;
		packet.append(buf->peek(),maxPacketLen);
		buf->retrieve(maxPacketLen);
		sendRedisPacket(id,&packet);
	}
	if(buf->readableBytes() > 0)
	{
		sendRedisPacket(id,buf);
	}
}

void ProxyServer::onRedisConnection(hiredis::Hiredis* c,int status)
{
	if(status != REDIS_OK)
	{
		LOG_ERROR << "redis connectcallback error:" << c->errstr();
	}
	else
	{
		LOG_INFO << "redis connected..";
//		for(int id = 1; id < maxConns; ++id)
		{
			//m_connIds.push(id);
		}
	}
}
	
void ProxyServer::onRedisDisconnection(hiredis::Hiredis* c, int status)
{
	if(status != REDIS_OK)
	{
		LOG_ERROR << "redis disconnectcallback Error:" << c->errstr();
	}
	else
	{
		LOG_INFO << "redis disconnected...";
	}	
}

void ProxyServer::onRedisGetResult(hiredis::Hiredis* c,redisReply* reply)
{
	LOG_INFO << " brpop " << std::string(reply->element[0]->str,reply->element[0]->len)
				<< " " << std::string(reply->element[1]->str,reply->element[1]->len);	

	std::string ret;
	std::string task(reply->element[1]->str,reply->element[1]->len);
	dataserver::SetUsrStkCfg stkcfg;
	stkcfg.set_taskid("1000001");
	stkcfg.set_usrid("zhangqi");
	dataserver::UserStockCfg* pUserscfg = stkcfg.add_stkcfg();
	pUserscfg->set_stockcode("600123");
	pUserscfg->set_bulletin(1);
	pUserscfg->set_max_price(12.11);
	pUserscfg->set_run(1);
	pUserscfg->set_incrementid(12345);

	dataserver::UserStockCfg* pUserscfg1 = stkcfg.add_stkcfg();
	pUserscfg1->set_stockcode("600223");
	pUserscfg1->set_bulletin(1);
	pUserscfg1->set_max_price(42.85);
	pUserscfg1->set_run(1);
	pUserscfg1->set_incrementid(9812);

	google::protobuf::Message* protomsg = NULL;
	protomsg = &stkcfg;
	std::string connname = m_taskconns[task];
	LOG_INFO << "connname " << connname << ", task "<<task;
	for(ConnectionMap::iterator it(m_conns.begin()); it != m_conns.end(); ++it)
	{
		TcpConnectionPtr conn = it->second;
  		if(connname == std::string(conn->name().c_str()))
  		{			
			m_codec.send(conn,*protomsg);
    		break;
  		}
	}
//	m_redis.command(boost::bind(&ProxyServer::onRedisGetResult,this,_1,_2),"BRPOP test 0");
}

void ProxyServer::onPushTask(hiredis::Hiredis* c, redisReply* reply/*,std::string* ret*/)
{
	LOG_INFO << " set " << redisReplyToString(reply);
	m_redis.command(boost::bind(&ProxyServer::onRedisGetResult,this,_1,_2),"BRPOP test 0");
}

ProxyServer::~ProxyServer()
{
	connsClear();	
}



void ProxyServer::sendMsgQueue(const MessagePtr& message,std::string title)
{
	std::string msgname = message->GetTypeName();
	std::string titlename = "push:" + msgname;
	std::string value = message->DebugString();	
	LOG4CXX_INFO(log4cxx::Logger::getLogger(PROXYSERVER),value);
}

void ProxyServer::setLoginfo(const char* logprop)
{
	PropertyConfigurator::configure(logprop);
}

void ProxyServer::onSetusrstk(const TcpConnectionPtr& conn,	const SetusrstkPtr& message,Timestamp)
{
	LOG4CXX_INFO(log4cxx::Logger::getLogger(PROXYSERVER),"recv SetUsrStk!");
} 

void ProxyServer::queue_task(const std::string& task,std::string& result)
{

	dataserver::SetUsrStkCfg stkcfg;
	stkcfg.set_taskid("1000001");
   	stkcfg.set_usrid("zhangqi");
    dataserver::UserStockCfg* pUserscfg = stkcfg.add_stkcfg();
    pUserscfg->set_stockcode("600123");
    pUserscfg->set_bulletin(1);
    pUserscfg->set_max_price(12.11);
    pUserscfg->set_run(1);
    pUserscfg->set_incrementid(12345);

    dataserver::UserStockCfg* pUserscfg1 = stkcfg.add_stkcfg();
    pUserscfg1->set_stockcode("600223");
    pUserscfg1->set_bulletin(1);
    pUserscfg1->set_max_price(42.85);
    pUserscfg1->set_run(1);
    pUserscfg1->set_incrementid(9812);

	google::protobuf::Message* protomsg = NULL;
	protomsg = &stkcfg;
	std::string connname = m_taskconns[task];
	for(ConnectionMap::iterator it(m_conns.begin()); it != m_conns.end(); ++it)
	{
		TcpConnectionPtr conn = it->second;
		if(connname == std::string(conn->name().c_str()))
		{
			m_codec.send(conn,*protomsg);
			break;
		}
	}
}


void ProxyServer::connsClear()
{
	m_conns.clear();
}

void ProxyServer::onRemoveConnection(const TcpConnectionPtr& conn)
{
	m_conns.erase(std::string(conn->name().c_str()));
}

void ProxyServer::dealRedisIncrstkcfg(std::string result)
{
	std::stringstream stream;
    stream<<result;
    std::string type,user,stk,bulletin,maxpirce,incr;
    try
    {       
	    ptree pt,p1,p2,p3,p4;
	    read_json<ptree>(stream,pt);
	    type = pt.get<std::string>("tasktype");
	    std::cout<<"tasktype: "<<type<<std::endl;
	    p1 = pt.get_child("user");
	    for(ptree::iterator it = p1.begin(); it != p1.end(); it++)
	    {
			p2 = it->second;
			user = p2.get<std::string>("UID");
			std::cout<<"UID: "<<user<<std::endl;
			p3 = p2.get_child("stocks");
			for(ptree::iterator iter = p3.begin(); iter != p3.end(); iter++)
			{
				p4 = iter->second;
				stk = p4.get<std::string>("stockcode");
				bulletin = p4.get<std::string>("bulletin1");
				incr = p4.get<std::string>("incrementid");
				std::cout<<stk<<","<<bulletin<<","<<incr<<std::endl;
			 }
		}
	}
	catch(ptree_error& e)
	{
		std::cout << "error for ptree parse.." << std::endl;
	}

}

std::string toString(long long value)
{
	char buf[32] = {0};
	snprintf(buf,sizeof(buf),"%lld",value);
	return buf;
}

std::string redisReplyToString(const redisReply* reply)
{
  	static const char* const types[] = { "",
      "REDIS_REPLY_STRING", "REDIS_REPLY_ARRAY",
      "REDIS_REPLY_INTEGER", "REDIS_REPLY_NIL",
      "REDIS_REPLY_STATUS", "REDIS_REPLY_ERROR" };
  	std::string str;
  	if (!reply) return str;

  	str += types[reply->type] + std::string("(") + toString(reply->type) + ") ";

  	str += "{ ";
  	if (reply->type == REDIS_REPLY_STRING ||
    	  reply->type == REDIS_REPLY_STATUS ||
    	  reply->type == REDIS_REPLY_ERROR)
  	{
    	str += '"' + std::string(reply->str, reply->len) + '"';
  	}
  	else if (reply->type == REDIS_REPLY_INTEGER)
  	{
   	 	str += toString(reply->integer);
  	}
  	else if (reply->type == REDIS_REPLY_ARRAY)
  	{
    	str += toString(reply->elements) + " ";
    	for (size_t i = 0; i < reply->elements; i++)
    	{
      		str += " " + redisReplyToString(reply->element[i]);
    	}
  	}
  	str += " }";

  	return str;
}
