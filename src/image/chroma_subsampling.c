#include "image/chroma_subsampling.h"

const ChromaSubsampling SUBSAMPLING_444 = {
  .Y  = {1, 1},
  .Cb = {1, 1},
  .Cr = {1, 1}
};

const ChromaSubsampling SUBSAMPLING_422 = {
  .Y  = {1, 1},
  .Cb = {2, 1},
  .Cr = {2, 1}
};

const ChromaSubsampling SUBSAMPLING_420 = {
  .Y  = {1, 1},
  .Cb = {2, 2},
  .Cr = {2, 2}
};