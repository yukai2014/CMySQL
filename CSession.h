/*
 * CSession.h
 *
 *  Created on: 2014-9-4
 *      Author: imdb
 */

#ifndef CSESSION_H_
#define CSESSION_H_

#include "CDefine.h"
#include "CMysqlUtil.h"

enum status{to_shakehand, to_check, to_command, command};

class Session
{
public:
	Session();
	Session(int fd);
	virtual ~Session();
	bool check_timeout();
	int64_t get_last_time();

	inline sockaddr_in get_addr(){
		return addr_;
	}

	void set_addr(sockaddr_in addr){
		addr_ = addr;
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

#endif /* CSESSION_H_ */
