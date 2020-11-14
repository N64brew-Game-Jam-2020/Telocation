
#include "level.h"

#include "src/boot.h"
#include "src/collision/collisionscene.h"
#include "src/graphics/graphics.h"
#include "src/graphics/dynamic.h"
#include "src/system/memory.h"
#include "src/cadet/cadet.h"
#include "src/robot/robot.h"
#include "src/puzzle/switch.h"
#include "src/puzzle/door.h"
#include "src/puzzle/breakable.h"
#include "src/puzzle/movingplatform.h"
#include "src/puzzle/entranceexit.h"
#include "src/effects/shadow.h"
#include "src/time/time.h"
#include "src/input/inputfocus.h"
#include "src/input/controller.h"
#include "src/levels/levels.h"

struct LevelDefinition* gLoadedLevel;

#define LEVEL_HAS_CADET 1
#define LEVEL_HAS_ROBOT 2

static CleanupFunction* gCleanupFn; 
static void** gCleanupParam;
static int gCleanupCount;
int gLevelFlags;
struct TimeUpdateListener gLevelUpdateListener;
int gCurrentLevel;
int gNextLevel;

void levelNext() {
    if (gNextLevel == gCurrentLevel && gCurrentLevel + 1 < _level_group_all_levels_count) {
        gNextLevel = gCurrentLevel + 1;
    }
}

void levelPrev() {
    if (gNextLevel == gCurrentLevel && gCurrentLevel > 0) {
        gNextLevel = gCurrentLevel - 1;
    }
}

void levelUpdate(void* data) {
    if ((gLevelFlags & LEVEL_HAS_CADET) && (gLevelFlags & LEVEL_HAS_ROBOT) && getButtonDown(0, L_TRIG | Z_TRIG)) {
        if (gInputMask & InputMaskRobot) {
            gInputMask = INPUT_MASK_CADET;
        } else {
            gInputMask = INPUT_MASK_ROBOT;
        }
    }

    if ((!(gLevelFlags & LEVEL_HAS_CADET) || gCadetExit.isActive) && (!(gLevelFlags & LEVEL_HAS_ROBOT) || gRobotExit.isActive)) {
        levelNext();
    }
    
    if (getButtonDown(0, R_JPAD)) {
        levelNext();
    } else if (getButtonDown(0, L_JPAD)) {
        levelPrev();
    }
}

void levelExpand(struct LevelDefinition* levelDef) {
    /////////////////////
    // switches

    struct PuzzleSwitch* switches = heapMalloc(
        ARRAY_SIZE(struct PuzzleSwitch, levelDef->levelData->switchCount), 
        ALIGNMENT_OF(struct PuzzleSwitch)
    );

    int i;
    for (i = 0; i < levelDef->levelData->switchCount; ++i) {
        struct LevelSwitchDef* def = &levelDef->levelData->switches[i];
        switchInit(&switches[i], &def->pos, def->type, def->color);
    }

    /////////////////////
    // doors
    
    struct PuzzleDoor* doors = heapMalloc(
        ARRAY_SIZE(struct PuzzleDoor, levelDef->levelData->doorCount), 
        ALIGNMENT_OF(struct PuzzleDoor)
    );

    for (i = 0; i < levelDef->levelData->doorCount; ++i) {
        struct LevelDoorDef* def = &levelDef->levelData->doors[i];
        doorInit(&doors[i], &def->pos, def->color);
    }

    /////////////////////
    // barriers

    struct Breakable* breakables = heapMalloc(
        ARRAY_SIZE(struct Breakable, levelDef->levelData->breakableCount),
        ALIGNMENT_OF(struct Breakable)
    );

    for (i = 0; i < levelDef->levelData->breakableCount; ++i) {
        struct LevelBreakableDef* def = &levelDef->levelData->breakables[i];
        breakableInit(&breakables[i], &def->pos, def->type);
    }

    /////////////////////
    // platform slots

    struct MovingPlatformSlot* slots = heapMalloc(
        ARRAY_SIZE(struct MovingPlatformSlot, levelDef->levelData->platformSlotCount),
        ALIGNMENT_OF(struct MovingPlatformSlot)
    );

    for (i = 0; i < levelDef->levelData->platformSlotCount; ++i) {
        movingPlatformSlotInit(&slots[i], &levelDef->levelData->platformSlots[i].pos);
    }
    
    movingPlatformJoinSlots(slots, levelDef->levelData->platformSlotCount);

    /////////////////////
    // platform slots

    struct MovingPlatform* platforms = heapMalloc(
        ARRAY_SIZE(struct MovingPlatform, levelDef->levelData->platformCount),
        ALIGNMENT_OF(struct MovingPlatform)
    );

    for (i = 0; i < levelDef->levelData->platformCount; ++i) {
        struct LevelPlatformDef* platform = &levelDef->levelData->platforms[i];
        movingPlatformInit(&platforms[i], &platform->pos, &slots[platform->slotIndex], platform->color);
    }

    /////////////////////
    // cleanup
    
    gCleanupCount = 0;
    gCleanupFn = 0;
    gCleanupParam = 0;
}

void levelCleanup(struct LevelDefinition* levelDef) {
    int i;

    for (i = 0; i < gCleanupCount; ++i) {
        gCleanupFn[i](gCleanupParam[i]);
    }
}

void levelLoad(struct LevelDefinition* levelDef) {
    if (gLoadedLevel) {
        levelCleanup(gLoadedLevel);
    }

    heapReset();
    osUnmapTLBAll();

    u32 len = (u32)(_staticSegmentRomEnd - _staticSegmentRomStart);
    char* staticSegment = heapMalloc(len, 8);
    romCopy(_staticSegmentRomStart, (char*)staticSegment, len);

    len = (u32)(levelDef->levelRomEnd - levelDef->levelRomStart);
    u32 levelAlign;
    u32 levelPageMask;
    tlbAlign(len, &levelAlign, &levelPageMask);

    char* levelSegment = heapMalloc(len, levelAlign);
    romCopy(levelDef->levelRomStart, levelSegment, len);
    osMapTLB(0, levelPageMask, (void*)(LEVEL_SEGMENT << 24), osVirtualToPhysical(levelSegment), -1, -1);


    len = (u32)(levelDef->theme->themeRomEnd - levelDef->theme->themeRomStart);
    char* themeSegment = heapMalloc(len, 8);
    romCopy(levelDef->theme->themeRomStart, (char*)themeSegment, len);

    timeResetListeners();
    signalResetAll();

    graphicsInitLevel(
        staticSegment, 
        levelSegment, 
        themeSegment, 
        levelDef->levelData->graphics, 
        levelDef->theme->theme
    );

    renderSceneReset(&gScene);

    collisionSceneUseGrid(levelDef->levelData->collision);
    
    gLevelFlags = 0;

    gLevelFlags |= LEVEL_HAS_CADET;
    cameraInit(&gScene.camera);
    cadetReset(&levelDef->levelData->cadetStart);
    entranceExitInit(&gCadetExit, &levelDef->levelData->cadetFinish, 1);

    if (levelDef->levelData->robotStart.z < 0.5 && levelDef->levelData->robotStart.x > -0.5) {
        gLevelFlags |= LEVEL_HAS_ROBOT;
        robotReset(&levelDef->levelData->robotStart);
        entranceExitInit(&gRobotExit, &levelDef->levelData->robotFinish, 0);
    }

    levelExpand(levelDef);
    timeAddListener(&gLevelUpdateListener, levelUpdate, 0);

    gLoadedLevel = levelDef;

    gScene.transparentMaterials[TransparentMaterialTypeShadow] = _drop_shadow_material;
}