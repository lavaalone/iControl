
#if defined(WIN_OS)
	typedef signed __int8     	int8_t;
	typedef signed __int16    	int16_t;
	typedef signed __int32    	int32_t;
	typedef signed __int64      int64_t;
	typedef unsigned __int8   	uint8_t;
	typedef unsigned __int16  	uint16_t;
	typedef unsigned __int32  	uint32_t;
	typedef unsigned __int64    uint64_t;

	//type define
	typedef uint8_t					UINT8;
	typedef int8_t					INT8;
	typedef uint8_t					BYTE;

	typedef uint16_t				UINT16;
	typedef int16_t					INT16;
	typedef uint32_t				UINT32;
	typedef int32_t					INT32;
	typedef uint64_t 				UINT64;
	typedef int64_t 				INT64;

	typedef uint16_t				UNICHAR;
#else

	#include <stdint.h>

	//type define
	typedef uint8_t					UINT8;
	typedef int8_t					INT8;
	typedef uint8_t					BYTE;
	typedef uint16_t				UINT16;
	typedef int16_t					INT16;
	typedef uint32_t				UINT32;
	typedef int32_t					INT32;
	typedef uint64_t 				UINT64;
	typedef int64_t 				INT64;

	typedef uint16_t				UNICHAR;
#endif

// special data types for scripting
typedef double						t_timer;
typedef short						t_var;
typedef short						t_param;

#define FORMAT_NUMBER_TYPE          INT64	//update FORMAT_NUMBER_PRINT_STR if change FORMAT_NUMBER_TYPE
#define FORMAT_NUMBER_PRINT_STR		"%lld"
typedef struct sRect {
	float x;
	float y;
	float w;
	float h;
} sRECT;

typedef struct sPoint {
	float x;
	float y;
} sPOINT;

