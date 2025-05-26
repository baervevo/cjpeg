#ifndef CHROMA_SUBSAMPLING_H
#define CHROMA_SUBSAMPLING_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint8_t horizontal;
  uint8_t vertical;
} SamplingFactor;

typedef struct {
  SamplingFactor Y;
  SamplingFactor Cb;
  SamplingFactor Cr;
} ChromaSubsampling;

extern const ChromaSubsampling SUBSAMPLING_444;
extern const ChromaSubsampling SUBSAMPLING_422;
extern const ChromaSubsampling SUBSAMPLING_420;

#endif