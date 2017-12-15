#ifndef _LOADER_H_
#define _LOADER_H_

#include "types.h"

enum load_alloc_type
{
    LOAD_SCRATCH,
    LOAD_PERSIST
};

struct file_binary;
typedef struct file_binary file_binary_t;

struct file_binary* file_binary_load(const char* p_path, enum load_alloc_type load_type);
struct file_binary* file_binary_load_with_header(const char* p_path, enum load_alloc_type load_type, const void* p_header, size_t header_size);
void file_binary_unload(struct file_binary* p_bin);
size_t file_binary_get_size(const struct file_binary* p_bin);
const void* file_binary_get_data(struct file_binary* p_bin);

#endif // !_LOADER_H_
