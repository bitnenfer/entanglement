#ifndef _ALLOC_H_
#define _ALLOC_H_

#include "types.h"

/* Default page size will be assumed at 4096 bytes */

void initalize_alloc();
void shutdown_alloc();
void* page_alloc(size_t size); /* Page size alignment */
void page_free(void* p_page);
void* slot_alloc(size_t size);
void slot_free(void* p_ptr);
void* heap_alloc(size_t size, size_t alignment);
void heap_free(void* p_ptr);
void* scratch_alloc(size_t size, size_t alignment);
void scratch_clear();

#endif // !_ALLOC_H_
