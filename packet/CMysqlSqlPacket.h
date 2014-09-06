/*
 * CMysqlSQLPacket.h
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#ifndef C_MYSQL_SQL_PACKET_H_
#define C_MYSQL_SQL_PACKET_H_

#include "../CMysqlDefine.h"
#include "../CMysqlUtil.h"

#include <stdint.h>
#include <iostream>
using namespace std;


class CMysqlSQLPacket {
public:
	CMysqlSQLPacket();
	virtual ~CMysqlSQLPacket();

	int encode(char* buffer, int64_t length, int64_t& pos);
	virtual int serialize(char* buffer, int64_t length, int64_t& pos)=0;
};

#endif /* CMYSQLSQLPACKET_H_ */
