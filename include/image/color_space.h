#ifndef COLOR_SPACE_H
#define COLOR_SPACE_H

#include "image/chroma_subsampling.h"
#include "image/channel.h"

struct Image;

typedef enum {
  COLOR_SPACE_RGB,
  COLOR_SPACE_YCBCR
} ColorSpace;

void image_rgb_to_ycbcr(const struct Image* rgb, struct Image* ycbcr, const ChromaSubsampling* subsampling);

static uint8_t rgb_to_y(const uint8_t r, const uint8_t g, const uint8_t b);
static uint8_t rgb_to_cb(const uint8_t r, const uint8_t g, const uint8_t b);
static uint8_t rgb_to_cr(const uint8_t r, const uint8_t g, const uint8_t b);
  
#endif