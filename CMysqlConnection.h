/*
 * CSession.h
 *
 *  Created on: 2014-9-4
 *      Author: imdb
 */

#ifndef C_MYSQL_CONNECTION_H_
#define C_MYSQL_CONNECTION_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#include "CMysqlDefine.h"
#include "CMysqlUtil.h"
using namespace std;

enum status{to_shakehand, to_check, to_command, command};

class CMysqlConnection
{
public:
	CMysqlConnection();
	CMysqlConnection(int fd);
	CMysqlConnection(int fd, sockaddr_in addr);
	virtual ~CMysqlConnection();
	bool check_timeout();
	int64_t get_last_time();

	const sockaddr_in& get_addr() const {
		return addr_;
	}

	void set_addr(sockaddr_in addr){
		addr_ = addr;
	}

	int get_fd() const {
		return fd_;
	}

private:
	string username_;
	string password_;
	int fd_;
	timeval last_used_time_;
	sockaddr_in addr_;
//	gettimeofday();
	double current_time_;
	status stat_;
};

#endif /* C_MYSQL_SESSION_H_ */
