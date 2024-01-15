
#ifndef READ_WITH_MMAP_H
#define READ_WITH_MMAP_H

void *open_mmapfile(const char* filename, size_t* size);


void close_mmapfile(void* addr, size_t size);

#endif
