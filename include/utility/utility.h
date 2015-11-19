
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <vector>
#include <string>

typedef struct _tag_keyvalues_
{
	std::vector<std::string> keys;
	std::vector<std::string> values;
}keyvalue;
	
typedef struct _data_task_
{
	std::string key;
	std::string task;
}data_task;

typedef struct _condition_
{
	std::vector<std::string> keyary;
	std::vector<std::string> valueary;
}condition;

typedef enum _task_type_
{
	SET_USER_LOAD = 1000,
	GET_USER_LOAD,

	SET_USER_STOCK = 2000,
	GET_USER_STOCK,

	GET_INCR_USERSTK = 3000,

	UNKNOWN_TASK = 1000000

}task_type;

int split(const std::string& src,std::vector<std::string>& ret,std::string sep);

int splits(const std::string& src,keyvalue& kvs,std::string sep);

void getKeyValue(keyvalue& kvs,std::string key,std::string& value);

void display(keyvalue& kv);

int getStkcfgIncrResult(std::string text,std::string& result,long long int flag);

void toJsonString(std::string& result);

void stringReplace(std::string& orc,std::string src,std::string des);


#endif
