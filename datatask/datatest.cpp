#include <string>
#include "datatask_node.h"
#include "mongodb/em_mongodb.h"

int main()
{	
	boost::asio::io_service ioService;
	RedisAsyncClient redisclient(ioService);
	datatask_node node(ioService,redisclient,"dataserver.ini");
	ioService.run();
	return 1 ;
}
