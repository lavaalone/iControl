#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "Define_Platform.h"
#include "Define_Build.h"
#include "Define_TypeAndMacro.h"
#include "Define_Const.h"
#include "Define_Misc.h"
#include "Define_Screen.h"
#include "Define_zOrder.h"
#include "Define_Item.h"
#include "Define_NPC_ORDER.h"
#include "Define_Building.h"
#include "Define_Product.h"
#include "Define_Bug.h"
#include "Define_Material.h"
#include "Define_Plant.h"
#include "Define_Warehouse.h"
#include "Define_IBShop.h"
#include "Define_Pot.h"
#include "Define_PrivateShop.h"
#include "Define_Payment.h"
#include "Define_Position_Modify.h"
#include "Define_TUTORIAL_FLURRY.h"
#include "Define_FLURRY.h"
//#include "Define_Server_Key.h"
//#include "Define_Server_Cmd.h"
//#include "Define_Server_DB_Id.h"


//#include "../Defines_Server/CommandID.h"
//#include "../Defines_Server/DatabaseID.h"
//#include "../Defines_Server/KeyID.h"
//#include "../Defines_Server/ReturnCode.h"

#include "./Define_Server_PortTo_Client.h"


#include "Define_TreeBean.h"

//#include "../Lib/Debug/DebugMacro.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef ANDROID_OS
    #include <android/log.h>
    #define Log(...)  __android_log_print(ANDROID_LOG_INFO,"NativeLib",__VA_ARGS__)
    #define SDCARD_PATH     "../sdcard/vng/demo/"
#else
    #define SDCARD_PATH     ""
    #define Log(...)  printf(__VA_ARGS__);printf("\n")
#endif

//#include "./_src_gen/IncludeAll.h"



#endif
