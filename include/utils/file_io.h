#ifndef FILE_IO_H
#define FILE_IO_H

#include <stddef.h>
#include <stdint.h>

uint8_t* read_file(const char* path, size_t* length);
int write_file(const char* path, const uint8_t* data, size_t length);

#endif