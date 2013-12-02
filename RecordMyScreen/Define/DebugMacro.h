#ifndef _DEBUG_MACRO
#define _DEBUG_MACRO

#ifdef _DEBUG
//debug build

	#ifdef MAC_OS
	//on mac os

		#define LOG(s)					            printf(s)
		#define MENUBASE_DEBUG_LOG(s)	            printf(s, x)
		#define STATE_MACHINE_DEBUG_OUT(s)	        printf(s, x)
		#define BEAN_TREE_DEBUG_OUT(s)	            printf(s, x)
		#define PLANPOT_DEBUG_OUT(s)	            printf(s, x)
		#define TOUCH_CRASH_DEBUG_OUT(s)	        //printf(s, x)
		#define TOUCH_CRASH_DEBUG_OUT_UPDATE(s)	    //printf(s, x)
		#define TOOLTIP_DEBUG_OUT(s)	            //printf(s, x)
		#define LOG_FPS(s)	                        //printf(s, x)
		#define LOG_RENDER(s)	                    printf(s, x)
		#define LOG1(s, x)				            printf(s, x)
		#define LOG2(s, x, y)			            printf(s, x, y)
		#define LOG3(s, x, y, z)		            printf(s, x, y, z)
		#define _DBG					            printf

	#elif defined(ANDROID_OS)

		#define LOG(...)				            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define MENUBASE_DEBUG_LOG(...)	            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define STATE_MACHINE_DEBUG_OUT(...)	    __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define BEAN_TREE_DEBUG_OUT(...)	        __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define PLANPOT_DEBUG_OUT(...)	            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define TOUCH_CRASH_DEBUG_OUT(...)	        //__android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define TOUCH_CRASH_DEBUG_OUT_UPDATE(...)	//__android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define TOOLTIP_DEBUG_OUT(...)	//__android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define LOG_FPS(...)	                    //__android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define LOG_RENDER(...)	                    __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define LOG1(...)				            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define LOG2(...)				            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define LOG3(...)				            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define LOG_INFO(...) 			            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define LOG_ERROR(...) 			            __android_log_print(ANDROID_LOG_ERROR, "VNG",__VA_ARGS__)
		#define _DBG(...)				            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)

	#elif defined(BADA_OS)

		#define LOG(...)				            AppLog(__VA_ARGS__)
		#define MENUBASE_DEBUG_LOG(...)	            AppLog(__VA_ARGS__)
		#define STATE_MACHINE_DEBUG_OUT(...)	    AppLog(__VA_ARGS__)
		#define BEAN_TREE_DEBUG_OUT(...)	        AppLog(__VA_ARGS__)
		#define PLANPOT_DEBUG_OUT(...)	            AppLog(__VA_ARGS__)
		#define TOUCH_CRASH_DEBUG_OUT(...)	        //AppLog(__VA_ARGS__)
		#define TOUCH_CRASH_DEBUG_OUT_UPDATE(...)	//AppLog(__VA_ARGS__)
		#define TOOLTIP_DEBUG_OUT(...)	//AppLog(__VA_ARGS__)
		#define LOG_FPS(...)	                    //AppLog(__VA_ARGS__)
		#define LOG_RENDER(...)	                    AppLog(__VA_ARGS__)
		#define LOG1(...)				            AppLog(__VA_ARGS__)
		#define LOG2(...)				            AppLog(__VA_ARGS__)
		#define LOG3(...)				            AppLog(__VA_ARGS__)
		#define _DBG(...)				            AppLog(__VA_ARGS__)

	#else
	//on win os

		#define LOG(s)					            OutputDebugStringA(s)
		#define LOG1(s, x)				            {char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define LOG2(s, x, y)			            {char sLog[256]; sprintf(sLog, s, x, y); OutputDebugStringA(sLog);}
		#define LOG3(s, x, y, z)		            {char sLog[256]; sprintf(sLog, s, x, y, z); OutputDebugStringA(sLog);}
		#define LOG_INFO(...) 			            {printf(__VA_ARGS__); printf("\n");}
		#define LOG_ERROR(...) 			            {printf(__VA_ARGS__); printf("\n");}
		#define MENUBASE_DEBUG_LOG(...)	            {char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define STATE_MACHINE_DEBUG_OUT(...)	    {char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define BEAN_TREE_DEBUG_OUT(...)	        {char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define PLANPOT_DEBUG_OUT(...)	            {char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define TOUCH_CRASH_DEBUG_OUT(...)	        //{char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define TOUCH_CRASH_DEBUG_OUT_UPDATE(...)	//        {char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define TOOLTIP_DEBUG_OUT(...)	        //{char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define LOG_FPS(...)	                    //{char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define LOG_RENDER(...)	                    {char sLog[256]; sprintf(sLog, s, x); OutputDebugStringA(sLog);}
		#define _DBG					            printf

	#endif


#else
//release build

	#define LOG(s)
	#define LOG1(s, x)
	#define LOG2(s, x, y)
	#define LOG3(s, x, y, z)
	#define MENUBASE_DEBUG_LOG(...)                 {printf(__VA_ARGS__); printf("\n");}
	#define STATE_MACHINE_DEBUG_OUT(...)            {printf(__VA_ARGS__); printf("\n");}
	#define BEAN_TREE_DEBUG_OUT(...)                {printf(__VA_ARGS__); printf("\n");}
	#define PLANPOT_DEBUG_OUT(...)                  {printf(__VA_ARGS__); printf("\n");}
	#define TOOLTIP_DEBUG_OUT(...)                  //{printf(__VA_ARGS__); printf("\n");}
	#define LOG_FPS(...)                            //{printf(__VA_ARGS__); printf("\n");}
	#define LOG_RENDER(...) 			            {printf(__VA_ARGS__); printf("\n");}
	#define _DBG(...)

	#ifdef ANDROID_OS
		#define LOG_INFO(...) 			            __android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
		#define LOG_ERROR(...) 			            __android_log_print(ANDROID_LOG_ERROR, "VNG",__VA_ARGS__)
        #define TOUCH_CRASH_DEBUG_OUT(...)          //__android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)
        #define TOUCH_CRASH_DEBUG_OUT_UPDATE(...)	//__android_log_print(ANDROID_LOG_INFO, "VNG",__VA_ARGS__)

	#else
		#define LOG_INFO(...) 			                {printf(__VA_ARGS__); printf("\n");}
		#define LOG_ERROR(...) 			                {printf(__VA_ARGS__); printf("\n");}
        #define TOUCH_CRASH_DEBUG_OUT(...)              //{printf(__VA_ARGS__); printf("\n");}
        #define TOUCH_CRASH_DEBUG_OUT_UPDATE(...)	    //{printf(__VA_ARGS__); printf("\n");}
	#endif
#endif

#endif
