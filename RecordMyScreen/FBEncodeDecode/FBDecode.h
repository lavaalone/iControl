#ifndef _FBDECODE_H
#define _FBDECODE_H

#include <map>
#include <string>
#include <list>
#include <vector>

#include "../Misc/utf8.h"

class FBData
{
public:
    BYTE    _type;
    BYTE    _sub_type;
    int     _len;
    BYTE*   _data;

    FBData(BYTE* data, int len, BYTE type)
    {
        _data = data;
        _len = len;
        _type = type;
		_sub_type = 0;
    }

	FBData(BYTE* data, int len, BYTE type, BYTE sub_type)
    {
        _data = data;
        _len = len;
        _type = type;
		_sub_type = sub_type;
    }

    ~FBData()
    {
        delete[] _data;
    }
};

class FBDecode
{
	//data type
	#define		FBDECODE_STRING_UTF8	1
	#define		FBDECODE_INT8			2
	#define		FBDECODE_INT16			3
	#define		FBDECODE_INT32			4
	#define		FBDECODE_INT64			5
	#define		FBDECODE_FLOAT			6
	#define		FBDECODE_DOUBLE			7
	#define		FBDECODE_BINARY			8
	#define		FBDECODE_STRING_ANSI	9
	#define		FBDECODE_STRING_UNICODE	10
	#define		FBDECODE_ARRAY			11

private:

	std::map<UINT32, FBData*>	_map;

	void ClearMap()
	{
        if (_map.size() > 0)
		{
			std::map<UINT32,FBData*>::iterator itr = _map.begin();
            std::map<UINT32,FBData*>::iterator itr_end = _map.end();

			for (; itr != itr_end; itr++)
			{
				FBData* data = itr->second;
				delete data;
			}

			_map.clear();
		}
	}

public:

	FBDecode()
	{

	}

	~FBDecode()
	{
		if (_map.size() > 0)
		{
			std::map<UINT32,FBData*>::iterator itr = _map.begin();
            std::map<UINT32,FBData*>::iterator itr_end = _map.end();

			for (; itr != itr_end; itr++)
			{
				FBData* data = itr->second;
				delete data;
			}
		}
	}

	bool Decode(BYTE* buf, int length)
	{
	    ClearMap();

		int offset = 0;
        UINT32 key = 0;
        BYTE* val = NULL;
        FBData* data = NULL;
        UINT32 len = 0;

		while (offset < length)
		{
			//read key
            BYTE* p = (BYTE*)&key;
            p[3] = buf[offset++];
            p[2] = buf[offset++];
            p[1] = buf[offset++];
            p[0] = buf[offset++];

			//read type len
			int type = buf[offset++]&0xFF;

			//read value
			switch (type)
			{
				case FBDECODE_INT8:
					val = new BYTE[1];
					val[0] = buf[offset++];

					data = new FBData(val, 1, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));

					break;

				case FBDECODE_INT16:
					val = new BYTE[2];
					memcpy(val, buf + offset, 2);

                    data = new FBData(val, 2, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));

                    offset += 2;
					break;

				case FBDECODE_INT32:
					val = new BYTE[4];
					memcpy(val, buf + offset, 4);

                    data = new FBData(val, 4, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));

                    offset += 4;
					break;

				case FBDECODE_INT64:
					val = new BYTE[8];
					memcpy(val, buf + offset, 8);

