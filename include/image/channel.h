#ifndef CHANNEL_H
#define CHANNEL_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  const char* name;
  uint8_t* data;
  size_t width;
  size_t height;
  size_t stride;
} Channel;

#endif