#ifndef _UTILS_H_
#define _UTILS_H_

#include "types.h"

#define LD_UTILS_CLAMP(a, b, c) ((a) < (b) ? (b) : ((a) > (c) ? (c) : (a)))
#define LD_UTILS_TO_POINTER(value) ((void*)(value))
#define LD_UTILS_FORWARD_POINTER(pointer, offset) ((void*)((uintptr_t)LD_UTILS_TO_POINTER(pointer) + offset))
#define LD_UTILS_POINTER_TO_UINT(pointer) ((uintptr_t)(pointer))
#define LD_UTILS_ALIGN_POINTER(pointer, base) LD_UTILS_TO_POINTER(((LD_UTILS_POINTER_TO_UINT(pointer))+((base)-1)) & ~((base)-1))
#define LD_UTILS_IS_POINTER_ALIGNED(pointer, alignment) (((uintptr_t)pointer & (uintptr_t)(alignment - 1)) == 0)
#define LD_UTILS_KB(value) (value * 1024)
#define LD_UTILS_MB(value) (LD_UTILS_KB(value) * 1024)
#define LD_UTILS_GB(value) ((LD_UTILS_MB((uint64_t)value) * 1024))
#define LD_UTILS_UNUSED(x) ((void)&x)
#define LD_UTILS_OFFSETOF(type, member) ((size_t)&(((type*)0)->member))
#define LD_UTILS_IN_RANGE(value, min_value, max_value) (value >= min_value && value <= max_value)
#define LD_UTILS_IS_POT(x) (((x != 0) && ((x & (~x + 1)) == x)))
#define LD_UTILS_ENABLED(x) (bool32_t)((x) ? 1 : 0)
#define LD_UTILS_ROUND_POT(x) {\
    (x)--;\
    (x) |= (x) >> 1;\
    (x) |= (x) >> 2;\
    (x) |= (x) >> 4;\
    (x) |= (x) >> 8;\
    (x) |= (x) >> 16;\
    (x)++;\
}


#endif // !_UTILS_H_
