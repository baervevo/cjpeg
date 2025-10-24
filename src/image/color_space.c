#include <stdlib.h>

#include "image/color_space.h"
#include "image/image.h"
#include "utils/math.h"

void rgb_to_ycbcr(
  const Image* rgb, Image* ycbcr,
  const ChromaSubsampling* subsampling
) {
  if (!rgb || !ycbcr) return;
  if (rgb->color_space != COLOR_SPACE_RGB || ycbcr->color_space != COLOR_SPACE_YCBCR) return;
  if (rgb->width != ycbcr->width || rgb->height != ycbcr->height) return;
  if (rgb->channel_count < 3 || ycbcr->channel_count < 3) return;
  Channel* R = get_channel_by_name(rgb, "R");  
  Channel* G = get_channel_by_name(rgb, "G");
  Channel* B = get_channel_by_name(rgb, "B");
  Channel* Y = get_channel_by_name(ycbcr, "Y");
  Channel* Cb = get_channel_by_name(ycbcr, "Cb");
  Channel* Cr = get_channel_by_name(ycbcr, "Cr");  
  if (!R || !G || !B || !Y || !Cb || !Cr) return;
  size_t width = R->width;
  size_t height = R->height;
  size_t chroma_width = (width + subsampling->Cb.horizontal - 1) / subsampling->Cb.horizontal;
  size_t chroma_height = (height + subsampling->Cb.vertical - 1) / subsampling->Cb.vertical;
  uint32_t* Cb_accumulator = calloc(chroma_width * chroma_height, sizeof(uint32_t));
  uint32_t* Cr_accumulator = calloc(chroma_width * chroma_height, sizeof(uint32_t));
  uint16_t* count = calloc(chroma_width * chroma_height, sizeof(uint16_t));
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      size_t i = y * R->stride + x;
      uint8_t r = R->data[i];
      uint8_t g = G->data[i];
      uint8_t b = B->data[i];
      size_t cb_x = x / subsampling->Cb.horizontal;
      size_t cb_y = y / subsampling->Cb.vertical;
      size_t cb_i = cb_y * chroma_width + cb_x;
      Y->data[y * Y->stride + x] = rgb_to_y(r, g, b);
      Cb_accumulator[cb_i] += rgb_to_cb(r, g, b);
      Cr_accumulator[cb_i] += rgb_to_cr(r, g, b);
      count[cb_i]++;
    }
  }
  for (size_t y = 0; y < chroma_height; ++y) {
    for (size_t x = 0; x < chroma_width; ++x) {
      size_t i = y * chroma_width + x;
      uint32_t cb_sum = Cb_accumulator[i];
      uint32_t cr_sum = Cr_accumulator[i];
      uint16_t n = count[i];
      if (n == 0) n = 1;
      Cb->data[y * Cb->stride + x] = clamp_to_uint8_t(cb_sum / n);
      Cr->data[y * Cr->stride + x] = clamp_to_uint8_t(cr_sum / n);
    }
  }
  free(Cb_accumulator);
  free(Cr_accumulator);
  free(count);
}

static inline uint8_t rgb_to_y(const uint8_t r, const uint8_t g, const uint8_t b) {
  float y_float = 0.299f * (r) + 0.587f * (g) + 0.114f * (b);
  return clamp_to_uint8_t(y_float); 
}

static inline uint8_t rgb_to_cb(const uint8_t r, const uint8_t g, const uint8_t b) {
  float cb_float = -0.168736f * (r) - 0.331264f * (g) + 0.5f * (b) + 128.0f;
  return clamp_to_uint8_t(cb_float);
}

static inline uint8_t rgb_to_cr(const uint8_t r, const uint8_t g, const uint8_t b) {
  float cr_float =  0.5f * (r) - 0.418688f * (g) - 0.081312f * (b) + 128.0f;
  return clamp_to_uint8_t(cr_float);
}
