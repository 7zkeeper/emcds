// ksm_zk.cpp
#include "ksm_zk.h"

KSM_ZK::KSM_ZK()
{
	m_zh = NULL;
	m_connected = 0;
	m_expired = 0;
	m_errorstring[0] = '\0';
}

KSM_ZK::~KSM_ZK()
{
	Close();
}

int KSM_ZK::readIni(std::string iniFile)
{
		return 1;
}

void KSM_ZK::InitZK_cb()
{
	//zoo_set_debug_level(ZOO_LOG_LEVLEL_INFO);
	SetMainWatcher_cb(df_main_watcher);
	SetGetChildWatcher_cb(df_getchild_watcher);
	SetGetDataWatcher_cb(df_getdatawatcher);	

	SetCreateNode_cb(df_create_completion);
	SetDeleteNode_cb(df_delete_completion);
	SetExistNode_cb(df_existnode_completion);
	SetGetData_cb(df_getdata_completion);
	SetSetData_cb(df_setdata_completion);
	SetGetChild_cb(df_getchild_completion);	
}

int KSM_ZK::Connect(const char* hostport)
{
	InitZK_cb();
	int ret =-1;
	if(m_zh)
		return ret;
	const int TIME_OUT = 15000;
	m_zh = zookeeper_init(hostport,
					m_mainwatcher_fn,
					TIME_OUT,
					0,
					this,
					0);
	if(m_zh) ret = 0;
	return ret;
}

	
int KSM_ZK::Close()
{
	int ret = -1;
	if(m_zh)
	{
		zookeeper_close(m_zh);
		m_zh = NULL;
	}
	return ret;
}

int KSM_ZK::init(std::string iniFile)
{
	return 1;
}

bool KSM_ZK::IsConnected()
{
	return m_connected;
}

bool KSM_ZK::IsExpired()
{
	return m_expired;
}
zhandle_t* KSM_ZK::GetZK() const
{
	return m_zh;
}
	

//create znode must have parent node
int KSM_ZK::CreateNode(const char* path,void* data)
{
	int ret = -1;
	node_info* pnode = new node_info();
	if(pnode == NULL)
	{
		ret = -10000;
		LOG_ERROR(("new node_info error."));
		return ret;
	}	
	pnode->ksm_zk = this;
	pnode->name = const_cast<char*>( path );
	sprintf(pnode->path,"%s",path);
	pnode->value = reinterpret_cast<char*>( data );
	pnode->value_len = strlen(pnode->value);
	if(m_zh && m_connected)
	{
		char* value = reinterpret_cast<char*>(data);
		ret = zoo_acreate(m_zh,
					path,
					value,
					strlen(value),
					&ZOO_OPEN_ACL_UNSAFE,
					0,
					m_createnode_fn,
					(const void*) pnode);
	}
	return ret;
}

void getnode_completion_cb(int rc,const char* path,int len,
							const struct Stat* stat,const void* data)
{
}

//gets the data associated with a znode
int KSM_ZK::GetNodeData(const char* path)
{
	int ret = -1;
	node_info* pnode = new node_info();
	if(pnode == NULL)
	{
		ret = -10000;
		LOG_ERROR(("new node_info error."));
		return ret;
	}	
	pnode->ksm_zk = this;
	pnode->name = const_cast<char*>(path);
	sprintf(pnode->path,"%s",path);
	pnode->value = NULL;
	pnode->value_len = 0;
	sprintf(pnode->path,"%s",path);
/*	ret = zoo_aget(m_zh,
				path,
				0,
				m_getdata_cb,
				(const void*)pnode);*/
	ret = zoo_awget(m_zh,
					path,
					m_getdatawatcher_fn,
					this,
					m_getdata_fn,
					(const void*)pnode->path);//pnode);
	printf("path:%s,node->name:%s\n",path,pnode->path);	
	return ret;
}

//sets the data associated with a znode 
int KSM_ZK::SetNodeData(const char* path,void* data)
{
	int ret = -1;
	node_info* pnode = new node_info();
	if(pnode == NULL)
	{
		ret = -10000;
		LOG_ERROR(("new node_info error."));
		return ret;
	}	
	pnode->ksm_zk = this;
	pnode->name = const_cast<char*>(path);
	sprintf(pnode->path,"%s",path);
	pnode->value = reinterpret_cast<char*>( data );
	pnode->value_len = strlen(pnode->value);
	ret = zoo_aset(m_zh,
					path,
					pnode->value,
					pnode->value_len,
					0,
					m_setdata_fn,
					(const void*) pnode);

	return ret;
}

