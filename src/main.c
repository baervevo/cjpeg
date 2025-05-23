#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rle.h"
#include "utils/file_io.h"
#include "utils/macros.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <encode|decode> <input_file> [output_file]\n", argv[0]);
    return EXIT_FAILURE;
  }
  const char* mode = argv[1];
  const char* input_path = argv[2];
  const char* output_path = (argc >= 4) ? argv[3] : "output.bin";
  size_t input_length;
  uint8_t* input_data = read_file(input_path, &input_length);
  if (!input_data) {
    fprintf(stderr, "Failed to read input file\n");
    return EXIT_FAILURE;
  }
  size_t output_max = input_length * 2;
  uint8_t* output_data = malloc(output_max);
  if (!output_data) {
    perror("malloc");
    free(input_data);
    return EXIT_FAILURE;
  }
  size_t output_len = 0;
  if (strcmp(mode, "encode") == 0) {
    output_len = rle_encode(input_data, input_length, output_data, output_max);
    if (write_file(output_path, output_data, output_len) == -1) {
      fprintf(stderr, "Failed to write to file");
      free(input_data);
      free(output_data);
      return EXIT_FAILURE;
    }
  } else if (strcmp(mode, "decode") == 0) {
    output_len = rle_decode(input_data, input_length, output_data, output_len);
  } else {
    fprintf(stderr, "Unknown mode: %s\n", mode);
    free(input_data);
    free(output_data);
    return EXIT_FAILURE;
  }
  free(input_data);
  free(output_data);
  return EXIT_SUCCESS;
}