#define GAME_INSTANCE				            CGame::_this
#define GAME_STATEMACHINE			            CGame::_this->getStateMachine()
#define GAMEPLAY_BACKGROUND                     cStateGamePlay::GetInstance()->GetBackGround()
#define STATE_GAMEPLAY_CAMERA		            cStateGamePlay::GetInstance()->m_Camera
#define STATE_GAMEPLAY		                    cStateGamePlay::GetInstance()
#define STATE_LEVELUP		                    cStateLevelUp::GetInstance()
#define STATE_PRIVATESHOP                       cStatePrivateShop::GetInstance()
#define STATE_SNS_WARNING                       cStateSNSWarning::GetInstance()
#define STATE_DIALOG		                    cStateDialog::GetInstance()
#define STATE_WAREHOUSE		                    cStateWareHouse::GetInstance()
#define STATE_OPENCLOUD		                    cStateOpenCloud::GetInstance()
#define STATE_WAREHOUSE_CAMERA		            cStateWareHouse::GetInstance()->_camera
#define STATE_UPGRADEPOT		                cStateUpgradePot::GetInstance()
#define STATE_NEWSBOARD 		                cStateNewBoard::GetInstance()
#define STATE_SYSTEMGIFTS 		                cStateSystemGift::GetInstance()
#define STATE_BUILDING_INFO 	                cStateBuildingInfo::GetInstance()
#define STATE_UPGRADE_BUILDING                  cStateUpgradeBuilding::GetInstance()
#define STATE_UPGRADE_SUCCESS                   cStateUpgradeSuccessful::GetInstance()
#define STATE_USE_ALL_ITEMS_WARNING             cStateUseItemWarning::GetInstance()
#define STATE_UPDATE_LATER                      cStateUpdateLater::GetInstance()
#define STATE_DISCONNECT                        cStateDisconnectScreen::GetInstance()
#define STATE_LOADING                           CStateLoading::GetInstance()
#define STATE_LOADING_SCREEN                    cStateLoadingScreen::GetInstance()
#define STATE_NOTENOUGH_MONEY                   cStateNotEnoughMoney::GetInstance()
#define STATE_TUTORIAL_NPC                      cStateTutorialNPC::GetInstance()
#define STATE_TUTORIAL_NPC_RED                  cStateTutorialNPCRed::GetInstance()
#define STATE_TUTORIAL_SHADOW                   cStateTutorialShadow::GetInstance()
#define STATE_MACHINE_UPGRADE_WARNING           cStateMachineUpgradeWarning::GetInstance()
#define STATE_ORDER                        		cStateNewOrder::GetInstance()
#define STATE_PAYMENT                        	CStatePayment::GetInstance()
#define UI_FRIENDLIST		                    CFriendList::GetInstance()
#define UI_MENU		                            CUIMenu::GetInstance()
#define GAME_BEANTREE				            cBeanTree::GetInstance()
#define GAME_ACTIONMENU                         CGame::_this->getMenuAction()
#define GAME_USERINTERFACE                      CUserInterface::GetInstance()
#define GAME_PRIVATESHOPDATA                    CGame::_this->GetUserData()->GetPrivateShopInfo()
#define GAME_BUILDINGINFO(id)                   CGame::_this->getBuildingInfoDatabase(id)
#define GAME_PRODUCTINFO(id)                    CGame::_this->getProductItemInfoDatabase(id)
#define GAME_PLANTPOTINFO(id)                   CGame::_this->getPlantPotInfoDatabase(id)
#define GAME_PLANTINFO(id)                      CGame::_this->getPlantInfoDatabase(id)
#define GAME_BUGINFO(id)                        CGame::_this->getBugInfoDatabase(id)
#define GAME_LEVELINFO(id)                      CGame::_this->getLevelInfoDatabase(id)
#define GAME_TUTORIAL_INFO                      CGame::_this->getTutorailInfoDatabase()
#define GAME_TUTORIAL_LOGIC                     CGame::_this->getTutorialLogic()
#define GAME_BROADCAST_INFO                     CGame::_this->GetBroadcastInfo()
#define GAME_MATERIALINFO(id)                   CGame::_this->getMaterialInfoDatabase(id)
#define GAME_NEWSBOARDINFO                      GAME_INSTANCE->getNewBoardInfo()
#define GAME_SHOW_ALPHABG(isShow, priority)     CGame::_this->ShowAlphaBackground(isShow, priority)
#define GAME_USERDATA                           CGame::_this->GetUserData()
#define GAME_USERLEVEL                          GAME_USERDATA->GetUserInfo()->GetUserLevel()
#define GAME_ORDERSYSTEM                        CStateOrder::GetInstance()
#define GAME_ORDERINFO                          GAME_INSTANCE->GetQuestDatabase()
#define GAME_LEVELUP                            cStateLevelUp::GetInstance()
#define GAME_MISSIONOWL                         CMissionOwl::GetInstance()
#define	SHOW_WARNING_TEXT                       GAME_INSTANCE->WarningText
#define	GAME_DEVICENAME                         GAME_INSTANCE->GetDeviceName
#define	GAME_FIRMWAREVER                        GAME_INSTANCE->GetFirmwareVer
#if USE_FRIEND_LIST == 1
#define GAME_FRIENDLIST                         CGame::_this->GetFriendList()
#define	GAME_IS_AT_FRIEND_GARDEN                GAME_INSTANCE->IsAtFriendGarden()
#endif
#define GAME_GLOBAL_TOOLTIP                     CGame::global_tooltip
#define GAME_UPGRADE_ITEM_FACTORY               CBubleUpgradeItemFactory::GetInstance()
#define CHECK_WARE_HOUSE_WITH_POPUP             GAME_INSTANCE->CheckAndShowFullWareHousePopup
#define CHECK_WARE_HOUSE                        GAME_INSTANCE->CheckAndShowFullWareHouse

#ifdef USE_FLURRY
/**
- event_name: ten cua su kien:
- event_param first: ten cua param
- event_param second: gia tri cua param
**/
    #define LOG_FURRY                           GAME_INSTANCE->LogFlurry
