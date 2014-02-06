#include "CUtils.h"
#include "DebugMacro.h"
#include <list>
////////////////////////////////////////////////////////////////////////////////
// Read ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

UINT8 CUtils::ReadUInt8(UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadUInt8(UINT8* data, INT32 offset) Begin");
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadUInt8(UINT8* data, INT32 offset) End");
	return data[offset];
}

UINT16 CUtils::ReadUInt16(UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadUInt16(UINT8* data, INT32 offset) Begin");
	UINT8 v1 = ReadUInt8(data, offset); offset++;
	UINT8 v2 = ReadUInt8(data, offset);
	TOUCH_CRASH_DEBUG_OUT("CUtils::ReadUInt16(UINT8* data, INT32 offset) End");
	return (v1 | (v2 << 8));
}

UINT32 CUtils::ReadUInt32(UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadUInt32(UINT8* data, INT32 offset) Begin");
	UINT8 v1 = ReadUInt8(data, offset); offset++;
	UINT8 v2 = ReadUInt8(data, offset); offset++;
	UINT8 v3 = ReadUInt8(data, offset); offset++;
	UINT8 v4 = ReadUInt8(data, offset);
	TOUCH_CRASH_DEBUG_OUT("CUtils::ReadUInt32(UINT8* data, INT32 offset) End");
	return (v1 | (v2 << 8) | (v3 << 16) | (v4 << 24));
}

INT8 CUtils::ReadS8(UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadS8(UINT8* data, INT32 offset) Begin");
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadS8(UINT8* data, INT32 offset) End");
	return (INT8)ReadUInt8(data, offset);
}

INT16 CUtils::ReadS16(UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadS16(UINT8* data, INT32 offset) Begin");
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadS16(UINT8* data, INT32 offset) End");
	return (INT16)ReadUInt16(data, offset);
}

INT32 CUtils::ReadS32(UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadS32(UINT8* data, INT32 offset) Begin");
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadS32(UINT8* data, INT32 offset) End");
	return (INT32)ReadUInt32(data, offset);
}

INT32 CUtils::ReadInt(UINT8* data, INT32 offset, UINT8 size)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadInt(UINT8* data, INT32 offset, UINT8 size) Begin");
	if(size == 0) return 0;
	INT32 val = 0;
	UINT8 shift = 0;
	while(shift < size)
	{
		val |= (ReadUInt8(data, offset) << (shift << 3)); offset++;
		shift++;
	}
	TOUCH_CRASH_DEBUG_OUT("CUtils::ReadInt(UINT8* data, INT32 offset, UINT8 size) End");
	return val;
}

float CUtils::ReadFloat(UINT8* data, INT32 offset, UINT8 int_size, UINT8 fra_size)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadFloat(UINT8* data, INT32 offset, UINT8 int_size, UINT8 fra_size) Begin");
	INT32 int_part = ReadInt(data, offset, int_size); offset += int_size;
	INT32 fra_part = ReadInt(data, offset, fra_size);
	float val = (float)int_part;
	val += (float)fra_part / (1 << (fra_size << 3));
    TOUCH_CRASH_DEBUG_OUT("CUtils::ReadFloat(UINT8* data, INT32 offset, UINT8 int_size, UINT8 fra_size) End");
	return val;
}

////////////////////////////////////////////////////////////////////////////////
// Write ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CUtils::WriteUInt8(UINT8 val, UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::WriteUInt8(UINT8 val, UINT8* data, INT32 offset) Begin");
	data[offset] = val;
	TOUCH_CRASH_DEBUG_OUT("CUtils::WriteUInt8(UINT8 val, UINT8* data, INT32 offset) End");
}

void CUtils::WriteUInt16(UINT16 val, UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::WriteUInt16(UINT16 val, UINT8* data, INT32 offset) Begin");
	WriteUInt8(val & 0xFF, data, offset); offset++;
	WriteUInt8((val >> 8) & 0xFF, data, offset);
	TOUCH_CRASH_DEBUG_OUT("CUtils::WriteUInt16(UINT16 val, UINT8* data, INT32 offset) End");
}

void CUtils::WriteUInt32(UINT32 val, UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::WriteUInt32(UINT32 val, UINT8* data, INT32 offset) Begin");
	WriteUInt8(val & 0xFF, data, offset); offset++;
	WriteUInt8((val >> 8) & 0xFF, data, offset); offset++;
	WriteUInt8((val >> 16) & 0xFF, data, offset); offset++;
	WriteUInt8((val >> 24) & 0xFF, data, offset);
	TOUCH_CRASH_DEBUG_OUT("CUtils::WriteUInt32(UINT32 val, UINT8* data, INT32 offset) End");
}

