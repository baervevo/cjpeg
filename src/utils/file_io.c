#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

#include "utils/file_io.h"
#include "utils/macros.h"

uint8_t* read_file(const char* path, size_t* length) {
  if (!path || !length) return NULL;
  FILE* file = fopen(path, "rb");
  if (!file) FAIL("fopen");
  if (fseek(file, 0, SEEK_END) != 0) FAIL("fseek");
  long size = ftell(file);
  if (size < 0) FAIL("ftell");
  uint8_t* buffer = malloc((size_t) size);
  if (!buffer) FAIL("malloc");
  rewind(file);
  size_t read = fread(buffer, 1, (size_t)size, file);
  if (read != (size_t)size) FAIL("fread");
  fclose(file);
  *length = (size_t)size;
  return buffer;
cleanup:
  if (file) fclose(file);
  free(buffer);
  return NULL;
}

int write_file(const char* path, const uint8_t* data, size_t length) {
  if (!path || !data) return -1;
  FILE* file = fopen(path, "wb");
  if (!file) FAIL("fopen");
  size_t written = fwrite(data, 1, length, file);
  if (written != length) FAIL("fwrite");
  if (fclose(file) != 0) FAIL("fclose");
  return 0;
cleanup:
  if (file) fclose(file);
  return -1;
}