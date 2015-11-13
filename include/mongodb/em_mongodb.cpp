/* author 	: zhangqi
 * filename : em_mongodb.cpp
 * version  : 0.1
 */

#include "em_mongodb.h"
#include "inifile/inifile.h"

using namespace mongo;

const unsigned int DEF_MONGOPORT = 27017;
const unsigned int DEF_CONNECT = 10;
const unsigned int DEF_TIMEOUT = 0;
 
em_mongodb::em_mongodb()
{
	std::cout << "em_mongodb constructor." << std::endl;
}

em_mongodb::em_mongodb(std::string& iniFile)
{
	m_iniFile = iniFile;
	init(iniFile);
}

em_mongodb::~em_mongodb()
{
}

int em_mongodb::readIni(std::string file)
{
	int ret = 0;
	std::string port;
	std::string conn_num;
	std::string timeout;
	inifile::IniFile ini;
	ret = ini.open(file.c_str());
	
	if(ret != -1)
	{
		ini.getValue("MONGODB","mongo_ip",m_mongodbpara.ip);
		ini.getValue("MONGODB","mongo_port",port);
		ini.getValue("MONGODB","connect",conn_num);
		ini.getValue("MONGODB","timeout",timeout);
	
		std::cout<<"ip: "<<m_mongodbpara.ip<<",port: "<<port<<", connect: "<< conn_num <<", timeout: "<<timeout<<std::endl;
		if(port.size()>0)
			m_mongodbpara.port = atoi(port.c_str());
		else
			m_mongodbpara.port = DEF_MONGOPORT;
		if(conn_num.size()>0)
			m_mongodbpara.connectnum = atoi(conn_num.c_str());
		else
			m_mongodbpara.connectnum = DEF_CONNECT;
		if(timeout.size()>0)
			m_mongodbpara.timeout = atoi(timeout.c_str());
		else
			m_mongodbpara.timeout = DEF_TIMEOUT;
	}
	return ret;
}

int em_mongodb::init(std::string file)
{
	int ret = -1;
	if(!m_instance.initialized())
	{
		std::cout<<"init mongoclient error"<<std::endl;
		return MDB_FAIL_INSTANCE;
	}
	ret = readIni(file);
	m_iniFile = file;
	if(ret == -1)
		return MDB_ERR_INI;

	if(m_connpool.size()>0)
		return MDB_EXISTCONNPOOL;
	
	boost::mutex::scoped_lock lock(m_iomux);
	pthread_mutex_init(&m_jobmux,NULL);
	if((sem_init(&m_jobsem,0,0))<0)
		return MDB_ERR_SEM;

	pthread_mutex_lock(&m_jobmux);
	for(unsigned int i = 0;i<m_mongodbpara.connectnum;++i)
	{
		DBClientConnection* pconn = new DBClientConnection(true,0,m_mongodbpara.timeout);
		if(pconn)
		{
			m_connpool[pconn] = false;
			std::cout<<"NO."<<i<<": db connection create."<<std::endl;
		}
	}
	pthread_mutex_unlock(&m_jobmux);
//	connect();
	return MDB_RET_SUCCESS;
}

int em_mongodb::init()
{
	return 1;
}
int em_mongodb::release()
{
	int ret = 0;
	pthread_mutex_lock(&m_jobmux);
	std::map<DBClientConnection*,bool>::iterator it = m_connpool.begin();
	while(it != m_connpool.end())
	{
		delete it->first;
		it++;
	}
	pthread_mutex_unlock(&m_jobmux);
	return ret;
}

int em_mongodb::connect()
{
	int ret = 0;

	boost::mutex::scoped_lock lock(m_iomux);
	pthread_mutex_lock(&m_jobmux);
	
	std::map<DBClientConnection*,bool>::iterator it = m_connpool.begin();
	while(it != m_connpool.end())
	{
		std::string errmsg = "";
		HostAndPort host(m_mongodbpara.ip,m_mongodbpara.port);
		if(!(it->first->connect(host,errmsg)))		
		{	
			std::cerr<<"connect ip: " <<m_mongodbpara.ip<<std::endl;
			std::cerr<<"port: "<<m_mongodbpara.port<<std::endl;
			it->second = true;
		}
		else
		{
			std::cout<<"NO."<<ret<<": connection ok"<<std::endl;
		}
		sem_post(&m_jobsem);
		it++;
		ret++;
	}
	pthread_mutex_unlock(&m_jobmux);
	ret = MDB_RET_SUCCESS;
	return ret;
}


