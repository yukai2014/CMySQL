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
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>

#include "packet/CMysqlSprPacket.h"
#include "packet/CMysqlCommandPacket.h"
#include "packet/CMysqlResHeaderPacket.h"
#include "packet/CMysqlSQLPacket.h"
#include "packet/CMysqlFieldPacket.h"
#include "packet/CMysqlEofPacket.h"
#include "CMysqlConnection.h"
#include "CMysqlLoginer.h"
#include "ThreadPool.h"
#include "Logs.h"

using namespace std;

class CMysqlLoginer;

class CMysqlServer {
public:
	CMysqlServer();
	virtual ~CMysqlServer();

public:
	int start();
	int initialize();

	inline void set_port(){
	}

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

	int listen_port(int port);

	bool AcceptConnection(int fd, int &connected_fd);
	bool ReceiveData(epoll_event event, char *buf);
	bool ReceiveData(int fd);
	int has_full_session(){
		int ret = C_SUCCESS;
		//TODO
		return ret;
	}

public:
	ThreadPool *threadpool_;
	queue<CMysqlSQLPacket*> in_queue_;
	queue<CMysqlSQLPacket*> out_queue_;
	map<int, CMysqlConnection*> fd_to_session;
	char *temp_buffer;	//TODO: should be replaced by memory pool

private:
	int listening_fd;
	int epoll_fd;
	int port_;
	int work_threads_count_;
	int connection_max_count_;
	CMysqlLoginer loginer_;

//	map<int , sockaddr_in> fd_to_adddr;
};

#endif /* CMYSQLSERVER_H_ */
