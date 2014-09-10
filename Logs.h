/*
 * logs.h
 *
 *  Created on: 2014-9-2
 *      Author: imdb
 */

#ifndef LOGS_H_
#define LOGS_H_

#include <stdio.h>
#include <stdarg.h>
#include "CMysqlUtil.h"


#define OUTPUTERROR(a) cout<<"ERROR:"<<strerror(errno)<<"."<<a<<endl

#define DEBUG

class Logs
{
public:

	//    static inline void print_current_time(){
	//    	timeval tv;
	//    	tm t;
	//    	gettimeofday(&tv, NULL);
	//    	localtime_r(&(tv.tv_sec), &t);
	//    	printf("[%Y-%m-%d %H:%M:%S.%06.6d] ",
	//    			t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int)tv.tv_usec);
	//    }

	static void log(const char *format, ...){
#ifdef DEBUG
		CMysqlUtil::print_current_time();
		printf("INFO  ");

		va_list arg;
		va_start(arg, format);
		vprintf(format, arg);
		printf("\n");
		va_end(arg);
#endif
	}

	static void elog(const char *format, ...){
		CMysqlUtil::print_current_time();
		printf("ERROR ");

		va_list arg;
		va_start(arg, format);
		vprintf(format, arg);
		printf("\n");
		va_end(arg);
	}
};


#endif /* LOGS_H_ */
