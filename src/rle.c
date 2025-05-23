#include "rle.h"

size_t rle_encode(const uint8_t* input, size_t input_length, uint8_t* output, uint8_t output_max) {
  if (!input || !output || input_length == 0) return 0;
  size_t in = 0, out = 0;
  while (in < input_length) {
    uint8_t byte = input[in];
    size_t run = 1;
    while (in + run < input_length && input[in + run] == byte && run < 255) {
      run++;
    }
    if (out + 2 > output_max) break;
    output[out++] = byte;
    output[out++] = run;
    in += run;
  }
  return out;
}

size_t rle_decode(const uint8_t* input, size_t input_length, uint8_t* output, uint8_t output_max) {
  if (!input || !output || input_length % 2 != 0) return 0;
  size_t in = 0, out = 0;
  while (in < input_length) {
    uint8_t byte = input[in++];
    uint8_t count = input[in++];
    if (out + count > output_max) break;
    for (uint8_t i = 0; i < count; ++i) {
      output[out++] = byte;
    }
  }
  return out;
}
