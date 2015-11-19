/* author	: zhangqi
 * filename	: datatask_node.cpp
 * version	: 0.1
 */

#include "inifile/inifile.h"
#include "datatask_node.h"
#include "utility/mongodb_flag.h"
#include "mongodb/BSONCreator.h"
#include <mongo/client/dbclient.h>
#include <mongo/bson/bson.h>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace mongo;
using namespace boost::property_tree;

datatask_node::datatask_node(boost::asio::io_service& ioService,
				RedisAsyncClient& rd,std::string iniFile)
	: m_ioService(ioService),m_redis(ioService,rd)
{
	init(iniFile);
}

datatask_node::~datatask_node()
{
}

int datatask_node::readIni(std::string iniFile)
{
	int ret = 0;
	m_redis.readIni(iniFile);
	m_zookeeper.readIni(iniFile);
	return ret;
}

int datatask_node::init(std::string iniFile)
{
	int ret = 0;
	readIni(iniFile);
	m_mongodb.init(iniFile);
	m_redis.init(boost::bind(&datatask_node::task_work,this,_1,_2));
	m_zookeeper.init(iniFile);
 	m_mongodb.connect();
	return ret;
}

int datatask_node::run()
{
	return 1;
}


int datatask_node::writeResult(std::string value)
{
	std::cout<< "rettitle: "<<m_redis.getRetTitle()<<", val: "<<value <<std::endl;
	m_redis.getRedis().command("LPUSH",m_redis.getRetTitle(),value,boost::bind(&redisworker::onLpush,&m_redis,_1));
	return 1;
}


void datatask_node::parsepara(std::string redistask,std::string& result)
{
	std::string dbcoll,value;
	mongo::Query cond;
	BSONObj valobj;
	
	keyvalue ret;
	splits(redistask,ret,";");
	std::string tasktype = "";
	display(ret);
	getKeyValue(ret,TASK_TYPE,tasktype);
	std::cout<<"parsepara: "<< redistask << std::endl;
	if(tasktype.empty())	
		return ;
	int type = boost::lexical_cast<int>(tasktype);// atoi(tasktype.c_str());
	std::cout << "typed: "<<type<<std::endl;
	result.clear();
	deal_task((task_type)type,ret,result);
}

void datatask_node::dealSetUserStk(std::string redistask,std::string& result)
{
	std::cout << "get setuserstk quest." << std::endl;
	std::cout << redistask << std::endl;

	bool exist = false;
	keyvalue ret;
	splits(redistask,ret,";");
	std::string user,stockcode;
	getKeyValue(ret,"userid",user);
	BSONObj bob = createSetUserStockCfg(user,ret,exist);
	char dbcoll[255] = {0};
	sprintf(dbcoll,"%s.%s",DB_NAME,STKCFG_SETS);

	Query query = MONGO_QUERY(USERSTOCK_UID<<user<<USERSTOCK_STOCKS<<BSON("$elemMatch"<<BSON(USERSTOCK_STOCKCODE<<stockcode)));
	std::string mongo_ret ;
	m_mongodb.query(dbcoll,query,mongo_ret);
	if(mongo_ret.size() > 10)
		exist = true;
	m_mongodb.setvalue(dbcoll,query,bob,exist);
/*
	std::stringstream stream;
	stream << redistask;

	try
	{
		ptree pt,p1,p2;
		std::string stk,bulletin,maxprice,minprice,run,range,incr;
		read_json<ptree>(stream,pt);
		std::string userid = pt.get<std::string>("usrid");
		p1 = pt.get_child("stkcfg");

		bool exist = false;
		mongo::BSONObjBuilder c_bob,stock_bob;
		char k[1024] = {0};
		if(!exist)
			sprintf(k,"%s",USERSTOCK_STOCKCODE);
		else
			sprintf(k,"%s.$.%s",USERSTOCK_STOCKS,USERSTOCK_STOCKCODE);

		c_bob.append(USERSTOCK_UID,userid);

		for(ptree::iterator it = p1.begin(); it != p1.end(); it++)
		{
			p2 = it->second;
			stk = p2.get<std::string>(USERSTOCK_STOCKCODE);
			bulletin = p2.get(USERSTOCK_BULLETIN,"1");
			incr = p2.get<std::string>(USERSTOCK_INCR);
			maxprice = p2.get(USERSTOCK_MAXPRICE,"-1.0");
			minprice = p2.get(USERSTOCK_MINPRICE,"-1.0");
			run = p2.get(USERSTOCK_RUN,"1");
			range = p2.get(USERSTOCK_RANGE,"-10000");
			
			double maxp,minp,drange;
			maxp = boost::lexical_cast<double>(maxprice);
			minp = boost::lexical_cast<double>(minprice);
			drange = boost::lexical_cast<double>(range);
			if(!exist)
				stock_bob.append(USERSTOCK_UID,userid.c_str());
			stock_bob.append(k,stk.c_str());
		}
	}
	catch(ptree_error& e)
	{
		std::cout << "error for ptree parse.." << std::endl;
	}
*/	
}