DBClientConnection* em_mongodb::getConn()
{
	sem_wait(&m_jobsem);
	DBClientConnection* pconn = NULL;
	boost::mutex::scoped_lock lock(m_iomux);
	std::map<DBClientConnection*,bool>::iterator it = m_connpool.begin();
	while(it != m_connpool.end())
	{
		if(it->second == false)
		{
			it->second = true;
			pconn = it->first;
			break;
		}
		it++;
	}
	return pconn;
}

int em_mongodb::query(std::string dbcoll,mongo::Query cond,std::string& out)
{
	int ret = MDB_FAIL_QUERY;
	DBClientConnection* pconn = getConn();
	if(!pconn)
		return ret;

	BSONObj obj = pconn->findOne(dbcoll,cond);
	out =  obj.toString();
	boost::mutex::scoped_lock lock(m_iomux);
	m_connpool[pconn] = false;
	sem_post(&m_jobsem);
	ret = MDB_RET_SUCCESS;
	return ret;	
}
	
int em_mongodb::query(std::string dbcoll,mongo::Query cond,std::vector<BSONObj>& out,int count)
{
	int ret = 0;
	DBClientConnection* pconn = getConn();
	if(!pconn)
		return ret;

	auto_ptr<DBClientCursor> cursor = pconn->query(dbcoll,cond,count);
//	std::cout<<"result for query,return BSONObjs"<<std::endl;
	while(cursor->more())
	{
		out.push_back(cursor->next());
		ret++;
	}
	boost::mutex::scoped_lock lock(m_iomux);
	m_connpool[pconn] = false;
	sem_post(&m_jobsem);
	return ret;	
}


int em_mongodb::setvalue(std::string dbcoll,mongo::Query cond,BSONObj valObj,bool flag)	
{
	int ret = MDB_FAIL_SET;
	DBClientConnection* pconn = getConn();
	if(!pconn)
		return ret;

	pconn->update(dbcoll,cond,valObj,flag);
	std::string errmsg = pconn->getLastError();
	if(errmsg.empty())
		ret = MDB_RET_SUCCESS;
	boost::mutex::scoped_lock lock(m_iomux);
	m_connpool[pconn] = false;
	sem_post(&m_jobsem);
	return ret;
}			
 	
void em_mongodb::queryincrement(std::string dbcoll,BSONElement last)
{
//	int ret = MDB_FAIL_QUERY;
	DBClientConnection* pconn = getConn();
	if(!pconn)
		return ;
	mongo::Query cond = mongo::Query().sort("$natural");
//	BSONElement last;// = minKey.firstElement();
	while(1)
	{
		std::auto_ptr<mongo::DBClientCursor> cursor = 
			pconn->query(dbcoll,cond,0,0,0,QueryOption_CursorTailable|QueryOption_AwaitData);
		while(1)
		{
			if(!cursor->more())
			{
				if(cursor->isDead())
				{
					break;
				}
				continue;
			}
			BSONObj obj = cursor->next();
			last = obj["_id"];
			//do something here...
			incrementfunc(obj);
		}
//		cond = mongo::Query("_id"<<BSON("$gt"<<last)).sort("$natural");			
	}
	boost::mutex::scoped_lock(m_iomux);
	m_connpool[pconn] = false;
	sem_post(&m_jobsem);
}	

int em_mongodb::incrementfunc(BSONObj obj)
{
	int ret = -1;
	std::cout<<"obj: "<<obj.toString()<<std::endl;
	return ret;
}

void em_mongodb::releaseconn(DBClientConnection* pconn)
{
	boost::mutex::scoped_lock(m_iomux);
	m_connpool[pconn] = false;
	sem_post(&m_jobsem);
}	
