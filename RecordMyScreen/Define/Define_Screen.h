
#if BUILD_QUALITY==BUILD_SD
	#define k_SCREEN_WIDTH				320
	#define k_SCREEN_HEIGHT				240
	#define k_SCREEN_SCALE_X			0.45
	#define k_SCREEN_SCALE_Y			0.45
	#define IS_USE_DEVICE_SCREEN_WIDTH  1
    #define BUILD_RES_STR               "320x240"
	#define k_SHADER_DIV_X              0.0f
	#define _MAX_AVATAR_DISPLAYNAME_LEN 8
#elif BUILD_QUALITY==BUILD_SD480
	#define k_SCREEN_WIDTH				320
	#define k_SCREEN_HEIGHT				480
    #define BUILD_RES_STR               "320x480"
	#define k_SHADER_DIV_X              0.0f
	#define _MAX_AVATAR_DISPLAYNAME_LEN 8
#elif BUILD_QUALITY==BUILD_HD_960_640
	#define k_SCREEN_WIDTH				960
	#define k_SCREEN_HEIGHT				640
	#define k_SCREEN_SCALE_X			1.2
	#define k_SCREEN_SCALE_Y			1.2
	#define IS_USE_DEVICE_SCREEN_WIDTH  0
    #define BUILD_RES_STR               "960x640"
    #define k_SHADER_DIV_X              88.0f
    #define _MAX_AVATAR_DISPLAYNAME_LEN 8
#else
	#define k_SCREEN_WIDTH				800
	#define k_SCREEN_HEIGHT				480
	#define k_SCREEN_SCALE_X			1
	#define k_SCREEN_SCALE_Y			1
	#define IS_USE_DEVICE_SCREEN_WIDTH  1
    #define BUILD_RES_STR               "800x480"
	#define k_SHADER_DIV_X              0.0f
	#define _MAX_AVATAR_DISPLAYNAME_LEN 8
#endif

#if BUILD_QUALITY==BUILD_HD
#define k_SCREEN_SCALE_X			1
#define k_SCREEN_SCALE_Y			1
#endif // BUILD_QUALITY

#if (IS_USE_DEVICE_SCREEN_WIDTH == 1)
    #if BUILD_QUALITY==BUILD_HD
        #define k_SCREEN_WIDTH_BASE				GAME_INSTANCE->GetScreenWidth() // CHI SU DUNG BIEN NAY KHONG SU DUNG BIEN WIDTH, HEIGHT O TREN
        #define k_SCREEN_HEIGHT_BASE			480
    #else
        #define k_SCREEN_WIDTH_BASE				(GAME_INSTANCE->GetScreenWidth() / k_SCREEN_SCALE_X) // CHI SU DUNG BIEN NAY KHONG SU DUNG BIEN WIDTH, HEIGHT O TREN
        #define k_SCREEN_HEIGHT_BASE			(GAME_INSTANCE->GetScreenHeight() / k_SCREEN_SCALE_Y) // CHI SU DUNG BIEN NAY KHONG SU DUNG BIEN WIDTH, HEIGHT O TREN
    #endif
#else
	#if BUILD_QUALITY==BUILD_HD_960_640
		#define k_SCREEN_WIDTH_BASE				(GAME_INSTANCE->GetSpecScreenWidth() / k_SCREEN_SCALE_X) // CHI SU DUNG BIEN NAY KHONG SU DUNG BIEN WIDTH, HEIGHT O TREN
		#define k_SCREEN_HEIGHT_BASE			(k_SCREEN_HEIGHT / k_SCREEN_SCALE_Y)
	#else
		#define k_SCREEN_WIDTH_BASE				800 // CHI SU DUNG BIEN NAY KHONG SU DUNG BIEN WIDTH, HEIGHT O TREN
		#define k_SCREEN_HEIGHT_BASE			480
	#endif
#endif

#define GOLD_INTERFACE_POSITION_X       750
#define GOLD_INTERFACE_POSITION_Y       35

#define COIN_INTERFACE_POSITION_X       750
#define COIN_INTERFACE_POSITION_Y       75

#define GOLD_IBSHOP_POSITION_X          305
#define GOLD_IBSHOP_POSITION_Y          20

#define COIN_IBSHOP_POSITION_X          455
#define COIN_IBSHOP_POSITION_Y          20

#define TOOL_INTERFACE_POSITION_X       750
#define TOOL_INTERFACE_POSITION_Y       135

#define FRIENDLIST_INTERFACE_POSITION_X       750
#define FRIENDLIST_INTERFACE_POSITION_Y       435

#define EXP_INTERFACE_POSITION_X       350
#define EXP_INTERFACE_POSITION_Y       40

//treebean
#if (BUILD_QUALITY==BUILD_SD)
    #define DESTINATION_SHOP_UI_X          187
    #define DESTINATION_SHOP_UI_Y          60
#elif (BUILD_QUALITY==BUILD_HD_960_640)
    #define DESTINATION_SHOP_UI_X          187
    #define DESTINATION_SHOP_UI_Y          42
#else
    #define DESTINATION_SHOP_UI_X          187
    #define DESTINATION_SHOP_UI_Y          42
#endif
#define SHOP_INTERFACE_POSITION_X       40
#define SHOP_INTERFACE_POSITION_Y       435

#define NUOC_THAN_HALF_HEIGHT          23
#define BUILDING_COCOON_HALF_HEIGHT    30
#define BUILDING_ICON_HALF_HEIGHT       32

#define BUILDING_BUBBLE_STATUS_X        -160
#define BUILDING_BUBBLE_STATUS_Y        -45
#define BUILDING_BUBBLE_STATUS_WIDTH    145
#define BUILDING_BUBBLE_STATUS_HEIGHT   145

#define DROP_ITEM_CONTROL_POINT_ONE_RANGE_X       100
#define DROP_ITEM_CONTROL_POINT_ONE_RANGE_Y       -100
#define DROP_ITEM_CONTROL_POINT_TWO_RANGE_X       100
#define DROP_ITEM_CONTROL_POINT_TWO_RANGE_Y       -200

#define TUTORIAL_NPC_WIDTH_DIALOG_TEXT                      260

#define MOVING_SPEED                    15
#define FLOOR_SCROLL_RATIO              (-3)
#define    QUEST_BLOCK   0
#define    QUEST_COMPLETE  1
#define    QUEST_UNCOMPLETE    2
#define    QUEST_WAITING   3
#define    QUEST_BLOCK_NEXT 4
#define ACTIONMENU_ITEM_TOUCH_WIDTH     64

#define MININUM_DRAG_DIV                30

#define    ORDER_ITEM_POS_X             -54
#define    ORDER_ITEM_POS_Y             -122
#define    ORDER_ITEM_POS_WIDTH         108
#define    ORDER_ITEM_POS_HEIGHT        127

#define DEFAULT_UI_ITEM_INFO_DETAIL     100