void datatask_node::setUserLoad(keyvalue kv,std::string& result)
{	
	mongo::BSONObjBuilder c_bob,r_bob;
	mongo::BSONArrayBuilder sub;
	std::string token,apptype,flag,lastuid,lasttime,firsttime;
	std::string loginnum,appversion,incrementid,osversion,comment;

	getKeyValue(kv,MOBILE_TOKEN,token);
	getKeyValue(kv,MOBILE_LASTUID,lastuid);

	c_bob.append(MOBILE_TOKEN,token);
	c_bob.append("apptypes.apptype",apptype);

	std::string strret = "";
	std::string dbcoll;
	bool c_res = true;
	m_mongodb.query(dbcoll,c_bob.obj(),strret);
	if(strret.size()<10)
		c_res = false;
	else
		c_res = true;

	size_t index = 0;
	mongo::BSONObjBuilder fieldbuild,appbuild,finalbuild,cc_bob;
//	int nflag,nloginnum;
//	long long lltime,lftime;
	cc_bob.append(MOBILE_TOKEN,token);

	for(; index < kv.keys.size();index++)
	{
		char k[1024] = {0};
		if(!c_res)
			sprintf(k,"%s",kv.keys[index].c_str());
		else
			sprintf(k,"apptypes.$.%s",kv.keys[index].c_str());

		std::string key = kv.keys[index];	
	
	}
	result = "set value ok";
}

void datatask_node::getUserLoad(keyvalue kv,std::string& result)
{

	result = "get value is ok";
}

void datatask_node::setUserStock(keyvalue kv,std::string& result)
{
	result = "set user stock ok";
}

void datatask_node::getUserStock(keyvalue kv,std::string& result)
{
	result = "get user stock ok";
}

