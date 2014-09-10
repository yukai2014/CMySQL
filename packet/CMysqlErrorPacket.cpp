

#include "CMysqlErrorPacket.h"
#include "../CMysqlUtil.h"

CMysqlErrorPacket::CMysqlErrorPacket():field_count_(0xff)
{
	errcode_ = 2000;
	sqlstate_ = "HY000";
}

CMysqlErrorPacket::~CMysqlErrorPacket()
{
}

int CMysqlErrorPacket::encode(char* buffer, int64_t length, int64_t& pos)
{
	int ret = C_SUCCESS;
	int64_t start_pos = pos;
	if (NULL == buffer || 0 >= length || pos < 0)
	{
		Logs::elog("invalid argument buffer=%p, length=%ld, pos=%ld",
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
				Logs::elog("serialize packet haader size failed, buffer=%p, buffer length=%ld, packet length=%d, pos=%ld",
						buffer, length, pkt_len, start_pos);
			}
			else if (C_SUCCESS != (ret = CMysqlUtil::store_int1(buffer, length, 2, start_pos)))
			{
				Logs::elog("serialize packet haader seq failed, buffer=%p, buffer length=%ld, seq number=%d, pos=%ld",
						buffer, length, 2, start_pos);
			}
		}
		else
		{
			Logs::elog("encode error packet data failed");
		}
	}
	return ret;

}
int CMysqlErrorPacket::serialize(char* buffer, int64_t len, int64_t& pos)
{
	int ret = C_SUCCESS;

	if (NULL == buffer || 0 >= len || pos < 0)
	{
		Logs::elog("invalid argument buffer=%p, length=%ld, pos=%ld",
				buffer, len, pos);
		ret = C_INVALID_ARGUMENT;
	}
	else
	{
		if (C_SUCCESS != (ret = CMysqlUtil::store_int1(buffer, len, field_count_, pos)))
		{
			Logs::elog("serialize field_count failed, buffer=%p, len=%ld, field_count_=%u, pos=%ld",
					buffer, len, field_count_, pos);
		}
		else if (C_SUCCESS != (ret = CMysqlUtil::store_int2(buffer, len, errcode_, pos)))
		{
			Logs::elog("serialize errcode failed, buffer=%p, len=%ld, errcode=%u, pos=%ld",
					buffer, len, errcode_, pos);
		}
		else if (C_SUCCESS != (ret = CMysqlUtil::store_int1(buffer, len, MARKER, pos)))
		{
			Logs::elog("serialize marker failed, buffer=%p, len=%ld, marker=%c, pos=%ld",
					buffer, len, '#', pos);
		}

		if (C_SUCCESS == ret)
		{
			if ((buffer + pos + SQLSTATE_SIZE) < buffer + len)
			{
				memcpy(buffer + pos, sqlstate_, SQLSTATE_SIZE);
				pos += SQLSTATE_SIZE;
			}
			else
			{
				Logs::elog("not enough buffer to serialize sqlstate, buffer=%p, len=%ld,"
						"sqlstate length=%ld,pos=%ld", buffer, len, SQLSTATE_SIZE, pos);
				ret = C_ERROR;
			}
		}

		if (C_SUCCESS == ret)
		{
			ret = CMysqlUtil::store_obstr_nzt(buffer, len, message_, pos);
			if (C_SUCCESS != ret)
			{
				Logs::elog("serialize message failed, buffer=%p, len=%ld, message length=%d,"
						"pos=%ld", buffer, len, message_.length(), pos);
			}
		}
	}
	return ret;
}

uint64_t CMysqlErrorPacket::get_serialize_size()
{
	uint64_t len = 0;
	len += 9;/*1byte field_count + 2bytes errno + 1byte sqlmarker + 5bytes sqlstate*/
	len += MAX_STORE_LENGTH + message_.length();
	return len;
}

int CMysqlErrorPacket::set_message(const string& message)
{
	int ret = C_SUCCESS;
	if ( 0 >= message.size())
	{
		Logs::elog("invalid argument message.ptr=%p, message.length()=%d",
				&message, message.length());
		ret = C_INVALID_ARGUMENT;
	}
	else
	{
		message_.assign(message);
	}
	return ret;
}