#endif

#if (USE_TUTORIAL == 1)

#endif

#ifdef USE_FACEBOOK
#define ISCONNECT_FACEBOOK                  CGame::_this->IsConnectFacebook()
#define ISLINK_FACEBOOK                     CGame::_this->IsLinkFacebook()
#define CONNECT_FACEBOOK                    CGame::_this->ConnectFacebook
#define FEEDWALL_FACEBOOK                    CGame::_this->FeedWallFacebook
#endif
#ifdef USE_ZINGME
#define ISCONNECT_ZING                  CGame::_this->IsConnectZing()
#define ISLINK_ZING                     CGame::_this->IsLinkZing()
#endif
#define GET_PLANT_DIAMOND_SKIP_TIME(time)             GAME_INSTANCE->getDiamondSkipTimeInfo()->GetPlantEstimateDiamond(time);
#define GET_MACHINE_DIAMOND_SKIP_TIME(time)           GAME_INSTANCE->getDiamondSkipTimeInfo()->GetMachineEstimateDiamond(time);
#define GET_PRODUCT_DIAMOND_SKIP_TIME(time)           GAME_INSTANCE->getDiamondSkipTimeInfo()->GetProductEstimateDiamond(time);
#define GET_SKIP_ADS_DIAMOND_SKIP_TIME(time)          GAME_INSTANCE->getDiamondSkipTimeInfo()->GetSkipAdsEstimateDiamond(time);
#define GET_SKIP_ORDER_DIAMOND_SKIP_TIME(time)        GAME_INSTANCE->getDiamondSkipTimeInfo()->GetSkipOrderEstimateDiamond(time);

#define	SHOW_SRPITE_TEXT_ALIGN                  _LEFT|_TOP
#define	SHOW_SRPITE                             GAME_INSTANCE->ShowSprite
#define GAME_IBSHOP				                cStateIBShop::GetInstance()
#define GAME_OPTION				                CStateOption::GetInstance()

#define GAME_DESTINATION_STORE                  STATE_GAMEPLAY->GetDestinationStore()

#ifndef NULL
	#define NULL				0
#endif
#define CHECKQUEST                  GAME_ORDERSYSTEM->CheckAllQuest()
#define SAFE_DEL(a)					{if(a){delete (a);(a) = NULL;}}
#define SAFE_DEL_INTERACTIVE(a)		{if(a){InteractiveList::Remove(a);a = NULL;}}
#define SAFE_DEL_DISPLAYOBJECT(a)	{if(a){DisplayList::Remove(a);a = NULL;}}
#define SAFE_DEL_ARRAY(a)			{if(a){delete[] (a);(a) = NULL;}}
#define SAFE_DEL_ARRAY_TYPE(a, t)	{if((t)a){delete[] ((t)(a));(a) = NULL;}}
#define SAFE_DEL_ARRAY_OBJ(p, n)	{if (p) {for (int __i = 0; __i < (n); __i++) SAFE_DEL((p)[__i]); SAFE_DEL_ARRAY(p);}}
#define SAFE_DEL_ARRAY_ARRAY(p, n)	{if (p) {for (int __i = 0; __i < (n); __i++) SAFE_DEL_ARRAY((p)[__i]); SAFE_DEL_ARRAY(p);}}

#define TEST_FLAG(var, flag)				((var & (flag)) != (0))
#define SET_FLAG(var, flag)					(var |= (flag))
#define CLEAR_FLAG(var, flag)				(var &= ~(flag))

//treebean
#if (BUILD_QUALITY==BUILD_SD)
#define CONVERT_INT(a)				    ((int)(a))
#elif (BUILD_QUALITY==BUILD_HD_960_640)
#define CONVERT_INT(a)				    (a)
#else
#define CONVERT_INT(a)				    (a)
#endif

#define GX_ASSERT
#define	FB_NEW						new

#define UNISTRING   std::basic_string<UNICHAR>
