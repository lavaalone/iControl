
#import "SocketConnection.h"
#import "FB_zlib.h"


@implementation SocketConnection

- (void) dealloc
{
	[super dealloc];
}


@end

//extern CGame* g_pGame;

extern "C" namespace internal
{
	char 				_ip[20];
	int 				_port = 80;
	int 				_socket_id = -1;
		
	char				_buffer[9];
	bool				_is_connected = false;

	pthread_t			_thread_id;	
	
	uint32_t i_MurmurHash(BYTE* data, int len)
	{
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
	
	void *SocketReceiveThread(void* args)
	{
		//FirebatGame* app = (FirebatGame*) (FirebatGame::GetInstance());
		int bytes_recv = 0;
		while (_is_connected)
		{
			bytes_recv = recv(_socket_id, _buffer, 9, 0);
			if (bytes_recv > 0)
			{
				int offset = 0;
				int type = _buffer[offset++];
				
				if (type == 100 || type == 101)
				{
					uint32_t crc = 0;
					BYTE* p = (BYTE*)(&crc);
					p[3] = _buffer[offset++];
					p[2] = _buffer[offset++];
					p[1] = _buffer[offset++];
					p[0] = _buffer[offset++];
					
					int body_len = 0;
					p = (BYTE*)(&body_len);
					p[3] = _buffer[offset++];
					p[2] = _buffer[offset++];
					p[1] = _buffer[offset++];
					p[0] = _buffer[offset++];
					
					if (body_len > 0)
					{
						BYTE* body_data = new BYTE[body_len];
						offset = 0;
						//read body data
						do
						{
							bytes_recv = recv(_socket_id, body_data + offset, body_len - offset, 0);
							if (bytes_recv > 0)
							{
								offset += bytes_recv;
							}
							else
							{
								OS_CloseConnection();
								return NULL;
							}
						}
						while (offset < body_len);
						
						//checksum
						uint32_t re_crc = i_MurmurHash(body_data, body_len);
						
						if (crc == re_crc)
						{
							if (type == 101)
							{
								LOG_INFO("FBSocket ListenAndRecv decompressing msg !");
								int output_buff_length;
								BYTE* output_buffer = FB_Decompress_package(body_data, body_len, &output_buff_length);
								if (output_buffer == NULL)
								{
									LOG_INFO("FBSocket can't decompress package received from server!");
								}
								else
								{
									OS_NotifyMsg(output_buffer, output_buff_length);
								}
								SAFE_DEL_ARRAY(output_buffer);
							}
							else
							{
								LOG_INFO("FBSocket ListenAndRecv!");
								OS_NotifyMsg(body_data, body_len);
							}
						}
						else
						{
							LOG_INFO("FBSocket checksum fail !");
						}
						SAFE_DEL_ARRAY(body_data);
					}
				}
			}
			else if (bytes_recv == 0)
			{
				LOG_INFO("FBSocket receive data but disconnect !");
				
				OS_CloseConnection();
				return NULL;
			}
			else
			{
				LOG_INFO("FBSocket receive data error code.");
				
				OS_CloseConnection();
				return NULL;
			}
		}
		
		return NULL;
	
	}

}

extern "C" void OS_NotifyMsg(BYTE* data, int length)
{
//	if (g_pGame != NULL)
//		g_pGame->NotifyMessageReceived(data, length);
}

int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( hostname ) ) == NULL) 
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
     
    return 1;
}

extern "C" int OS_OpenConnection(char* ip, int port)
{
	LOG_INFO("OS_OpenConnection ip : %s | port: %d", ip, port);
	char ipnew[100];
    hostname_to_ip(ip, ipnew);
	LOG_INFO("ip new %s", ipnew);
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
    addr.sin_len = sizeof(addr);
	addr.sin_family = AF_INET; 		// AF_INET or AF_INET6 to force version
	addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ipnew);
	
	
    LOG_INFO("addr family %d", addr.sin_family);
    LOG_INFO("addr port %d", addr.sin_port);
    LOG_INFO("addr ip %d", addr.sin_addr.s_addr);
	
	int status;
    //create socket

	internal::_socket_id = socket(AF_INET, SOCK_STREAM, 0);
    
	LOG_INFO("OS_OpenConnection %d", internal::_socket_id);
	if (internal::_socket_id == -1)
	{
		return false;
	}
    
   
	//connect
	status = connect(internal::_socket_id, (struct sockaddr*)&addr, sizeof(addr));
	LOG_INFO("OS_OpenConnection connect status %d", status);
	if (status == -1)
	{
		LOG_INFO("Connect error %s %d", strerror(errno), errno);
        return false;
	}
	
	strcpy(internal::_ip, ip);
	internal::_port = port;
	internal::_is_connected = true;
	
	//start listen thread
	// pthread_mutex_init(&_mutex, NULL);
    
    status = pthread_create(&internal::_thread_id, NULL, internal::SocketReceiveThread, NULL);
	
    LOG_INFO("FBSocket Connect create pthread status: %d", status);
	return true;
}



