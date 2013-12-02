#ifndef DEFINE_FLURRY_H_INCLUDED
#define DEFINE_FLURRY_H_INCLUDED

/**************************GLOBAL DEFINE*******************************/
#define		FLURRY_PARAMETER_NAME                "Name"
#define		FLURRY_PARAMETER_DIAMON              "Diamon"
#define		FLURRY_PARAMETER_LEVEL               "Level"
#define		FLURRY_PARAMETER_EXP                 "Exp"
#define		FLURRY_PARAMETER_REPU                "Repu"
#define		FLURRY_PARAMETER_NUMBER              "Number"
#define		FLURRY_PARAMETER_MACHINE             "Machine"
#define		FLURRY_PARAMETER_PRODUCT             "Product"
#define		FLURRY_PARAMETER_TYPE                "Type"
#define		FLURRY_PARAMETER_DOF                 "DOF"
#define		FLURRY_PARAMETER_NUM_DOF             "Num DOF"
#define		FLURRY_PARAMETER_CAPACITY            "Capacity"
#define		FLURRY_PARAMETER_QUANTITY            "Quantity"
#define		FLURRY_PARAMETER_PRICE               "Price"
#define		FLURRY_PARAMETER_ITEM_TYPE           "Item Type"
#define		FLURRY_PARAMETER_ITEM_NAME           "Item Name"
#define		FLURRY_PARAMETER_ADS                 "Have Ad"
#define		FLURRY_PARAMETER_FRIENDS             "Friends"
#define		FLURRY_PARAMETER_IS_FRIEND           "Is Friend"
#define		FLURRY_PARAMETER_IS_NOT_FRIEND       "Is Not Friend"
#define		FLURRY_PARAMETER_GAME_STATE          "Game State"
#define		FLURRY_PARAMETER_START_POINT         "Start Point"


/**************************EVENT NAME PLANT*******************************/
#define		FLURRY_EVENT_PLANT_SKIP_TIME            "Plant_Skip_Time"
#define		FLURRY_EVENT_PLANT_BUY_DIRECT           "Plant_Buy_Direct"
#define		FLURRY_EVENT_PLANT_BUY_CRACKET          "Plant_Buy_Vot"

/**************************EVENT NAME STORAGE*******************************/
#define		FLURRY_EVENT_STORAGE_UPGRADE            "Storage_Upgrade"
#define		FLURRY_EVENT_STORAGE_UPGRADE_FARM       "Storage_Upgrade_Farm"
#define		FLURRY_EVENT_STORAGE_UPGRADE_PRODUCT    "Storage_Upgrade_Product"
#define		FLURRY_EVENT_STORAGE_UPGRADE_ITEM       "Storage_Upgrade_Item"

#define		FLURRY_EVENT_STORAGE_BUY_MATERIAL       "Storage_Buy_Material_%d"


/**************************EVENT NAME STORAGE*******************************/
#define		FLURRY_EVENT_IBSHOP_GOLD                "IBShop_Gold"
#define		FLURRY_EVENT_IBSHOP_POT                 "IBShop_Pot"
#define		FLURRY_EVENT_IBSHOP_UPGRADE             "IBShop_Upgrade"
#define		FLURRY_EVENT_IBSHOP_OTHER               "IBShop_Other"


/**************************EVENT NAME LEVELUP*******************************/
#define		FLURRY_EVENT_LEVEL_UP                   "Level_up"
#define		FLURRY_EVENT_CLOUD_UNLOCK               "Cloud_Unlock"
#define		FLURRY_EVENT_CLOUD_OPEN                 "Cloud_Open"

/**************************EVENT NAME MACHINE*******************************/
#define		FLURRY_EVENT_MACHINE_UNLOCK            "Machine_Unlock"
#define		FLURRY_EVENT_MACHINE_UNFREEZE          "Machine_UnFreeze"
#define		FLURRY_EVENT_MACHINE_SKIPTIME          "Machine_SkipTime"
#define		FLURRY_EVENT_MACHINE_OPEN              "Machine_Open"
#define		FLURRY_EVENT_MACHINE_BUY_SLOT          "Machine_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_0_BUY_SLOT        "Machine_%d_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_1_BUY_SLOT        "Machine_1_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_2_BUY_SLOT        "Machine_2_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_3_BUY_SLOT        "Machine_3_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_4_BUY_SLOT        "Machine_4_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_5_BUY_SLOT        "Machine_5_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_6_BUY_SLOT        "Machine_6_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_7_BUY_SLOT        "Machine_7_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_8_BUY_SLOT        "Machine_8_Buy_Slot"
#define		FLURRY_EVENT_MACHINE_REPAIR            "Machine_Repair"

