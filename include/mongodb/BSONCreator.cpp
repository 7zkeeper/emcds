/* author 	: zhangqi
 * filename : BSONCreator.cpp
 * version  : 2015/09/15
 */

#include "BSONCreator.h"
#include "utility/mongodb_flag.h"

using mongo::BSONObjBuilder;
using mongo::BSONElement;  
using mongo::BSONObj;
using mongo::BSONArray;
using mongo::BSONArrayBuilder;


BSONObj createSetUserStockCfg(std::string user,keyvalue value,bool exist)
{
	BSONObj retObj;
	size_t 	index = 0;
	
	BSONObjBuilder fieldbuild,stockbuild,finalbuild,c_bob;
	c_bob.append("UID",user);

	std::string uid,stkcode;
	int bulltin = 0;
	float max_price = 0.0f,min_price = 0.0f;
	long long int increment = 0;
	
	for(; index<value.keys.size(); index++)
	{
		char k[1024] = {0};
		if(!exist)
			sprintf(k,"%s",value.keys[index].c_str());
		else
			sprintf(k,"stocks.$.%s",value.keys[index].c_str());
		
		std::string key = value.keys[index];
		if(key == "uid")
		{
			uid = value.values[index];
			if(!exist)
				stockbuild.append(value.keys[index].c_str(),uid.c_str());
		}
		else if(key == "stockcode")
		{
			stkcode = value.values[index];
			stockbuild.append(k,stkcode.c_str());
		}
		else if(key == "max_price")
		{
			sscanf(value.values[index].c_str(),"%f",&max_price);
			if(max_price != 0.0f)
				stockbuild.append(k,max_price);
		}
		else if(key == "min_price")
		{
			sscanf(value.values[index].c_str(),"%f",&min_price);
			if(min_price != 0.0f)
				stockbuild.append(k,min_price);
		}
		else if(key == "bulltin")
		{
			sscanf(value.values[index].c_str(),"%d",&bulltin);
			stockbuild.append(k,bulltin);
		}
		else if(key == "run")
		{
			sscanf(value.values[index].c_str(),"%f",&max_price);
			if(max_price != 0.0f)
				stockbuild.append(k,max_price);
		}
		else if(key == "incrementId")
		{
			sscanf(value.values[index].c_str(),"%Ld",&increment);
			stockbuild.append(k,increment);
		}
	}
	if(!exist)
	{
		fieldbuild.append("stocks",stockbuild.obj());
		finalbuild.append("$push",fieldbuild.obj());
	}
	else
	{
		c_bob.append("stocks.stockcode",stkcode.c_str());
		finalbuild.append("$set",stockbuild.obj());
	}
	//mongo::Query query = c_bob.obj();
	return finalbuild.obj();	
}

BSONObj createCommonSub(std::string dbcoll,std::string kv,std::string mkey,std::string arrkey,keyvalue value,bool exist)
{
	std::string subkey;
	int pos = arrkey.find(".");
	BSONObjBuilder fieldbuild,subbuild,finalbuild;
	if(pos > 0)
		subkey = arrkey.substr(pos+1,arrkey.size()-pos-1);
	else
		return finalbuild.obj();
	
	size_t index = 0;
		
	if(!exist)
	{
		for(; index < value.values.size();index++)
		{
			subbuild.append(value.keys[index].c_str(),value.values[index].c_str());
		}
		fieldbuild.append(subkey,subbuild.obj());
		finalbuild.append("$push",fieldbuild.obj());
	}
	else
	{
		for(index=1;index<value.values.size();index++)
		{
			char k[1024]={0};
			sprintf(k,"%s.$.%s",subkey.c_str(),value.keys[index].c_str());
			subbuild.append(k,value.values[index].c_str());
		}
		finalbuild.append("$set",subbuild.obj());
	}
	return finalbuild.obj();
}

void parseMobileToken(BSONObj obj,mobile_apptypes& app)
{
	app.token = obj.getStringField("Token");
	if(obj.getField("incrementID").ok())
		app.incrementID = obj.getField("incrementID").Long();
	else
		app.incrementID = -1;
	app.osversion = obj.getStringField("osversion");
	app.comment = obj.getStringField("comment");

	std::vector<BSONElement> elements = obj["apptypes"].Array();
	std::vector<BSONElement>::iterator it = elements.begin();

	for(; it != elements.end(); ++it)
	{
		BSONObj appobj = it->Obj();
		apptypeinfo appinfo;
		appinfo.apptype = appobj.getIntField("apptype");		
		if(appobj.getField("flag").ok())
			appinfo.flag = appobj.getIntField("flag");
		else 
			appinfo.flag = 0;
		appinfo.lastuid = appobj.getStringField("lastuid");
		if(appobj.getField("lasttime").ok())
			appinfo.lasttime = appobj.getField("lasttime").Long();
		else
			appinfo.lasttime = 0;
		appinfo.appversion = appobj.getStringField("appversion");
		app.apptypes.push_back(appinfo);
	}
}

int paraseUserStockCfg(BSONObj obj,std::vector<user_stock_cfg>& uscarray)
{
	std::string uid = obj.getStringField("Uid");
	std::vector<BSONElement> elements = obj["stocks"].Array();
	std::vector<BSONElement>::iterator it = elements.begin();
	int count = 0;
	for(; it != elements.end(); ++it)
	{
		BSONObj stock = it->Obj();
		user_stock_cfg usc;
		usc.uid = uid;
		usc.stock = stock.getStringField("stock");
		usc.bulletin = stock.getIntField("bulletin");
		if(stock.getField("max_price").ok())
			usc.max_price = stock.getField("max_price").Double();
		else
			usc.max_price = -0.111;
		
		if(stock.getField("min_price").ok())
			usc.min_price = stock.getField("min_price").Double();
		else
			usc.min_price = -0.111;
	
		usc.run = stock.getIntField("run");
		uscarray.push_back(usc);
		count++;
	}
	return count ;
}


