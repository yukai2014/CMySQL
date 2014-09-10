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

class CMysqlLoginer
{
public:
	struct LoginInfo
	{
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
		memset(buffer_, 0, sizeof(buffer_));
		return buffer_;
	}
private:
	CMysqlServer *server_;
	char *buffer_;
	LoginInfo login_info_;

};

#endif /* C_MYSQL_LOGINER_H_ */
