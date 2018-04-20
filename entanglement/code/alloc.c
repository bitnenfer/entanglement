#include <stdlib.h>

#include "alloc.h"
#include "utils.h"
#include "platform.h"

/* =================== */
/* Slot Allocator HEAD */
/* =================== */
#if defined(LD_PLATFORM_ARCH_X64)
#define ALLOC_SLOT_COUNT 8
static const size_t kSlotSize[ALLOC_SLOT_COUNT] = { 8, 16, 32, 64, 128, 256, 512, 1024 };
static const size_t kSlotBufferSizes[ALLOC_SLOT_COUNT] = {
    LD_UTILS_MB(1),
    LD_UTILS_MB(1),
    LD_UTILS_MB(1),
    LD_UTILS_MB(1),
    LD_UTILS_MB(2),
    LD_UTILS_MB(4),
    LD_UTILS_MB(8),
    LD_UTILS_MB(16)
};
#else
#define ALLOC_SLOT_COUNT 9
static const size_t kSlotSize[ALLOC_SLOT_COUNT] = { 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
static const size_t kSlotBufferSizes[ALLOC_SLOT_COUNT] = {
    LD_UTILS_MB(1),
    LD_UTILS_MB(1),
    LD_UTILS_MB(1),
    LD_UTILS_MB(1),
    LD_UTILS_MB(1),
    LD_UTILS_MB(2),
    LD_UTILS_MB(4),
    LD_UTILS_MB(8),
    LD_UTILS_MB(16)
};
#endif

struct memory_pool
{
    void* pMainBuffer;
    void* pPoolBuffer;
    void** pPoolElements;
    byte_t* pMainElements;
    size_t poolLength;
    size_t mainByteLength;
    size_t elementCapacity;
    size_t stride;
};

struct memory_pool gSlotPools[ALLOC_SLOT_COUNT];

static void* ldMemoryPoolAlloc(struct memory_pool* pPool)
{
    void* pPointer = NULL;

    if (pPool->poolLength > 0)
    {
        pPointer = pPool->pPoolElements[--(pPool->poolLength)];
#if defined(LD_PLATFORM_DEBUG)
        memset(pPointer, 0xAA, pPool->stride);
#endif
    }
    else if (pPool->mainByteLength + pPool->stride < pPool->elementCapacity * pPool->stride)
    {
        pPointer = (void*)&pPool->pMainElements[(pPool->mainByteLength += pPool->stride)];
#if defined(LD_PLATFORM_DEBUG)
        memset(pPointer, 0xAA, pPool->stride);
#endif
    }

    return pPointer;
}

static void ldMemoryPoolFree(struct memory_pool* pPool, void* pPointer)
{
    if (pPool->poolLength < pPool->elementCapacity)
    {
#if defined(LD_PLATFORM_DEBUG)
        memset(pPointer, 0xDD, pPool->stride);
#endif
        pPool->pPoolElements[pPool->poolLength++] = pPointer;
    }
}

static int ldMemoryPoolOwnsAddress(struct memory_pool* pPool, void* pPointer)
{
    return (LD_UTILS_IN_RANGE(
        pPointer,
        pPool->pMainBuffer,
        LD_UTILS_FORWARD_POINTER(pPool->pMainBuffer, pPool->elementCapacity * pPool->stride)
        ));
}

static struct memory_pool* ldGetPoolBySize(size_t size)
{
    if (size <= kSlotSize[ALLOC_SLOT_COUNT - 1] || size == 0)
    {
        LD_UTILS_ROUND_POT(size);

        if (size < kSlotSize[0]) return &gSlotPools[0];

        /* Simple binary search */
        if (size < kSlotSize[ALLOC_SLOT_COUNT / 2])
        {
            for (int32_t index = 0; index < ALLOC_SLOT_COUNT; ++index)
            {
                if (size == kSlotSize[index]) return &gSlotPools[index];
            }
        }
        else
        {
            for (int32_t index = ALLOC_SLOT_COUNT - 1; index >= 0; --index)
            {
                if (size == kSlotSize[index]) return &gSlotPools[index];
            }
        }
    }
    return NULL;
}

static struct memory_pool* ldGetPoolByAddress(void* pPointer)
{
    for (int32_t index = 0; index < ALLOC_SLOT_COUNT; ++index)
    {
        if (ldMemoryPoolOwnsAddress(&gSlotPools[index], pPointer))
        {
            return &gSlotPools[index];
        }
    }
    return NULL;
}
/* =================== */
/* Slot Allocator TAIL */
/* =================== */

/* =================== */
/* =================== */

/* =================== */
/* Scratch Alloc. HEAD */
/* =================== */
void* gScratchBufferHead = NULL;
void* gScratchBufferTail = NULL;
size_t gScratchSize = 0;
const size_t kScratchCapacity = LD_UTILS_MB(16);
/* =================== */
/* Scratch Alloc. TAIL */
/* =================== */

/* =================== */
/* =================== */

/* =================== */
/* Heap Allocator HEAD */
/* =================== */
struct chunk_info
{
    size_t chunkSize;
    struct chunk_info* pNext;
};
struct chunk_info* gFreelistHead = NULL;
struct chunk_info* gFreelistTail = NULL;
void* gFreelistBuffer = NULL;
void* gFreelistCurrent = NULL;
size_t gFreelistSize = 0;
const size_t kFreelistCapacity = LD_UTILS_MB(64);
#define ALLOC_MEMTOCHUNK(mem) (struct chunk_info*)((struct chunk_info*)mem - 1)
#define ALLOC_CHUNKTOMEM(chunk) (void*)((struct chunk_info*)chunk + 1)
/* =================== */
/* Heap Allocator TAIL */
/* =================== */

void ldInitMem()
{
    /* Initialize Slot Allocator */
    {
        for (int32_t index = 0; index < ALLOC_SLOT_COUNT; ++index)
        {
            struct memory_pool* pPool = &gSlotPools[index];
            pPool->poolLength = 0;
            pPool->mainByteLength = 0;
            pPool->stride = kSlotSize[index];
            pPool->elementCapacity = kSlotBufferSizes[index] / kSlotSize[index];
            pPool->pMainBuffer = ldPageMalloc(kSlotBufferSizes[index]);
            pPool->pPoolBuffer = ldPageMalloc(pPool->elementCapacity * sizeof(void*));
            pPool->pMainElements = (byte_t*)pPool->pMainBuffer;
            pPool->pPoolElements = (void**)pPool->pPoolBuffer;
        }
    }

    /* Initialize Scratch Allocator */
    {
        gScratchBufferHead = ldPageMalloc(kScratchCapacity);
        gScratchBufferTail = gScratchBufferHead;
        gScratchSize = 0;
    }

    /* Initialize Heap Allocator */
    {
        gFreelistHead = NULL;
        gFreelistTail = NULL;
        gFreelistBuffer = ldPageMalloc(kFreelistCapacity);
        gFreelistCurrent = gFreelistBuffer;
        gFreelistSize = 0;
    }
}

void ldShutdownMem()
{
    /* Shutdown Slot Allocator */
    {
        for (int32_t index = 0; index < ALLOC_SLOT_COUNT; ++index)
        {
            struct memory_pool* pPool = &gSlotPools[index];
            ldPageFree(pPool->pMainBuffer);
            ldPageFree(pPool->pPoolBuffer);
            pPool->poolLength = 0;
            pPool->mainByteLength = 0;
            pPool->stride = 0;
            pPool->elementCapacity = 0;
            pPool->pMainElements = NULL;
            pPool->pPoolElements = NULL;
            pPool->pMainBuffer = NULL;
            pPool->pPoolBuffer = NULL;
        }
    }

    /* Shutdown Scratch Allocator */
    {
        ldPageFree(gScratchBufferHead);
        gScratchBufferHead = NULL;
        gScratchBufferTail = NULL;
        gScratchSize = 0;
    }

    /* Shutdown Heap Allocator */
    {
        ldPageFree(gFreelistBuffer);
        gFreelistHead = NULL;
        gFreelistTail = NULL;
        gFreelistBuffer = NULL;
        gFreelistCurrent = NULL;
        gFreelistSize = 0;
    }
}

void* ldSlotMalloc(size_t size)
{
    struct memory_pool* pPool = ldGetPoolBySize(size);
    if (pPool != NULL)
    {
        return ldMemoryPoolAlloc(pPool);
    }
    return NULL;
}

void ldSlotFree(void* pPointer)
{
    struct memory_pool* pPool = ldGetPoolByAddress(pPointer);
    if (pPool)
    {
        ldMemoryPoolFree(pPool, pPointer);
    }
}

void* ldHeapMalloc(size_t size, size_t alignment)
{
    if (gFreelistHead != NULL)
    {
        struct chunk_info* pInfo = gFreelistHead;
        struct chunk_info* pPrev = NULL;

        while (pInfo != NULL)
        {
            if (pInfo->chunkSize >= size &&
                LD_UTILS_IS_POINTER_ALIGNED(ALLOC_CHUNKTOMEM(pInfo), alignment))
            {
                if (pPrev != NULL)
                {
                    pPrev->pNext = pInfo->pNext;
                    pInfo->pNext = NULL;
                }
                else if (pInfo->pNext != NULL)
                {
                    gFreelistHead = pInfo->pNext;
                }
                else
                {
                    gFreelistHead = NULL;
                    gFreelistTail = NULL;
                }
                void* pAllocPointer = ALLOC_CHUNKTOMEM(pInfo);
#if defined(LD_PLATFORM_DEBUG)
                memset(pAllocPointer, 0xAA, pInfo->chunkSize);
#endif
                return pAllocPointer;
            }
            pPrev = pInfo;
            pInfo = pInfo->pNext;
        }
    }

    void* pNewPointer = LD_UTILS_ALIGN_POINTER(LD_UTILS_FORWARD_POINTER(gFreelistCurrent, sizeof(struct chunk_info)), alignment);
    if (LD_UTILS_IN_RANGE(pNewPointer, gFreelistBuffer, LD_UTILS_FORWARD_POINTER(gFreelistBuffer, kFreelistCapacity)))
    {
        struct chunk_info* pInfo = ALLOC_MEMTOCHUNK(pNewPointer);
        pInfo->chunkSize = size;
        pInfo->pNext = NULL;
#if defined(LD_PLATFORM_DEBUG)
        memset(pNewPointer, 0xAA, size);
#endif
        gFreelistCurrent = LD_UTILS_FORWARD_POINTER(pNewPointer, size);
        return pNewPointer;
    }

    return NULL;
}

void ldHeapFree(void* pPointer)
{
    if ((LD_UTILS_IN_RANGE(pPointer, gFreelistBuffer, LD_UTILS_FORWARD_POINTER(gFreelistBuffer, kFreelistCapacity))))
    {
        struct chunk_info* pInfo = ALLOC_MEMTOCHUNK(pPointer);
        if (gFreelistTail != NULL)
        {
            pInfo->pNext = NULL;
            gFreelistTail->pNext = pInfo;
            gFreelistTail = gFreelistTail->pNext;
        }
        else
        {
            gFreelistHead = pInfo;
            gFreelistTail = gFreelistHead;
        }
#if defined(LD_PLATFORM_DEBUG)
        memset(pPointer, 0xDD, pInfo->chunkSize);
#endif
    }
}

void* ldScratchMalloc(size_t size, size_t alignment)
{
    void* pNewPointer = LD_UTILS_ALIGN_POINTER(gScratchBufferTail, alignment);
    if (LD_UTILS_IN_RANGE(LD_UTILS_FORWARD_POINTER(pNewPointer, size), gScratchBufferHead, LD_UTILS_FORWARD_POINTER(gScratchBufferHead, kScratchCapacity)))
    {
        gScratchBufferTail = LD_UTILS_FORWARD_POINTER(pNewPointer, size);
#if defined(LD_PLATFORM_DEBUG)
        memset(pNewPointer, 0xAA, size);
#endif
        return pNewPointer;
    }
    return NULL;
}

void ldScratchReset()
{
    gScratchBufferTail = gScratchBufferHead;
}
