cmake_minimum_required(VERSION 3.5)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(cmatrix_esp32)

# Set the required components for the project
set(REQUIRED_COMPONENTS freertos esp32 spi_flash)

# Specify the source files
set(SOURCE_FILES main.c)

# Set the target chip to ESP32-S3
idf_build_set_property(TARGET esp32s3 REQUIRE)
