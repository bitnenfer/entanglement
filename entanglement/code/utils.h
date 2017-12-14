#ifndef _UTILS_H_
#define _UTILS_H_

#include "types.h"

#define UTILS_CLAMP(a, b, c) ((a) < (b) ? (b) : ((a) > (c) ? (c) : (a)))
#define UTILS_TO_POINTER(value) ((void*)(value))
#define UTILS_FORWARD_POINTER(pointer, offset) ((void*)((uintptr_t)UTILS_TO_POINTER(pointer) + offset))
#define UTILS_POINTER_TO_UINT(pointer) ((uintptr_t)(pointer))
#define UTILS_ALIGN_POINTER(pointer, base) UTILS_TO_POINTER(((UTILS_POINTER_TO_UINT(pointer))+((base)-1)) & ~((base)-1))
#define UTILS_IS_POINTER_ALIGNED(pointer, alignment) (((uintptr_t)pointer & (uintptr_t)(alignment - 1)) == 0)
#define UTILS_KB(value) (value * 1024)
#define UTILS_MB(value) (UTILS_KB(value) * 1024)
#define UTILS_GB(value) ((UTILS_MB((uint64_t)value) * 1024))
#define UTILS_UNUSED(x) ((void)&x)
#define UTILS_OFFSETOF(type, member) ((size_t)&(((type*)0)->member))
#define UTILS_IN_RANGE(value, min_value, max_value) (value >= min_value && value <= max_value)
#define UTILS_IS_POT(x) (((x != 0) && ((x & (~x + 1)) == x)))
#define UTILS_ENABLED(x) (bool32_t)((x) ? UTILS_TRUE : UTILS_FALSE)
#define UTILS_ROUND_POT(x) {\
    (x)--;\
    (x) |= (x) >> 1;\
    (x) |= (x) >> 2;\
    (x) |= (x) >> 4;\
    (x) |= (x) >> 8;\
    (x) |= (x) >> 16;\
    (x)++;\
}


#endif // !_UTILS_H_