void CUtils::WriteS8(INT8 val, UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::WriteS8(INT8 val, UINT8* data, INT32 offset) Begin");
	WriteUInt8((UINT8)val, data, offset);
	TOUCH_CRASH_DEBUG_OUT("CUtils::WriteS8(INT8 val, UINT8* data, INT32 offset) End");
}

void CUtils::WriteS16(INT16 val, UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::WriteS16(INT16 val, UINT8* data, INT32 offset) Begin");
	WriteUInt16((UINT16)val, data, offset);
	TOUCH_CRASH_DEBUG_OUT("CUtils::WriteS16(INT16 val, UINT8* data, INT32 offset) End");
}

void CUtils::WriteS32(INT32 val, UINT8* data, INT32 offset)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::WriteS32(INT32 val, UINT8* data, INT32 offset) Begin");
	WriteUInt32((UINT32)val, data, offset);
	TOUCH_CRASH_DEBUG_OUT("CUtils::WriteS32(INT32 val, UINT8* data, INT32 offset) End");
}

void CUtils::WriteInt(INT32 val, UINT8* data, INT32 offset, UINT8 size)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::WriteInt(INT32 val, UINT8* data, INT32 offset, UINT8 size) Begin");
	UINT8 shift = 0;
	while(shift < size)
	{
		WriteUInt8((val >> (shift << 3)) & 0xFF, data, offset); offset++;
		shift++;
	}
	TOUCH_CRASH_DEBUG_OUT("CUtils::WriteInt(INT32 val, UINT8* data, INT32 offset, UINT8 size) End");
}

