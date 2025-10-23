cmake_minimum_required(VERSION 4.0)

project(codex)
project(codexl)
set(CMAKE_CXX_STANDARD 20)

add_executable(codex
        src/main.cpp
        src/ArgParser.cpp app.rc
        src/CodexManager.cpp
        src/base64.cpp
        src/hex.cpp)

add_library(codexl STATIC
        src/base64.cpp
        src/hex.cpp)

include_directories("${CMAKE_SOURCE_DIR}/include")
target_link_libraries(codex codexl)
