/*
 * CMysqlLoginer.cpp
 *
 *  Created on: 2014-9-6
 *      Author: imdb
 */
#include "CMysqlLoginer.h"
#include "CMysqlServer.h"

CMysqlLoginer::CMysqlLoginer(){

}

CMysqlLoginer::~CMysqlLoginer(){

}

int CMysqlLoginer::login(int fd){
	Logs::log("start to shake hand");
	int ret;
	ret = shake_hand(fd);

	return C_SUCCESS;
}

int CMysqlLoginer::shake_hand(int fd){
	int ret;
	CMysqlHandshakePacket shakehand_packet;
	shakehand_packet.set_thread_id(pthread_self());


	int64_t len = MAX_PACKET_SIZE;
	int64_t pos = 0;
	ret = shakehand_packet.serialize(server_->temp_buffer, len, pos);

	return C_SUCCESS;
}
