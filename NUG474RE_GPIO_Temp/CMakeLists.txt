cmake_minimum_required(VERSION 3.30)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(NUCLEO_G474RE_FW_Study_1 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Toolchain
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_AR arm-none-eabi-ar)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Compile flags
add_compile_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

# Optimization
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    add_compile_options(-Os)
else ()
    add_compile_options(-Og -g)
endif ()

# Include paths
include_directories(
        Inc
        Drivers/CMSIS/Device/ST/STM32G4xx/Include
        Drivers/CMSIS/Include
)

add_definitions(-DSTM32G474xx)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32G474RETX_FLASH.ld)
set(STARTUP_FILE Startup/startup_stm32g474retx.s)
set(SYSTEM_FILE Src/system_stm32g4xx.c)

# === Firmware C version ===
add_executable(fw_c.elf
        Src/main.c
        Src/system_stm32g4xx.c
        Src/syscalls.c
        Startup/startup_stm32g474retx.s
)

set_target_properties(fw_c.elf PROPERTIES LINKER_LANGUAGE C)

target_link_options(fw_c.elf PRIVATE -T${LINKER_SCRIPT} -Wl,-Map=fw_c.map -Wl,--gc-sections)
add_custom_command(TARGET fw_c.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex fw_c.elf fw_c.hex
        COMMAND ${CMAKE_OBJCOPY} -Obinary fw_c.elf fw_c.bin
)

# === Firmware C++ version ===
add_executable(fw_cpp.elf
        Src/cpp_main.cpp
        Src/AppLed.cpp
        Src/system_stm32g4xx.c
        Src/syscalls.c
        Startup/startup_stm32g474retx.s
)

target_link_options(fw_cpp.elf PRIVATE -T${LINKER_SCRIPT} -Wl,-Map=fw_cpp.map -Wl,--gc-sections)
add_custom_command(TARGET fw_cpp.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex fw_cpp.elf fw_cpp.hex
        COMMAND ${CMAKE_OBJCOPY} -Obinary fw_cpp.elf fw_cpp.bin
)
