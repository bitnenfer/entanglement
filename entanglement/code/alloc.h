#ifndef _ALLOC_H_
#define _ALLOC_H_

#include "types.h"

/* Default page size will be assumed at 4096 bytes */

void ldInitMem();
void ldShutdownMem();
void* ldPageMalloc(size_t size); /* Page size LD_ALIGNment */
void ldPageFree(void* pPage);
void* ldSlotMalloc(size_t size);
void ldSlotFree(void* pPointer);
void* ldHeapMalloc(size_t size, size_t LD_ALIGNment);
void ldHeapFree(void* pPointer);
void* ldScratchMalloc(size_t size, size_t LD_ALIGNment);
void ldScratchReset();

#endif // !_ALLOC_H_
