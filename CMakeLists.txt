cmake_minimum_required(VERSION 3.10)

set(EXENAME QMLOpenGLVTK)

project(${EXENAME} LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(PROJECT_SOURCE_DIR ./)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(SOURCES
    app/main.cpp
    src/QmlVTKRenderWindowInteractor.cpp
)

add_definitions(-std=c++11 -fext-numeric-literals -DPTHREADS_USED)

add_executable(${EXENAME} ${HEADERS} ${SOURCES} ${RESOURCES})