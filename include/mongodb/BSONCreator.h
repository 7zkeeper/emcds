/* author	: zhangqi
 * filename : BSONCreator.h
 * version  : 0.1
 */
#ifndef BSON_CREATOR_H_
#define BSON_CREATOR_H_

#include "mongo/client/dbclient.h"
#include <string>
#include <vector>
#include "utility/utility.h"

using mongo::BSONObj;
/*
typedef struct _kvpair_
{
	std::vector<std::string> keyary;
	std::vector<std::string> valueary;
}kvpair;
*/
typedef struct _tag_user_stock_cfg
{
	std::string uid;
	std::string stock;
	int bulletin;
	float max_price;
	float min_price;
	long long int riseday;
	long long int fallday;
	int	run;
}user_stock_cfg;

typedef struct _tag_notify_cfg
{
	std::string uid;
	unsigned int apptype;
	int			flag;
}notify_cfg;

typedef struct _tag_apptype_info
{
	unsigned int 	apptype;
	int	flag;
	std::string  	lastuid;
	long long int 	lasttime;
	long long int 	firsttime;
	int 			loginnum;
	std::string 	appversion;
}apptypeinfo;

typedef struct _tag_mobile_apptypes
{
	std::string token;
	std::vector<apptypeinfo>	apptypes;
	long long int incrementID;
	std::string osversion;
	std::string comment;
}mobile_apptypes;

BSONObj createSetUserStockCfg(std::string user,keyvalue value,bool exist);

BSONObj createCommonSub(std::string dbcoll,std::string kv,std::string mkey,std::string arrkey,keyvalue value,bool exist);

int paraseUserStockCfg(BSONObj obj,std::vector<user_stock_cfg>& uscarray);

BSONObj createMobileToken(apptypeinfo appinfo);

BSONObj createSetUserLoad(std::string token,keyvalue kv,bool exist);

void parseMobileToken(BSONObj obj);


#endif 
