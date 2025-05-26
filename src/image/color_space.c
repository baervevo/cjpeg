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
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      size_t i = y * R->stride + x;
      Y->data[i] = rgb_to_y(
        &R->data[i], &G->data[i], &B->data[i]
      );
    }
  }
  size_t Y_horizontal = subsampling->Y.horizontal;
  size_t Y_vertical = subsampling->Y.vertical;
  size_t cb_sample_width = Y_horizontal / subsampling->Cb.horizontal;
  size_t cb_sample_height = Y_vertical / subsampling->Cb.vertical;
  for (size_t y = 0; y < height; y += cb_sample_height) {
    for (size_t x = 0; x < width; x += cb_sample_width) {
      float cb_sum = 0;
      size_t count = 0;
      for (size_t row = 0; row < cb_sample_height; ++row) {
        for (size_t col = 0; col < cb_sample_width; ++col) {
          size_t pixel_x = x + col;
          size_t pixel_y = y + row;
          if (pixel_x >= width || pixel_y >= height ) continue;
          size_t i = pixel_y * R->stride + pixel_x;
          cb_sum += rgb_to_cb(
            &R->data[i], &G->data[i], &B->data[i]
          );
          count++;
        }
      }
      float cb_avg = (count > 0) ? (cb_sum / count) : 0;
      size_t cb_index = (y / cb_sample_height) * Cb->stride + (x / cb_sample_width);
      Cb->data[cb_index] = clamp_to_uint8_t(cb_avg);
    }
  }
  size_t cr_sample_width = Y_horizontal / subsampling->Cr.horizontal;
  size_t cr_sample_height = Y_vertical / subsampling->Cr.vertical;
  for (size_t y = 0; y < height; y += cr_sample_height) {
    for (size_t x = 0; x < width; x += cr_sample_width) {
      float cr_sum = 0;
      size_t count = 0;
      for (size_t row = 0; row < cr_sample_height; ++row) {
        for (size_t col = 0; col < cr_sample_width; ++col) {
          size_t pixel_x = x + col;
          size_t pixel_y = y + row;
          if (pixel_x >= width || pixel_y >= height ) continue;
          size_t i = pixel_y * R->stride + pixel_x;
          cr_sum += rgb_to_cr(
            &R->data[i], &G->data[i], &B->data[i]
          );
          count++;
        }
      }
      float cr_avg = (count > 0) ? (cr_sum / count) : 0;
      size_t cr_index = (y / cr_sample_height) * Cr->stride + (x / cr_sample_width);
      Cr->data[cr_index] = clamp_to_uint8_t(cr_avg);
    }
  }
}

uint8_t rgb_to_y(const uint8_t* r, const uint8_t* g, const uint8_t* b) {
  if (!r || !g || !b) return 0;
  float y_float = 0.299f * (*r) + 0.587f * (*g) + 0.114f * (*b);
  return clamp_to_uint8_t(y_float); 
}

uint8_t rgb_to_cb(const uint8_t* r, const uint8_t* g, const uint8_t* b) {
  if (!r || !g || !b) return 0;
  float cb_float = -0.168736f * (*r) - 0.331264f * (*g) + 0.5f * (*b) + 128.0f;
  return clamp_to_uint8_t(cb_float);
}

uint8_t rgb_to_cr(const uint8_t* r, const uint8_t* g, const uint8_t* b) {
  if (!r || !g || !b) return 0;
  float cr_float =  0.5f * (*r) - 0.418688f * (*g) - 0.081312f * (*b) + 128.0f;
  return clamp_to_uint8_t(cr_float);
}