void datatask_node::getIncrUserStock(keyvalue kv,std::string& result)
{
	std::string value = "";	
	getKeyValue(kv,MOBILE_INCR,value);
	std::cout<<"getIncrUserStock: "<<MOBILE_INCR<<": "<<value<<std::endl;
	if(value.size() < 4)
		return ;
	long long int incrid = boost::lexical_cast<long long int>(value);
	std::cout<< "initial result: " << result << std::endl;	
	int count = 0;
	value = "0";
	getKeyValue(kv,QUERY_COUNT,value);
	if(value.size() < 1)
		count = 0;
	else
		count = boost::lexical_cast<int>(value);

	//STKCFG_SETS
	Query query = MONGO_QUERY(USERSTOCK_STOCKS<<BSON("$elemMatch"<<BSON(USERSTOCK_INCR<<BSON("$gte"<<incrid))));
		
	BSONObj obj = BSON(USERSTOCK_STOCKS<<BSON("$elemMatch"<<BSON(USERSTOCK_INCR<<BSON("$gte"<<incrid))));
	std::cout << "obj: "<<obj<<std::endl;
	std::vector<BSONObj> out;
	char dbcol[255] = {0};
	sprintf(dbcol,"%s.%s",DB_NAME,STKCFG_SETS);
	m_mongodb.query(dbcol,query,out,count);
	
	result += "{ \"tasktype\":\"3000\",\"user\":[ ";	
	if(out.size() > 0)
	{
		for(size_t index = 0; index < out.size();index++)
		{
			if(index > 0)
				result += ",";
			result += "{ \"UID\":";
			result += out[index].getStringField("UID");
			result += ",\"stocks\":[";
			BSONObj sub = out[index]["stocks"].Obj();
			std::vector<BSONElement> cfgs;
			sub.elems(cfgs);
			for(size_t i = 0 ; i < cfgs.size() ; i++)
			{
				std::cout << cfgs[i] << std::endl;
				std::string strid = cfgs[i]["incrementid"].toString();
				std::string tmpid;
				if( i > 0)
					result += ",";
				size_t first = 0;
				if((first=strid.find(".")) != std::string::npos)	
				{
					int flaglen = strlen("incrementid:");
	
					tmpid = strid.substr(flaglen,first-flaglen);
					tmpid.erase(0,tmpid.find_first_not_of(" "));
				}
				std::cout<<"tmpid: " << tmpid << std::endl;
				long long int id = boost::lexical_cast<long long int>(tmpid);
				std::cout << strid << ", " << tmpid << ", id: " << id << ", qid: " << incrid << std::endl;
				if(incrid < id)
				{
				//	result += cfgs[i];
					std::string item1 = cfgs[i].toString();
				//	std::string item1 = cfgs[i].Obj().jsonString();
					std::string item(item1,item1.find(":")+1,item1.size()-item1.find(":")-1);
					result += item;
				}
			}
			result += "]";
			result += "} ";
		}
	}
	result += "] } ";

//	BSONObj retObj(result.c_str());
//	std::cout<<retObj<<std::endl;
	std::cout<<result<<std::endl;
}

void datatask_node::deal_task(task_type type,keyvalue kv,std::string& result)
{
	switch(type)
	{
	case SET_USER_LOAD:
		setUserLoad(kv,result);
		break;
	case GET_USER_LOAD:
		getUserLoad(kv,result);
		break;
	case SET_USER_STOCK:
		setUserStock(kv,result);
		break;
	case GET_USER_STOCK:
		getUserStock(kv,result);
		break;
	case GET_INCR_USERSTK:
		getIncrUserStock(kv,result);
		break;
	case UNKNOWN_TASK:
		break;
	}
}


