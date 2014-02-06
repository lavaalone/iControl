#ifndef _FBENCODE_H
#define _FBENCODE_H

#include <string.h>
#include <list>
#include <vector>

#include "utf8.h"

class FBEncode
{
	//data type
	#define		FBENCODE_STRING_UTF8	1
	#define		FBENCODE_INT8			2
	#define		FBENCODE_INT16			3
	#define		FBENCODE_INT32			4
	#define		FBENCODE_INT64			5
	#define		FBENCODE_FLOAT			6
	#define		FBENCODE_DOUBLE			7
	#define		FBENCODE_BINARY			8
	#define		FBENCODE_STRING_ANSI	9
	#define		FBENCODE_STRING_UNICODE	10
	#define		FBENCODE_ARRAY			11

private:
	std::list<BYTE*>	    _data;
    std::list<int>	    	_data_len;
    std::list<uint32_t>	    _keys;

	int 				    _output_size;

public:

	FBEncode()
	{
		_output_size = 0;
	}

	~FBEncode()
	{
	    std::list<BYTE*>::iterator iter;
        std::list<BYTE*>::iterator iter_end = _data.end();
        for (iter = _data.begin(); iter != iter_end; iter++)
        {
            delete[] (*iter);
        }
	}

	void Clear()
	{
        if (_data.size() > 0)
        {
            std::list<BYTE*>::iterator iter;
            std::list<BYTE*>::iterator iter_end = _data.end();
            for (iter = _data.begin(); iter != iter_end; iter++)
            {
                delete[] (*iter);
            }
            _data.clear();
            _data_len.clear();
            _keys.clear();
            _output_size = 0;
        }

	}

	void GetBuffer(BYTE* buf)
	{
		int offset = 0;

        std::list<BYTE*>::iterator iter_data = _data.begin();
        std::list<BYTE*>::iterator iter_data_end = _data.end();
        std::list<int>::iterator iter_len = _data_len.begin();

        for ( ; iter_data != iter_data_end; iter_data++, iter_len++)
        {
            BYTE* data = *iter_data;

            if (data)
            {
                int data_len = *iter_len;

                memcpy(buf + offset, data, data_len);
                offset += data_len;
            }
        }
	}

	int GetBufferLength()
	{
		return _output_size;
	}

	bool AddStringANSI(const char* key, const char* value)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		UINT16 value_len = strlen(value);

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(value_len, var_int, var_int_len);

		//alloc data
		int data_len = 4 + 1 + var_int_len + value_len;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_STRING_ANSI;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//write value data
		memcpy(p, value, value_len);

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddStringUTF8(const char* key, UNICHAR* value, UINT16 length)
	{
	    uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		//encode utf8
		std::list<BYTE> utf8_str;
		utf8::utf16to8<UNICHAR*, std::back_insert_iterator<std::list<BYTE> > >(value, value + length, std::back_inserter(utf8_str));

		int utf8_len = utf8_str.size();

		//alloc data
		int data_len = 4 + 1 + 2 + utf8_len;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_STRING_UTF8;
		p++;

		//write value len
		v = (BYTE*)(&utf8_len);
		*p = v[1];
		p++;
		*p = v[0];
		p++;

		//write value data
		std::list<BYTE>::iterator iter_end = utf8_str.end();
		for (std::list<BYTE>::iterator iter = utf8_str.begin(); iter != iter_end; iter++)
		{
			*p = *iter;
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddStringUnicode(const char* key, UNICHAR* value, UINT16 length)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(length, var_int, var_int_len);

		//alloc data
		int data_len = 4 + 1 + var_int_len + 2*length;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_STRING_UNICODE;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//write value data
		memcpy(p, value, length*2);

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AppendBinary(BYTE* bin, int length, std::list<uint32_t> keys)
	{
		std::list<uint32_t>::iterator iter1_end = keys.end();

		for (std::list<uint32_t>::iterator iter1 = keys.begin(); iter1 != iter1_end; iter1++)
		{
			//check duplicate
			for (std::list<uint32_t>::iterator iter2 = _keys.begin(); iter2 != _keys.end(); iter2++)
			{
				if (*iter2 == *iter1)
				{
					printf("FBENCODE ERROR: AppendBinary has one duplicate !");
					return false;
				}
			}

			_keys.push_back(*iter1);
		}

		_data.push_back(bin);
		_data_len.push_back(length);

		_output_size += length;

		return true;
	}

	bool AddBinary(const char* key, BYTE* value, UINT16 length)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(length, var_int, var_int_len);

		//alloc data
		int data_len = 4 + 1 + var_int_len + length;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_BINARY;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//write value data
		memcpy(p, value, length);

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}
    
    
	bool AddLongBinary(const char* key, BYTE* value, INT32 length)
	{
		uint32_t k = MurmurHash(key);
        
		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);
            
			return false;
		}
        
		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(length, var_int, var_int_len);
        
