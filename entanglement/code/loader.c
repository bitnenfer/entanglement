#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x) assert((x))
#define STBI_MALLOC(x) malloc(x)
#define STBI_FREE(x) free(x)
#define STBI_REALLOC(x, y) realloc(x, y)

#include "stb_image.h"
    
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

int32_t ldGfxCreateTexture2DNearestClamp(int32_t width, int32_t height, const void* pPixels);
void ldGfxDiscardTexture(int32_t texture);

int32_t ldFileBinaryToImage(image_t* pOut, file_binary_t* pFileBinary)
{
    size_t size = ldFileBinaryGetSize(pFileBinary);
    const void* pData = ldFileBinaryGetData(pFileBinary);
    const void* pPixels = NULL;
    int32_t channelCount = 0;
    pPixels = (const void*)stbi_load_from_memory((uint8_t*)pData, (int32_t)size, &pOut->width, &pOut->height, &channelCount, 4);
    if (pPixels == NULL) return 0;
    pOut->textureId = ldGfxCreateTexture2DNearestClamp(pOut->width, pOut->height, pPixels);
    if (pOut->textureId == 0) return 0;
    pOut->fwidth = (float32_t)pOut->width;
    pOut->fheight = (float32_t)pOut->height;
    stbi_image_free((void*)pPixels);
    return 1;
}

int32_t ldLoadImage(const char* pPath, image_t* pOut)
{
    int32_t w, h, c;
    const void* pPixels = (const void*)stbi_load(pPath, &w, &h, &c, 4);
    if (pPixels == NULL) return 0;
    pOut->textureId = ldGfxCreateTexture2DNearestClamp(w, h, pPixels);
    if (pOut->textureId == 0) return 0;
    pOut->fwidth = (float32_t)w;
    pOut->fheight = (float32_t)h;
    pOut->width = w;
    pOut->height = h;
    stbi_image_free((void*)pPixels);
    return 0;
}


void ldDiscardImage(image_t* pOut)
{
    ldGfxDiscardTexture(pOut->textureId);
    memset(pOut, 0, sizeof(image_t));
}