void CUtils::WriteFloat(float val, UINT8* data, INT32 offset, UINT8 int_size, UINT8 fra_size)
{
    TOUCH_CRASH_DEBUG_OUT("CUtils::WriteFloat(float val, UINT8* data, INT32 offset, UINT8 int_size, UINT8 fra_size) Begin");
	INT32 int_part = (INT32)val;
	INT32 fra_part = (INT32)((val - int_part) * (1 << (fra_size << 3)));
	WriteInt(int_part, data, offset, int_size); offset += int_size;
	WriteInt(fra_part, data, offset, fra_size);
	TOUCH_CRASH_DEBUG_OUT("CUtils::WriteFloat(float val, UINT8* data, INT32 offset, UINT8 int_size, UINT8 fra_size) End");
}
//int CUtils::ConvertListUNICHARToUNICHAR(UNICHAR* return_unichar,list<UNICHAR> listChar)
//{
//    int i = 0;
//    for (std::list<UNICHAR>::iterator it=listChar.begin(); it!=listChar.end(); ++it)
//    {
//        int temp = (*it);
//        return_unichar[i] = ((UNICHAR)temp);
//        i++;
//    }
//    return_unichar[i] = 0;
//    return i;
//}
int CUtils::ConvertArrUNICHARToINTArr(int* result, UNICHAR* unichar, int length)
{
    int i = 0;
    for (;i < length; i++)
    {
        result[i] = unichar[i];
    }
    return i;
}
//int CUtils::ConvertListUNICHARToCharArray(char* return_charArray,list<UNICHAR> listChar)
//{
//    LOG_INFO("ConvertListUNICHARToCharArray warning maybe lost info!!!!!!!!!");
//    int i = 0;
//    for (std::list<UNICHAR>::iterator it=listChar.begin(); it!=listChar.end(); ++it)
//    {
//        int temp = (*it);
//        return_charArray[i] = ((char)temp);
//        i++;
//    }
//    LOG_INFO("ConvertListUNICHARToCharArray 1");
//    return_charArray[i] = 0;
//    return i;
//}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*********CHIENKQ*******/
//int CUtils::ParseStringToInt(list<UNICHAR> str, UNICHAR splitChar, int* result)
//{
//    char*       digit_str = NULL;
//    int         idx_str       = 0;
//    int         num_result = 0;
//    bool        _is_negative = false;
//    for (std::list<UNICHAR>::iterator it = str.begin(); it != str.end(); ++it)
//    {
//        if(!digit_str)
//        {
//            digit_str = new char[128];
//            memset(digit_str, 0, 128);
//        }
//        if((*it) == 45) //dấu trừ
//            _is_negative = true;
//        else if((*it) > 47 && (*it) < 58)//từ 0 đến 9
//        {
//            digit_str[idx_str] = (char)(*it);
//            idx_str++;
//        }
//        if((*it) == splitChar || (*it) == 0)
//        {
//            digit_str[idx_str] = 0;//đóng chuổi
//            result[num_result] = atoi(digit_str);
//            if(_is_negative)
//            {
//                result[num_result] *= -1;
//                _is_negative = false;
//            }
//
//            SAFE_DEL_ARRAY(digit_str);
//            num_result++;
//            idx_str = 0;
//            continue;
//        }
//    }
//    // Lay thong tin so cuoi cung
//    // vi so cuoi cung ko co trong vong lap
//    if(digit_str)
//    {
//        result[num_result] = atoi(digit_str);
//        if(_is_negative)
//        {
//            result[num_result] *= -1;
//            _is_negative = false;
//        }
//
//
//        SAFE_DEL_ARRAY(digit_str);
//        num_result++;
//    }
//
//    return num_result;
//}
//int CUtils::RemoveVietnameseAccentMarks(list<UNICHAR> input, char* output)
//{
//    UNICHAR unicodeArray[input.size()];
//    int unicodeLen = CUtils::ConvertListUNICHARToUNICHAR(unicodeArray, input);
//    return RemoveVietnameseAccentMarks(unicodeArray, unicodeLen, output);
//}
int CUtils::RemoveVietnameseAccentMarks(UNICHAR* input, int inputLen, char* output)
{
    if (output == NULL)
    {
        return 0;
    }

    for (int i = 0; i < inputLen; i++)
    {

        switch (input[i])
        {
            case 'a': case 0x00E1: case 0x00E0: case 0x1EA1: case 0x1EA3: case 0x00E3:
            case 0x00E2: case 0x1EA5: case 0x1EA7: case 0x1EAD: case 0x1EA9: case 0x1EAB:
            case 0x0103: case 0x1EAF: case 0x1EB1: case 0x1EB7: case 0x1EB3: case 0x1EB5:
                output[i] = 'a';
                break;

            case 'A': case 0x00C1: case 0x00C0: case 0x1EA0: case 0x1EA2: case 0x00C3:
            case 0x00C2: case 0x1EA4: case 0x1EA6: case 0x1EAC: case 0x1EA8: case 0x1EAA:
            case 0x0102: case 0x1EAE: case 0x1EB0: case 0x1EB6: case 0x1EB2: case 0x1EB4:
                output[i] = 'A';
                break;

            case 'e': case 0x00E9: case 0x00E8: case 0x1EB9: case 0x1EBB: case 0x1EBD:
            case 0x00EA: case 0x1EBF: case 0x1EC1: case 0x1EC7: case 0x1EC3: case 0x1EC5:
                output[i] = 'e';
                break;

            case 'E': case 0x00C9: case 0x00C8: case 0x1EB8: case 0x1EBA: case 0x1EBC:
            case 0x00CA: case 0x1EBE: case 0x1EC0: case 0x1EC6: case 0x1EC2: case 0x1EC4:
                output[i] = 'E';
                break;

            case 'o': case 0x00F3: case 0x00F2: case 0x1ECD: case 0x1ECF: case 0x00F5:
            case 0x00F4: case 0x1ED1: case 0x1ED3: case 0x1ED9: case 0x1ED5: case 0x1ED7:
            case 0x01A1: case 0x1EDB: case 0x1EDD: case 0x1EE3: case 0x1EDF: case 0x1EE1:
                output[i] = 'o';
                break;

            case 'O': case 0x00D3: case 0x00D2: case 0x1ECC: case 0x1ECE: case 0x00D5:
            case 0x00D4: case 0x1ED0: case 0x1ED2: case 0x1ED8: case 0x1ED4: case 0x1ED6:
            case 0x01A0: case 0x1EDA: case 0x1EDC: case 0x1EE2: case 0x1EDE: case 0x1EE0:
                output[i] = 'O';
                break;

            case 'u': case 0x00FA: case 0x00F9: case 0x1EE5: case 0x1EE7: case 0x0169:
            case 0x01B0: case 0x1EE9: case 0x1EEB: case 0x1EF1: case 0x1EED: case 0x1EEF:
                output[i] = 'u';
                break;

            case 'U': case 0x00DA: case 0x00D9: case 0x1EE4: case 0x1EE6: case 0x0168:
            case 0x01AF: case 0x1EE8: case 0x1EEA: case 0x1EF0: case 0x1EEC: case 0x1EEE:
                output[i] = 'U';
                break;

            case 'i': case 0x00ED: case 0x00EC: case 0x1ECB: case 0x1EC9: case 0x0129:
                output[i] = 'i';
                break;

            case 'I': case 0x00CD: case 0x00CC: case 0x1ECA: case 0x1EC8: case 0x0128:
                output[i] = 'I';
                break;

            case 'y': case 0x00FD: case 0x1EF3: case 0x1EF5: case 0x1EF7: case 0x1EF9:
                output[i] = 'y';
                break;

            case 'Y': case 0x00DD: case 0x1EF2: case 0x1EF4: case 0x1EF6: case 0x1EF8:
                output[i] = 'Y';
                break;

            case 'd': case 0x0111:
                output[i] = 'd';
                break;

            case 'D': case 0x0110:
                output[i] = 'D';
                break;

            default:
                output[i] = input[i];
                break;
        }
    }

    output[inputLen] = 0;
    return inputLen;
}
int CUtils::ConvertGameItemTypeIdToExcelDataSheetId(int TypeId)
{
//    switch (TypeId)
//    {
//        case IT_POT:
//            return SHEET_POT;
//            break;
//        case IT_PLAN:
//            return SHEET_SEED;
//            break;
//        case IT_BUILDING:
//            return SHEET_MACHINE;
//            break;
//        case IT_BUG:
//            return SHEET_PEST;
//            break;
//        case IT_PRODUCT:
//            return SHEET_PRODUCT;
//            break;
//        case IT_MONEY:
//            break;
//        case IT_COUNT:
//            break;
//        case IT_DECOR:
//            break;
//        case IT_MATERIAL:
//            return SHEET_MATERIAL;
//            break;
//        case IT_PEARL:
////            return SHEET_PEARL;
//            break;
//    }
    return -1;
}

