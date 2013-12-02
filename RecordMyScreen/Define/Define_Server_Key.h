// ------------------------------------- REQUEST -------------------------------
#define	KEY_USER_COMMAND_ID				"command_id"
#define	KEY_USER_REQUEST_STATUS			"request_status"
#define	KEY_USER_ID						"user_id"
#define	KEY_DEVICE_ID					"device_id"
#define	KEY_USER_REQUEST_ID				"request_id"
#define	KEY_USER_SESSION_ID				"session_id"
#define	KEY_USER_NEW_SESSION_ID 		"new_session_id"
#define	KEY_REQUEST_STATUS				"request"
#define	KEY_FACEBOOK_ID					"fb_id"
#define	KEY_FACEBOOK_ACCESS_TOKEN		"fb_access_token"

#define	KEY_USER_INFOS					"user"
#define	KEY_SEED_INFOS					"seed"
#define	KEY_POT_INFOS					"pot"
#define	KEY_PEST_INFOS					"pest"
#define	KEY_WAREHOUSE_INFOS				"warehouse"

#define	KEY_FLOORS						"floor_%d"
#define	KEY_STOCKS						"stock_%d"
#define	KEY_MACHINES					"machine_%d"
#define	KEY_SLOTS					    "slot_%d"
#define	KEY_GAME_CONSTANT				"gc_%d"
//------------------------------------- ORDER ---------------------------------
#define KEY_ORDER_DELIVERED_NUM         "order_delivered_num"
#define KEY_ORDER                       "order"
#define KEY_USER_ORDER_COUNT            "user_order_count"
#define KEY_NPC_ORDER                   "order_npc"
#define KEY_USER_ORDER					"user_order_%d"

#define KEY_ORDER_ID					"order_id"
#define KEY_ORDER_DELIVERY_TIME			"order_delivery_time"
#define KEY_ORDER_REWARD_GOLD			"order_reward_gold"
#define KEY_ORDER_REWARD_EXP			"order_reward_exp"
#define KEY_ORDER_ITEM_COUNT			"order_reward_item_count"
#define KEY_ORDER_PRODUCT_COUNT			"order_reward_prod_count"
#define KEY_ORDER_NEW_WAIT_TIME			"order_new_wait_time"
#define KEY_ORDER_INDEX					"order_index"

// ------------------------------------- USER -------------------------------
#define KEY_USER_LEVEL					"user_level"
#define KEY_USER_EXP						"user_exp"
#define KEY_USER_EXP_LVL					"user_exp_lvl"
#define KEY_USER_GOLD					"user_gold"
#define KEY_USER_DIAMOND					"user_diamond"
#define KEY_USER_REPUTATION				"user_reputation"
#define KEY_USER_FLOOR					"user_floor"
#define KEY_USER_VIP_LEVEL				"user_vip_level"
#define KEY_USER_VIP_ACTIVE				"user_vip_active"
#define KEY_USER_VIP_TIME				"user_vip_time"
#define KEY_USER_NAME					"user_name"

// ------------------------------------- FLOOR -------------------------------
#define FLOOR_NUM						"floor_num"
#define HARVEST_FIRST_FLOOR				"harvest_first_floor"
#define HARVEST_SECOND_FLOOR				"harvest_second_floor"
#define PLANT_FIRST_FLOOR				"plant_first_floor"
#define PLANT_SECOND_FLOOR				"plant_second_floor"
#define PUT_POT_FIRST_FLOOR				"put_pot_first_floor"
#define PUT_POT_SECOND_FLOOR				"put_pot_second_floor"

// ------------------------------------- STOCK -------------------------------
#define KEY_STOCK_ID						"stock_id"
#define KEY_STOCK_SILO					"stock_silo"
#define KEY_STOCK_BARN					"stock_barn"
#define KEY_STOCK_WAREHOUSE				"stock_warehouse"
#define KEY_STOCK_CAPACITY_MAX			"capacity_max"
#define KEY_STOCK_CAPACITY_CUR			"capacity_cur"

#define KEY_STOCK_PRODUCT_COUNT			"stock_product_count"
#define KEY_STOCK_PRODUCT_TYPE			"stock_product_type"
#define KEY_STOCK_PRODUCT_ID				"stock_product_id"
#define KEY_STOCK_PRODUCT_NUM			"stock_product_num"
#define KEY_STOCK_TOTAL_ITEM			"stock_total_item"

#define KEY_STOCK_LEVEL					"stock_level"

