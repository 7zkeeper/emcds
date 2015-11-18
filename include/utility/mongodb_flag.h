/* author	: zhangqi
 * filename : mongodb_flag.h
 * version	: 0.1
 * desc		: about field of collection's document
 */
#ifndef MONGODB_FLAG_H_
#define MONGODB_FLAG_H_

//redis flag
#define TASK_TYPE			"tasktype"
#define TASK_ID				"task_id"
#define USER				"user"


//mongodb flag
#define QUERY_COUNT 		"qcount"
#define DB_NAME				"test"
#define STKCFG_SETS			"usr_stk_cfg"
#define MOBILE_SETS			"mobile"
#define UIDMOBILE_SETS		"uid_mobiles"

#define MONGO_ID			"_id"

//Mobile collection
#define MOBILE_TOKEN 		"token"
#define MOBILE_APPTYPES		"apptypes"
#define MOBILE_APPTYPE		"apptype"
#define MOBILE_FLAG			"flag"
#define MOBILE_LASTUID		"lastUID"
#define MOBILE_LASTTIME		"lasttime"
#define MOBILE_FIRSTTIME 	"firsttime"
#define MOBILE_LOGINNUM		"loginnum"
#define MOBILE_APPVERSION  	"appversion"
#define MOBILE_INCR			"incrementid"
#define MOBILE_OSVERSION	"osversion"
#define MOBILE_COMMENT		"comment"


//userstock
#define USERSTOCK_UID		"UID"
#define USERSTOCK_STOCKS	"stocks"
#define USERSTOCK_STOCKCODE	"stockcode"
#define USERSTOCK_BULLETIN	"bulletin"
#define USERSTOCK_MAXPRICE	"max_price"
#define USERSTOCK_MINPRICE	"min_price"
#define USERSTOCK_RANGE		"range"
#define USERSTOCK_RUN		"run"
#define USERSTOCK_INCR		"incrementid"

//UIDTOKEN
#define UIDTOKEN_UID		"UID"
#define UIDTOKEN_APPTYPES	"apptypes"
#define UIDTOKEN_APPTYPE	"apptype"
#define UIDTOKEN_FLAG		"flag"
#define UIDTOKEN_DEVICEIDS	"deviceIDS"
#define UIDTOKEN_INCR		"incrementID"

#endif
