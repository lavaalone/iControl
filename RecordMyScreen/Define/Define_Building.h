#ifndef DEFINE_BUILDING_H_INCLUDED
#define DEFINE_BUILDING_H_INCLUDED

//ID
#define     BUILDING_ID_NUOCEP      0
#define     BUILDING_ID_LOSAY       1
#define     BUILDING_ID_NGOC        2
#define     BUILDING_ID_03          3
#define     BUILDING_ID_04          4
#define     BUILDING_ID_05          5
#define     BUILDING_ID_06          6
#define     BUILDING_ID_07          7
#define     BUILDING_ID_08          8
#define     BUILDING_ID_09          9
#define     BUILDING_ID_10          10
#define     BUILDING_ID_11          11

#define     BUILDING_NUM            GAME_INSTANCE->getNumOfItemsForType(IT_BUILDING)


//BUILDING_SLOT_TYPE_PRODUCING
#define     BUILDING_SLOT_TYPE_PRODUCING    0
#define     BUILDING_SLOT_TYPE_QUEUING      1
#define     BUILDING_SLOT_TYPE_FREE         2
#define     BUILDING_SLOT_TYPE_EXPAND       3
#define     BUILDING_SLOT_TYPE_NUM          4


#define     MAX_COMPLETE_ITEM               10
#define     DURATION_COST_PER_ITEM          1

#define     BUILDING_ANIM_ICON              MACHINE_00_ANIM_ICON
#define     BUILDING_ANIM_WORK              MACHINE_00_ANIM_WORK

//BONUS_ITEM
#define     BONUS_ITEM_GOLD                 0
#define     BONUS_ITEM_EXP                  1
#define     BONUS_ITEM_DIAMOND              2

#define     COUNT_BONUS_ITEM                3
#define     MAX_BONUS_ITEM_COUNT            3

//LEVEL
#define     MAX_LEVEL                       3

#if (BUILD_QUALITY==BUILD_SD)
    #define MACHINE_SKIP_TIMEBAR_X                 90

#elif (BUILD_QUALITY==BUILD_HD_960_640)
    #define MACHINE_SKIP_TIMEBAR_X                 100

#else
    #define MACHINE_SKIP_TIMEBAR_X                 116
#endif

#endif // DEFINE_BUILDING_H_INCLUDED
