###########
# Project #
###########
set(PROJECT_SOURCE_DIR ./)
set(EXENAME QMLOpenGLVTK)
cmake_minimum_required(VERSION 3.10)
project(${EXENAME} LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(CMAKE_AUTOMOC ON)

#########################
# External Dependencies #
#########################

# Find Qt
set(CMAKE_PREFIX_PATH $ENV{QT_DIR}/../)
find_package(Qt5 COMPONENTS Quick Widgets Core Qml QuickControls2 REQUIRED)
qt5_add_resources(RESOURCES resources/qml.qrc)

#Find VTK

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(SOURCES
    app/main.cpp
    src/QmlVTKRenderWindowInteractor.cpp
)

add_executable(${EXENAME} ${HEADERS} ${SOURCES} ${RESOURCES})

target_link_libraries(${EXENAME} Qt5::Quick Qt5::Widgets Qt5::Qml Qt5::QuickControls2)

# add_custom_command(TARGET ${EXENAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_PREFIX_PATH}\\bin $<TARGET_FILE_DIR:${EXENAME}>)
# add_custom_command(TARGET ${EXENAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_PREFIX_PATH}\\plugins $<TARGET_FILE_DIR:${EXENAME}>)
# add_custom_command(TARGET ${EXENAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_PREFIX_PATH}\\qml $<TARGET_FILE_DIR:${EXENAME}>)