#ifndef DEFINE_WAREHOUSE_H_INCLUDED
#define DEFINE_WAREHOUSE_H_INCLUDED

#define WAREHOUSE_TYPE_NORMAL                   0
#define WAREHOUSE_TYPE_PRIVATE_SLOT             1


//#define NUMBER_UPGRADE_REQUIREMENT_ITEM         3

#define WAREHOUSE_ID_PLANT                      0
#define WAREHOUSE_ID_PRODUCT                    1
#define WAREHOUSE_ID_ITEM                       2

#define WAREHOUSE_STATE_NORMAL                  0
#define WAREHOUSE_STATE_UPGRADE                 1

#define WAREHOUSE_PANEL_SUBMENU_START_X         260
#define WAREHOUSE_PANEL_SUBMENU_START_Y         50

#define WAREHOUSE_PANEL_SUBMENU_WIDTH           245
#define WAREHOUSE_PANEL_SUBMENU_HEIGHT          328

#define WAREHOUSE_EXCHANGE_SUBMENU_WIDTH        215
#define WAREHOUSE_EXCHANGE_SUBMENU_HEIGHT       50

#define WAREHOUSE_BACKGROUND_RECT_START_X       188
#define WAREHOUSE_BACKGROUND_RECT_START_Y       133

#define WAREHOUSE_RECT_COLOR_CODE               0xDCE5ADFF
#define WAREHOUSE_WHITE_COLOR_CODE              0xFFFFFFFF

#define WAREHOUSE_BACKGROUND_RECT_WIDTH         260
#define WAREHOUSE_BACKGROUND_RECT_HEIGHT        300

#define WAREHOUSE_WHITE_RECT_WIDTH              270
#define WAREHOUSE_WHITE_RECT_HEIGHT             285

#define WAREHOUSE_LISTUI_NUM_COL                2
#define WAREHOUSE_LISTUI_NUM_ROW                3

#define WAREHOUSE_LISTUI_SPACE_X                120
#define WAREHOUSE_LISTUI_SPACE_Y                80

#if (BUILD_QUALITY==BUILD_SD)
    #define WAREHOUSE_LISTUI_X                      120
    #define WAREHOUSE_LISTUI_Y                      180

    #define WAREHOUSE_LISTUI_START_ITEM_X           190
    #define WAREHOUSE_LISTUI_START_ITEM_Y           245

    #define WAREHOUSE_LISTUI_WIDTH                  265
    #define WAREHOUSE_LISTUI_HEIGHT                 260

#elif (BUILD_QUALITY==BUILD_HD_960_640)
    #define WAREHOUSE_LISTUI_X                      168
    #define WAREHOUSE_LISTUI_Y                      170

    #define WAREHOUSE_LISTUI_START_ITEM_X           228
    #define WAREHOUSE_LISTUI_START_ITEM_Y           250

    #define WAREHOUSE_LISTUI_WIDTH                  265
    #define WAREHOUSE_LISTUI_HEIGHT                 280
#else
    #define WAREHOUSE_LISTUI_X                      188
    #define WAREHOUSE_LISTUI_Y                      140

    #define WAREHOUSE_LISTUI_START_ITEM_X           228
    #define WAREHOUSE_LISTUI_START_ITEM_Y           213

    #define WAREHOUSE_LISTUI_WIDTH                  265
    #define WAREHOUSE_LISTUI_HEIGHT                 290
#endif
#define     WAREHOUSE_NUM                   2

#endif // DEFINE_BUILDING_H_INCLUDED