// ------------------------------------- SLOT -------------------------------
#define SLOT_PROPERTY_POT_ID				"pot_id"
#define SLOT_PROPERTY_SEED_ID			"seed_id"
#define SLOT_PROPERTY_GROWTIME			"growtime"
#define SLOT_PROPERTY_SOWTIME			"sowtime"
#define SLOT_PROPERTY_XP_RECEIVE			"xp"
#define SLOT_PROPERTY_PEST_ID			"pest"

// ------------------------------------- MACHINE -------------------------------
#define KEY_MACHINE_ID					"machine_id"
#define KEY_MACHINE_LEVEL				"machine_level"
#define KEY_MACHINE_ACTIVE_TIME			"machine_active_time"
#define KEY_MACHINE_STATUS				"status"
#define KEY_MACHINE_DURABILITY_CUR		"durability_cur"
#define KEY_MACHINE_SLOT_MAX				"slot_max"
#define KEY_MACHINE_SLOT_CUR				"slot_cur"
#define KEY_MACHINE_PROD_COUNT			"prod_count"
#define KEY_MACHINE_PROD_INFOS			"prod_info"

#define KEY_MACHINE_SLOT_PRODUCT_ID		"slot_product_id"
#define KEY_MACHINE_SLOT_PRODUCT_TIME	"slot_product_time"

#define KEY_MACHINE_PROD_STATUS			"prod_status"

#define KEY_MACHINE_PROD_SLOT_ID			"prod_slot_id"
#define KEY_MACHINE_AT_FLOOR				"machine_at_floor"

#define KEY_STOCK_PROD_COMPLETED			"stock_prod_completed"

// ------------------------------------- PRODUCT -------------------------------
#define KEY_PRODUCT_TYPE					"product_type"
#define KEY_PRODUCT_ID					"product_id"
#define KEY_MATERIAL_ID					"material_id"

// ------------------------------------- PLANT -------------------------------
#define KEY_PLANT_ID						"plant_id"
#define KEY_PLANT_NAME					"plant_name"
#define KEY_PLANT_PRICE					"plant_price"
#define KEY_PLANT_GROW_TIME				"plant_grow_time"
#define KEY_PLANT_HARVEST_EXP			"plant_harvest_exp"
#define KEY_PLANT_ITEM_RECEIVE_RATIO		"plant_item_receive_ratio"
#define KEY_PLANT_DIAMON_SKIP_TIME		"plant_diamond_skip_time"
#define KEY_PLANT_DIAMON_BUY				"plant_diamond_buy"
#define KEY_PLANT_GOLD_SELL_DEFAULT		"plant_gold_sell_default"
#define KEY_PLANT_GOLD_SELL_MIN			"plant_gold_sell_min"
#define KEY_PLANT_GOLD_SELL_MAX			"plant_gold_sell_max"
#define KEY_PLANT_BUG_ID					"plant_bug_id"
#define KEY_PLANT_HAS_BUG					"plant_has_bug"
#define KEY_PLANT_BUG_APPEAR_RATIO		"plant_bug_appear_ratio"
#define KEY_PLANT_CURRENT_LEVEL			"plant_current_level"
#define KEY_PLANT_HARVEST_TO_LEVEL_UP	"plant_harvest_to_level_up"
#define KEY_PLANT_AT_FLOOR               "plant_at_floor"
#define KEY_PLANT_AT_SLOT                "plant_at_slot"
#define KEY_PLANT_LEVEL                  "plant_level"

// ------------------------------------- POT -------------------------------
#define KEY_POT_ID						"pot_id"
#define KEY_POT_NAME						"pot_name"
#define KEY_POT_PRICE					"pot_price"
#define KEY_POT_UNLOCK_EXP				"pot_unlock_exp"
#define KEY_POT_EXP_INCREASE				"pot_exp_increase"
#define KEY_POT_TIME_DECREASE			"pot_time_decrease"
#define KEY_POT_BUG_APPEAR_RATIO			"pot_bug_appear_ratio"
#define KEY_POT_EXP_RATIO				"pot_exp_ratio"
#define KEY_POT_GOLD_UPGRADE				"pot_gold_upgrade"
#define KEY_POT_PEARL_ID_NUM				"pot_pearl_id_num"
#define KEY_POT_UPGRADE_RATIO			"pot_upgrade_ratio"
#define KEY_POT_GOLD_DEFAULT				"pot_gold_default"
#define KEY_POT_GOLD_MIN					"pot_gold_min"
#define KEY_POT_GOLD_MAX					"pot_gold_max"
#define KEY_POT_AT_FLOOR					"pot_at_floor"
#define KEY_POT_AT_SLOT					"pot_at_slot"
#define KEY_POT_LEVEL					"pot_level"

