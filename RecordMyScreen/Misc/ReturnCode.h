


#define RESPONSE_ERROR 					 0 // request fail
#define RESPONSE_OK 					 1

#define RESPONSE_SAVE_ERROR 					 2 // critical error, should reload all data
#define RESPONSE_LOAD_ERROR 					 3 // critical error, should reload all data

#define RESPONSE_INVALID_PARAMS 					 4
#define RESPONSE_INVALID_FLOOR_PARAM 					 5 // floor param < 0 or >					 userTotalFloor.
#define RESPONSE_INVALID_SLOT_PARAM 					 6 // slot < 0 or slot >					 max_slot_per_floor.

#define RESPONSE_STOCK_IS_FULL 					 7 // full stock, can't increase more item.

#define RESPONSE_POT_IS_NOT_EMPTY 					 8 // pot is containing plant, can not move/hide/delete
#define RESPONSE_CANT_FIND_POT 					 9 // slot is empty, can not find pot

#define RESPONSE_INVALID_PLANT_ID 					 10 // invalid plant id ( plant id < 0 or plant id > max_plant_id)
#define RESPONSE_INVALID_POT_ID 					 11 // invalid pot id ( pot id < 0 or pot id > max_pot_id)

#define RESPONSE_CANT_DELETE_POT 					 12 // concurrent access problem
#define RESPONSE_CANT_CREATE_NEW_POT 					 13 // concurrent access problem

#define RESPONSE_CANT_INCREASE_OBJECT 					 14 // stock
#define RESPONSE_CANT_DECREASE_OBJECT 					 15 // stock
#define RESPONSE_CANT_SET_OBJECT_VALUE 					 16 // stock

#define RESPONSE_SLOT_IS_NOT_EMPTY 					 17 // slot is not empty, can not place more pot

#define RESPONSE_NOT_ENOUGH_GOLD 					 18
#define RESPONSE_NOT_ENOUGH_REPUTATION 					 19
#define RESPONSE_NOT_ENOUGH_DIAMOND 					 20
#define RESPONSE_NOT_ENOUGH_LEVEL 					 21

#define RESPONSE_UPGRADE_POT_SUCCESS 					 22
#define RESPONSE_UPGRADE_POT_FAIL 					 23

#define RESPONSE_INVALID_MACHINE_ID 					 24
#define RESPONSE_PRODUCT_NOT_COMPLETE 					 25
#define RESPONSE_MACHINE_IS_EMPTY 					 26

#define RESPONSE_ORDER_PRODUCT_NOT_ENOUGH 					 27
#define RESPONSE_ORDER_STILL_WAITING 					 28

#define RESPONSE_IBS_INVALID_PACK_ID 					 29
#define RESPONSE_IBS_PACK_NOT_ACTIVE 					 30
#define RESPONSE_STOCK_ADD_ITEM_FAILED 					 31
#define RESPONSE_IBS_INVALID_ITEM_TYPE 					 32
#define RESPONSE_IBS_ITEM_SOLD_OUT 					 33
#define RESPONSE_IBS_INVALID_PRICE 					 34
#define RESPONSE_CANT_SUBSTRACT_MONEY 					 35
#define RESPONSE_NOT_ENOUGH_PRODUCT 					 36
#define RESPONSE_IBS_INVALID_SALE_DATE 					 37
#define RESPONSE_IBS_PACKAGE_OUT_DATE 					 38

#define RESPONSE_INVALID_PRODUCT_ID 					 39

#define RESPONSE_PS_CANT_FIND_UNOCCUPIED_SLOT_FRIEND					 40
#define RESPONSE_PS_CANT_ADD_SLOT 					 41
#define RESPONSE_PS_INVALID_FRIEND_NUMBER 					 42

#define RESPONSE_LOAD_FRIEND_DATA_ERROR 					 43
#define RESPONSE_CANCEL_ITEM_PS_FAILED 					 44
#define RESPONSE_PS_ADS_NOT_AVAILABLE 					 45
#define RESPONSE_PS_ITEM_NOT_SELLING 					 46
#define RESPONSE_PS_CANT_FIND_UNOCCUPIED_SLOT_DIAMOND 					 47
#define RESPONSE_CONCURRENT_ACCESS_PROBLEM 					 48
#define RESPONSE_FB_ID_ALREADY_USED 					 49
#define RESPONSE_PS_ITEM_IS_NOT_SOLD 					 50
#define RESPONSE_FB_AUTHENTICATE_FAIL 					 51
#define RESPONSE_POT_AT_MAX_ID 					 52
#define RESPONSE_CANT_GET_PS_MANAGER 					 53
#define RESPONSE_PS_DATA_IS_LOCKED 					 54 // should display the message please try again later (max 12 seconds)

#define RESPONSE_INVALID_ORDER_INDEX 					 55

#define RESPONSE_REQUIRE_LOGIN 					 56 // should send command login

#define RESPONSE_UPGRADE_MACHINE_SUCCESS 					 57
#define RESPONSE_UPGRADE_MACHINE_FAIL 					 58

#define RESPONSE_MACHINE_DATA_IS_LOCKED 					 59

#define RESPONSE_MACHINE_HAD_BEEN_REPAIRED 					 60

#define RESPONSE_ALREADY_LOGIN 					 61

#define RESPONSE_INVALID_ORDER_LETTER_INDEX 					 62

#define RESPONSE_WRONG_REQUEST_ID 					 63

#define RESPONSE_UPGRADE_FAIL_LOSE_POT 					 64

#define RESPONSE_WRONG_UPDATE_VERSION 					 65

#define RESPONSE_RETRY_LOGIN 					 66
#define RESPONSE_BAN 					 67

#define RESPONSE_NEW_DATE 					 68

#define RESPONSE_INVALID_ORDER_TYPE 					 69

#define RESPONSE_PROCESSING_SOCIAL_LOGIN 					 70

#define RESPONSE_EXIT_GAME 					 127

