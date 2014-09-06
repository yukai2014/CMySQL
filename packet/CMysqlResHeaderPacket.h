/*
 * CMysqlResHeaderPacket.h
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#ifndef C_MYSQL_RES_HEADER_PACKET_H_
#define C_MYSQL_RES_HEADER_PACKET_H_

#include "../CMysqlUtil.h"
#include "CMysqlSqlPacket.h"
#include <stdint.h>

class CMysqlResHeaderPacket: public CMysqlSQLPacket{
public:
	CMysqlResHeaderPacket();
	virtual ~CMysqlResHeaderPacket();

	/* encode函数就是加header */
	int serialize(char* buffer, int64_t len, int64_t& pos);
	inline void set_field_count(int count) {
		field_count_=count;
	}
	inline uint64_t get_field_count() const;
	uint64_t get_serialize_size();

private:
	uint64_t field_count_;
};

#endif /* CMYSQLRESHEADERPACKET_H_ */
