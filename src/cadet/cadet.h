
#ifndef _CADET_CADET_C
#define _CADET_CADET_C

#include "src/collision/sphereactor.h"
#include "src/math/basictransform.h"
#include "src/time/time.h"

#define CADET_RADIUS    0.2f
#define CADET_SPEED     3.0f
#define CADET_ACCEL     24.0f
#define CADET_AIR_ACCEL 8.0f

#define CADET_JUMP_IMPULSE  4.0f
#define CADET_JUMP_ACCEL    4.0f

struct Cadet;

typedef void (*CadetState)(struct Cadet* cadet);

#define CADET_IS_JUMPING  (1 << 1)

struct Cadet {
    struct BasicTransform transform;
    struct SphereActor actor;
    CadetState state;
    struct TimeUpdateListener updateListener;
};

extern struct Cadet gCadet;

void cadetInit();
void cadetReset(struct Vector3* startLocation);

#endif