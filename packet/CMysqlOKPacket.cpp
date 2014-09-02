/*
 * CMysqlOKPacket.cpp
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#include "CMysqlOKPacket.h"

#include <iostream>
#include <bitset>
using namespace std;

CMysqlOKPacket::CMysqlOKPacket()
		:field_count_(0x00),
		affected_rows_(0),
		insert_id_(0),
		server_status_(0x22),
		warning_count_(0){

}

CMysqlOKPacket::~CMysqlOKPacket() {

}

int CMysqlOKPacket::encode(char* buffer, int64_t length, int64_t& pos){
	int ret = C_SUCCESS;

	int64_t start_pos = pos;	//0
	pos += 4;	// 4
	ret = serialize(buffer,length,pos);
	uint32_t pkt_len = static_cast<uint32_t>(pos-start_pos-4);	//16-0-4 = 12
	ret = CMysqlUtil::store_int3(buffer,length,pkt_len,start_pos);
	ret = CMysqlUtil::store_int1(buffer,length,2,start_pos);
	return ret;
}

int CMysqlOKPacket::serialize(char* buffer, int64_t length, int64_t& pos){
	int ret = C_SUCCESS;
	/*
	 * ==================报文体============
	 * OK报文，值恒为0x00
	 * 受影响的行数0
	 * 索引ID值0
	 * 服务器状态2
	 * 警告计数0
	 * 服务器消息（可选）
	 * */
//	cout<<field_count_<<endl;
	ret = CMysqlUtil::store_int1(buffer,length,field_count_,pos);	//pos =5
//	cout<<affected_rows_<<endl;
	ret = CMysqlUtil::store_length(buffer,length,affected_rows_,pos);	// 6
//	cout<<insert_id_<<endl;
	ret = CMysqlUtil::store_length(buffer,length,insert_id_,pos);	// 7
//	cout<<server_status_<<endl;
	ret = CMysqlUtil::store_int2(buffer,length,server_status_,pos);	// 9
//	cout<<warning_count_<<endl;
	ret = CMysqlUtil::store_int2(buffer,length,warning_count_,pos);	// 11

	{	// for test	-Yu
		cout<<"ret: ";
		for (int i = 0; i < 16; ++i){
			bitset<8> a((int)buffer[i]);
			cout<<a<<"-";
		}
		cout<<endl;
		string str(buffer);
		cout<<"传输前的报文内容： "<<str.length()<<endl;
	}

	const char *hello="hello";
	memcpy(buffer+pos,hello,5);
	pos=pos+5;		// 16
//	ret = CMysqlUtil::store_obstr(buffer,length,message_,pos);
	return ret;
}
