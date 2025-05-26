#include "image/chroma_subsampling.h"

const ChromaSubsampling SUBSAMPLING_444 = {
  .Y  = {1, 1},
  .Cb = {1, 1},
  .Cr = {1, 1}
};

const ChromaSubsampling SUBSAMPLING_422 = {
  .Y  = {2, 1},
  .Cb = {1, 1},
  .Cr = {1, 1}
};

const ChromaSubsampling SUBSAMPLING_420 = {
  .Y  = {2, 2},
  .Cb = {1, 1},
  .Cr = {1, 1}
};