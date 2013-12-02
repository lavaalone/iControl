#ifndef DEFINES_ZORDER_H_INCLUDED
#define DEFINES_ZORDER_H_INCLUDED

// càng lớn thì độ ưu tiên càng cao

#define     Z_GAMEPLAY_RECT                 10

#define     Z_TREE_BEAN                     40
#define     Z_CLOUD_FLOOR                   50  //50 - 80
#define     Z_BEAN_SLOT                     99
#define     Z_CLOUD_SLOT                    100
#define     Z_PLANT_POT                     117
#define     Z_CLOUD_SLOT_OVER               118
#define     Z_BUILDING_ITEM                 210
#define     Z_BUILDING_COMPLETE_ITEM        500

#define     Z_DROP_HARVEST_ITEM             2000

#define     Z_UI_MENU                       4000
#define     Z_FRIEND_LIST                   4000

#define     Z_BNT_INTERFACE                 5000


#define     Z_UPGRADE_POT                   14000

#define     Z_BUILDING_INFO                 14500
#define     Z_UPGRADE_BUILDING              14800


#define     Z_ACTION_MENU                   15000    //tất cả các item của action menu nên có z lớn hơn
#define     Z_ACTION_MENU_ITEM              15010    //tất cả các item của action menu nên có z lớn hơn
#define     Z_ACTION_MENU_ITEM_PAGE         15011    //tất cả các item của action menu nên có z lớn hơn

#define     Z_UPGRADE_WARNING               16000

#define     Z_ORDER_OWL                     17000

#define     Z_WAREHOUSE                     17500
#define     Z_PRIVATESHOP                   18000
#define     Z_PRIVATESHOP_UPDATE            18500
#define     Z_WAREHOUSE_STATE               18900    //tất cả các item của wallhouse nên có z lớn hơn

#define     Z_VERSION_ORDERSYSTEM           20000

#define     Z_NEWBOARD                      21000

#define     Z_POPUP_TOOLTIP_BACKGROUND      22000
#define     Z_POPUP_TOOLTIP                 22001
#define     Z_POPUP_TOOLTIP_BUTTON          22010

#define     Z_OPEN_CLOUD                    26000
#define     Z_UNLOCK_ICE_MACHINE            27000
#define     Z_DIALOG                        28000    // for dialog

#define     Z_NOTENOUGMONEY                 47000
#define     Z_IBSHOP                        48000

#define     Z_DESTINATION_SHOP_ICON         49000

#define     Z_TUTORIAL_SHADOW               50000
#define     Z_TUTORIAL_NPC                  51000

#define     Z_UPDATELATER                   52000

#define     Z_CONNECT_SNS_WARNING           52500

#define     Z_VERSION_LEVEL_UP              53000

#define     Z_LEVELUP                       54000

#define     Z_BROADCAST_TEXT                70000
#define     Z_RECONNECT_SCREEN              80000
#define     Z_VERSION_TEXT                  100000    // Version always on top
#endif // DEFINES_ZORDER_H_INCLUDED