// ------------------------------------- DECOR -------------------------------
#define KEY_DECOR_ID						"decor_id"
#define KEY_DECOR_AT_FLOOR				"decor_at_floor"
#define KEY_DECOR_AT_SLOT				"decor_at_slot"

// ------------------------------------- SLOT  -------------------------------
#define KEY_SLOT_INDEX_SHORT						"slot_id"
#define KEY_SLOT_HARVEST_EXP                                "slot_harvest_exp"

// ------------------------------------- FLOOR  -------------------------------
#define KEY_FLOOR_INDEX_SHORT                                                     "floor_id"
    #define KEY_TOTAL_FLOOR_CHANGED_INT						"total_floor_changed"
// ------------------------------------- OTHERS -------------------------------
#define KEY_SERVER_TIME_INT                                                           "second"

        // ------------------------------------- FUNCTION PARAMS -------------------------------
        // MOVE POT
#define KEY_MOVE_POT_SRC_FLOOR_INDEX_SHORT						"floor_index_src"
#define KEY_MOVE_POT_SRC_SLOT_INDEX_SHORT						"slot_index_src"
#define KEY_MOVE_POT_DES_FLOOR_INDEX_SHORT						"floor_index_des"
#define KEY_MOVE_POT_DES_SLOT_INDEX_SHORT						"slot_index_des"
#define KEY_LUCKY_LEAF               	                        "lucky_leaf_id"

#define KEY_LUCKY_LEAF_SHORT                                                       "lucky_leaf_id"

#define KEY_PUT_POT						"put_pot_%d"
#define KEY_PLANT_FLOWER						"plant_%d"
#define KEY_HARVEST						"harvest_%d"
#define KEY_CATCH_BUG						"catch_bug_%d"
#define KEY_PLANT_INSTANT_GROW			"instant_grow_%d"


//////////////////////////////REQUEST_STATUS/////////////////////////
#define REQUEST_STATUS_ERROR						 		0
#define REQUEST_STATUS_OK						     		1

#define	REQUEST_STATUS_SAVE_ERROR							2 // critical error, should reload all data
#define	REQUEST_STATUS_LOAD_ERROR							3 // critical error, should reload all data

#define	REQUEST_STATUS_INVALID_PARAMS						4
#define	REQUEST_STATUS_INVALID_FLOOR_PARAM 					5 // floor param < 0 or >= userTotalFloor.
#define	REQUEST_STATUS_INVALID_SLOT_PARAM 					6 // slot < 0 or slot >= max_slot_per_floor.

#define	REQUEST_STATUS_STOCK_IS_FULL 						7 // full stock, can't increase more item.

#define	REQUEST_STATUS_POT_IS_NOT_EMPTY 					8 // pot is containing plant, can not move/hide/delete
#define	REQUEST_STATUS_CANT_FIND_POT 						9 // slot is empty, can not find pot

#define	REQUEST_STATUS_INVALID_PLANT_ID 					10 // invalid plant id ( plant id < 0 or plant id > max_plant_id)
#define	REQUEST_STATUS_INVALID_POT_ID 						11 // invalid pot id ( pot id < 0 or pot id > max_pot_id)

#define	REQUEST_STATUS_CANT_DELETE_POT 						12 // concurrent access problem
#define	REQUEST_STATUS_CANT_CREATE_NEW_POT					13 // concurrent access problem

#define	REQUEST_STATUS_CANT_INCREASE_OBJECT 				14 // stock
#define	REQUEST_STATUS_CANT_DECREASE_OBJECT 				15 // stock
#define	REQUEST_STATUS_CANT_SET_OBJECT_VALUE 				16 // stock

#define	REQUEST_STATUS_SLOT_IS_NOT_EMPTY					17 // slot is not empty, can not place more pot

#define	REQUEST_STATUS_NOT_ENOUGH_GOLD						18
#define	REQUEST_STATUS_NOT_ENOUGH_REPUTATION				19
#define	REQUEST_STATUS_NOT_ENOUGH_DIAMOND					20
#define	REQUEST_STATUS_NOT_ENOUGH_LEVEL						21

#define	REQUEST_STATUS_UPGRADE_POT_SUCCESS					22
#define	REQUEST_STATUS_UPGRADE_POT_FAIL						23

////////////////////////////////////////////////////////////////////
#define KEY_MAX_ROW_INT			            		"max_row"
#define KEY_MAX_COL_INT						        "max_column"
#define	KEY_GAME_INFO				                    "%d_%d"
