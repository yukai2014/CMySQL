/*
 * CMysqlCommandPacket.h
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#ifndef C_MYSQL_COMMAND_PACKET_H_
#define C_MYSQL_COMMAND_PACKET_H_

#include <string.h>
#include <stdint.h>

#include "c_define.h"
#include "c_mysql_util.h"

// sizeof(CMysqlCommandPacket) = 24
// because virtual function hold 8 Bytes, regardless virtual function count
class CMysqlCommandPacket {
public:
	CMysqlCommandPacket();
	virtual ~CMysqlCommandPacket();

    inline void set_header(uint32_t pkt_length, uint8_t pkt_seq)
    {
      length_ = pkt_length;
      seq_ = pkt_seq;
    }

    inline void set_type(uint8_t type)
    {
      type_ = type;
    }

   inline void set_receive_ts(const int64_t &now)
    {
      receive_ts_ = 0;
    }
   inline void set_sql_command( char* const sql_command, int length)
   {
	   sql_command_ = sql_command;
	   sql_command_length_ = length;
   }
   inline char* get_sql_command(){
	   return sql_command_;
   }
private:
    uint32_t length_;
    uint8_t seq_;
    uint8_t type_;
    uint64_t receive_ts_;
    char *sql_command_;
    uint32_t sql_command_length_;
};

#endif /* CMYSQLCOMMANDPACKET_H_ */