/**************************EVENT NAME PRODUCT*******************************/
#define		FLURRY_EVENT_PRODUCT_PRODUCE           "Product_Produce"
#define		FLURRY_EVENT_PRODUCT_SKIP_TIME         "Product_SkipTime"
#define		FLURRY_EVENT_PRODUCT_BUY_DIRECT        "Product_BuyDirect"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_0         "Product_Produce_%d"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_1         "Product_Produce_1"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_2         "Product_Produce_2"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_3         "Product_Produce_3"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_4         "Product_Produce_4"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_5         "Product_Produce_5"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_6         "Product_Produce_6"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_7         "Product_Produce_7"
#define		FLURRY_EVENT_PRODUCT_PRODUCE_8         "Product_Produce_8"

/**************************EVENT NAME ORDER*******************************/
#define		FLURRY_EVENT_ORDERS_CREATE             "Orders_Create"
#define		FLURRY_EVENT_ORDERS_COMPLETE           "Orders_Complete"
#define		FLURRY_EVENT_ORDERS_CANCEL             "Orders_Cancel"
#define		FLURRY_EVENT_ORDERS_SKIP_TIME          "Orders_SkipTime"
#define		FLURRY_EVENT_ORDERS_BUY_ITEM           "Orders_BuyItem"
#define		FLURRY_EVENT_ORDERS_DOF_RESELECT       "Orders_DOF_Reselect"
#define		FLURRY_EVENT_ORDERS_DOF_SELECT         "Orders_DOF_Select"
#define		FLURRY_EVENT_ORDERS_DOF_COMPLETE       "Orders_DOF_Complete"
#define		FLURRY_EVENT_ORDERS_DOP_SELECT         "Orders_DOP_Select"
#define		FLURRY_EVENT_ORDERS_DOP_COMPLETE       "Orders_DOP_Complete"


/**************************EVENT NAME PRIVATESHOP*******************************/
#define		FLURRY_EVENT_PSHOP_OPEN_SLOT_BY_DIAMOND          "PShop_Open_Slot_By_Diamond"
#define		FLURRY_EVENT_PSHOP_OPEN_SLOT_BY_FRIEND           "PShop_Open_Slot_By_Friend"
#define		FLURRY_EVENT_PSHOP_SELL                          "PShop_Sell"
#define		FLURRY_EVENT_PSHOP_SELL_AD                       "PShop_Sell_Ad"
#define		FLURRY_EVENT_PSHOP_SKIP_TIME_AD                  "PShop_SkipTime_Ad"
#define		FLURRY_EVENT_PSHOP_SELL_0                        "PShop_Sell_%d"
#define		FLURRY_EVENT_PSHOP_SELL_1                        "PShop_Sell_1"
#define		FLURRY_EVENT_PSHOP_SELL_2                        "PShop_Sell_2"
#define		FLURRY_EVENT_PSHOP_SELL_3                        "PShop_Sell_3"
#define		FLURRY_EVENT_PSHOP_SELL_4                        "PShop_Sell_4"
#define		FLURRY_EVENT_PSHOP_SELL_5                        "PShop_Sell_5"
#define		FLURRY_EVENT_PSHOP_SELL_6                        "PShop_Sell_6"
#define		FLURRY_EVENT_PSHOP_SELL_7                        "PShop_Sell_7"
#define		FLURRY_EVENT_PSHOP_SELL_8                        "PShop_Sell_8"
#define		FLURRY_EVENT_PSHOP_SELL_9                        "PShop_Sell_9"
#define		FLURRY_EVENT_PSHOP_SELL_10                       "PShop_Sell_10"
#define		FLURRY_EVENT_PSHOP_BUY                           "PShop_Buy"

/**************************EVENT NAME OTHER*******************************/
#define     FLURRY_EVENT_OTHER_DISCONNECT                    "Disconnect"
#define     FLURRY_EVENT_OTHER_FACEBOOK_LINK                 "Facebook_Link"

/**************************EVENT NAME STATE*******************************/
#define     FLURRY_EVENT_STATE_GARDEN                        "State_Garden"
#define     FLURRY_EVENT_STATE_ORDERS                        "State_Orders"
#define     FLURRY_EVENT_STATE_NEWBOARD                      "State_Newboard"
#define     FLURRY_EVENT_STATE_PSHOP_ME                      "State_PShop_Me"
#define     FLURRY_EVENT_STATE_STORAGE_FARM                  "State_Storage_Farm"
#define     FLURRY_EVENT_STATE_STORAGE_PRODUCT               "State_Storage_Product"
#define     FLURRY_EVENT_STATE_STORAGE_ITEM                  "State_Storage_Item"
#define     FLURRY_EVENT_STATE_STORAGE_FARM_UPGRADE          "State_Storage_Farm_Upgarde"
#define     FLURRY_EVENT_STATE_STORAGE_PRODUCT_UPGRADE       "State_Storage_Product_Upgarde"
#define     FLURRY_EVENT_STATE_STORAGE_ITEM_UPGRADE          "State_Storage_Item_Upgarde"


#endif // DEFINE_FLURRY_H_INCLUDED
