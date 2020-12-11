
#include <ultralog.h>
#include "audio.h"
#include "src/boot.h"

extern OSSched         gScheduler;

#define MAX_SEQUENCE_COUNT      2

#define MAX_SEQ_LENGTH         (40 * 1024)

u8* gAudioHeapBuffer;

ALSeqPlayer	   *gSequencePlayer;
static u8          *gSequenceData[MAX_SEQUENCE_COUNT];
static s32         gSequenceLen[MAX_SEQUENCE_COUNT];
static ALSeq       *gSequence[MAX_SEQUENCE_COUNT];
static ALSeqMarker gSequenceStart[MAX_SEQUENCE_COUNT];
static ALSeqMarker gSequenceLoopStart[MAX_SEQUENCE_COUNT];
static ALSeqMarker gSequenceEnd[MAX_SEQUENCE_COUNT];
static int gNextSeq = 0;
static char* gCurrentSeq = 0;
struct BasicTransform* gListener;
struct Vector3 gListenerRight = {1.0f, 0.0f, 0.0f};

ALHeap             gAudioHeap;
ALSndPlayer gSoundPlayer;

#define MAX_PENDING_SOUNDS  4
#define UNUSED_PENDING_SOUND -1

struct PendingSound {
    ALSndId snd;
    float pitch;
    float volume;
    float pan;
    int priority;
};

struct SeqPlayEvent gPendingSeq;
struct PendingSound gPendingSounds[MAX_PENDING_SOUNDS];

#define MAX_SOUNDS 40

void soundPlayerInit() {
    ALSndpConfig sndConfig;

    sndConfig.maxEvents = MAX_EVENTS;
    sndConfig.maxSounds = MAX_SOUNDS;
    sndConfig.heap = &gAudioHeap;

    alSndpNew(&gSoundPlayer, &sndConfig);
}

void audioStopSequence() {
    if (alSeqpGetState(gSequencePlayer) != AL_STOPPED) {
        alSeqpStop(gSequencePlayer);
        gCurrentSeq = 0;
    }
}

void audioPlaySequence(struct SeqPlayEvent* playEvent) {
    return;
    if (gCurrentSeq == playEvent->romStart) {
        return;
    } else if (alSeqpGetState(gSequencePlayer) != AL_STOPPED) {
        alSeqpStop(gSequencePlayer);

        gPendingSeq = *playEvent;
    } else {
        gSequenceLen[gNextSeq] = playEvent->romEnd - playEvent->romStart;
        romCopy(playEvent->romStart, (char *) gSequenceData[gNextSeq], gSequenceLen[gNextSeq]);

        alSeqNew(gSequence[gNextSeq], gSequenceData[gNextSeq], gSequenceLen[gNextSeq]);
        alSeqNewMarker(gSequence[gNextSeq], &gSequenceStart[gNextSeq], playEvent->playbackStart);    
        alSeqNewMarker(gSequence[gNextSeq], &gSequenceLoopStart[gNextSeq], playEvent->loopStart);
        alSeqNewMarker(gSequence[gNextSeq], &gSequenceEnd[gNextSeq], playEvent->loopEnd);
        alSeqpLoop(gSequencePlayer, &gSequenceLoopStart[gNextSeq], &gSequenceEnd[gNextSeq], playEvent->loopCount);
        alSeqpSetVol(gSequencePlayer, playEvent->volume);

        if (playEvent->playbackStart) {
            alSeqSetLoc(gSequence[gNextSeq], &gSequenceStart[gNextSeq]);
        }

        alSeqpSetSeq(gSequencePlayer, gSequence[gNextSeq]);
        alSeqpPlay(gSequencePlayer);
        gCurrentSeq = playEvent->romStart;

        gNextSeq = (gNextSeq + 1) % MAX_SEQUENCE_COUNT;
    }
}

void audioInit() 
{
    ALBankFile    *bankPtr;
    u32           bankLen;
    ALSynConfig   c;
    ALSeqpConfig  seqc;
    amConfig      amc;
    
    alHeapInit(&gAudioHeap, gAudioHeapBuffer, AUDIO_HEAP_SIZE);    

    bankLen = _bankSegmentRomEnd - _bankSegmentRomStart;
    bankPtr = alHeapAlloc(&gAudioHeap, 1, bankLen);
    romCopy(_bankSegmentRomStart, (char *)bankPtr, bankLen);
    
    alBnkfNew(bankPtr, (u8 *) _tableSegmentRomStart);

    c.maxVVoices = MAX_VOICES;
    c.maxPVoices = MAX_VOICES;
    c.maxUpdates = MAX_UPDATES;
    c.dmaproc    = 0;
    c.fxType	 = AL_FX_SMALLROOM;
    c.outputRate = 0;
    c.heap       = &gAudioHeap;
    
    amc.outputRate = 44100;
    amc.framesPerField = NUM_FIELDS;
    amc.maxACMDSize = MAX_RSP_CMDS;
 
    amCreateAudioMgr(&c, AUDIO_PRIORITY, &amc);
    
    seqc.maxVoices      = MAX_VOICES;
    seqc.maxEvents      = MAX_EVENTS;
    seqc.maxChannels    = 16;
    seqc.heap           = &gAudioHeap;
    seqc.initOsc        = 0;
    seqc.updateOsc      = 0;
    seqc.stopOsc        = 0;
#ifdef DEBUG
    seqc.debugFlags     = NO_VOICE_ERR_MASK | NOTE_OFF_ERR_MASK | NO_SOUND_ERR_MASK;
#endif
    gSequencePlayer = alHeapAlloc(&gAudioHeap, 1, sizeof(ALSeqPlayer));
    alSeqpNew(gSequencePlayer, &seqc);
    alSeqpSetBank(gSequencePlayer, bankPtr->bankArray[0]);

    soundPlayerInit();

    int i;

    for (i = 0; i < MAX_SEQUENCE_COUNT; ++i) {
        gSequenceData[i] = alHeapAlloc(&gAudioHeap, 1, MAX_SEQ_LENGTH);
        gSequence[i] = alHeapAlloc(&gAudioHeap, 1, sizeof(ALSeq));
    }


    for (i = 0; i < MAX_PENDING_SOUNDS; ++i) {
        gPendingSounds[i].snd = UNUSED_PENDING_SOUND;
    }
}

