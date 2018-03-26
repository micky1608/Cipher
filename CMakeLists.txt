cmake_minimum_required(VERSION 3.9)
project(Cipher C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Sources/main.c Sources/error.c Sources/utilCipher.c Sources/files.c Sources/caeser.c Sources/substitution.c Sources/vigenere.c Sources/playfair.c Sources/self-encryption.c Sources/utilEnum.c Sources/utilString.c)

set(HEADER_FILES Headers/enum.h Headers/error.h Headers/structures.h Headers/utilCipher.h Headers/files.h Headers/caesar.h Headers/substitution.h Headers/vigenere.h Headers/playfair.h Headers/self-encryption.h Headers/utilEnum.h Headers/global.h Headers/main.h Headers/utilString.h)

add_executable(Cipher ${SOURCE_FILES} ${HEADER_FILES})