//checks the existence of a znode in zookeeper
int KSM_ZK::IsExistNode(const char* path)
{
	int ret = -1;
	node_info* pnode = new node_info();
	if(pnode == NULL)
	{
		ret = -10000;
		LOG_ERROR(("new node_info error."));
		return ret;
	}	
	pnode->ksm_zk = this;
	pnode->name = const_cast<char*>( path );
	sprintf(pnode->path,"%s",path);
	ret = zoo_awexists(m_zh,
					path,
					m_existsnodewatcher_fn,
					this,
					m_existsnode_fn,
					(const void*) pnode);	
	return ret;
}

//get lists the children of znode	
int KSM_ZK::GetChildren(const char* path)
{
	int ret = -1;
	node_info* pnode = new node_info();
	if(pnode == NULL)
	{
		ret = -10000;
		LOG_ERROR(("new node_info error."));
		return ret;
	}	
	pnode->ksm_zk = this;
	pnode->name = const_cast<char*>( path );	
	sprintf(pnode->path,"%s",path);	
//	pnode->data = reinterpret_cast<char*>( data );
//	pnode->value_lenn = strlen(pnode->data);
	ret = zoo_awget_children(m_zh,
							path,
							m_getchildwatcher_fn,
							this,
							m_getchild_fn,
							(const void*) pnode);			
	return ret;
}

//deletes znode in zookeeper
int KSM_ZK::DeleteNode(const char* path)
{
	int ret = -1;
//	char message[1024]= {0};
	node_info* pnode = new node_info();
	if(pnode == NULL)
	{
		ret = -10000;
		LOG_ERROR(("new node_info error."));
		return ret;
	}	
	pnode->ksm_zk = this;
	pnode->name = const_cast<char*>( path );
	sprintf(pnode->path,"%s",path);
//	pnode->data = reinterpret_cast<char*>( data );
//	pnode->value_lenn = strlen(pnode->data);
	ret = zoo_adelete(m_zh,
					path,
					-1,
					m_deletenode_fn,
					(const void*) pnode);

	return ret;
}

void KSM_ZK::SetMainWatcher_cb(watcher_fn cb)
{
	m_mainwatcher_fn = cb;
}

void KSM_ZK::SetGetChildWatcher_cb(watcher_fn cb)
{
	m_getchildwatcher_fn = cb;
}	

void KSM_ZK::SetGetDataWatcher_cb(watcher_fn cb)
{
	m_getdatawatcher_fn = cb;
}

void KSM_ZK::SetCreateNode_cb(string_completion_t cb)
{
	m_createnode_fn = cb;
}

void KSM_ZK::SetDeleteNode_cb(void_completion_t cb)
{
	m_deletenode_fn = cb;
}

void KSM_ZK::SetExistNode_cb(stat_completion_t cb)
{
	m_existsnode_fn = cb;
}

void KSM_ZK::SetGetData_cb(data_completion_t cb)
{
	m_getdata_fn = cb;
}

void KSM_ZK::SetSetData_cb(stat_completion_t cb)
{
	m_setdata_fn = cb;
}

void KSM_ZK::SetGetChild_cb(strings_completion_t cb)
{
	m_getchild_fn = cb;
}

int KSM_ZK::HandleEvent(ZK_Para* para)
{
	int ret=0;

	return ret;
}
	

//auxiliary function
char* make_path(int num,...)
{
	const char* tmp_string;
	va_list arguments;

	va_start(arguments, num);
	int total_length = 0;
	int i = 0;
	for(; i < num ; i++)
	{
		tmp_string = va_arg(arguments,const char*);
		if(tmp_string != NULL)
		{
			total_length += strlen(tmp_string);
		}
	}
	va_end(arguments);
	
	char* path = (char*)malloc(total_length * sizeof(char) +1);
	path[0] = '\0';
	va_start( arguments,num);
	
	for(i = 0; i < num; num++)
	{
		tmp_string = va_arg(arguments , const char*);
		if(tmp_string != NULL)
		{
			strcat(path,tmp_string);
		}
	}
	return path;
}

