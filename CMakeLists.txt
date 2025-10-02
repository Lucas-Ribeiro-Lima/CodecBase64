cmake_minimum_required(VERSION 4.0)

project(CodecBase64)
project(CodecBase64Lib)
set(CMAKE_CXX_STANDARD 20)

add_executable(CodecBase64 src/main.cpp app.rc)
add_library(CodecBase64Lib STATIC src/base64.cpp)

include_directories("${CMAKE_SOURCE_DIR}/include")
target_link_libraries(CodecBase64 CodecBase64Lib)
