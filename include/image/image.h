#ifndef IMAGE_H
#define IMAGE_H

#include <stddef.h>
#include <stdint.h>

#include "image/color_space.h"
#include "image/channel.h"

typedef struct {
  size_t width;
  size_t height;
  size_t channel_count;
  Channel* channels; // TODO(@mariusz): Improve cache locality
  ColorSpace color_space;
} Image;

Channel* get_channel_by_name(const Image* image, const char* name);

#endif