struct String_vector* make_copy(const struct String_vector* vect)
{
	struct String_vector* tmp_vector =(String_vector*) malloc(sizeof(struct String_vector));
	tmp_vector->data = (char**)malloc(vect->count * sizeof(const char *));
	tmp_vector->count = vect->count;
	int i = 0;
	for(; i < vect->count; i++)
	{
		tmp_vector->data[i] = strdup(vect->data[i]);
	}
	return tmp_vector;
}

int allocate_vector(struct String_vector* v, int32_t len)
{
	if(!len)
	{
		v->count = 0;
		v->data = 0;
	}
	else
	{
		v->count = len;
		v->data = (char**)malloc(sizeof(*v->data)*len);
	}
	return 0;
}

void free_vector(struct String_vector* vect)
{
	int i=0;
	for(; i < vect->count; i++)
	{
		free(vect->data[i]);
	}
	
	free(vect->data);
	free(vect);
}

struct String_vector* added_and_set(const struct String_vector* current,
								struct String_vector** previous)
{
	struct String_vector* diff = (struct String_vector*)malloc(sizeof(struct String_vector));
	int count = 0;
	int i = 0;
	for(i = 0; i < current->count ; i++)
	{
		if(!contains(current->data[i],(*previous)))
		{
			count++;
		}
	}
	
	allocate_vector(diff,count);
	
	//int prev_count = count;
	count = 0;
	
	for(i = 0 ; i < current->count ; i++)
	{
		if(!contains(current->data[i],(*previous)))
		{
			diff->data[count] =(char*) malloc(sizeof(char)* strlen(current->data[i]) + 1);
			memcpy(diff->data[count++],
					current->data[i],
					strlen(current->data[i]));
		}
	}
	free_vector((struct String_vector*) *previous);
	(*previous) = make_copy(current);
	return diff;
}

struct String_vector* removed_and_set(const struct String_vector* current,
										struct String_vector** previous)
{
	struct String_vector* diff  = (struct String_vector*)malloc(sizeof(struct String_vector));
	int count  = 0 ;
	int i = 0;
	struct String_vector* p = const_cast<String_vector*> (current);
	for(; i < (*previous)->count; i++)
	{
		if(contains((*previous)->data[i],p))
		{
			count++;
		}
	}

	allocate_vector(diff,count);
	
//	int prev_count = count;
	count = 0;
	for(i = 0 ; i < (*previous)->count ; i++)
	{
		if(!contains((*previous)->data[i],p))
		{
			diff->data[count] = (char*)malloc(sizeof(char) * strlen((*previous)->data[i]));
			strcpy(diff->data[count++],(*previous)->data[i]);
		}
	}

	free_vector((struct String_vector*)*previous);
	(*previous) = make_copy(p);
	return diff;

}

int contains(const char* child,struct String_vector* children)
{
	int i = 0;
	for(; i < children->count ; i++)
	{
		if(!strcmp(child,children->data[i]))
		{
			return 1;
		}
	}
	return 0;
}

void df_getdatawatcher(zhandle_t* zh,int type,int state,const char* path,void* context)
{
	char message[1024] = {0};
	if(context == NULL)
		return;
	KSM_ZK* pzk = reinterpret_cast<KSM_ZK*>(context);
	
	if(type == ZOO_CHANGED_EVENT)
	{
		pzk->GetNodeData(path);
		printf("[path]:%s get data changed event.\n",path);	
	}
	else
	{
		sprintf(message,"Watched event: %s",TypeEvent2String(type));
		LOG_DEBUG((message));
		printf("%s\n",message);
	}


}
	
void df_main_watcher(zhandle_t* zh,int type,int state,const char* path,void* context)
{
	if(context == NULL)
		return;
	char message[1024] = {0};
	KSM_ZK* pzk = reinterpret_cast<KSM_ZK*>(const_cast<void*>(context));
	if(type == ZOO_SESSION_EVENT)
	{
		if(state == ZOO_CONNECTED_STATE)
		{
			pzk->m_connected = 1;
			LOG_DEBUG(("Received a connected event."));
		}
	//	else if( state == ZOO_NOTCONNECTED_STATE)
	//	{
	//		pzk->m_connected = 0;
			//sprintf(message,"Recevied a disconnected event.");
			//LOG_WARN(message);
	//	}
		else if( state == ZOO_EXPIRED_SESSION_STATE)
		{
			pzk->m_expired = 1;
			pzk->m_connected = 0;
		}
	}
	sprintf(message,"Event: %s %d.",TypeEvent2String(type),state);
	LOG_DEBUG((message));
}
		

