CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

project(Aurum VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(Qt${QT_VERSION_MAJOR}_FOUND)
    file(GLOB ALGO_SOURCES "${CMAKE_SOURCE_DIR}/src/algorithms/*/*.cpp")
    file(GLOB MAIN_SOURCES "${CMAKE_SOURCE_DIR}/src/main/*.cpp")
    fiLe(GLOB HEADER_SRC "${CMAKE_SOURCE_DIR}/include/*")

    set(PROJECT_SOURCES
            main.cpp
            ${HEADER_SRC}
            ${MAIN_SOURCES}
            ${ALGO_SOURCES}
            src/ui/startwindow.h src/ui/startwindow.cpp src/ui/startwindow.ui
            src/ui/processwindow.h src/ui/processwindow.cpp src/ui/processwindow.ui
            src/ui/queuewindow.h src/ui/queuewindow.cpp src/ui/queuewindow.ui
    )

    qt_add_executable(Aurum
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

if(WIN32)
    set_property(TARGET Aurum PROPERTY WIN32_EXECUTABLE true)
endif()

    target_link_libraries(Aurum PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

    include(GNUInstallDirs)
    install(TARGETS Aurum
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    target_include_directories(Aurum PRIVATE
        ${CMAKE_SOURCE_DIR}/include/
    )

    qt_finalize_executable(Aurum)
else()
    message(FATAL_ERROR "Qt not found. Please make sure Qt is installed and CMake can find it.")
endif()