int audioPlayState(ALSndId snd) {
    alSndpSetSound(&gSoundPlayer, snd);
    return alSndpGetState(&gSoundPlayer);
}

void audioStopSound(ALSndId snd) {
    alSndpSetSound(&gSoundPlayer, snd);
    alSndpStop(&gSoundPlayer);
}

int audioPendsound(ALSndId snd, float pitch, float volume, float pan, int priority) {
    int i;

    for (i = 0; i < MAX_PENDING_SOUNDS; ++i) {
        if (gPendingSounds[i].snd == UNUSED_PENDING_SOUND) {
            gPendingSounds[i].snd = snd;
            gPendingSounds[i].volume = volume;
            gPendingSounds[i].pitch = pitch;
            gPendingSounds[i].priority = priority;
            return 1;
        }
    }

    for (i = 0; i < MAX_PENDING_SOUNDS; ++i) {
        if (gPendingSounds[i].priority < priority) {
            gPendingSounds[i].snd = snd;
            gPendingSounds[i].volume = volume;
            gPendingSounds[i].pitch = pitch;
            gPendingSounds[i].priority = priority;
            return 1;
        }
    }

    return 0;
}

void audioRestartPlaySound(ALSndId snd, float pitch, float volume, float pan, int priority) {
    alSndpSetSound(&gSoundPlayer, snd);
    if (alSndpGetState(&gSoundPlayer) != AL_STOPPED) {
        if (audioPendsound(snd, pitch, volume, pan, priority)) {
            alSndpStop(&gSoundPlayer);
        }
    } else {
        audioPlaySound(snd, pitch, volume, pan, priority);
    }
}

void audioPlaySound(ALSndId snd, float pitch, float volume, float pan, int priority) {
    if (volume > 0.0f && snd != UNUSED_PENDING_SOUND) {
        alSndpSetSound(&gSoundPlayer, snd);
        alSndpSetPitch(&gSoundPlayer, pitch);
        float floatAsShort = volume * 32767;
        if (floatAsShort > 32767.0f) {
            alSndpSetVol(&gSoundPlayer, 32767);
        } else {
            alSndpSetVol(&gSoundPlayer, (s16)floatAsShort);
        }

        float panAs127 = (pan + 1.0f) * 128.0f;

        if (panAs127 <= 0.0f) {
            alSndpSetPan(&gSoundPlayer, 0);
        } else if (panAs127 >= 255.0f) {
            alSndpSetPan(&gSoundPlayer, 255);
        } else {
            alSndpSetPan(&gSoundPlayer, (u8)(panAs127));
        }
        alSndpSetPriority(&gSoundPlayer, snd, 10);

        if (alSndpGetState(&gSoundPlayer) == AL_STOPPED) {
            alSndpPlay(&gSoundPlayer);
        }
    }
}

#define HALF_DECAY_RADIUS   20.0f
#define SOUND_VELOCITY      50.0f

void audioPlaySound3D(ALSndId snd, float pitch, float volume, struct Vector3* source, struct Vector3* velocity, int restart, int priority) {
    if (!gListener) {
        audioPlaySound(snd, pitch, volume, 0.0f, priority);
    } else {
        struct Vector3 offset;
        vector3Sub(source, &gListener->position, &offset);

        float distance = vector3MagSqrd(&offset);
        float pan;

        if (distance > 0.1f) {
            volume *= (0.5f * HALF_DECAY_RADIUS * HALF_DECAY_RADIUS) / distance;
            float invDistance = 1.0f / sqrtf(distance);
            pitch *= SOUND_VELOCITY / (SOUND_VELOCITY + vector3Dot(&offset, velocity) * invDistance);
            pan = vector3Dot(&gListenerRight, &offset) * invDistance;
        } else {
            volume *= 100.0f;
            pan = 0.0f;
        }


        if (restart) {
            audioRestartPlaySound(snd, pitch, volume, pan, priority);
        } else {
            audioPlaySound(snd, pitch, volume, pan, priority);
        }
    }
}

void audioUpdate() {
    int i;

    if (gListener) {
        quatMultVector(&gListener->rotation, &gRight, &gListenerRight);
    }

    for (i = 0; i < MAX_PENDING_SOUNDS; ++i) {
        if (gPendingSounds[i].snd != UNUSED_PENDING_SOUND) {
            if (audioPlayState(gPendingSounds[i].snd) == AL_STOPPED) {
                audioPlaySound(
                    gPendingSounds[i].snd, 
                    gPendingSounds[i].pitch, 
                    gPendingSounds[i].volume, 
                    gPendingSounds[i].pan, 
                    gPendingSounds[i].priority
                );

                gPendingSounds[i].snd = UNUSED_PENDING_SOUND;
            }
        }
    }

    if (gPendingSeq.romStart && alSeqpGetState(gSequencePlayer) == AL_STOPPED) {
        audioPlaySequence(&gPendingSeq);
        gPendingSeq.romStart = 0;
    }
}