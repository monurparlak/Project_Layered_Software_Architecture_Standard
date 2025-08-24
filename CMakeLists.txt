cmake_minimum_required(VERSION 3.13)

# Project Name and Language
project(embedded_system_project C)

# C Standard Definition
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output Binary Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include Directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/device/hardware/include
    ${CMAKE_SOURCE_DIR}/hal
)

# Core Source Files
set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/main.c
)

# Device Layer: Drivers for peripherals like buttons, LEDs, etc.
set(DEVICE_FILES
    ${CMAKE_SOURCE_DIR}/device/hardware/src/button.c
)

# HAL Layer: Hardware Abstraction for specific MCU platform
set(HAL_FILES
    ${CMAKE_SOURCE_DIR}/hal/hal_gpio.c
)

# Target Executable
add_executable(embedded_app
    ${SRC_FILES}
    ${DEVICE_FILES}
    ${HAL_FILES}
)

# Output ELF, HEX, and BIN files if cross-compiling for embedded MCU
add_custom_command(TARGET embedded_app POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/embedded_app ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/embedded_app.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/embedded_app ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/embedded_app.bin
    COMMENT "Generating .hex and .bin files"
)

# Optional: Define target MCU, cross-compile toolchain, flags
# set(CMAKE_TOOLCHAIN_FILE path/to/toolchain.cmake)
# set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
# set(CMAKE_C_FLAGS "-DSTM32F4XX -O2")

# Future extension: tests, mocks, simulation
# enable_testing()
# add_subdirectory(tests)
