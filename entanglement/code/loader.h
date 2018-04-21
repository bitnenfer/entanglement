#ifndef _LOADER_H_
#define _LOADER_H_

#include "types.h"
#include "canvas.h"

enum load_alloc_type
{
    LOAD_SCRATCH,
    LOAD_PERSIST
};

struct file_binary;
typedef struct file_binary file_binary_t;

struct file_binary* ldFileBinaryLoad(const char* pPath, enum load_alloc_type loadType);
struct file_binary* ldFileBinaryLoadWithHeader(const char* pPath, enum load_alloc_type loadType, const void* pHeader, size_t headerSize);
void ldFileBinaryUnload(struct file_binary* pFileBinary);
size_t ldFileBinaryGetSize(const struct file_binary* pFileBinary);
const void* ldFileBinaryGetData(struct file_binary* pFileBinary);
int32_t ldFileBinaryToImage(image_t* pOut, file_binary_t* pFileBinary);
int32_t ldLoadImage(const char* pPath, image_t* pOut);
void ldDiscardImage(image_t* pOut);

#endif // !_LOADER_H_
