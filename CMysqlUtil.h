/*
 * CMysqlUtil.h
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#ifndef C_MYSQL_UTIL_H_
#define C_MYSQL_UTIL_H_

#include "CMysqlDefine.h"
#include <sys/time.h>
#include <time.h>

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

class CMysqlUtil {
public:
	enum EMySQLFieldType
	{
		MYSQL_TYPE_DECIMAL,
		MYSQL_TYPE_TINY,
		MYSQL_TYPE_SHORT,
		MYSQL_TYPE_LONG,
		MYSQL_TYPE_FLOAT,
		MYSQL_TYPE_DOUBLE,
		MYSQL_TYPE_NULL,
		MYSQL_TYPE_TIMESTAMP,
		MYSQL_TYPE_LONGLONG,
		MYSQL_TYPE_INT24,
		MYSQL_TYPE_DATE,
		MYSQL_TYPE_TIME,
		MYSQL_TYPE_DATETIME,
		MYSQL_TYPE_YEAR,
		MYSQL_TYPE_NEWDATE,
		MYSQL_TYPE_VARCHAR,
		MYSQL_TYPE_BIT,
		MYSQL_TYPE_NEWDECIMAL=246,
		MYSQL_TYPE_ENUM=247,
		MYSQL_TYPE_SET=248,
		MYSQL_TYPE_TINY_BLOB=249,
		MYSQL_TYPE_MEDIUM_BLOB=250,
		MYSQL_TYPE_LONG_BLOB=251,
		MYSQL_TYPE_BLOB=252,
		MYSQL_TYPE_VAR_STRING=253,
		MYSQL_TYPE_STRING=254,
		MYSQL_TYPE_GEOMETRY=255,
		MYSQL_TYPE_NOT_DEFINED=65535
	};

	CMysqlUtil();
	virtual ~CMysqlUtil();

public:
	static int store_null(char *buf, int64_t len, int64_t &pos);
	static int store_int1(char *buf,int64_t len,int8_t v,int64_t &pos);
	static int store_int2(char *buf,int64_t len,int16_t v,int64_t &pos);
	static int store_int3(char *buf,int64_t len,int32_t v,int64_t &pos);
	static int store_int4(char *buf,int64_t len,int32_t v,int64_t &pos);
	static int store_int8(char *buf, int64_t len, int64_t v, int64_t &pos);
	static int store_str(char *buf, int64_t len, const char *str, int64_t &pos);
	static int store_length(char *buf, int64_t len, uint64_t length, int64_t &pos);

	static int store_str_v(char *buf, int64_t len, const char *str,const uint64_t length, int64_t &pos);
	static int store_str_vzt(char *buf, int64_t len, const char *str,const uint64_t length, int64_t &pos);
	static int store_obstr_nzt(char *buf, int64_t len, string str, int64_t &pos);


	static void get_uint3(char *&pos, uint32_t &v);
	static void get_uint4(char *&pos, uint32_t &v);
	static void get_uint1(char *&pos, uint8_t &v);

	static int get_mysql_type(EMySQLFieldType &,uint8_t &,uint32_t &);
	static int store_obstr(char *buf, int64_t len, string str, int64_t &pos)
	{
		return store_str_v(buf, len, str.c_str(), str.length(), pos);
	}

	// us
	static int64_t get_current_time(){
		timeval time;
		gettimeofday(&time, NULL);
		return ((int64_t)time.tv_sec)*1000000 + time.tv_usec;
	}

	static void print_current_time(){
		timeval tv;
		tm t;
		gettimeofday(&tv, NULL);
		localtime_r(&(tv.tv_sec), &t);
		printf("[%d-%d-%d %d:%d:%d.%6.6d] ",
				t.tm_year+1900, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int)tv.tv_usec);
	}

};

#endif /* CMYSQLUTIL_H_ */
