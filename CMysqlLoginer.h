/*
 * CMysqlLoginer.h
 *
 *  Created on: 2014-9-6
 *      Author: imdb
 */

#ifndef C_MYSQL_LOGINER_H_
#define C_MYSQL_LOGINER_H_

#include "Logs.h"
#include "CMysqlDefine.h"
//#include "CMysqlServer.h"
#include "packet/CMysqlHandshakePacket.h"
#include "packet/CMysqlOKPacket.h"
#include "packet/CMysqlErrorPacket.h"
#include "CMysqlSession.h"

class CMysqlServer;

union CMysqlClientCapability {
	//			CMysqlClientCapability();
	uint32_t cap_flags;
	//ref:http://dev.mysql.com/doc/internals/en/connection-phase.html#packet-Protocol::CapabilityFlags
	struct CapabilityFlags {
		uint32_t CLIENT_LONG_PASSWORD:1;
		uint32_t CLIENT_FOUND_ROWS:1;
		uint32_t CLIENT_LONG_FLAG:1;
		uint32_t CLIENT_CONNECT_WITH_DB:1;
		uint32_t CLIENT_NO_SCHEMA:1;
		uint32_t CLIENT_COMPRESS:1;
		uint32_t CLIENT_ODBC:1;
		uint32_t CLIENT_LOCAL_FILES:1;
		uint32_t CLIENT_IGNORE_SPACE:1;
		uint32_t CLIENT_PROTOCOL_41:1;
		uint32_t CLIENT_INTERACTIVE:1;
		uint32_t CLIENT_SSL:1;
		uint32_t CLIENT_IGNORE_SIGPIPE:1;
		uint32_t CLIENT_TRANSACTIONS:1;
		uint32_t CLIENT_RESERVED:1;
		uint32_t CLIENT_SECURE_CONNECTION:1;
		uint32_t CLIENT_MULTI_STATEMENTS:1;
		uint32_t CLIENT_MULTI_RESULTS:1;
		uint32_t CLIENT_PS_MULTI_RESULTS:1;
		uint32_t CLIENT_PLUGIN_AUTH:1;
		uint32_t CLIENT_CONNECT_ATTRS:1;
		uint32_t CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA:1;
		uint32_t CLIENT_RESERVED_NOT_USE:10;
	}CapabilityFlags;
};

class CMysqlLoginer {
public:
	struct LoginInfo {
		union CMysqlClientCapability capability_;
		uint32_t max_message_length_;
		uint8_t character_set_;
		string user_name_;
		string auth_;
		string db_;
	};
public:
	CMysqlLoginer();
	~CMysqlLoginer();

	int shake_hand(const CMysqlSession& session);
	int login(const CMysqlSession& session);
	int check_authority(const CMysqlSession& session);
	int receive_authority(const CMysqlSession& session);
	int send_authority_res(const CMysqlSession& session);
	int check_authority();

	int write_data(int fd, char *buffer, int len);
	int read_data(int fd, char *buffer, int len);

	char *get_buffer(){		// TODO: use memory pool
		return buffer_;
	}
private:
	CMysqlServer *server_;
	char *buffer_;
	LoginInfo login_info_;

};

#endif /* C_MYSQL_LOGINER_H_ */
