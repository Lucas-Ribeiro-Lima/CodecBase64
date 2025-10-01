cmake_minimum_required(VERSION 4.0)
project(CodecBase64)

set(CMAKE_CXX_STANDARD 20)

add_executable(CodecBase64 src/main.cpp src/base64.cpp)

include_directories("${CMAKE_SOURCE_DIR}/include")