sPOINT CUtils::CalculateBezierPoint(float t, sPOINT s, sPOINT c1, sPOINT c2, sPOINT e)
{
    float u = 1 - t;
    float tt = t*t;
    float uu = u*u;
    float uuu = uu * u;
    float ttt = tt * t;

    sPOINT p;
    p.x = s.x * uuu;
    p.y = s.y * uuu;
    p.x += 3 * uu * t * c1.x;
    p.y += 3 * uu * t * c1.y;
    p.x += 3 * u * tt * c2.x;
    p.y += 3 * u * tt * c2.y;
    p.x += ttt * e.x;
    p.y += ttt * e.y;

    return p;
}

int CUtils::ReadFile(char* filename, char* text)
{
    char pathFile[1024];
#ifdef ANDROID_OS
    sprintf(pathFile, "/sdcard/vng/sgmb/%s", filename);
#else
	#ifdef MAC_OS
		sprintf(pathFile, "%s", GetDocumentPath(filename));
	#else
		sprintf(pathFile, "%s", filename);
	#endif
#endif
    FILE* stream = fopen(pathFile, "r");
    if (stream == NULL)
    {
        /* File could not be opened for writing. */
        LOG_INFO("CUtils::ReadFile() can't open file");
        return NULL;
    }
    fgets(text, 1024, stream); // lay dong dau tien

    /* Close the stream. */
    if (fclose(stream) != 0)
    {
        /* Error occured while closing the stream. */
        LOG_INFO("CUtils::ReadFile() error occur when closing file !!!!");
    }
    return strlen(text);
}

bool CUtils::WriteFile(char* filename, char* text)
{
    char pathFile[1024];
#ifdef ANDROID_OS
    sprintf(pathFile, "/sdcard/vng/sgmb/%s", filename);
#else
	#ifdef MAC_OS
		sprintf(pathFile, "%s", GetDocumentPath(filename));
	#else
		sprintf(pathFile, "%s", filename);
	#endif
#endif
    FILE* stream = fopen(pathFile, "w");
    if (stream == NULL)
    {
        /* File could not be opened for writing. */
        LOG_INFO("CUtils::WriteFile() can't open file");
        return false;
    }
    LOG_INFO("CUtils::WriteFile() %s", stream);
    fputs(text, stream);

    /* Close the stream. */
    if (fclose(stream) != 0)
    {
        /* Error occured while closing the stream. */
        LOG_INFO("CUtils::WriteFile() error occur when closing file !!!!");
    }
    return true;
}
