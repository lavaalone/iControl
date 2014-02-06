#ifndef _OS_INTERFACE_H
#define _OS_INTERFACE_H

#include "Defines.h"
#include "cUtils.h"
#if defined(MAC_OS) || defined(ANDROID_OS) || defined(BADA_OS)
#include <unistd.h>
#endif

extern "C" int GetPhoneOrientation();
extern "C" const char* GetiPhoneUDID();
extern "C" const char* GetRealFilePath(const char* filename);
#ifdef MAC_OS
extern "C" const char* GetDocumentPath(const char* filename);
#endif
#ifdef ANDROID_OS
	extern "C" bool _isPressedBackKey;
#else
	#ifdef MAC_OS
    	extern "C" unsigned long OS_GetTime();
	#else
		extern "C" UINT64 OS_GetTime();
	#endif
    extern "C" void OS_Sleep(unsigned int milisec);
#endif

extern "C" bool SaveAppData(const char* filename, const char* data_to_save, int data_length, bool is_append);
extern "C" int  ReadAppData(const char* filename, char* &readed_data);
extern "C" bool DeleteAppData(const char* filename);
extern "C" void SaveImageToPhotosAlbum(char* img_data, int img_data_len);
extern "C" void InitFBSession();
extern "C" void NativeRequestLogoutFacebook();
extern "C" void NativePostFeedFacebook(int* name, int nameLeng, int* caption, int captionLeng,
                                       int* descript, int descriptLeng, char* link, char* picture);
extern "C" void PublishingFacebookFeedStories(int new_score);
extern "C" void ShowFBConnectDialog();
extern "C" void ShowFBConnectButton(int x, int y);
extern "C" void HideFBConnectButton();
extern "C" void GetFriendsUseApp(unsigned long long fbuid);

//text input
extern "C" void StartTextInput(char* text_buff, unsigned int buff_size, int x, int y, int w, int h);
extern "C" void CloseTextInput();
extern "C" bool IsTextInputDone();

//sfx and music
extern "C" void OS_LoadMusic(const char* filename);
extern "C" void OS_PlayCurrentMusic(int num_loop);
extern "C" void OS_StopCurrentMusic();
extern "C" bool OS_IsCurrentMusicPlaying();
extern "C" void OS_LoadSFX(const char* filename, int sound_id);
extern "C" void OS_PlaySFX(int sound_id);
extern "C" void OS_StopAllSFX();
extern "C" void CopyToSDCard (const char* cfileNameWithoutExtension, const char* cExtension, int len);

extern "C" void OS_CallNotifi(int* notifi_id,int length,int cmd_id);

#ifdef MAC_OS
extern "C" void OS_CallNotification(uint16_t *notifi_id,int length, INT64 expired_time, int notify_type);
#else
extern "C" void OS_CallNotification(int* notifi_id,int length, INT64 expired_time, int notify_type);
#endif
//network
extern "C" int OS_OpenConnection(char* ip, int port);
extern "C" void OS_CloseConnection();
extern "C" int OS_IsConnected();
extern "C" int OS_SendDataToServer(BYTE* data, int len, int is_zip);
extern "C" int OS_ShowDialog(int type, int* title, int titleLen, int* content, int contentLen,
                              int* hiddenContent, int hiddenLen, int* labelBtn1, int label1Len,
                              int* labelBtn2, int label2Len, int* labelBtn3, int label3Len);
extern "C" int OS_CheckNetworkAvailable();

extern "C" void OS_HideShowLostNetworkDialog();

extern "C" void OS_QuitGame();

extern "C" void OS_GetDeviceName(char* name);
extern "C" void OS_GetFirmwareVersion(char* firmware);
#ifdef ANDROID_OS
extern "C" void OS_GetDeviceID(char* firmware);
#endif
extern "C" char* OS_GetBundleVersion();

#ifdef USE_FACEBOOK
extern "C" int OS_ConnectFacebook();
#endif

#if(USE_LOAD_IMG_FRIEND_LIST == 1)
extern "C" void OS_SendImageRequest(char* url);
#endif

#ifdef USE_SYSTEM_KEYBOARD
    extern "C" void OS_ShowKeyBoard(int keyboard_type);
    extern "C" void OS_HideKeyBoard();
    #ifdef MAC_OS
        extern "C" void OS_InitSystemKeyBoard();
        extern "C" bool OS_CheckIsIPhone5();
    #endif
#endif

#ifdef USE_SYSTEM_SMS
    extern "C" void OS_SendSMSPayment(char* smsNumber, char* smsText);
#endif


#ifdef USE_FLURRY
    extern "C" void OS_FlurryLogParam(char* event_name, char* event_param, va_list arg);
#endif

#endif	//_OS_INTERFACE_H
