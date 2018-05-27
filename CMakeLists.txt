cmake_minimum_required(VERSION 2.8.0)
project(BasicCPPLogger)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
