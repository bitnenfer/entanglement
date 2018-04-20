#include "alloc.h"
#include <stdlib.h>

void* ldPageMalloc(size_t size)
{
    return malloc(size);
}

void ldPageFree(void* p_page)
{
    free(p_page);
}
