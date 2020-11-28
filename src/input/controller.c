
#include "controller.h"
#include "src/system/assert.h"
#include "src/save/savefile.h"

static OSMesg gDummyMessage;
OSMesgQueue gContMessageQ;
OSContStatus gControllerStatus[MAXCONTROLLERS];
OSContPad gControllerState[MAXCONTROLLERS];
u16 gControllerLastButton[MAXCONTROLLERS];

#define OUTER_DEAD_ZONE     10

int gInputRange[MAXCONTROLLERS] = {
    64,
    64,
    64,
    64,
};

void controllersInit() {
    u8 pattern;
    osCreateMesgQueue(&gContMessageQ, &gDummyMessage, 1);
    osSetEventMesg(OS_EVENT_SI, &gContMessageQ, (OSMesg) 0);

    osContInit(&gContMessageQ, &pattern, &gControllerStatus[0]);

    saveFileLoad();

    assert((pattern & 1) && !(gControllerStatus[0].errno & CONT_NO_RESPONSE_ERROR));

    osContStartReadData(&gContMessageQ);
}

void controllersReadData() {
    int i;

    if (osRecvMesg(&gContMessageQ, &gDummyMessage, OS_MESG_NOBLOCK) == 0) {
        for (i = 0; i < MAXCONTROLLERS; ++i) {
            gControllerLastButton[i] = gControllerState[i].button;
        }

        osContGetReadData(gControllerState);
        osContStartReadData(&gContMessageQ);
    }
}

int getButton(int controller, int mask) {
    if (controller == -1) {
        return 0;
    }

    return gControllerState[controller].button & mask;
}

int getButtonDown(int controller, int mask) {
    if (controller == -1) {
        return 0;
    }

    return gControllerState[controller].button & ~gControllerLastButton[controller] & mask;
}

int getButtonUp(int controller, int mask) {
    if (controller == -1) {
        return 0;
    }

    return ~gControllerState[controller].button & gControllerLastButton[controller] & mask;
}

extern struct Vector2 getJoystick(int controller) {
    struct Vector2 result;

    if (controller == -1) {
        result.x = 0;
        result.y = 0;
        return result;
    }
    
    s8 rawX = gControllerState[controller].stick_x;

    if (rawX > gInputRange[controller]) {
        gInputRange[controller] = rawX;
    } else if (rawX < -gInputRange[controller]) {
        gInputRange[controller] = -rawX;
    }

    s8 rawY = gControllerState[controller].stick_y;

    if (rawY > gInputRange[controller]) {
        gInputRange[controller] = rawY;
    } else if (rawY < -gInputRange[controller]) {
        gInputRange[controller] = -rawY;
    }

    float scale = 1.0f / (float)(gInputRange[controller] - OUTER_DEAD_ZONE);

    result.x = rawX * scale;
    result.y = -rawY * scale;

    if (result.x < -1.0f) {
        result.x = -1.0f;
    } else if (result.x > 1.0f) {
        result.x = 1.0f;
    }

    if (result.y < -1.0f) {
        result.y = -1.0f;
    } else if (result.y > 1.0f) {
        result.y = 1.0f;
    }

    float magSqr = result.x * result.x + result.y * result.y;

    if (magSqr > 1.0f) {
        vector2Scale(&result, 1.0f / sqrtf(magSqr), &result);
    }

    return result;
}