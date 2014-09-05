/*
 * CMysqlServer.h
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#ifndef C_MYSQL_SERVER_H_
#define C_MYSQL_SERVER_H_

#include <iostream>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <map>

#include "packet/CMysqlSprPacket.h"
#include "packet/CMysqlCommandPacket.h"
#include "CMysqlResHeaderPacket.h"
#include "CMysqlSqlPacket.h"
#include "ThreadPool.h"
#include "Logs.h"
#include "CSession.h"

using namespace std;

#define OB_LIKELY(x)       __builtin_expect(!!(x),1)


//ObMySQLRowPacket
class CMysqlServer {
public:
	CMysqlServer();
	virtual ~CMysqlServer();

public:

	inline void set_port(int port){
//		port_ = 2345;
		//TODO: read value from config
	}

	void set_work_threads_count(){
//		if ( < 0){
//			elog();
//		}
//		else{
//			work_threads_count_ = ;
//		}
//		work_threads_count_ = 4;
//		TODO: read value from config
	}

	inline void set_connection_max_count(){

	}

	int listen_port(port);

	bool AcceptConnection(int epoll_fd, int fd);
	bool ReceiveData(epoll_event event, char *buf);
	bool ReceiveData(epoll_event event);

public:
	ThreadPool *threadpool_;
	queue<CMysqlSQLPacket*> in_queue_;
	queue<CMysqlSQLPacket*> out_queue_;
	map<int, Session*> fd_to_session;

private:
	int listening_fd;
	int port_;
	int work_threads_count_;
	int connection_max_count_;
//	map<int , sockaddr_in> fd_to_adddr;
};

#endif /* CMYSQLSERVER_H_ */
