CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

project(Context_Switching_Emulator, LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/CMake/Files)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/CMake/build)

add_executable(Context_Switching_Emulator 
    main.cpp
)

target_include_directories(Context_Switching_Emulator PRIVATE
    src
)