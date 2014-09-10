/*
 * CSession.cpp
 *
 *  Created on: 2014-9-4
 *      Author: imdb
 */
#include "CMysqlSession.h"

CMysqlSession::CMysqlSession(){

}

CMysqlSession::CMysqlSession(int fd):fd_(fd), stat_(to_check){

}

CMysqlSession::~CMysqlSession(){

}


CMysqlSession::CMysqlSession(int fd, sockaddr_in addr):fd_(fd), addr_(addr) {

}

bool CMysqlSession::check_timeout(){
	return (CMysqlUtil::get_current_time()-get_last_time()) > TIMEOUT;
}

int64_t CMysqlSession::get_last_time(){
	return int64_t(last_used_time_.tv_sec * 1000000 + last_used_time_.tv_usec);
}

