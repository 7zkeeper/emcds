#include "utility.h"
#include <string.h>
#include <iostream>
#include <boost/lexical_cast.hpp>

int split(const std::string& src,std::vector<std::string>& ret,std::string sep)
{
	if(src.empty())
	{
		return 0;
	}

	std::string tmp;
	std::string::size_type pos_begin = src.find_first_not_of(sep);
	std::string::size_type comma_pos = 0;

	while(pos_begin != std::string::npos)
	{
		comma_pos = src.find(sep,pos_begin);
		if(comma_pos != std::string::npos)
		{
			tmp = src.substr(pos_begin,comma_pos-pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = src.substr(pos_begin);
			pos_begin = comma_pos;
		}
		
		if(!tmp.empty())
		{
			ret.push_back(tmp);
			tmp.clear();
		}

	}
	return 0;	
}

int splits(const std::string& src,keyvalue& ret,std::string sep )
{
	if(src.empty())
	{
		return 0;
	}

	std::string tmp;
	std::string::size_type pos_begin = src.find_first_not_of(sep);
	std::string::size_type comma_pos = 0;
	int count = 0;
	while(pos_begin != std::string::npos)
	{
		comma_pos = src.find(sep,pos_begin);
		if(comma_pos != std::string::npos)
		{
			tmp = src.substr(pos_begin,comma_pos-pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = src.substr(pos_begin);
			pos_begin = comma_pos;
		}
		
		if(!tmp.empty())
		{
			std::vector<std::string> vs;
			split(tmp,vs,":");
			ret.keys.push_back(vs[0]);
			ret.values.push_back(vs[1]);
			tmp.clear();
			count++;
		}

	}
	return count;	
}

void getKeyValue(keyvalue& kv,std::string key,std::string& value)
{
	size_t index = 0;
	for(; index < kv.keys.size();index++)
	{
		if(kv.keys[index] == key)
		{
			value = kv.values[index];
			return;
		}
	}
}	

void display(keyvalue& kv)
{
	size_t index = 0;
	for(; index < kv.keys.size(); index++)
	{
		std::cout<<"key: "<<kv.keys[index]<<",value: "<<kv.values[index]<<std::endl;
	}
}


int getStkcfgIncrResult(std::string text,std::string& result,long long int flag)
{
	int count = 0;
	std::vector<std::string> stkcfgs;
	size_t first = text.find("[");
	size_t last = text.find("]");
	std::string s(text,first+1,last-first-1);

	first = s.find("{");
	while(first != std::string::npos)
	{
		last = s.find("}",first);
		std::string item(s,first,last-first+1);
		std::cout<<item<<std::endl;
		first = s.find("{",last+1);
		stkcfgs.push_back(item);
	}

	int index = 0;
	for(; index < stkcfgs.size(); index++)
	{
		first = stkcfgs[index].find("incrementid: ")+sizeof("incrementid: ")-1;
		last = stkcfgs[index].find("}",first);
		size_t temp = stkcfgs[index].find(",",first);
		if(last > temp)
			last = temp;
		std::string incr(stkcfgs[index],first,last-first);
		std::string incrid;
		std::cout<<incr<<std::endl;
		if((first=incr.find(".")) != std::string::npos)		
			incrid = incr.substr(0,first);
		long long int id = boost::lexical_cast<long long int>(incrid);
		std::cout<<"id: "<<id<<std::endl;
		if(id > flag)
		{
			result += stkcfgs[index];
			count++;
		}
	}
	std::cout<<result<<std::endl;
	return count;
}
