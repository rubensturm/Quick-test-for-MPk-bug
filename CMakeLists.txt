cmake_minimum_required(VERSION 3.15)

# Use Clang for C and ASM (AT&T syntax)
set(CMAKE_C_COMPILER clang)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})

project(mpkbug C ASM)

# Set compiler flags
set(CMAKE_C_STANDARD 11)
set(COMMON_COMPILE_OPTIONS -Wall -Wextra -ggdb -fPIC -fno-exceptions -march=native)
set(OPTIMIZATION -O3 -flto)

set_property(SOURCE signal_entry.asm APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")

add_executable(test altstack.c signal_entry.asm)
target_compile_options(test PUBLIC ${COMMON_COMPILE_OPTIONS})
target_link_options(test PUBLIC ${COMMON_LINK_OPTIONS})