
#include "breakable.h"

#include "src/collision/collisionscene.h"
#include "src/graphics/renderscene.h"
#include "src/level/level.h"
#include "src/audio/audio.h"
#include "src/audio/playersounds.h"

struct CollisionCollider gBreakablePlatformCollider = {
    ColliderTypeBox,
    CollisionLayersGeometry,
    .box = {
        {-1.0f, 0.0f, -1.0f},
        {1.0f, 2.0f, 1.0f},
    }
};

struct CollisionCollider gBreakableBarrierCollider = {
    ColliderTypeBox,
    CollisionLayersGeometry,
    .box = {
        {-1.0f, 0.0f, -1.0f},
        {1.0f, 4.0f, 1.0f},
    }
};

void breakableTrigger(void* data, struct Vector3* origin) {
    struct Breakable* breakable = (struct Breakable*)data;
    if (breakable->renderActorId != ACTOR_ID_NONE) {
        audioRestartPlaySound(
            gPlayerSoundIds[SoundRocksBreak],
            1.0f,
            0.7f,
            0.0f, 
            10
        );

        dynamicActorRemoveFromGroup(&gScene.dynamicActors, &breakable->renderActorId);

        sparseCollisionRemove(&gSparseCollisionGrid, &breakable->collider);

        rockFragmentsInit(&breakable->breakEffect, &breakable->transform.position, breakable->type ? 3 : 2, origin);
    }
}

void breakableRender(struct DynamicActor* data, struct GraphicsState* state) {
    struct Breakable* breakable = (struct Breakable*)data->data;
    Gfx* toRender = gLoadedLevel->theme->theme->themeMeshes[
        breakable->type ? LevelThemeMeshesBreakBarrier : LevelThemeMeshesBreakPlatform
    ];

    Mtx* nextTransfrom = graphicsStateNextMtx(state);
    transformToMatrixL(data->transform, 1.0f / 256.0f, nextTransfrom);
    gSPMatrix(state->dl++, OS_K0_TO_PHYSICAL(nextTransfrom), G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPDisplayList(state->dl++, toRender);
    gSPPopMatrix(state->dl++, G_MTX_MODELVIEW);
    gDPPipeSync(state->dl++);
}

void breakableInit(struct Breakable* breakable, struct Vector3* position, int type) {
    transformIdentity(&breakable->transform);
    breakable->transform.position = *position;

    struct CollisionCollider* collider;

    switch (type) {
        case BreakableTypePlatform:
            collider = &gBreakablePlatformCollider;
            break;
        default:
            collider = &gBreakableBarrierCollider;
            break;
    }

    breakable->collider.collider = collider;
    breakable->collider.transform = &breakable->transform;
    breakable->collider.data = breakable;
    breakable->collider.trigger = breakableTrigger;
    breakable->collider.triggerMask = CollisionLayersBreakable;

    breakable->type = type;

    sparseCollisionAdd(&gSparseCollisionGrid, &breakable->collider, NULL);

    breakable->renderActorId = dynamicActorAddToGroup(&gScene.dynamicActors, &breakable->transform, breakable, breakableRender, DynamicMaterialTypeBreakable, 2.0f);

}