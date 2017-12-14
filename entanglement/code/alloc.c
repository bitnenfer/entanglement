#include "alloc.h"
#include "utils.h"

static void memory_set(void* p_dst, byte_t value, size_t buffer_size)
{
    for (size_t index = 0; index < buffer_size; ++index)
    {
        ((byte_t*)p_dst)[index] = value;
    }
}

/* =================== */
/* Slot Allocator HEAD */
/* =================== */
#if defined(PLATFORM_ARCH_X64)
#define ALLOC_SLOT_COUNT 8
static const size_t k_SlotSizes[ALLOC_SLOT_COUNT] = { 8, 16, 32, 64, 128, 256, 512, 1024 };
static const size_t k_SlotBufferSizes[ALLOC_SLOT_COUNT] = {
    UTILS_MB(1),
    UTILS_MB(1),
    UTILS_MB(1),
    UTILS_MB(1),
    UTILS_MB(2),
    UTILS_MB(4),
    UTILS_MB(8),
    UTILS_MB(16)
};
#else
#define ALLOC_SLOT_COUNT 9
static const size_t k_SlotSizes[ALLOC_SLOT_COUNT] = { 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
static const size_t k_SlotBufferSizes[ALLOC_SLOT_COUNT] = {
    UTILS_MB(1),
    UTILS_MB(1),
    UTILS_MB(1),
    UTILS_MB(1),
    UTILS_MB(1),
    UTILS_MB(2),
    UTILS_MB(4),
    UTILS_MB(8),
    UTILS_MB(16)
};
#endif

struct memory_pool
{
    void* p_main_buffer;
    void* p_pool_buffer;
    void** p_pool_elements;
    byte_t* p_main_elements;
    size_t pool_length;
    size_t main_byte_length;
    size_t element_capacity;
    size_t stride;
};

struct memory_pool g_SlotPools[ALLOC_SLOT_COUNT];

static void* memory_pool_alloc(struct memory_pool* p_pool)
{
    void* p_pointer = NULL;

    if (p_pool->pool_length > 0)
    {
        p_pointer = p_pool->p_pool_elements[--(p_pool->pool_length)];
#if defined(PLATFORM_DEBUG)
        memory_set(p_pointer, 0xAA, p_pool->stride);
#endif
    }
    else if (p_pool->main_byte_length + p_pool->stride < p_pool->element_capacity * p_pool->stride)
    {
        p_pointer = (void*)&p_pool->p_main_elements[(p_pool->main_byte_length += p_pool->stride)];
#if defined(PLATFORM_DEBUG)
        memory_set(p_pointer, 0xAA, p_pool->stride);
#endif
    }

    return p_pointer;
}

static void memory_pool_free(struct memory_pool* p_pool, void* p_pointer)
{
    if (p_pool->pool_length < p_pool->element_capacity)
    {
#if defined(PLATFORM_DEBUG)
        memory_set(p_pointer, 0xDD, p_pool->stride);
#endif
        p_pool->p_pool_elements[p_pool->pool_length++] = p_pointer;
    }
}

static int memory_pool_owns_address(struct memory_pool* p_pool, void* p_pointer)
{
    return (UTILS_IN_RANGE(
        p_pointer,
        p_pool->p_main_buffer,
        UTILS_FORWARD_POINTER(p_pool->p_main_buffer, p_pool->element_capacity * p_pool->stride)
        ));
}

static struct memory_pool* get_pool_by_size(size_t size)
{
    if (size <= k_SlotSizes[ALLOC_SLOT_COUNT - 1] || size == 0)
    {
        UTILS_ROUND_POT(size);

        if (size < k_SlotSizes[0]) return &g_SlotPools[0];

        /* Simple binary search */
        if (size < k_SlotSizes[ALLOC_SLOT_COUNT / 2])
        {
            for (int32_t index = 0; index < ALLOC_SLOT_COUNT; ++index)
            {
                if (size == k_SlotSizes[index]) return &g_SlotPools[index];
            }
        }
        else
        {
            for (int32_t index = ALLOC_SLOT_COUNT - 1; index >= 0; --index)
            {
                if (size == k_SlotSizes[index]) return &g_SlotPools[index];
            }
        }
    }
    return NULL;
}

static struct memory_pool* get_pool_by_address(void* p_pointer)
{
    for (int32_t index = 0; index < ALLOC_SLOT_COUNT; ++index)
    {
        if (memory_pool_owns_address(&g_SlotPools[index], p_pointer))
        {
            return &g_SlotPools[index];
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
void* g_ScratchBufferHead = NULL;
void* g_ScratchBufferTail = NULL;
size_t g_ScratchSize = 0;
const size_t k_ScratchCapacity = UTILS_MB(16);
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
    size_t chunk_size;
    struct chunk_info* p_next;
};
struct chunk_info* g_FreelistHead = NULL;
struct chunk_info* g_FreelistTail = NULL;
void* g_FreelistBuffer = NULL;
void* g_FreelistCurrent = NULL;
size_t g_FreelistSize = 0;
const size_t k_FreelistCapacity = UTILS_MB(64);
#define ALLOC_MEMTOCHUNK(mem) (struct chunk_info*)((struct chunk_info*)mem - 1)
#define ALLOC_CHUNKTOMEM(chunk) (void*)((struct chunk_info*)chunk + 1)
/* =================== */
/* Heap Allocator TAIL */
/* =================== */

void initalize_alloc()
{
    /* Initialize Slot Allocator */
    {
        for (int32_t index = 0; index < ALLOC_SLOT_COUNT; ++index)
        {
            struct memory_pool* p_pool = &g_SlotPools[index];
            p_pool->pool_length = 0;
            p_pool->main_byte_length = 0;
            p_pool->stride = k_SlotSizes[index];
            p_pool->element_capacity = k_SlotBufferSizes[index] / k_SlotSizes[index];
            p_pool->p_main_buffer = page_alloc(k_SlotBufferSizes[index]);
            p_pool->p_pool_buffer = page_alloc(p_pool->element_capacity * sizeof(void*));
            p_pool->p_main_elements = (byte_t*)p_pool->p_main_buffer;
            p_pool->p_pool_elements = (void**)p_pool->p_pool_buffer;
        }
    }

    /* Initialize Scratch Allocator */
    {
        g_ScratchBufferHead = page_alloc(k_ScratchCapacity);
        g_ScratchBufferTail = g_ScratchBufferHead;
        g_ScratchSize = 0;
    }

    /* Initialize Heap Allocator */
    {
        g_FreelistHead = NULL;
        g_FreelistTail = NULL;
        g_FreelistBuffer = page_alloc(k_FreelistCapacity);
        g_FreelistCurrent = g_FreelistBuffer;
        g_FreelistSize = 0;
    }
}

void shutdown_alloc()
{
    /* Shutdown Slot Allocator */
    {
        for (int32_t index = 0; index < ALLOC_SLOT_COUNT; ++index)
        {
            struct memory_pool* p_pool = &g_SlotPools[index];
            page_free(p_pool->p_main_buffer);
            page_free(p_pool->p_pool_buffer);
            p_pool->pool_length = 0;
            p_pool->main_byte_length = 0;
            p_pool->stride = 0;
            p_pool->element_capacity = 0;
            p_pool->p_main_elements = NULL;
            p_pool->p_pool_elements = NULL;
            p_pool->p_main_buffer = NULL;
            p_pool->p_pool_buffer = NULL;
        }
    }

    /* Shutdown Scratch Allocator */
    {
        page_free(g_ScratchBufferHead);
        g_ScratchBufferHead = NULL;
        g_ScratchBufferTail = NULL;
        g_ScratchSize = 0;
    }

    /* Shutdown Heap Allocator */
    {
        page_free(g_FreelistBuffer);
        g_FreelistHead = NULL;
        g_FreelistTail = NULL;
        g_FreelistBuffer = NULL;
        g_FreelistCurrent = NULL;
        g_FreelistSize = 0;
    }
}

void* slot_alloc(size_t size)
{
    struct memory_pool* p_pool = get_pool_by_size(size);
    if (p_pool != NULL)
    {
        return memory_pool_alloc(p_pool);
    }
    return NULL;
}

void slot_free(void* p_ptr)
{
    struct memory_pool* p_pool = get_pool_by_address(p_ptr);
    if (p_pool)
    {
        memory_pool_free(p_pool, p_ptr);
    }
}

void* heap_alloc(size_t size, size_t alignment)
{
    if (g_FreelistHead != NULL)
    {
        struct chunk_info* p_info = g_FreelistHead;
        struct chunk_info* p_prev = NULL;

        while (p_info != NULL)
        {
            if (p_info->chunk_size >= size &&
                UTILS_IS_POINTER_ALIGNED(ALLOC_CHUNKTOMEM(p_info), alignment))
            {
                if (p_prev != NULL)
                {
                    p_prev->p_next = p_info->p_next;
                    p_info->p_next = NULL;
                }
                else if (p_info->p_next != NULL)
                {
                    g_FreelistHead = p_info->p_next;
                }
                else
                {
                    g_FreelistHead = NULL;
                    g_FreelistTail = NULL;
                }
                void* p_alloc_pointer = ALLOC_CHUNKTOMEM(p_info);
#if defined(PLATFORM_DEBUG)
                memory_set(p_alloc_pointer, 0xAA, p_info->chunk_size);
#endif
                return p_alloc_pointer;
            }
            p_prev = p_info;
            p_info = p_info->p_next;
        }
    }

    void* p_new_pointer = UTILS_ALIGN_POINTER(UTILS_FORWARD_POINTER(g_FreelistCurrent, sizeof(struct chunk_info)), alignment);
    if (UTILS_IN_RANGE(p_new_pointer, g_FreelistBuffer, UTILS_FORWARD_POINTER(g_FreelistBuffer, k_FreelistCapacity)))
    {
        struct chunk_info* p_info = ALLOC_MEMTOCHUNK(p_new_pointer);
        p_info->chunk_size = size;
        p_info->p_next = NULL;
#if defined(PLATFORM_DEBUG)
        memory_set(p_new_pointer, 0xAA, size);
#endif
        g_FreelistCurrent = UTILS_FORWARD_POINTER(p_new_pointer, size);
        return p_new_pointer;
    }

    return NULL;
}

void heap_free(void* p_pointer)
{
    if ((UTILS_IN_RANGE(p_pointer, g_FreelistBuffer, UTILS_FORWARD_POINTER(g_FreelistBuffer, k_FreelistCapacity))))
    {
        struct chunk_info* p_info = ALLOC_MEMTOCHUNK(p_pointer);
        if (g_FreelistTail != NULL)
        {
            p_info->p_next = NULL;
            g_FreelistTail->p_next = p_info;
            g_FreelistTail = g_FreelistTail->p_next;
        }
        else
        {
            g_FreelistHead = p_info;
            g_FreelistTail = g_FreelistHead;
        }
#if defined(PLATFORM_DEBUG)
        memory_set(p_pointer, 0xDD, p_info->chunk_size);
#endif
    }
}

void* scratch_alloc(size_t size, size_t alignment)
{
    void* p_new_pointer = UTILS_ALIGN_POINTER(g_ScratchBufferTail, alignment);
    if (UTILS_IN_RANGE(UTILS_FORWARD_POINTER(p_new_pointer, size), g_ScratchBufferHead, UTILS_FORWARD_POINTER(g_ScratchBufferHead, k_ScratchCapacity)))
    {
        g_ScratchBufferTail = UTILS_FORWARD_POINTER(p_new_pointer, size);
#if defined(PLATFORM_DEBUG)
        memory_set(p_new_pointer, 0xAA, size);
#endif
        return p_new_pointer;
    }
    return NULL;
}

void scratch_clear()
{
    g_ScratchBufferTail = g_ScratchBufferHead;
}