void datatask_node::updateUserStockCfg(std::string dbcoll,std::string uid,condition value)
{
	mongo::BSONObjBuilder c_bob,r_bob;
	mongo::BSONArrayBuilder sub;
	c_bob.append("UID",uid);
	c_bob.append("stocks.stockcode",value.valueary[0].c_str());
	
	std::string strret;
	bool c_res = true;
	m_mongodb.query(dbcoll,c_bob.obj(),strret);
	if(strret.size() < 10)
		c_res = false;
	else 
		c_res = true;
	
	size_t index = 0;
	mongo::BSONObjBuilder fieldbuild,stockbuild,finalbuild,cc_bob;
	
	cc_bob.append("UID",uid);		
	std::string retuid,retstockcode;
	int bulltin,run;
	float max_price=0.0f,min_price=0.0f;
	long long int increment=0;
	
	for(;index<value.keyary.size();index++)
	{
		char k[1024] = {0};
		if(!c_res)
			sprintf(k,"%s",value.keyary[index].c_str());
		else
			sprintf(k,"stocks.$.%s",value.keyary[index].c_str());
		
		std::string key = value.keyary[index];
		if(key == "uid")
		{
			retuid = value.valueary[index];
			if(!c_res)
				stockbuild.append(value.keyary[index].c_str(),retuid.c_str());
		}
		else if(key == "stockcode")
		{
			retstockcode = value.valueary[index];
			stockbuild.append(k,retstockcode.c_str());
		}
		else if(key == "max_price")
		{
			sscanf(value.valueary[index].c_str(),"%f",&max_price);
			if(max_price != 0.0f)
				stockbuild.append(k,max_price);
		}
		else if(key == "min_price")
		{
			sscanf(value.valueary[index].c_str(),"%f",&min_price);
			if(min_price != 0.0f)
				stockbuild.append(k,min_price);
		}
		else if(key == "bulltin")
		{
			sscanf(value.valueary[index].c_str(),"%d",&bulltin);
			stockbuild.append(k,bulltin);
		}
		else if(key == "run")
		{
			sscanf(value.valueary[index].c_str(),"%d",&run);
			stockbuild.append(k,run);
		}
		else if(key == "incrementId")
		{
			sscanf(value.valueary[index].c_str(),"%Ld",&increment);
			stockbuild.append(k,increment);
		}
	}	
	mongo::Query query;
	if(!c_res)
	{
		fieldbuild.append("stocks",stockbuild.obj());
		finalbuild.append("$push",fieldbuild.obj());
		query = cc_bob.obj();
	}	
	else
	{
		cc_bob.append("stocks.stockcode",value.valueary[0].c_str());
		finalbuild.append("$set",stockbuild.obj());
		query = cc_bob.obj();
	}
	m_mongodb.setvalue(dbcoll.c_str(),query,finalbuild.obj(),true);
}

int datatask_node::setArrayInfo(std::string dbcoll,std::string kv,std::string mkey,std::string arrkey,condition value)
{
	std::string subkey;
	int pos = arrkey.find(".");
	if(pos > 0)
		subkey = arrkey.substr(pos+1,arrkey.size()-pos-1);
	else
		return -1;
		
	mongo::BSONObjBuilder c_bob,r_bob;
	mongo::BSONArrayBuilder sub;
	size_t index = 0;
	c_bob.append(mkey,kv);
	c_bob.append(arrkey,value.valueary[0].c_str());
//	mongo::BSONObj bobj = m_db.getconn()->findOne(dbcoll.c_str(),c_bob.obj());
//	std::vector<mongo::BSONElement> v;
//	bobj.elems(v);
//	std::string strret = bobj.toString();
//	pos = strret.find(value.valueary[0].c_str());
//	bool c_res = (pos!=-1) ? true:false;
		
	std::string strret;
	bool c_res = true;
	m_mongodb.query(dbcoll,c_bob.obj(),strret);
	if(strret.size() < 10)
		c_res = false;
	else 
		c_res = true;

	mongo::BSONObjBuilder fieldbuild,subbuild,finalbuild;
	mongo::BSONObjBuilder cc_bob;
	cc_bob.append(mkey,kv);
	mongo::Query query;
	
	if(!c_res)
	{
		for(; index < value.valueary.size();index++)
		{
			subbuild.append(value.keyary[index].c_str(),value.valueary[index].c_str());
		}
		fieldbuild.append(subkey,subbuild.obj());
		finalbuild.append("$push",fieldbuild.obj());
	}
	else
	{
		cc_bob.append(arrkey,value.valueary[0].c_str());
		for(index=1;index<value.valueary.size();index++)
		{
			char k[1024]={0};
			sprintf(k,"%s.$.%s",subkey.c_str(),value.keyary[index].c_str());
			subbuild.append(k,value.valueary[index].c_str());
		}
		finalbuild.append("$set",subbuild.obj());
	}
	query = cc_bob.obj();
	m_mongodb.setvalue(dbcoll.c_str(),query,finalbuild.obj(),true);
	return 1;
}


void datatask_node::task_work(const std::string& task,std::string& result)
{
	//parse task and get result
	std::cout<<"datatask_node::task_work( "<< task <<","<< result<<")"<<std::endl;
	parsepara(task,result);
		
	//write result to the result title in redis
	writeResult(result);
}



/*
*/
