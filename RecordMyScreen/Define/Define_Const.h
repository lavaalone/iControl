//FPS
#define FPS_LIMIT					30
#define FPS_DELAY_TIME				(1000/FPS_LIMIT)

//(1000/FPS_LIMIT)

//Touch State
#define TOUCH_IDLE					0
#define TOUCH_UP					1
#define TOUCH_DOWN					2
#define TOUCH_DRAG					3
#define TOUCH_OVER					5
#define TOUCH_DRAG_NONE_EVENT		6

#define DIALOG_TYPE_NEED_UPDATE_VERSION		0
#define DIALOG_TYPE_BUTTON_2		        1
#define DIALOG_TYPE_BUTTON_3		        2
#define DIALOG_TYPE_DISCONNECT		        3

//Game State
#define k_GS_TEST					1
#define k_GS_SCENE					2


//Game Sub State
#define k_INIT						1
#define k_FIRST_TIME				2
#define k_LOOP						3
#define k_DESTROY					4

//facebook connect
#define FB_APPS_API_KEY				"YOUR_API_KEY"
#define FB_APPS_SECRET_KEY			"YOUR_SECRET_KEY"
#define FB_APPS_KEY_LEN				32

#define CF_SLOT_PER_FLOOR           6

#define ACTION_MENU_DELAY_TIME      200

//GAME_ERROR
#define GAME_GENENAL_ERROR_OK                           0
#define GAME_GENENAL_ERROR_NOTENOUGH_REQUIREITEMS       1
#define GAME_GENENAL_ERROR_FULL_SLOT                    2
#define GAME_GENENAL_ERROR_DURATION                     3
#define GAME_GENENAL_ERROR_FULL_STORGAGE                4
#define GAME_GENERAL_ERROR_USE_ALL_ITEMS                5
#define GAME_GENENAL_ERROR_COUNT                        6


//GFX_INDEX
#define GFX_PLAN_FIRSTID                                GFX_PLAN_FIRSTID_F_HOAHONG
#define GFX_GAMEITEM_ANIMID_MENU_ICON                   FLOWER_001_HOA_HONG_ANIM_DROP_MENU_ICON
#define GFX_GAMEITEM_ANIMID_HINT_ICON                   FLOWER_001_HOA_HONG_ANIM_HINT_ICON
#define GFX_GAMEITEM_ANIMID_DISABLE                     FLOWER_001_HOA_HONG_ANIM_DISABLE

#define GFX_GAMEITEM_ANIMID_FLOWER_MATURE               FLOWER_001_HOA_HONG_ANIM_MATURE
#define GFX_GAMEITEM_ANIMID_FLOWER_TEENAGE              FLOWER_001_HOA_HONG_ANIM_TEENAGE

#define GFX_FONT_FLY_NUMBER                             GFX_FONT_16_OUTLINE_BLACK
#define GFX_FONT_NUMBER_INTERFACE                       GFX_FONT_16_OUTLINE_BLACK

#define GFX_ICON_GOLD                                   GFX_MONEY_ITEM_FIRSTID_000
#define GFX_ICON_DIAMOND                                GFX_MONEY_ITEM_001_DIAMOND
#define GFX_ICON_HEART                                  GFX_MONEY_ITEM_002_HEART

//GFX_POT_INDEX
#define GFX_POT_NORMAL_ID                               0
#define GFX_POT_NORMAL_SELECT_ID                        1
#define GFX_POT_DISABLE_ID                              2
#define GFX_POT_PLANT_ID                                3
#define GFX_POT_PLANT_SELECT_ID                         4

#define GFX_MACHINE_WORK_LV1_ID                         0
#define GFX_MACHINE_REST_LV1_ID                         1
#define GFX_MACHINE_BROKEN_LV1_ID                       2
#define GFX_MACHINE_WORK_LV2_ID                         3
#define GFX_MACHINE_REST_LV2_ID                         4
#define GFX_MACHINE_BROKEN_LV2_ID                       5
#define GFX_MACHINE_WORK_LV3_ID                         6
#define GFX_MACHINE_REST_LV3_ID                         7
#define GFX_MACHINE_BROKEN_LV3_ID                       8
#define GFX_MACHINE_ICON_LV1_ID                         9
#define GFX_MACHINE_ICON_LV2_ID                         10
#define GFX_MACHINE_ICON_LV3_ID                         11

#define DEFINE_KEYBOARD_TYPE_TEXT                       0x00000001
#define DEFINE_KEYBOARD_TYPE_NUMBER                     0x00000002

#define SNS_WARNING_LEVEL          10

#define TUTORIAL_LEVEL_UNLOCK_GROW_PLANT    2
#define TUTORIAL_LEVEL_UNLOCK_OPEN_MACHINE  3
#define TUTORIAL_LEVEL_UNLOCK_ORDER         4
#define TUTORIAL_LEVEL_UNLOCK_OPEN_CLOUD    5
#define TUTORIAL_LEVEL_CONNECT_SNS          6
#define TUTORIAL_LEVEL_UNLOCK_PS            8
#define TUTORIAL_LEVEL_UNLOCK_UPGRADE_POT   16

#define GROUND_HOUSES_LEVEL_REQUIRE                     TUTORIAL_LEVEL_UNLOCK_PS
#define WARE_HOUSE_LEVEL_REQUIRE                        TUTORIAL_LEVEL_UNLOCK_GROW_PLANT
#define UPGRADE_POT_LEVEL_REQUIRE                       TUTORIAL_LEVEL_UNLOCK_UPGRADE_POT

#define CONFIG_INFO_FORMAT                              "music:%d sound:%d intro:%d"