                    data = new FBData(val, 8, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));

                    offset += 8;
					break;

				case FBDECODE_FLOAT:
					val = new BYTE[4];
					memcpy(val, buf + offset, 4);

                    data = new FBData(val, 4, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));

                    offset += 4;
					break;

				case FBDECODE_STRING_UTF8:
					len = 0;
				    p = (BYTE*)&len;
				    p[1] = buf[offset++];
				    p[0] = buf[offset++];

					val = new BYTE[len];
					memcpy(val, buf + offset, len);

                    data = new FBData(val, len, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));
                    offset += len;
					break;

				case FBDECODE_BINARY:
					len = ReadVarInt(buf, offset);

					val = new BYTE[len];
					memcpy(val, buf + offset, len);

                    data = new FBData(val, len, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));

                    offset += len;
					break;

                case FBDECODE_STRING_ANSI:
					len = ReadVarInt(buf, offset);

					val = new BYTE[len];
					memcpy(val, buf + offset, len);

                    data = new FBData(val, len, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));

					offset += len;
                    break;

                case FBDECODE_STRING_UNICODE:
					len = ReadVarInt(buf, offset);
                    len <<= 1;

					val = new BYTE[len];
					memcpy(val, buf + offset, len);

                    data = new FBData(val, len, type);

					_map.insert(std::pair<UINT32,FBData*>(key, data));

					offset += len;
                    break;

				case FBDECODE_ARRAY:
					if (DecodeArray(key, buf, offset, length) == false)
					{
						return false;
					}
					break;

				default:
					return false;
			}

			if (offset > length)
            {
                return false;
            }
		}

		return true;
	}

	bool DecodeArray(UINT32 key, BYTE* buf, int& offset, int length)
	{
		int subtype = buf[offset++]&0xFF;

		UINT32 len = 0;
		BYTE* p = NULL;

		switch (subtype)
		{
			case FBDECODE_INT8:
			{
				len = ReadVarInt(buf, offset);

				BYTE* value = new BYTE[len];
				memcpy(value, buf + offset, len);

				FBData* data = new FBData(value, len, FBDECODE_ARRAY, subtype);

				_map.insert(std::pair<UINT32,FBData*>(key, data));

				offset += len;
				break;
			}

			case FBDECODE_INT16:
			{
				len = ReadVarInt(buf, offset);
				len <<= 1;

				BYTE* value = new BYTE[len];
				memcpy(value, buf + offset, len);

				FBData* data = new FBData(value, len, FBDECODE_ARRAY, subtype);

				_map.insert(std::pair<UINT32,FBData*>(key, data));

				offset += len;

				break;
			}

			case FBDECODE_INT32:
			{
				len = ReadVarInt(buf, offset);
				len <<= 2;

				BYTE* value = new BYTE[len];
				memcpy(value, buf + offset, len);

				FBData* data = new FBData(value, len, FBDECODE_ARRAY, subtype);

				_map.insert(std::pair<UINT32,FBData*>(key, data));

				offset += len;

				break;
			}

			case FBDECODE_INT64:
			{
				len = ReadVarInt(buf, offset);
				len <<= 3;

				BYTE* value = new BYTE[len];
				memcpy(value, buf + offset, len);

				FBData* data = new FBData(value, len, FBDECODE_ARRAY, subtype);

				_map.insert(std::pair<UINT32,FBData*>(key, data));

				offset += len;

				break;
			}

			case FBDECODE_FLOAT:
			{
				len = ReadVarInt(buf, offset);
				len <<= 2;

				BYTE* value = new BYTE[len];
				memcpy(value, buf + offset, len);

				FBData* data = new FBData(value, len, FBDECODE_ARRAY, subtype);

				_map.insert(std::pair<UINT32,FBData*>(key, data));

				offset += len;

				break;
			}

			case FBDECODE_STRING_UTF8:
			{
				int off = offset;

				len = ReadVarInt(buf, offset);

				int str_len = 0;
				for (int i = 0; i < len; i++)
				{
					p = (BYTE*)&str_len;
					p[1] = buf[offset++];
					p[0] = buf[offset++];

					offset += str_len;
				}

				int data_len = offset - off;

				BYTE* value = new BYTE[data_len];
				memcpy(value, buf + off, data_len);

				FBData* data = new FBData(value, data_len, FBDECODE_ARRAY, subtype);

				_map.insert(std::pair<UINT32,FBData*>(key, data));

				break;
			}

			case FBDECODE_BINARY:
			{
				int off = offset;

				len = ReadVarInt(buf, offset);

				int str_len = 0;
				for (int i = 0; i < len; i++)
				{
					str_len = ReadVarInt(buf, offset);
					offset += str_len;
				}

				int data_len = offset - off;

				BYTE* value = new BYTE[data_len];
				memcpy(value, buf + off, data_len);

				FBData* data = new FBData(value, data_len, FBDECODE_ARRAY, subtype);

				_map.insert(std::pair<UINT32,FBData*>(key, data));

				break;
			}

			default:
				return false;
		}

		return true;
	}


	bool HasKey(const char* key)
	{
		UINT32 k = MurmurHash(key);

		std::map<UINT32,FBData*>::iterator it = _map.find(k);

	    if (it == _map.end())
		{
            return false;
		}

        return true;
	}

	std::list<UNICHAR> GetString(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        std::list<UNICHAR> str;

        if (val == NULL) return str;

        BYTE type = val->_type;

        if (type == FBDECODE_STRING_UTF8)
        {
            utf8::utf8to16<std::back_insert_iterator<std::list<UNICHAR> >, BYTE*> (val->_data, val->_data + val->_len, std::back_inserter(str));
        }
        else if (type == FBDECODE_STRING_ANSI)
        {
            UINT16 len = val->_len;

            for (int i = 0; i < len; i++)
            {
                str.push_back(val->_data[i]);
            }
        }
        else if (type == FBDECODE_STRING_UNICODE)
        {
            UINT16 len = val->_len/2;

            for (int i = 0; i < len; i++)
            {
                str.push_back(((val->_data[2*i]&0xFF)<<8) |
                              (val->_data[2*i + 1]&0xFF));
            }
        }

		return str;
	}

	std::basic_string<UNICHAR> GetStdString(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        std::basic_string<UNICHAR> str;

        if (val == NULL) return str;

        BYTE type = val->_type;
        if (type == FBDECODE_STRING_UTF8)
        {
            utf8::utf8to16<std::back_insert_iterator<std::basic_string<UNICHAR> >, BYTE*>(   val->_data,
                                                                                            (val->_data) + (val->_len),
                                                                                            std::back_inserter(str));
        }
        else if (type == FBDECODE_STRING_ANSI)
        {
            int len = val->_len;

            for (int i = 0; i < len; i++)
            {
                str.push_back(val->_data[i]);
            }
        }
        else if (type == FBDECODE_STRING_UNICODE)
        {
            int len = val->_len;

            for (int i = 0; i < len; i++)
            {
                str.push_back(((val->_data[2*i]&0xFF)<<8) |
                              (val->_data[2*i + 1]&0xFF));
            }
        }

		return str;
	}

	std::string GetAnsiString(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* data = _map[k];

        std::string str;

        if (data == NULL) return str;

        if (data->_type == FBDECODE_STRING_ANSI)
        {
            UINT16 len = data->_len;

            for (int i = 0; i < len; i++)
            {
                str.push_back(data->_data[i]);
            }
        }

        return str;
	}

	std::list<std::basic_string<UNICHAR> > GetStringArray(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_ARRAY && val->_sub_type == FBDECODE_STRING_UTF8)
        {
			int offset = 0;
			BYTE* data = val->_data;

			std::list<std::basic_string<UNICHAR> > array;

			int size = ReadVarInt(data, offset);

			int str_len = 0;
			std::basic_string<UNICHAR> str;
			BYTE* p = NULL;
			for (int i = 0; i < size; i++)
			{
				p = (BYTE*)&str_len;
				p[1] = data[offset++];
				p[0] = data[offset++];

                str.clear();
                utf8::utf8to16<std::back_insert_iterator<std::basic_string<UNICHAR> >, BYTE*>(   data + offset,
                                                                                                data + offset + str_len,
                                                                                                std::back_inserter(str));
				array.push_back(str);

				offset += str_len;
			}

            return array;
        }
		else
		{
			std::list<std::basic_string<UNICHAR> > array;
            return array;
		}
	}

	std::vector<BYTE> GetBinary(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_BINARY)
        {
			std::vector<BYTE> bin(val->_data, val->_data + val->_len);

            return bin;
        }
		else
		{
			std::vector<BYTE> bin;
            return bin;
		}
	}

	BYTE* GetBinary(const char* key, int& length)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_BINARY)
        {
			length = val->_len;

            return val->_data;
        }
		else
		{
			length = 0;
            return NULL;
		}
	}

	std::list<std::vector<BYTE> > GetBinaryArray(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_ARRAY && val->_sub_type == FBDECODE_BINARY)
        {
			int offset = 0;
			BYTE* data = val->_data;

			std::list<std::vector<BYTE> > array;

			int size = ReadVarInt(data, offset);

			int bin_len = 0;
			for (int i = 0; i < size; i++)
			{
				bin_len = ReadVarInt(data, offset);

				array.push_back(std::vector<BYTE>(data + offset, data + offset + bin_len));

				offset += bin_len;
			}

            return array;
        }
		else
		{
			std::list<std::vector<BYTE> > array;
            return array;
		}
	}

	INT8 GetInt8(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_INT8)
        {
            return val->_data[0];
        }

        return 0;
	}

	std::vector<INT8> GetInt8Array(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

		if (val != NULL && val->_type == FBDECODE_ARRAY && val->_sub_type == FBDECODE_INT8)
		{
			int len = val->_len;
			INT8* data = (INT8*)(val->_data);

			std::vector<INT8> array(data, data + len);

			return array;
		}
		else
		{
			std::vector<INT8> array;

			return array;
		}
	}

	INT16 GetInt16(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_INT16)
        {
            INT16 ret = 0;

            BYTE* p = (BYTE*)&ret;
            BYTE* data = val->_data;

            p[1] = data[0];
            p[0] = data[1];

            return ret;
        }

		return 0;
	}

	std::vector<INT16> GetInt16Array(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

		if (val != NULL && val->_type == FBDECODE_ARRAY && val->_sub_type == FBDECODE_INT16)
		{
			int len = val->_len;
			BYTE* data = val->_data;

			std::vector<INT16> array;

			INT16 a;
			BYTE* p = (BYTE*)&a;

			for (int i = 0; i < len; i += 2, data += 2)
			{
				p[1] = data[0];
				p[0] = data[1];

				array.push_back(a);
			}

			return array;
		}
		else
		{
			std::vector<INT16> array;

			return array;
		}
	}

	INT32 GetInt32(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_INT32)
        {
            INT32 ret = 0;

            BYTE* p = (BYTE*)&ret;
            BYTE* data = val->_data;

            p[3] = data[0];
            p[2] = data[1];
            p[1] = data[2];
            p[0] = data[3];

            return ret;
        }

		return 0;
	}

	std::vector<INT32> GetInt32Array(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

		if (val != NULL && val->_type == FBDECODE_ARRAY && val->_sub_type == FBDECODE_INT32)
		{
			int len = val->_len;
			BYTE* data = val->_data;

			std::vector<INT32> array;

			INT32 a;
			BYTE* p = (BYTE*)&a;
			for (int i = 0; i < len; i += 4, data += 4)
			{
				p[3] = data[0];
				p[2] = data[1];
				p[1] = data[2];
				p[0] = data[3];

				array.push_back(a);
			}

			return array;
		}
		else
		{
			std::vector<INT32> array;

			return array;
		}
	}

	INT64 GetInt64(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_INT64)
        {
            INT64 ret = 0;
            BYTE* p = (BYTE*)&ret;
            BYTE* data = val->_data;

            p[7] = data[0];
            p[6] = data[1];
            p[5] = data[2];
            p[4] = data[3];
            p[3] = data[4];
            p[2] = data[5];
            p[1] = data[6];
            p[0] = data[7];

            return ret;
        }

		return 0;
	}

	std::vector<INT64> GetInt64Array(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

		if (val != NULL && val->_type == FBDECODE_ARRAY && val->_sub_type == FBDECODE_INT64)
		{

			int len = val->_len;
			BYTE* data = val->_data;

			std::vector<INT64> array;

			INT64 a;
			BYTE* p = (BYTE*)&a;
			for (int i = 0; i < len; i += 8, data += 8)
			{
				p[7] = data[0];
				p[6] = data[1];
				p[5] = data[2];
				p[4] = data[3];
				p[3] = data[4];
				p[2] = data[5];
				p[1] = data[6];
				p[0] = data[7];

				array.push_back(a);
			}

			return array;
		}
		else
		{
			std::vector<INT64> array;

			return array;
		}
	}

	float GetFloat(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

        if (val != NULL && val->_type == FBDECODE_FLOAT)
        {
            float ret = 0;
            BYTE* p = (BYTE*)&ret;
            BYTE* data = val->_data;

            p[3] = data[0];
            p[2] = data[1];
            p[1] = data[2];
            p[0] = data[3];

            return ret;
        }

		return 0;
	}


	std::vector<float> GetFloatArray(const char* key)
	{
		UINT32 k = MurmurHash(key);

		FBData* val = _map[k];

		if (val != NULL && val->_type == FBDECODE_ARRAY && val->_sub_type == FBDECODE_FLOAT)
		{
			int len = val->_len;
			BYTE* data = val->_data;

			std::vector<float> array;

			float a;
			BYTE* p = (BYTE*)&a;
			for (int i = 0; i < len; i += 4, data += 4)
			{
				p[3] = data[0];
				p[2] = data[1];
				p[1] = data[2];
				p[0] = data[3];

				array.push_back(a);
			}

			return array;
		}
		else
		{
			std::vector<float> array;

			return array;
		}
	}

	private: int ReadVarInt(BYTE* buf, int& len)
	{
		int v = 0;
		int i = 0;
        int b = 0;

		do
		{
			b = buf[len++]&0xFF;

			v |= (b&0x7F)<<i;

			i += 7;
		}
		while (b > 127);

		return v;
	}

	private: UINT32 MurmurHash(const char* data)
	{
		int len = strlen(data);

		const int nblocks = len >> 2;

		UINT32 h1 = 123456;

		const UINT32 c1 = 0xcc9e2d51;
		const UINT32 c2 = 0x1b873593;

		//----------
		// body

		const UINT32 * blocks = (const UINT32 *)(data + nblocks*4);

		for(int i = -nblocks; i; i++)
		{
			UINT32 k1 = blocks[i];

			k1 *= c1;
			k1 = (k1 << 15) | (k1 >> 17);

			k1 *= c2;

			h1 ^= k1;
			h1 = (h1 << 13) | (h1 >> 19);
			h1 = h1*5+0xe6546b64;
		}

		//----------
		// tail

		const uint8_t * tail = (const uint8_t*)(data + nblocks*4);

		UINT32 k1 = 0;

		switch (len&3)
		{
			case 3: k1 ^= tail[2] << 16;
			case 2: k1 ^= tail[1] << 8;
			case 1: k1 ^= tail[0];
		};

		k1 *= c1;
		k1 = (k1 << 15) | (k1 >> 17);
		k1 *= c2;
		h1 ^= k1;

		//----------
		// finalization

		h1 ^= len;

		h1 ^= h1 >> 16;
		h1 *= 0x85ebca6b;
		h1 ^= h1 >> 13;
		h1 *= 0xc2b2ae35;
		h1 ^= h1 >> 16;

		return h1;
	}
};


#endif
