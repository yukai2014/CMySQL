/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * CMysqlErrorPacket.h is for what ...
 *
 * Version: ***: ob_mysql_error_packet.h  Wed Aug  1 11:33:32 2012 fangji.hcm Exp $
 *
 * Authors:
 *   Author fangji
 *   Email: fangji.hcm@taobao.com
 *     -some work detail if you want
 *
 *
 *	modified by YuKai		-- 2014.9.10
 *
 */
#ifndef C_MYSQL_ERROR_PACKET_H_
#define C_MYSQL_ERROR_PACKET_H_

#include <iostream>
#include <string.h>
using namespace std;

#include "CMysqlPacketHeader.h"
#include "CMysqlSQLPacket.h"
#include "../CMysqlState.h"
#include "../CMysqlDefine.h"
#include "../CMysqlUtil.h"
#include "../Logs.h"

class CMysqlErrorPacket : public CMysqlSQLPacket
{
public:
	static const uint64_t SQLSTATE_SIZE = 5;
	static const uint8_t MARKER = '#';
public:
	CMysqlErrorPacket();
	virtual ~CMysqlErrorPacket();

	int serialize(char* buffer, int64_t len, int64_t& pos);

	uint64_t get_serialize_size();
	virtual int encode(char *buffer, int64_t length, int64_t & pos);

	int set_message(const string& message);

	/**
	 * set error code and sql state string.
	 *
	 * @note OB_ERROR shouldn't passing to this function for
	 * hostorical reason.
	 *
	 * @note It will make a negation and truncate it from 4 bytes
	 * (int) to 2 bytes (uint16_t) for fitting msyql protocol.
	 *
	 * @param errcode oceanbase error code
	 */
	int set_errcode(int errcode)
	{
		errcode_ = static_cast<uint16_t>(-errcode);
		return set_sqlstate(CMysqlState::get_instance().get_jdbc_state(errcode));
	}

private:
	inline void set_errcode(int16_t code)
	{
		errcode_ = code;
	}

	int set_sqlstate(const char *sqlstate)
	{
		int ret = C_SUCCESS;
		if (SQLSTATE_SIZE == strlen(sqlstate))
		{
			sqlstate_ = sqlstate;
		}
		else
		{
			ret = C_INVALID_ARGUMENT;
		}
		return ret;
	}

	//for test
	inline uint8_t get_field_count() const
	{
		return field_count_;
	}

	inline int16_t get_err_code() const
	{
		return errcode_;
	}

	inline const char* get_sql_state()
	{
		return sqlstate_;
    }

	inline string& get_message()
	{
		return message_;
	}

private:
	uint8_t field_count_;   /* Always 0xff */
	int16_t errcode_;
	const char *sqlstate_;
	string message_;
};
#endif	// CMysqlErrorPacket.h
