
#include "memory.h"

static unsigned int gHeapStart;
static unsigned int gHeapEnd;
static unsigned int gHeapCurrent;

extern int gHeapStartPos;

void heapInit(unsigned int end)
{
    gHeapStart = (unsigned int)&gHeapStartPos;
    gHeapEnd = end;
    gHeapCurrent = end;
}

void heapReset()
{
    gHeapCurrent = gHeapEnd;
}

void* heapMalloc(unsigned int len, unsigned int align)
{
    if (align == 0) {
        align = 1;
    }

    gHeapCurrent -= len;
    gHeapCurrent = gHeapCurrent & ~(align - 1);
    void* result = (void*)gHeapCurrent;

    return result;
}

void tlbAlign(unsigned int len, u32* alignedSize, OSPageMask* pageMask) {
    if (len <= 0x1000) {
        *alignedSize = 0x1000;
        *pageMask = OS_PM_4K;
    } else if (len <= 0x4000) {
        *alignedSize = 0x4000;
        *pageMask = OS_PM_16K;
    } else if (len <= 0x10000) {
        *alignedSize = 0x10000;
        *pageMask = OS_PM_64K;
    } else if (len <= 0x40000) {
        *alignedSize = 0x40000;
        *pageMask = OS_PM_256K;
    } else if (len <= 0x100000) {
        *alignedSize = 0x100000;
        *pageMask = OS_PM_1M;
    } else if (len <= 0x400000) {
        *alignedSize = 0x400000;
        *pageMask = OS_PM_4M;
    } else {
        *alignedSize = 0x1000000;
        *pageMask = OS_PM_16M;
    }
}

#define FAST_MALLOC_HEAP_SIZE   0x10000

static char gFastMallocHeap[FAST_MALLOC_HEAP_SIZE];
static char* gFastMallocCurrent;

void* fastMalloc(int len, int align) {
    if (align == 0) {
        align = 1;
    }
    gFastMallocCurrent = (char*)(((int)gFastMallocCurrent + (align - 1)) & ~(align - 1));
    void* result = gFastMallocCurrent;
    gFastMallocCurrent += len;
    return result;
}

void fastMallocReset() {
    gFastMallocCurrent = gFastMallocHeap;
}