#include "alloc.h"
#include <Windows.h>

void* page_alloc(size_t size)
{
    void* p_pointer = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    return p_pointer;
}

void page_free(void* p_page)
{
    VirtualFree(p_page, 0, MEM_RELEASE);
}
