#ifndef _SOCKET_CONNECTION_H_
#define _SOCKET_CONNECTION_H_

#import <Foundation/NSObject.h>
#import <UIKit/UIKit.h>
//#import "CGame.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <list>
#include <pthread.h>
#include <arpa/inet.h>
#import "Define_TypeAndMacro.h"

#include "zlib.h"

typedef uint8_t			BYTE;

@interface SocketConnection : NSObject
{
	
}
@end

extern "C" void OS_NotifyMsg(BYTE* data, int length);
extern "C" int OS_OpenConnection(char* ip, int port);
extern "C" void OS_CloseConnection();
extern "C" int OS_IsConnected();
extern "C" int OS_SendDataToServer(BYTE* data, int len, int is_zip);
extern "C" void OS_CallNotifi(int* notifi_id,int length,int cmd_id);
extern "C" void OS_CallNotification(uint16_t *notifi_id,int length, INT64 expired_time, int notify_type);

#endif