		//alloc data
		int data_len = 4 + 1 + var_int_len + length;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;
        
		//write key
		BYTE* v = (BYTE*)(&k);
        
		*p = v[3];
		p++;
        
		*p = v[2];
		p++;
        
		*p = v[1];
		p++;
        
		*p = v[0];
		p++;
        
		//write data type
		*p = FBENCODE_BINARY;
		p++;
        
		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;
        
		//write value data
		memcpy(p, value, length);
        
		_data.push_back(data);
		_data_len.push_back(data_len);
        
		_output_size += data_len;
        
		return true;
	}

	bool AddInt8(const char* key, INT8 value)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !\n", key);

			return false;
		}

		int data_len = 4 + 2;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_INT8;
		p++;

		//write value data
		*p = value;

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddInt16(const char* key, INT16 value)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int data_len = 4 + 1 + 2;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_INT16;
		p++;

		//write value data
		v = (BYTE*)(&value);

		*p = v[1];
		p++;

		*p = v[0];

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddInt32(const char* key, INT32 value)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int data_len = 4 + 1 + 4;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_INT32;
		p++;

		//write value data
		v = (BYTE*)(&value);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddInt64(const char* key, INT64 value)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int data_len = 4 + 1 + 8;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_INT64;
		p++;

		//write value data
		v = (BYTE*)(&value);

		*p = v[7];
		p++;

		*p = v[6];
		p++;

		*p = v[5];
		p++;

		*p = v[4];
		p++;

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddFloat(const char* key, float value)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int data_len = 4 + 1 + 4;
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_FLOAT;
		p++;

		//write value data
		v = (BYTE*)(&value);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayInt8(const char* key, std::list<INT8> arr)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int arr_len = arr.size();

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(arr_len, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + arr_len;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_INT8;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		std::list<INT8>::iterator iter_end = arr.end();
		for (std::list<INT8>::iterator iter = arr.begin(); iter != iter_end; iter++)
		{
			*p = *iter;
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayInt8(const char* key, INT8* arr, int length)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(length, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + length;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_INT8;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//write value
		memcpy(p, arr, length);

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayInt16(const char* key, std::list<INT16> arr)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int arr_len = arr.size();

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(arr_len, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + arr_len*2;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_INT16;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		std::list<INT16>::iterator iter_end = arr.end();
		for (std::list<INT16>::iterator iter = arr.begin(); iter != iter_end; iter++)
		{
			v = (BYTE*) (&(*iter));

			*p = v[1];
			p++;

			*p = v[0];
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayInt16(const char* key, INT16* arr, int length)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(length, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + length*2;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_INT16;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//write value
		for (int i = 0; i != length; i++)
		{
			v = (BYTE*)(arr + i);

			*p = v[1];
			p++;

			*p = v[0];
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayInt32(const char* key, std::list<INT32> arr)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int arr_len = arr.size();

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(arr_len, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + arr_len*4;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_INT32;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		std::list<INT32>::iterator iter_end = arr.end();
		for (std::list<INT32>::iterator iter = arr.begin(); iter != iter_end; iter++)
		{
			v = (BYTE*) (&(*iter));

			*p = v[3];
			p++;

			*p = v[2];
			p++;

			*p = v[1];
			p++;

			*p = v[0];
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayInt32(const char* key, INT32* arr, int length)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(length, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + length*4;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_INT32;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//write value
		for (int i = 0; i != length; i++)
		{
			v = (BYTE*)(arr + i);

			*p = v[3];
			p++;

			*p = v[2];
			p++;

			*p = v[1];
			p++;

			*p = v[0];
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayInt64(const char* key, std::list<INT64> arr)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int arr_len = arr.size();

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(arr_len, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + arr_len*8;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_INT64;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		std::list<INT64>::iterator iter_end = arr.end();
		for (std::list<INT64>::iterator iter = arr.begin(); iter != iter_end; iter++)
		{
			v = (BYTE*) (&(*iter));

			*p = v[7];
			p++;

			*p = v[6];
			p++;

			*p = v[5];
			p++;

			*p = v[4];
			p++;

			*p = v[3];
			p++;

			*p = v[2];
			p++;

			*p = v[1];
			p++;

			*p = v[0];
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayInt64(const char* key, INT64* arr, int length)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}


		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(length, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + length*8;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_INT64;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		for (int i = 0; i != length; i++)
		{
			v = (BYTE*) (arr + i);

			*p = v[7];
			p++;

			*p = v[6];
			p++;

			*p = v[5];
			p++;

			*p = v[4];
			p++;

			*p = v[3];
			p++;

			*p = v[2];
			p++;

			*p = v[1];
			p++;

			*p = v[0];
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayFloat(const char* key, std::list<float> arr)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int arr_len = arr.size();

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(arr_len, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + arr_len*4;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_FLOAT;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		std::list<float>::iterator iter_end = arr.end();
		for (std::list<float>::iterator iter = arr.begin(); iter != iter_end; iter++)
		{
			v = (BYTE*) (&(*iter));

			*p = v[3];
			p++;

			*p = v[2];
			p++;

			*p = v[1];
			p++;

			*p = v[0];
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}

	bool AddArrayFloat(const char* key, float* arr, int length)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(length, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len + length*4;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_FLOAT;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//write value
		for (int i = 0; i != length; i++)
		{
			v = (BYTE*)(arr + i);

			*p = v[3];
			p++;

			*p = v[2];
			p++;

			*p = v[1];
			p++;

			*p = v[0];
			p++;
		}

		_data.push_back(data);
		_data_len.push_back(data_len);

		_output_size += data_len;

		return true;
	}
#ifdef MAC_OS
	bool AddArrayString(const char* key, std::list< std::list<UNICHAR> > arr)
	{
		uint32_t k = MurmurHash(key);
		
		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);
			
			return false;
		}
		
		int arr_len = arr.size();
		
		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(arr_len, var_int, var_int_len);
		
		int data_len = 4 + 1 + 1 + var_int_len;
		
		BYTE* data = new BYTE[data_len];
		BYTE* p = data;
		
		//write key
		BYTE* v = (BYTE*)(&k);
		
		*p = v[3];
		p++;
		
		*p = v[2];
		p++;
		
		*p = v[1];
		p++;
		
		*p = v[0];
		p++;
		
		//write data type
		*p = FBENCODE_ARRAY;
		p++;
		
		//write data type
		*p = FBENCODE_STRING_UTF8;
		p++;
		
		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;
		
		//add header first
		_data.push_back(data);
		_data_len.push_back(data_len);
		_output_size += data_len;
		
		//add each string
		std::list<BYTE> utf8_str;
		std::list<std::list<UNICHAR> >::iterator iter1_end = arr.end();
		for (std::list<std::list<UNICHAR> >::iterator iter1 = arr.begin(); iter1 != iter1_end; iter1++)
		{
			//encode utf8
			utf8_str.clear();
			
			utf8::utf16to8<std::list<UNICHAR>::iterator, std::back_insert_iterator<std::list<BYTE> > >(
																									   (*iter1).begin(),
																									   (*iter1).end(),
																									   std::back_inserter(utf8_str));
			
			int utf8_len = utf8_str.size();
			
			//write data
			data_len = 2 + utf8_len;
			data = new BYTE[data_len];
			p = data;
			
			v = (BYTE*)(&utf8_len);
			*p = v[1];
			p++;
			*p = v[0];
			p++;
			
			//write value data
			std::list<BYTE>::iterator iter2_end = utf8_str.end();
			for (std::list<BYTE>::iterator iter2 = utf8_str.begin(); iter2 != iter2_end; iter2++)
			{
				*p = *iter2;
				p++;
			}
			
			_data.push_back(data);
			_data_len.push_back(data_len);
			_output_size += data_len;
		}
		
		return true;
	}
#else
	bool AddArrayString(const char* key, std::list<std::basic_string<UNICHAR> > arr)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int arr_len = arr.size();

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(arr_len, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_STRING_UTF8;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//add header first
		_data.push_back(data);
		_data_len.push_back(data_len);
		_output_size += data_len;

		//add each string
		std::list<BYTE> utf8_str;
		std::list<std::basic_string<UNICHAR> >::iterator iter1_end = arr.end();
		for (std::list<std::basic_string<UNICHAR> >::iterator iter1 = arr.begin(); iter1 != iter1_end; iter1++)
		{
			//encode utf8
			utf8_str.clear();
			utf8::utf16to8<std::basic_string<UNICHAR>::iterator, std::back_insert_iterator<std::list<BYTE> > >((*iter1).begin(), (*iter1).end(), std::back_inserter(utf8_str));

			int utf8_len = utf8_str.size();

			//write data
			data_len = 2 + utf8_len;
			data = new BYTE[data_len];
			p = data;

			v = (BYTE*)(&utf8_len);
			*p = v[1];
			p++;
			*p = v[0];
			p++;

			//write value data
			std::list<BYTE>::iterator iter2_end = utf8_str.end();
			for (std::list<BYTE>::iterator iter2 = utf8_str.begin(); iter2 != iter2_end; iter2++)
			{
				*p = *iter2;
				p++;
			}

			_data.push_back(data);
			_data_len.push_back(data_len);
			_output_size += data_len;
		}

		return true;
	}
#endif
	bool AddArrayBinary(const char* key, std::list<std::vector<BYTE> > arr)
	{
		uint32_t k = MurmurHash(key);

		if (AddKey(k) == false)
		{
			printf("FBENCODE ERROR: Key \"%s\" has one duplicate !", key);

			return false;
		}

		int arr_len = arr.size();

		//get var int
		BYTE var_int[10];
		int var_int_len = 0;
		WriteVarInt(arr_len, var_int, var_int_len);

		int data_len = 4 + 1 + 1 + var_int_len;

		BYTE* data = new BYTE[data_len];
		BYTE* p = data;

		//write key
		BYTE* v = (BYTE*)(&k);

		*p = v[3];
		p++;

		*p = v[2];
		p++;

		*p = v[1];
		p++;

		*p = v[0];
		p++;

		//write data type
		*p = FBENCODE_ARRAY;
		p++;

		//write data type
		*p = FBENCODE_BINARY;
		p++;

		//write value len
		memcpy(p, var_int, var_int_len);
		p += var_int_len;

		//add header first
		_data.push_back(data);
		_data_len.push_back(data_len);
		_output_size += data_len;

		//add each binary
		std::list<std::vector<BYTE> >::iterator iter1_end = arr.end();
		for (std::list<std::vector<BYTE> >::iterator iter1 = arr.begin(); iter1 != iter1_end; iter1++)
		{
			int binary_len = (*iter1).size();

			//get var int
			var_int_len = 0;
			WriteVarInt(binary_len, var_int, var_int_len);

			//write data
			data_len = var_int_len + binary_len;
			data = new BYTE[data_len];
			p = data;

			//write var int
			memcpy(p, var_int, var_int_len);
			p += var_int_len;

			//write value data
			std::vector<BYTE>::iterator iter2_end = (*iter1).end();
			for (std::vector<BYTE>::iterator iter2 = (*iter1).begin(); iter2 != iter2_end; iter2++)
			{
				*p = *iter2;
				p++;
			}

			_data.push_back(data);
			_data_len.push_back(data_len);
			_output_size += data_len;
		}

		return true;
	}

	private: void WriteVarInt(int value, BYTE* buf, int& len)
	{
		len = 0;
		do
		{
			int a = value&0x7F;
			value >>= 7;

			if (value > 0)
			{
				a |= 0x80;
			}

			buf[len] = a;
			len++;
		}
		while (value > 0);
	}

	private: bool AddKey(uint32_t key)
	{
		std::list<uint32_t>::iterator iter_end = _keys.end();
		for (std::list<uint32_t>::iterator iter = _keys.begin(); iter != iter_end; iter++)
		{
			if (key == *iter)
			{
				return false;
			}
		}

		_keys.push_back(key);

		return true;
	}

	private: uint32_t MurmurHash(const char* data)
	{
		int len = strlen(data);

		const int nblocks = len >> 2;

		uint32_t h1 = 123456;

		const uint32_t c1 = 0xcc9e2d51;
		const uint32_t c2 = 0x1b873593;

		//----------
		// body

		const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);

		for(int i = -nblocks; i; i++)
		{
			uint32_t k1 = blocks[i];

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

		uint32_t k1 = 0;

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