void df_create_completion(int rc,const char* path,const void* value)
{
	char message[1024] = {0};
	switch(rc)

	{
		case ZCONNECTIONLOSS:
		case ZOPERATIONTIMEOUT:
			sprintf(message,"Connecting loss or time out.");
			LOG_ERROR((message));
			break;
		case ZOK:
			sprintf(message,"Create node [path]:%s.",const_cast<char*>(path));
			LOG_INFO((message));
			break;
		case ZNODEEXISTS:
			LOG_WARN(("Node already exists."));
			break;
		default:
			sprintf(message,"Something went wrong when create node.");
			LOG_ERROR((message));
			break;
	}
}



void df_delete_completion(int rc,const void* value)
{
	char message[1024] = {0};
	switch(rc)
	{
		case ZCONNECTIONLOSS:
		case ZOPERATIONTIMEOUT:
			sprintf(message,"Connectiong loss or timeout when delete node.");
			LOG_ERROR((message));
			break;

		case ZOK:
			sprintf(message,"delete node: %s",const_cast<char*>((const char*)(value)));
			LOG_DEBUG((message));
			//free(const_cast<char*>(value));
			break;
		
		default:
			sprintf(message,"Something went wrong when deleting task: %s",State2String(rc));
			LOG_ERROR((message));
			break;
	}
}

void df_getdata_completion(int rc,const char* data,int len,const struct Stat* stat,const void* value)
{
	switch(rc)
	{
		case ZCONNECTIONLOSS:
		case ZOPERATIONTIMEOUT:
			LOG_ERROR(("connectloss or timeout please try again."));
			printf("conncet loss or timeout,please try again.\n");
			break;
		case ZOK:
			if( NULL == data)
			{
				printf("it  doesnt exist data in this node.");
				return ;
			}
			else
			{
				char pdata[1024] = {0};
				memcpy(pdata,data,len);
				//	node_info* pctx = reinterpret_cast<node_info*>(const_cast<void*>(value));
		//		printf("[%s]: value_len :%d, value : %s\n",value,len,pdata);
			}
			break;
		case ZNONODE:
			printf("this node is not exist.\n");
			break;
		default:
			printf("something went wrong when checking node : %s\n",TypeEvent2String(rc));
			break;
	}
}	

void df_getchild_watcher(zhandle_t* zh,int type,int state,const char* path,void* context)
{
	char message[1024] = {0};
	if(context == NULL)
		return;
	KSM_ZK* pzk = reinterpret_cast<KSM_ZK*>(context);
	
	if(type == ZOO_CHILD_EVENT)
	{
		pzk->GetChildren(path);
		printf("get child event.\n");	
	}
	else
	{
		sprintf(message,"Watched event: %s",TypeEvent2String(type));
		LOG_DEBUG((message));
		printf("%s\n",message);
	}

}

void df_getchild_completion(int rc,const struct String_vector* strings,const void* data)
{
	struct String_vector* p = NULL;
	int i = 0;
	struct node_info* pnode = NULL;
			
	switch(rc)
	{
		case ZCONNECTIONLOSS:
		case ZOPERATIONTIMEOUT:
			LOG_ERROR(("connectloss or timeout please try again."));
			printf("conncet loss or timeout,please try again.\n");
			break;
		case ZOK:
			p = const_cast<struct String_vector*>( strings);
			for(i = 0; i < p->count; i++)
			{
				printf("data[%d]:%s\n",i,p->data[i]);
			}
			pnode = reinterpret_cast<node_info*>( const_cast<void*>(data));
			if(pnode == NULL)
			{
				LOG_ERROR(("new node_info error."));
				return ;
			}	
			//pnode->ksm_zk->GetChildren(pnode->name);
			break;
		case ZNONODE:
			printf("this node is not exist.\n");
			break;
		default:
			printf("something went wrong when checking node : %s\n",TypeEvent2String(rc));
			break;
	}	
}

