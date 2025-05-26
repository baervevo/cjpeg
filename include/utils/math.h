#ifndef MATH_H
#define MATH_H

#include <stdint.h>

static inline uint8_t clamp_to_uint8_t(float value) {
  if (value < 0.0f) return 0;
  if (value > 255.0f) return 255;
  return (uint8_t)(value + 0.5f);
}

#endif