BSONObj createMobileToken(apptypeinfo appinfo,bool exist)
{
	BSONObj retObj;
	BSONObjBuilder appbuild,fieldbuild,finalbuild,c_bob;
	char ftype[255] = {0};
	char fflag[255] = {0};
	char flastuid[255] = {0};
//	char flastuid[255] = {0};
	char flasttime[255] = {0};
	char fappversion[255] = {0};
	char token[255] = {0};

	c_bob.append("token",token);
	if(exist)
	{
		sprintf(ftype,"appinfo.$.apptype");
		sprintf(fflag,"appinfo.$.flag");
		sprintf(flastuid,"appinfo.$.lastuid");
		sprintf(flasttime,"appinfo.$.lasttime");
		sprintf(ftype,"appinfo.$.appversion");
	}
	else
	{
		sprintf(ftype,"apptype");
		sprintf(fflag,"flag");
		sprintf(flastuid,"lastuid");
		sprintf(flasttime,"lasttime");
		sprintf(ftype,"appversion");
	}
	appbuild.append(ftype,appinfo.apptype);
	appbuild.append(fflag,appinfo.flag);
	appbuild.append(flastuid,appinfo.lastuid);
	appbuild.append(flasttime,appinfo.lasttime);
	appbuild.append(fappversion,appinfo.appversion);

	if(!exist)
	{
		fieldbuild.append("apptypes",appbuild.obj());
		finalbuild.append("$push",fieldbuild.obj());
	}
	else
	{
		c_bob.append("token.apptypes",appinfo.apptype);
		finalbuild.append("$set",appbuild.obj());
	}

	return finalbuild.obj();
}

BSONObj createSetUserLoad(std::string token,keyvalue kv,bool exist)
{
	mongo::BSONObjBuilder c_bob,r_bob;
	mongo::BSONArrayBuilder sub;
	std::string apptype,flag,lastuid,lasttime,firsttime;
	std::string loginnum,appversion,incrementid,osversion,comment;

	getKeyValue(kv,MOBILE_TOKEN,token);
	getKeyValue(kv,MOBILE_LASTUID,lastuid);

	c_bob.append(MOBILE_TOKEN,token);
	c_bob.append("apptypes.apptype",apptype);

	std::string strret = "";
	std::string dbcoll;

	size_t index = 0;
	mongo::BSONObjBuilder fieldbuild,appbuild,finalbuild,cc_bob;
	int nflag,nloginnum;
	long long lltime,lftime,incr;
	cc_bob.append(MOBILE_TOKEN,token);

	for(; index < kv.keys.size();index++)
	{
		char k[1024] = {0};
		if(!exist)
			sprintf(k,"%s",kv.keys[index].c_str());
		else
			sprintf(k,"apptypes.$.%s",kv.keys[index].c_str());

		std::string key = kv.keys[index];	
		if( key == MOBILE_TOKEN)
		{
			if(!exist)
				appbuild.append(kv.keys[index].c_str(),token.c_str());
		}
		else if( key == MOBILE_APPTYPE )
		{
			appbuild.append(k,apptype.c_str());
		}
		else if( key == MOBILE_FLAG)
		{
			getKeyValue(kv,MOBILE_FLAG,flag);
			if(!flag.empty())
			{
				nflag = atoi(flag.c_str());
				appbuild.append(k,nflag);
			}
		}
		else if( key == MOBILE_LASTUID )
		{
			getKeyValue(kv,MOBILE_LASTUID,lastuid);
			appbuild.append(k,lastuid.c_str());
		}
		else if( key == MOBILE_LASTTIME )
		{
			getKeyValue(kv,MOBILE_LASTTIME,lasttime);
			sscanf(lasttime.c_str(),"%Ld",&lltime);
			appbuild.append(k,lltime);
		}
		else if( key == MOBILE_FIRSTTIME )
		{
			getKeyValue(kv,MOBILE_FIRSTTIME,firsttime);
			if(!firsttime.empty())
			{
				sscanf(firsttime.c_str(),"%Ld",&lftime);
				appbuild.append(k,lftime);
			}
		}

		else if( key == MOBILE_LOGINNUM )
		{
			getKeyValue(kv,MOBILE_LOGINNUM,loginnum);
			if(!loginnum.empty())
			{
				sscanf(loginnum.c_str(),"%d",&nloginnum);
				appbuild.append(k,nloginnum);
			}
		}
			
		else if( key == MOBILE_APPVERSION )
		{
			getKeyValue(kv,MOBILE_APPVERSION,appversion);
			if(!appversion.empty())
			{
				appbuild.append(k,appversion.c_str());
			}
		}
					
		else if( key == MOBILE_INCR )
		{
			getKeyValue(kv,MOBILE_INCR,incrementid);
			if(!incrementid.empty())
			{
				sscanf(incrementid.c_str(),"%Ld",&incr);
				appbuild.append(k,incr);
			}
		}
	}
	if(!exist)
	{
		fieldbuild.append(MOBILE_APPTYPES,appbuild.obj());
		finalbuild.append("$push",fieldbuild.obj());
	}
	else
	{
		c_bob.append("apptypes.apptype",apptype.c_str());
		finalbuild.append("$set",appbuild.obj());
	}
	return finalbuild.obj();
}
