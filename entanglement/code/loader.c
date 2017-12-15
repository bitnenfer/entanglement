#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "loader.h"
#include "utils.h"
#include "alloc.h"

struct file_binary
{
    enum load_alloc_type load_type;
    size_t size;
};

struct file_binary* file_binary_load(const char* p_path, enum load_alloc_type load_type)
{
    FILE* p_file;
    size_t size;
    p_file = fopen(p_path, "r");
    if (p_file == NULL) return NULL;

    fseek(p_file, 0, SEEK_END);
    size = ftell(p_file);
    rewind(p_file);

    void* p_buff;
    if (load_type == LOAD_PERSIST)
    {
        p_buff = page_alloc(sizeof(struct file_binary) + size);
    }
    else
    {
        p_buff = scratch_alloc(sizeof(struct file_binary) + size, 4);
    }
    fread(UTILS_FORWARD_POINTER(p_buff, sizeof(struct file_binary)), size, 1, p_file);
    struct file_binary* p_filebin = (struct file_binary*)p_buff;
    p_filebin->load_type = load_type;
    p_filebin->size = size;

    return p_filebin;
}

struct file_binary* file_binary_load_with_header(const char* p_path, enum load_alloc_type load_type, const void* p_header, size_t header_size)
{
    FILE* p_file;
    size_t size;
    p_file = fopen(p_path, "r");
    if (p_file == NULL) return NULL;

    fseek(p_file, 0, SEEK_END);
    size = ftell(p_file);
    rewind(p_file);

    void* p_buff;
    if (load_type == LOAD_PERSIST)
    {
        p_buff = page_alloc(sizeof(struct file_binary) + size + header_size);
    }
    else
    {
        p_buff = scratch_alloc(sizeof(struct file_binary) + size + header_size, 4);
    }
    memcpy(UTILS_FORWARD_POINTER(p_buff, sizeof(struct file_binary)), p_header, header_size);
    fread(UTILS_FORWARD_POINTER(p_buff, sizeof(struct file_binary) + header_size), size, 1, p_file);
    struct file_binary* p_filebin = (struct file_binary*)p_buff;
    p_filebin->load_type = load_type;
    p_filebin->size = size;

    return p_filebin;
}

void file_binary_unload(struct file_binary* p_bin)
{
    if (p_bin->load_type == LOAD_PERSIST)
    {
        page_free(p_bin);
    }
}

size_t file_binary_get_size(const struct file_binary* p_bin)
{
    return p_bin->size;
}

const void* file_binary_get_data(struct file_binary* p_bin)
{
    return (const void*)UTILS_FORWARD_POINTER(p_bin, sizeof(struct file_binary));
}
