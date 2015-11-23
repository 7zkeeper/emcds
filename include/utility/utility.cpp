#include "utility.h"
#include <string.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>


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
			stringReplace(vs[0],"\"","");
			stringReplace(vs[1],"\"","");
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
	stringReplace(key,"\"","");
	stringReplace(value,"\"","");
	for(; index < kv.keys.size();index++)
	{
		if(kv.keys[index] == key)
		{
			value = kv.values[index];
			std::cout << "[" << key << "]: " << value << std::endl;
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

	size_t index = 0;
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

void toJsonString(std::string& result)
{
	boost::regex r1("\\s*(\\w+)\\s*(:)\\s*(\\w+\\.?\\d*)",boost::regex::perl);
	boost::regex r2("\\s*(\\w+)\\s*:",boost::regex::perl);
	result = boost::regex_replace(result,r1,"\"$1\":\"$3\"");
	result = boost::regex_replace(result,r2,"\"$1\":");
}	

void redis2JsonString(std::string& result)
{
	stringReplace(result," ","");
	stringReplace(result,"[0:{","[{");
//	std::cout << result << std::endl;
	boost::regex re("\\}\\d:\\{");
	std::string ret = boost::regex_replace(result,re,"},{",boost::match_default|boost::format_all);
//	std::cout << result << std::endl;
}

void stringReplace(std::string& orc,std::string src,std::string des)
{
	std::string::size_type pos = 0;
	std::string::size_type srclen = src.size();
	std::string::size_type deslen = des.size();
	pos = orc.find(src,pos);
	while((pos != std::string::npos))
	{
		orc.replace(pos,srclen,des);
	    pos = orc.find(src,(pos+deslen));
	}
}

