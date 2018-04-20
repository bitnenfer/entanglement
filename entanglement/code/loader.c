#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "loader.h"
#include "utils.h"
#include "alloc.h"

struct file_binary
{
    enum load_alloc_type loadType;
    size_t size;
};

struct file_binary* ldFileBinaryLoad(const char* pPath, enum load_alloc_type loadType)
{
    FILE* pFile;
    size_t size;
    pFile = fopen(pPath, "r");
    if (pFile == NULL) return NULL;

    fseek(pFile, 0, SEEK_END);
    size = ftell(pFile);
    rewind(pFile);

    void* pBuffer;
    if (loadType == LOAD_PERSIST)
    {
        pBuffer = ldPageMalloc(sizeof(struct file_binary) + size);
    }
    else
    {
        pBuffer = ldScratchMalloc(sizeof(struct file_binary) + size, 4);
    }
    fread(LD_UTILS_FORWARD_POINTER(pBuffer, sizeof(struct file_binary)), size, 1, pFile);
    struct file_binary* pFilebin = (struct file_binary*)pBuffer;
    pFilebin->loadType = loadType;
    pFilebin->size = size;

    return pFilebin;
}

struct file_binary* ldFileBinaryLoadWithHeader(const char* pPath, enum load_alloc_type loadType, const void* pHeader, size_t headerSize)
{
    FILE* pFile;
    size_t size;
    pFile = fopen(pPath, "r");
    if (pFile == NULL) return NULL;

    fseek(pFile, 0, SEEK_END);
    size = ftell(pFile);
    rewind(pFile);

    void* pBuffer;
    if (loadType == LOAD_PERSIST)
    {
        pBuffer = ldPageMalloc(sizeof(struct file_binary) + size + headerSize);
    }
    else
    {
        pBuffer = ldScratchMalloc(sizeof(struct file_binary) + size + headerSize, 4);
    }
    memcpy(LD_UTILS_FORWARD_POINTER(pBuffer, sizeof(struct file_binary)), pHeader, headerSize);
    fread(LD_UTILS_FORWARD_POINTER(pBuffer, sizeof(struct file_binary) + headerSize), size, 1, pFile);
    struct file_binary* pFilebin = (struct file_binary*)pBuffer;
    pFilebin->loadType = loadType;
    pFilebin->size = size;

    return pFilebin;
}

void ldFileBinaryUnload(struct file_binary* pFileBinary)
{
    if (pFileBinary->loadType == LOAD_PERSIST)
    {
        ldPageFree(pFileBinary);
    }
}

size_t ldFileBinaryGetSize(const struct file_binary* pFileBinary)
{
    return pFileBinary->size;
}

const void* ldFileBinaryGetData(struct file_binary* pFileBinary)
{
    return (const void*)LD_UTILS_FORWARD_POINTER(pFileBinary, sizeof(struct file_binary));
}
