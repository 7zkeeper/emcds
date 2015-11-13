/* author	: zhangqi
 * filename : proxy.cpp
 * version  : 0.1
 */

#include "proxyserver.h"
#include <stdio.h>
int main(int argc,char* argv[])
{
	if(argc > 1)
	{	

		EventLoop loop;
		uint16_t port = static_cast<uint16_t>(atoi(argv[1]));
		InetAddress serverAddr(port);
		InetAddress redisAddr(6380);
		ProxyServer server(&loop,serverAddr,redisAddr,"proxyserver");
		server.setLoginfo("serverlog.properties");
		server.start();
		loop.loop();
	}
	else
	{
		printf("usage: %s port\n",argv[0]);
	}
	return 1;
}

