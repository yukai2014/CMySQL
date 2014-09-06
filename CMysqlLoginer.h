/*
 * CLoginer.h
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

class CMysqlServer;

class CMysqlLoginer
{
public:
	CMysqlLoginer();
	~CMysqlLoginer();

	int shake_hand(int fd);
	int login(int fd);
private:
	CMysqlServer *server_;

};

#endif /* C_MYSQL_LOGINER_H_ */
