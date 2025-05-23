#ifndef RLE_H
#define RLE_H

#include <stddef.h>
#include <stdint.h>

size_t rle_encode(const uint8_t* input, size_t input_length, uint8_t* output, uint8_t output_max);
size_t rle_decode(const uint8_t* input, size_t input_length, uint8_t* output, uint8_t output_max);

#endif