void df_existnode_completion(int rc,const struct Stat* stat,const void* data)
{
	switch(rc)
	{
		case ZCONNECTIONLOSS:
		case ZOPERATIONTIMEOUT:
			LOG_ERROR(("connectloss or timeout please try again."));
			printf("conncet loss or timeout,please try again.\n");
			break;
		case ZOK:
			printf("the node exists\n");
			break;
		case ZNONODE:
			printf("this node is not exist.\n");
			break;
		default:
			printf("something went wrong when checking node : %s\n",TypeEvent2String(rc));
			break;
	}

}

void df_setdata_completion(int rc, const struct Stat* stat,const void* data)
{
	switch(rc)
	{
		case ZCONNECTIONLOSS:
		case ZOPERATIONTIMEOUT:
			LOG_ERROR(("connectloss or timeout please try again."));
			printf("conncet loss or timeout,please try again.\n");
			break;
		case ZOK:
			printf("set data successed.\n");
			break;
		case ZNONODE:
			printf("this node is not exist.\n");
			break;
		default:
			printf("something went wrong when checking node : %s\n",TypeEvent2String(rc));
			break;
	}


}

//eventtype
const char * TypeEvent2String(int type)
{
    if (type == ZOO_CREATED_EVENT)
        return "CREATED_EVENT";
    if (type == ZOO_DELETED_EVENT)
        return "DELETED_EVENT";
    if (type == ZOO_CHANGED_EVENT)
        return "CHANGED_EVENT";
    if (type == ZOO_CHILD_EVENT)
        return "CHILD_EVENT";
    if (type == ZOO_SESSION_EVENT)
        return "SESSION_EVENT";
    if (type == ZOO_NOTWATCHING_EVENT)
        return "NOTWATCHING_EVENT";
    
    return "UNKNOWN_EVENT_TYPE";
}

//keeperstate
const char * State2String(int rc){
    if (rc == ZOK) {
        return "OK";
    }
    if (rc == ZSYSTEMERROR) {
        return "System error";
    }
    if (rc == ZRUNTIMEINCONSISTENCY) {
        return "Runtime inconsistency";
    }
    if (rc == ZDATAINCONSISTENCY) {
        return "Data inconsistency";
    }
    if (rc == ZCONNECTIONLOSS) {
        return "Connection to the server has been lost";
    }
    if (rc == ZMARSHALLINGERROR) {
        return "Error while marshalling or unmarshalling data ";
    }
    if (rc == ZUNIMPLEMENTED) {
        return "Operation not implemented";
    }
    if (rc == ZOPERATIONTIMEOUT) {
        return "Operation timeout";
    }
    if (rc == ZBADARGUMENTS) {
        return "Invalid argument";
    }
    if (rc == ZINVALIDSTATE) {
        return "Invalid zhandle state";
    }
    if (rc == ZAPIERROR) {
        return "API error";
    }
    if (rc == ZNONODE) {
        return "Znode does not exist";
    }
    if (rc == ZNOAUTH) {
        return "Not authenticated";
    }
    if (rc == ZBADVERSION) {
        return "Version conflict";
    }
    if (rc == ZNOCHILDRENFOREPHEMERALS) {
        return "Ephemeral nodes may not have children";
    }
    if (rc == ZNODEEXISTS) {
        return "Znode already exists";
    }
    if (rc == ZNOTEMPTY) {
        return "The znode has children";
    }
    if (rc == ZSESSIONEXPIRED) {
        return "The session has been expired by the server";
    }
    if (rc == ZINVALIDCALLBACK) {
        return "Invalid callback specified";
    }
    if (rc == ZINVALIDACL) {
        return "Invalid ACL specified";
    }
    if (rc == ZAUTHFAILED) {
        return "Client authentication failed";
    }
    if (rc == ZCLOSING) {
        return "ZooKeeper session is closing";
    }
    if (rc == ZNOTHING) {
        return "No response from server";
    }
    if (rc == ZSESSIONMOVED) {
        return "Session moved to a different server";
    }
   
    return "UNKNOWN_EVENT_TYPE";
}


