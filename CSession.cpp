/*
 * CSession.cpp
 *
 *  Created on: 2014-9-4
 *      Author: imdb
 */
#include "CSession.h"

Session::Session(){

}

Session::Session(int fd):fd_(fd), stat(to_check){

}

Session::~Session(){

}

bool Session::check_timeout(){
	return (get_current_time()-get_last_time()) > TIMEOUT;
}

int64_t Session::get_last_time(){
	return int64_t(last_used_time_.tv_sec * 1000000 + last_used_time_.tv_usec);
}

