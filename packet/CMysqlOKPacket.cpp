
#include "CMysqlOKPacket.h"
#include <bitset>


CMysqlOKPacket::CMysqlOKPacket()
:field_count_(0x00),
 affected_rows_(0),
 insert_id_(0),
 server_status_(0x22),
 warning_count_(0)
{
}

CMysqlOKPacket::~CMysqlOKPacket()
{
//	str_buf_.clear();
}

int CMysqlOKPacket::set_message(string& message)
{
	int ret = C_SUCCESS;
	if (message.empty() || 0 > message.length())
	{
		//Logs::elog
	ELOG("invalid argument message.ptr=%p, message.length=%d",
				&message, message.length());
		ret = C_ERROR;
	}
	else
	{
//		ret = str_buf_.write_string(message, &message_);
		message_.assign(message);
		if (C_SUCCESS != ret)
		{
			//Logs::elog
	ELOG("write string to messaget failed");
		}
	}
	return ret;
}

int CMysqlOKPacket::encode(char* buffer, int64_t length, int64_t& pos)
{
	//Logs::log
	LOG("in CMysqlOKPacket::encode Function");
	int ret = C_SUCCESS;
	int64_t start_pos = pos;
	if (NULL == buffer || 0 >= length || pos < 0)
	{
		//Logs::elog
	ELOG("invalid argument buffer=%p, length=%ld, pos=%ld",
				buffer, length, pos);
		ret = C_INVALID_ARGUMENT;
	}
	else
	{
		pos += C_MYSQL_PACKET_HEADER_SIZE;
		ret = serialize(buffer, length, pos);
		if (C_SUCCESS == ret)
		{
			uint32_t pkt_len = static_cast<uint32_t>(pos - start_pos - C_MYSQL_PACKET_HEADER_SIZE);
			if (C_SUCCESS != (ret = CMysqlUtil::store_int3(buffer, length, pkt_len, start_pos)))
			{
				//Logs::elog
	ELOG("serialize packet header size failed, buffer=%p, buffer length=%ld, packet length=%d, pos=%ld",
						buffer, length, pkt_len, start_pos);
			}
			else if (C_SUCCESS != (ret = CMysqlUtil::store_int1(buffer, length, 2, start_pos)))
			{
				//Logs::elog
	ELOG("serialize packet haader seq failed, buffer=%p, buffer length=%ld, seq number=%d, pos=%ld",
						buffer, length, 2, start_pos);
			}
		}
		else
		{
			//Logs::elog
	ELOG("encode ok packet data failed");
		}
	}

//	{
//		cout<<"received authority data: ";
//		for (int i = 0; i < 40; ++i){
//			bitset<8> a((int)buffer[i]);
//			cout<<a<<"-";
//		}
//		cout<<endl;
//	}

	return ret;
}

uint64_t CMysqlOKPacket::get_serialize_size()
{
	uint64_t len = 0;
	len += 5; /*1byte field_count + 2bytes server_status + 2bytes warning_count see MySQL protocol*/
	len += 9; /*max length for unit64_t*/
	len += 9; /*max length for store_length*/
	len += 9 + message_.length();
	return len;
}

int CMysqlOKPacket::serialize(char* buffer, int64_t length, int64_t& pos)
{
	int ret = C_SUCCESS;

	if (NULL == buffer || 0 >= length || pos < 0)
	{
		//Logs::elog
	ELOG("invalid argument buffer=%p, length=%ld, pos=%ld",
				buffer, length, pos);
		ret = C_INVALID_ARGUMENT;
	}
	else
	{
		if (C_SUCCESS != (ret = CMysqlUtil::store_int1(buffer, length, field_count_, pos)))
		{
			//Logs::elog
	ELOG("serialize field_count failed, buffer=%p, length=%ld, field_count=%u,"
					"pos=%ld", buffer, length, field_count_, pos);
		}
		else if (C_SUCCESS != (ret = CMysqlUtil::store_length(buffer, length, affected_rows_, pos)))
		{
			//Logs::elog
	ELOG("serialize affected_row failed, buffer=%p, length=%ld, affected_rows=%lu,"
					"pos=%ld", buffer, length, affected_rows_, pos);
		}
		else if (C_SUCCESS != (ret = CMysqlUtil::store_length(buffer, length, insert_id_, pos)))
		{
			//Logs::elog
	ELOG("serialize insert_id failed, buffer=%p, length=%ld, insert_id=%lu,"
					"pos=%ld", buffer, length, insert_id_, pos);
		}
		else if (C_SUCCESS != (ret = CMysqlUtil::store_int2(buffer, length, server_status_, pos)))
		{
			//Logs::elog
	ELOG("serialize server_status failed, buffer=%p, length=%ld, server_status=%u,"
					"pos=%ld", buffer, length, server_status_, pos);
		}
		else if (C_SUCCESS != (ret = CMysqlUtil::store_int2(buffer, length, warning_count_, pos)))
		{
			//Logs::elog
	ELOG("serialize warning_count failed, buffer=%p, length=%ld, warning_count=%u,"
					"pos=%ld", buffer, length, warning_count_, pos);
		}
		else if (0 != message_.length())
		{
			if (C_SUCCESS != (ret = CMysqlUtil::store_obstr(buffer, length, message_, pos)))
			{
				//Logs::elog
	ELOG("serialize message failed, buffer=%p, length=%ld, insert_id=%lu,"
						"pos=%ld", buffer, length, insert_id_, pos);
			}
		}
	}
	return ret;
}
