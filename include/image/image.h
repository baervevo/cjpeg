#ifndef IMAGE_H
#define IMAGE_H

#include <stddef.h>
#include <stdint.h>

#include "image/color_space.h"

typedef struct {
  const char* name;
  uint8_t* data;
  size_t width;
  size_t height;
  size_t stride;
} Channel;

typedef struct {
  size_t width;
  size_t height;
  size_t channel_count;
  Channel* channels;
  ColorSpace color_space;
} Image;

Channel* get_channel_by_name(const Image* image, const char* name);

#endif