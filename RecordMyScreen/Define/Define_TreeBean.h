#ifndef DEFINES_TREEBEAN_H_INCLUDED
#define DEFINES_TREEBEAN_H_INCLUDED

#define     TB_SLOT_ITEM_POT                0
#define     TB_SLOT_ITEM_PLAN               1
#define     TB_SLOT_ITEM_DECOR              2


//cloudSlot
#define CS_SLOT_W                       100
#define CS_SLOT_H                       100

//cloudfloor
#define CF_SLOT_DIV                     50
#define CF_SLOT_START_X                 200
#define CF_SLOT_START_Y                 0
#define NUM_OF_FLOOR                    10

//treebean
#if (BUILD_QUALITY==BUILD_SD)
    #define TB_FLOOR_START_Y                -35
#elif (BUILD_QUALITY==BUILD_HD_960_640)
    #define TB_FLOOR_START_Y                -25
#else
    #define TB_FLOOR_START_Y                -20
#endif
#define TB_FLOOR_PER_SCREEN             2

#define TB_FLOOR_DIV                    ((k_SCREEN_HEIGHT_BASE/2) + TB_FLOOR_START_Y)

#define TB_MAX_FLOOR                    20
#endif // DEFINES_TREEBEAN_H_INCLUDED
