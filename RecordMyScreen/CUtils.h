#ifndef __UTILS_H__
#define __UTILS_H__

#include "Defines.h"
#include "OS_Interface.h"
#include <list>
#include <stdio.h>
using namespace std;
class CUtils
{
public:

	static UINT8 ReadUInt8(UINT8* data, INT32 offset);
	static UINT16 ReadUInt16(UINT8* data, INT32 offset);
	static UINT32 ReadUInt32(UINT8* data, INT32 offset);
	static INT8 ReadS8(UINT8* data, INT32 offset);
	static INT16 ReadS16(UINT8* data, INT32 offset);
	static INT32 ReadS32(UINT8* data, INT32 offset);
	static INT32 ReadInt(UINT8* data, INT32 offset, UINT8 size);
	static float ReadFloat(UINT8* data, INT32 offset, UINT8 int_size, UINT8 fra_size);

	static void WriteS8(INT8 val, UINT8* data, INT32 offset);
	static void WriteS16(INT16 val, UINT8* data, INT32 offset);
	static void WriteS32(INT32 val, UINT8* data, INT32 offset);
	static void WriteUInt8(UINT8 val, UINT8* data, INT32 offset);
	static void WriteUInt16(UINT16 val, UINT8* data, INT32 offset);
	static void WriteUInt32(UINT32 val, UINT8* data, INT32 offset);
	static void WriteInt(INT32 val, UINT8* data, INT32 offset, UINT8 size);
	static void WriteFloat(float val, UINT8* data, INT32 offset, UINT8 int_size, UINT8 fra_size);
//    static int ConvertListUNICHARToUNICHAR(UNICHAR* return_unichar,list<UNICHAR> listChar);
    static int ConvertArrUNICHARToINTArr(int* result, UNICHAR* unichar, int length);
//    static int ConvertListUNICHARToCharArray(char* return_charArray,list<UNICHAR> listChar);
//	static int ParseStringToInt(list<UNICHAR> str, UNICHAR splitChar, int* result);
	static int RemoveVietnameseAccentMarks(UNICHAR* input, int inputLen, char* output);
//	static int RemoveVietnameseAccentMarks(list<UNICHAR> input, char* output);

	static int ConvertGameItemTypeIdToExcelDataSheetId(int TypeId);

	static int  ReadFile(char* filename, char* text);
    static bool WriteFile(char* filename, char* text);

	static sPOINT CalculateBezierPoint(float t, sPOINT s, sPOINT c1, sPOINT c2, sPOINT e);
};

#endif // __UTILS_H__
