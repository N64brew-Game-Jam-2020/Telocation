
#include "pausemenu.h"
#include "src/input/inputfocus.h"
#include "src/input/controller.h"
#include "src/graphics/graphics.h"
#include "src/font/fontrenderer.h"
#include "src/font/endlessbossbattle/endlessbossbattle.h"
#include "menu.h"
#include "src/level/level.h"
#include "src/boot.h"
#include "src/save/savefile.h"
#include "src/audio/playersounds.h"
#include "src/audio/audio.h"

#define PAUSE_MENU_WIDTH    120
#define PAUSE_MENU_HEIGHT   160

#define LINE_HEIGHT         20

char* gPauseMenuTitle = "Paused";

char* gPauseMenuText[PauseMenuItemCount] = {
    "Resume",
    "Restart Level",
    "Save",
    "Save and Quit",
};

struct PauseMenu gPauseMenu;

void pauseMenuRender(void* data, struct GraphicsState* state, struct FontRenderer* fontRenderer) {
    struct PauseMenu* pauseMenu =  (struct PauseMenu*)data;

    int modifiedHeight = SCALE_FOR_PAL(PAUSE_MENU_HEIGHT);
    int modfiedLineHeight = SCALE_FOR_PAL(LINE_HEIGHT);

    gDPPipeSync(state->dl++);
	gDPSetCombineLERP(state->dl++, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1);
    gDPFillRectangle(
        state->dl++, 
        (SCREEN_WD-PAUSE_MENU_WIDTH)>>1, 
        (gScreenHeight-modifiedHeight)>>1,
        (SCREEN_WD+PAUSE_MENU_WIDTH)>>1, 
        (gScreenHeight+modifiedHeight)>>1
    );
    gDPPipeSync(state->dl++);
    gDPSetCycleType(state->dl++, G_CYC_1CYCLE);

    gSPDisplayList(state->dl++, gEndlessBossBattleUse);

    float halfWidth = fontRendererMeasureWidth(&gEndlessBossBattle, gPauseMenuTitle);

    fontRendererSetScale(fontRenderer, 2.0f, 2.0f * gScreenYScale);

    fontRendererDrawCharacters(
        fontRenderer,
        &gEndlessBossBattle,
        &state->dl,
        gPauseMenuTitle,
        (SCREEN_WD >> 1) - (int)(halfWidth),
        ((gScreenHeight - modifiedHeight) >> 1) + SCALE_FOR_PAL(10)
    );

    fontRendererSetScale(fontRenderer, 1.0f, gScreenYScale);

    int i;

    for (i = 0; i < PauseMenuItemCount; ++i) {
        int isSaved = i == 2 && !saveFileNeedsSave();
        char* text = isSaved ? "Saved" : gPauseMenuText[i];
        halfWidth = fontRendererMeasureWidth(&gEndlessBossBattle, text) * 0.5f;
        int yOffset = 20 + i * modfiedLineHeight - (int)((modfiedLineHeight * PauseMenuItemCount) >> 1);


        if (pauseMenu->selectedItem == i) {
            if (isSaved) {
                gDPSetEnvColor(state->dl++, 0, 255, 0, 255);
            } else {
                gDPSetEnvColor(state->dl++, 255, 0, 255, 255);
            }
        } else {
            gDPSetEnvColor(state->dl++, 255, 255, 255, 255);
        }

        fontRendererDrawCharacters(
            fontRenderer,
            &gEndlessBossBattle,
            &state->dl,
            text,
            (SCREEN_WD >> 1) - (int)(halfWidth),
            (gScreenHeight >> 1) + yOffset
        );
    }
    gDPPipeSync(state->dl++);
}

void pauseMenuExit(struct PauseMenu* pauseMenu) {
    graphicsRemoveMenu(pauseMenuRender, pauseMenu);
    timeRemoveListener(&pauseMenu->updateListener, TimeUpdateGroupMenu);
    timeSetGroupDisabled(TimeUpdateGroupWorld, 0);
    inputMaskPop();
}

void pauseMenuUpdate(void* data) {
    struct PauseMenu* pauseMenu =  (struct PauseMenu*)data;

    int inputDir = menuGetInputDir(gControllerState[0].stick_y, &pauseMenu->lastVerticalInput, 0);

    if (inputDir > 0 && pauseMenu->selectedItem > 0) {
        pauseMenu->selectedItem--;
        audioRestartPlaySound(
            gPlayerSoundIds[SoundUIScroll],
            0.5f,
            1.0f,
            0.0f,
            10
        );
    } else if (inputDir < 0 && pauseMenu->selectedItem + 1 < PauseMenuItemCount) {
        pauseMenu->selectedItem++;
        audioRestartPlaySound(
            gPlayerSoundIds[SoundUIScroll],
            0.5f,
            1.0f,
            0.0f,
            10
        );
    }

    if (pauseMenu->selectedItem == -1) {
        pauseMenu->selectedItem = 0;
    } else if (getButtonDown(0, START_BUTTON)) {
        audioRestartPlaySound(
            gPlayerSoundIds[SoundUISelect],
            0.5f,
            MENU_SELECT_SOUND_VOLUME,
            0.0f,
            10
        );
        pauseMenuExit(pauseMenu);
    } else if (getButtonDown(0, A_BUTTON)) {
        audioRestartPlaySound(
            gPlayerSoundIds[SoundUISelect],
            0.5f,
            MENU_SELECT_SOUND_VOLUME,
            0.0f,
            10
        );
        switch (pauseMenu->selectedItem) {
            case PauseMenuItemResume:
                pauseMenuExit(pauseMenu);
                break;
            case PauseMenuItemRestart:
                restartLevel();
                break;
            case PauseMenuItemSave:
                saveFileSave();
                break;
            case PauseMenuItemMainMenu:
                saveFileSave();
                gNextLevel = SceneIndexMainMenu;
                break;
        }
    }
}

void pauseMenuShow(struct PauseMenu* pauseMenu) {
    pauseMenu->selectedItem = -1;

    graphicsAddMenu(pauseMenuRender, pauseMenu, 1);

    inputMaskPush(InputMaskPauseMenu);
    timeSetGroupDisabled(TimeUpdateGroupWorld, 1);

    pauseMenu->lastVerticalInput = 0;

    timeAddListener(&pauseMenu->updateListener, pauseMenuUpdate, pauseMenu, TimeUpdateGroupMenu);
}