cmake_minimum_required(VERSION 3.10)
project(cjpeg)

set (CMAKE_C_STANDARD 11)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(cjpeg src/main.c src/utils/file_io.c src/rle.c src/image/color_space.c src/image/image.c src/image/chroma_subsampling.c)
target_include_directories(cjpeg PRIVATE include)