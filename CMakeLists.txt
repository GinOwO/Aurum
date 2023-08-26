CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

project(Aurum VERSION 0.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/CMake/build)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB ALG_SOURCES "${CMAKE_SOURCE_DIR}/src/algorithms/*/*.cpp")
file(GLOB MAIN_SOURCES "${CMAKE_SOURCE_DIR}/src/main/*.cpp")
file(GLOB UI_SOURCES "${CMAKE_SOURCE_DIR}/src/ui/*.cpp")

add_executable(Aurum 
    main.cpp
    ${SOURCES}
    ${ALG_SOURCES}
    ${MAIN_SOURCES}
    ${UI_SOURCES}
)

target_include_directories(Aurum PRIVATE
    ${CMAKE_SOURCE_DIR}/include/
)