/*
 * CMysqlFieldPacket.h
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#ifndef C_MYSQL_FIELD_PACKET_H_
#define C_MYSQL_FIELD_PACKET_H_

#include <iostream>
#include <stdint.h>
#include <string>

#include "CMysqlSQLPacket.h"
using namespace std;

class CMysqlFieldPacket: public CMysqlSQLPacket {
public:
	CMysqlFieldPacket();
	virtual ~CMysqlFieldPacket();

    int serialize(char* buffer, int64_t length, int64_t& pos);
    virtual uint64_t get_serialize_size(){
    	return 0;
    };

private:
	const char *catalog_;	    /* Catalog for table */
	const char *db_;            /* database name for table*/
	uint32_t length_;            /*Width of column (create length) */
	uint16_t flags_;            /* Div flags */
	uint8_t decimals_;         /* Number of decimals in field */
	uint16_t charsetnr_;        /* Character set */

	string tname_;
	string org_tname_;
	string cname_;
	string org_cname_;
	string type_;
};

#endif /* CMYSQLFIELDPACKET_H_ */
