#ifndef COLOR_SPACE_H
#define COLOR_SPACE_H

#include "image/chroma_subsampling.h"

struct Image;

typedef enum {
  COLOR_SPACE_RGB,
  COLOR_SPACE_YCBCR
} ColorSpace;

void image_rgb_to_ycbcr(const struct Image* rgb, struct Image* ycbcr, const ChromaSubsampling* subsampling);

uint8_t rgb_to_y(const uint8_t* r, const uint8_t* g, const uint8_t* b);
uint8_t rgb_to_cb(const uint8_t* r, const uint8_t* g, const uint8_t* b);
uint8_t rgb_to_cr(const uint8_t* r, const uint8_t* g, const uint8_t* b);
  
#endif