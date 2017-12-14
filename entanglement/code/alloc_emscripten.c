#include "alloc.h"
#include <stdlib.h>

void* page_alloc(size_t size)
{
    return malloc(size);
}

void page_free(void* p_page)
{
    free(p_page);
}
