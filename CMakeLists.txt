cmake_minimum_required(VERSION 3.10)
project(jpeg_encoder)

set (CMAKE_C_STANDARD 11)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(jpeg_encoder src/main.c src/utils/file_io.c src/rle.c)
target_include_directories(jpeg_encoder PRIVATE include)