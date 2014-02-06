#define USE_GAME_ITEM_INFO			1	//dùng debug va truy vet luon bat là 1
#define USE_CGAME_HANDLE_TOUCH      0
#define USE_GAME_LUA_CODE           0
#define SKIP_SORTLIST_FRAME         0
#define USE_FLOATING_CLOUDS_ONBG    0
#define USE_REFRESH_BEANTREE        1
#define USE_FRIEND_LIST             1
#define USE_NEWBOARD             	1
#define USE_LOAD_IMG_FRIEND_LIST    1
#define USE_MUSIC_AND_SOUND         1
#define USE_SOUND_DEFAULT           1
#define USE_BUFFER_SPRITE           1
#define USE_VIP                     1
#define USE_ACTION_ONLY_WHEN_BEANTREE_BALANCED           1
#define USE_REMOVE_ALPHABG_AT_BEANTREE                   1
#define SFX_DEFAULT                 SFX_001_CONFIRM
#define USE_CHECK_CLIENT_VERSION    1

//for debug
#define USE_SHOW_FPS				0
#define USE_RELOAD_TEXTURE  		1
#define SHOW_BUTTON_PRIORITY        0
#define SHOW_DEBUG_MEMORY_LEACH     0
#define SHOW_TOUCH_RECT             0
#define DEFINE_ALPHA                0xFF33320
#define TOUCH_RECT_COLOR            0xFFFF00FF
#define TOUCH_RECT_COLOR_RED		0xFF0000FF
#define PRIORITY_DEFINE_ALPHA       -1//(Z_NEWBOARD + 20)
#define VIRTUAL_FRIEND_DEVICEID_FORM     "123456%d"
#define VIRTUAL_FRIEND_FIRST_DEVICEID    "1234560"

#define USE_TOKEN_VALIDATE          1

#define USE_ONLINE_CONNECTION       1
#define USE_ONLINE_DATA_INFO        1
#ifdef ANDROID_OS
    #define USE_LOCAL_SERVER            0
    #define USE_DISPLAY_USERNAME        0
#else
    #define USE_LOCAL_SERVER            0
    #define USE_DISPLAY_USERNAME        1
    #define BUFFER_LENGTH               256*1024
    #define VERSION_NAME                "0.0.35"
#endif
//@yokito define
#ifdef MAC_OS
	#define USE_LANDSCAPE			1
	#define USE_SYSTEM_KEYBOARD		1
	#define USE_FACEBOOK		    1
	#define USE_SYSTEM_SMS			1
#endif

#define USE_IOS_WIDESCREEN_IP5      0
/*********** If build on win, have to change value to 0 ************/
#ifdef ANDROID_OS
    #define COMPRESS_BEFORE_SEND        1
#else
    #define COMPRESS_BEFORE_SEND        1
#endif
#if(USE_ONLINE_CONNECTION == 1)

// Chienkq
#define DELAY_POT_SEND_SERVER       1
/** Send multiple servers **/
#ifdef ANDROID_OS
    #define USE_MULTIPLE_SERVERS        0
#else
    #define USE_MULTIPLE_SERVERS        0
#endif

#define SERVER_ADD               "192.168.2.111"
//#define SERVER_ADD                      "49.213.72.179"
#if(USE_LOCAL_SERVER == 1)
    #if defined(ANDROID_OS)
        #define IP_CONNECTION               "192.168.1.2"
        #define IP_PORT                     443
    #else
        #define IP_CONNECTION               "127.0.0.1"
        #if (USE_MULTIPLE_SERVERS == 1)
            #define IP_PORT                     443
        #else
            #define IP_PORT                     443
        #endif
    #endif
#else
    #define IP_CONNECTION               SERVER_ADD
    #define IP_PORT                     443
#endif

/** Use for fake data which contains the smaller value than real data **/
//#define IP_CHEAT_IP                     "sgm.apps.zing.vn"
#define IP_CHEAT_IP                     SERVER_ADD
#define IP_CHEAT_PORT                   8305

#endif

#define USE_NEW_BUILDING_INFO       1
#define USE_NEW_ORDER               1
/** Use for feedback 0000147.
 *  Put the flag to change the design easily.
 *  Change from show all the user's clouds can be unlocked to one cloud
 **/
#define SHOW_ALL_CLOUDS             0

#define USE_TUTORIAL                1
#define USE_TUTORIAL_V2             1

#define USE_NOTIFICATION            1

#define USE_SYSTEM_GIFT             1

#ifdef USE_FLURRY
#define USE_FLURRY_IN_C             1
#else
#define USE_FLURRY_IN_C             0
#endif

//build quality
#define BUILD_SD					0
#define BUILD_SD480					1
#define BUILD_HD					2
#define BUILD_HD_960_640			3



#ifdef _WIN32
#define USE_GENERATE_DEVICE_ID      1
#else
#define USE_GENERATE_DEVICE_ID      0
#endif
#if (USE_GENERATE_DEVICE_ID == 1)
    #define DEVICE_ID_FOR_FRIENDLIST      0
#endif
#define HAPPY_SERVER_NAME           "HAPPY_SERVER"
#define USE_HAPPY_SERVER_FEATURE    0
#define DEBUG_CONNECTION_CMD        1

#ifdef MAC_OS
	#define BUILD_QUALITY				BUILD_HD_960_640
	#define FLATFORM				    "iOS"
#else
	#define BUILD_QUALITY				BUILD_HD
	#define FLATFORM				    "ANDROID"
    #define USE_AUTO_SCALE              1
#endif
