#include <string.h>

#include "image/image.h"

Channel* get_channel_by_name(const Image* image, const char* name) {
  for (size_t i = 0; i < image->channel_count; ++i) {
    if (strcmp(image->channels[i].name, name) == 0) {
      return &image->channels[i];
    }
  }
  return NULL;
}