extern "C" void OS_CloseConnection()
{
	internal::_is_connected = false;
		
	if (internal::_socket_id >= 0)
	{
		close(internal::_socket_id);			
		internal::_socket_id = -1;
	}
	
	internal::_is_connected = false;
	
	if (internal::_socket_id >= 0)
	{
		close(internal::_socket_id);
		internal::_socket_id = -1;
	}
//	if (g_pGame != NULL)
//		g_pGame->NotifyConnectionClose();
}

extern "C" int OS_IsConnected()
{
	return internal::_is_connected ? 1 : 0;
}

extern "C" int OS_SendDataToServer(BYTE* data, int len, int is_zip)
{
	if (!internal::_is_connected)
	{
		return false;
	}
	
	BYTE* body = NULL;
	int body_len = 0;
	
	if (is_zip == 1)
	{
		LOG_INFO("SendDataToServer compressing msg begins !");
		body = FB_Compress_package(data, len, &body_len);
		if (body == NULL)
        {
			LOG_INFO("SendDataToServer can't compress to package");
            return false;
        }
		// SAFE_DEL_ARRAY(data);
		LOG_INFO("SendDataToServer compressing msg ends !");
	}
	else
	{
		LOG_INFO("SendDataToServer doesn't compress msg !");
		body = data;
		body_len = len;
	}
	
	uint32_t crc = internal::i_MurmurHash(body, body_len);
	
	int content_len = 1 + 4 + 4 + body_len;
	
	char* send_data = new char[content_len];
	
	send_data[0] = (is_zip == 1 ? 101 : 100);
	
	send_data[1] = ((crc>>24)&0xFF);
	send_data[2] = ((crc>>16)&0xFF);
	send_data[3] = ((crc>>8)&0xFF);
	send_data[4] = (crc&0xFF);
	
	send_data[5] = ((body_len>>24)&0xFF);
	send_data[6] = ((body_len>>16)&0xFF);
	send_data[7] = ((body_len>>8)&0xFF);
	send_data[8] = (body_len&0xFF);
	
	memcpy(send_data + 9, body, body_len);
	
	SAFE_DEL_ARRAY(body);
	
	int remain = content_len;
	int offset = 0;
	do
	{
		int bytes_sent = send(internal::_socket_id, send_data + offset, remain, 0);
		if (bytes_sent == -1)
		{
			LOG_INFO("FBSocket send data error code.");
			
			delete[] send_data;
			return false;
		}
		else
		{
			if (bytes_sent > 0)
			{
				remain -= bytes_sent;
				offset += bytes_sent;
			}
			else
			{
				LOG_INFO("FBSocket send data but disconnect !");
				
				delete[] send_data;
				return false;
			}
		}
	}
	while (remain > 0);
	
	delete[] send_data;
	return true;
}

extern "C" void OS_CallNotifi(int* c_string,int length_arr,int cmd_id)
{

}

extern "C" void OS_CallNotification(uint16_t *notifi_id,int length, INT64 expired_time, int notify_type)
{
	NSLog(@"OS_CallNotification");
	UILocalNotification *localNotif = [[UILocalNotification alloc] init];
	if(localNotif)
	{
		NSString *str = [[NSString alloc] initWithCharacters:(const unichar*)notifi_id length:length];
		NSLog(@"text notification %@", str);
		localNotif.alertBody = str;
		localNotif.alertAction = NSLocalizedString(@"Read Message", nil);
		localNotif.soundName = UILocalNotificationDefaultSoundName;
		//localNotif.applicationIconBadgeNumber = 1;
		NSDate  *time = [[NSDate date] dateByAddingTimeInterval:(NSTimeInterval)(expired_time/1000)];
		localNotif.fireDate = time;
		localNotif.timeZone = [NSTimeZone defaultTimeZone];
		
		[[UIApplication sharedApplication] scheduleLocalNotification:localNotif];
		NSLog(@" notification scheduled = %@", [[UIApplication sharedApplication] scheduledLocalNotifications]);
        
        [str release];
        [localNotif release];
	}
}



