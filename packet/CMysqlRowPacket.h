/*
 * CMysqlRowPacket.h
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#ifndef C_MYSQL_ROW_PACKET_H_
#define C_MYSQL_ROW_PACKET_H_

#include "CMysqlSqlPacket.h"
#include <stdint.h>

class CMysqlRowPacket: public CMysqlSQLPacket {
public:
	CMysqlRowPacket();
	virtual ~CMysqlRowPacket();

    int serialize(char* buffer, int64_t length, int64_t& pos);
    virtual uint64_t get_serialize_size() {
    	return 0;
    };

private:
    const string row_;
};

#endif /* CMYSQLROWPACKET_H_ */
