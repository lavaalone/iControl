#ifndef DEFINE_IBSHOP_H_INCLUDED
#define DEFINE_IBSHOP_H_INCLUDED

#if (BUILD_QUALITY==BUILD_SD)
    #define IBSHOP_BACKGROUND_WOOD_X             0
    #define IBSHOP_BACKGROUND_WOOD_Y             20

    #define IBSHOP_LISTUI_NUM_COL                3
    #define IBSHOP_LISTUI_NUM_ROW                2

    #define IBSHOP_LISTUI_SPACE_X                192
    #define IBSHOP_LISTUI_SPACE_Y                226

    #define IBSHOP_LISTUI_WIDTH                  650
    #define IBSHOP_LISTUI_HEIGHT                 480

    #define IBSHOP_LISTUI_X                      120
    #define IBSHOP_LISTUI_Y                      50

    #define IBSHOP_LISTUI_X_ITEM                 125
    #define IBSHOP_LISTUI_Y_ITEM                 80
#elif (BUILD_QUALITY==BUILD_HD_960_640)
    #define IBSHOP_BACKGROUND_WOOD_X             0
    #define IBSHOP_BACKGROUND_WOOD_Y             20

    #define IBSHOP_LISTUI_NUM_COL                3
    #define IBSHOP_LISTUI_NUM_ROW                2

    #define IBSHOP_LISTUI_SPACE_X                220
    #define IBSHOP_LISTUI_SPACE_Y                209

    #define IBSHOP_LISTUI_WIDTH                  680
    #define IBSHOP_LISTUI_HEIGHT                 470

    #define IBSHOP_LISTUI_X                      130
    #define IBSHOP_LISTUI_Y                      60

    #define IBSHOP_LISTUI_X_ITEM                 140
    #define IBSHOP_LISTUI_Y_ITEM                 80
#else
    #define IBSHOP_BACKGROUND_WOOD_X             30
    #define IBSHOP_BACKGROUND_WOOD_Y             -30

    #define IBSHOP_LISTUI_NUM_COL                3
    #define IBSHOP_LISTUI_NUM_ROW                2

    #define IBSHOP_LISTUI_SPACE_X                220
    #define IBSHOP_LISTUI_SPACE_Y                209

    #define IBSHOP_LISTUI_WIDTH                  650
    #define IBSHOP_LISTUI_HEIGHT                 450

    #define IBSHOP_LISTUI_X                      140
    #define IBSHOP_LISTUI_Y                      50

    #define IBSHOP_LISTUI_X_ITEM                 140
    #define IBSHOP_LISTUI_Y_ITEM                 60
#endif

#define IBSHOP_LEFTSIDE_LISTUI_NUM_COL                  1
#define IBSHOP_LEFTSIDE_LISTUI_NUM_ROW                  7

#define IBSHOP_LEFTSIDE_LISTUI_SPACE_X                  0
#define IBSHOP_LEFTSIDE_LISTUI_SPACE_Y                  95

#define IBSHOP_LEFTSIDE_LISTUI_X                        0
#define IBSHOP_LEFTSIDE_LISTUI_Y                        10

#define IBSHOP_LEFTSIDE_LISTUI_START_ITEM_X             65
#define IBSHOP_LEFTSIDE_LISTUI_START_ITEM_Y             100
//#define NUMBER_UPGRADE_REQUIREMENT_ITEM         3
//treebean
#if (BUILD_QUALITY==BUILD_SD)
    #define IBSHOP_LEFTSIDE_LISTUI_WIDTH                    120
    #define IBSHOP_LEFTSIDE_LISTUI_HEIGHT                   490
#elif (BUILD_QUALITY==BUILD_HD_960_640)
    #define IBSHOP_LEFTSIDE_LISTUI_WIDTH                    140
    #define IBSHOP_LEFTSIDE_LISTUI_HEIGHT                   500
#else
    #define IBSHOP_LEFTSIDE_LISTUI_WIDTH                    140
    #define IBSHOP_LEFTSIDE_LISTUI_HEIGHT                   470
#endif

#endif // DEFINE_BUILDING_H_INCLUDED
