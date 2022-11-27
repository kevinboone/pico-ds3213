cmake_minimum_required (VERSION 3.13)

include(pico_sdk_import.cmake)
set (BINARY "pico_ds3231")
set (PROJ "pico_ds3231")
project("pico_ds3231")

set (CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -Wconversion")
set (CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -Wconversion")

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file (GLOB ds3231_src CONFIGURE_DEPENDS "ds3231/src/*.c")

add_executable(${BINARY} main.c ${ds3231_src})

target_include_directories (${BINARY} PUBLIC ds3231/include)
target_include_directories (${BINARY} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
if (PICO_ON_DEVICE)
target_link_libraries (${BINARY} PRIVATE pico_stdlib hardware_i2c)
else()
target_link_libraries (${BINARY} PRIVATE pico_stdlib)
endif()

pico_enable_stdio_usb (${BINARY} 1)
pico_enable_stdio_uart (${BINARY} 0)
pico_add_extra_outputs(${BINARY})
