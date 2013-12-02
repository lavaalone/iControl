#define ORIENTATION_INVALID				(-1)
#define ORIENTATION_PORTRAIT			(1 << 0)
#define ORIENTATION_LANDSCAPE_90		(1 << 1)
#define ORIENTATION_LANDSCAPE_270		(1 << 2)

#define ORIENTATION_DEFAULT				ORIENTATION_PORTRAIT

#define MAX_TOUCHES 					10

#ifdef ANDROID_OS
	#include "config_Android_generated.h"
	#ifdef _DEBUG
		#include <android/log.h>
	#endif
#endif
