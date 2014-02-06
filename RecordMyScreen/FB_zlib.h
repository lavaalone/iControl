#include <stdlib.h>
#include "./zlib/zlib.h"
#include "Defines.h"
#import "DebugMacro.h"
#import <vector.h>

/* PACKAGE_CHUNK is the size of the memory chunk used by the zlib routines. */
#define PACKAGE_CHUNK               1024*2
// src is compressed data
// length is length of data after decompressing
BYTE* FB_Decompress_package(BYTE *src, int srcLen, int* length)
{
    LOG_INFO("Decompress_package begins");

    BYTE out_buff[PACKAGE_CHUNK];
    memset(out_buff, 0, PACKAGE_CHUNK);
    vector<BYTE> output_result;

    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = srcLen;
    strm.next_in = src;

	/** 15 window bits, and the +32 tells zlib to to detect if using gzip or zlib **/
    int ret = inflateInit2(&strm, 15 + 32);
    if (ret != Z_OK) {
        LOG_INFO("Decompress_package inflateInit2 failed\n");
        return NULL;
    }

    /* run inflate() on input until output buffer not full */
    do {
        memset(out_buff, 0, PACKAGE_CHUNK);

        strm.avail_out = PACKAGE_CHUNK;
        strm.next_out = (Bytef *)out_buff;
        ret = inflate(&strm, Z_NO_FLUSH);

        int have_bytes = PACKAGE_CHUNK - strm.avail_out;
        switch (ret) {
            case Z_STREAM_END:
            case Z_OK:
                for(int i = 0; i < have_bytes; i++)
                    output_result.push_back(out_buff[i]);
                break;
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_STREAM_ERROR:
            case Z_MEM_ERROR:
                LOG_INFO("Decompress_package fails ret = %d", ret);
                (void)inflateEnd(&strm);
                return NULL;
        }
    } while (ret != Z_STREAM_END);

	// realease the memory for z_stream
	if (inflateEnd(&strm) != Z_OK && strm.avail_out == 0)
	{		
		if (ret != Z_BUF_ERROR)
        {
            LOG_INFO("Decompress_package inflateEnd failed\n");
            return NULL;
        }
		return NULL;
	}

    LOG_INFO("Decompress_package inflate finished strm.total_out=%ld", strm.total_out);

    /** Convert vector<Byte> to byte array **/
    BYTE* result_bytes_array = new BYTE[strm.total_out];
    copy(output_result.begin(), output_result.begin() + strm.total_out, result_bytes_array);

    *length = strm.total_out;
    LOG_INFO("length=%d", *length);
    return result_bytes_array;
}

/** src is data which user want to compressed
 *  length is length of data after compressing
 **/
BYTE* FB_Compress_package(BYTE *src, int srcLen, int* length)
{
    LOG_INFO("FB_Compress_package begins 2222");

    BYTE out_buff[PACKAGE_CHUNK];
    memset(out_buff, 0, PACKAGE_CHUNK);
    vector<BYTE> output_result;

    z_stream strm;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;

    strm.avail_in = srcLen;
    strm.next_in = src;

	/** 31 is Gzip format, normal is 15**/
	const int windowBits = 15 + 16;

	int ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, windowBits,
                        8, Z_DEFAULT_STRATEGY);
    
    LOG_INFO("###FB_Compress_package deflateInit2 ret: %d", ret);
    
	if (ret != Z_OK) {
		LOG_INFO("FB_Compress_package deflateInit2 failed\n");
		return NULL;
	}

    int flush;
    if (srcLen <= PACKAGE_CHUNK)
        flush = Z_FINISH;
    else
        flush = Z_NO_FLUSH;
    /* run deflate() on input until output buffer not full */
    do {
        memset(out_buff, 0, PACKAGE_CHUNK);

        strm.avail_out = PACKAGE_CHUNK;
        strm.next_out = (Bytef *)out_buff;
        ret = deflate(&strm, flush);

        int have_bytes = PACKAGE_CHUNK - strm.avail_out;
        switch (ret) {
            case Z_STREAM_END:
            case Z_OK:
                for(int i = 0; i < have_bytes; i++)
                    output_result.push_back(out_buff[i]);
                break;
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_STREAM_ERROR:
            case Z_MEM_ERROR:
                LOG_INFO("Decompress_package fails ret = %d", ret);
                (void)inflateEnd(&strm);
                return NULL;
        }
    } while (ret != Z_STREAM_END && strm.avail_out == 0);

//    int retry = 0;
//    while (deflateEnd(&strm) != Z_OK) {
//        LOG_INFO("Retry %d", retry++);
//    }
	if (deflateEnd(&strm) != Z_OK)
	{
	    if (ret != Z_BUF_ERROR)
        {
            LOG_INFO("Compress_package deflate fail 2 !");
            return NULL;
        }
	}

	LOG_INFO("FB_Compress_package ends");

    /** Convert vector<Byte> to byte array **/
    BYTE* result_bytes_array = new BYTE[strm.total_out];
    copy(output_result.begin(), output_result.begin() + strm.total_out, result_bytes_array);

    *length = strm.total_out;
    LOG_INFO("length=%d", *length);
    return result_bytes_array;
}