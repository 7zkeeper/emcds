#include <vector>
#include <string>

typedef struct _tag_keyvalues_
{
	std::vector<std::string> keys;
	std::vector<std::string> values;
}keyvalue;
	
int split(const std::string& src,std::vector<std::string>& ret,std::string sep);

int splits(const std::string& src,keyvalue& kvs,std::string sep);

void getKeyValue(keyvalue& kvs,std::string key,std::string& value);

void display(keyvalue& kv);

int getStkcfgIncrResult(std::string text,std::string& result,long long int flag);
