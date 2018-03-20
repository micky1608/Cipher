cmake_minimum_required(VERSION 3.9)
project(Cipher C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Sources/main.c Sources/error.c Sources/utilCipher.c)

set(HEADER_FILES Headers/enum.h Headers/error.h Headers/structures.h Headers/utilCipher.h)

add_executable(Cipher ${SOURCE_FILES} ${HEADER_FILES})

