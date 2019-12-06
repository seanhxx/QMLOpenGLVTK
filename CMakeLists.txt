#TODO: Add cross platform compatibiliy

###########
# Project #
###########
cmake_minimum_required(VERSION 3.10)

project(QMLOpenGLVTK LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#########################
# External Dependencies #
#########################

#Set all dependencies dir
#Create Environment Variable QT_DIR, VTK_DIR point to bin. Example:
set(QT5_INSTALL_PREFIX $ENV{QT_DIR}/../)
set(VTK_INSTALL_PREFIX $ENV{VTK_DIR}/../)
set(CMAKE_PREFIX_PATH ${QT5_INSTALL_PREFIX})
set(CMAKE_PREFIX_PATH=%CMAKE_PREFIX_PATH%$<SEMICOLON>${VTK_INSTALL_PREFIX})

# Find Qt
find_package(Qt5 COMPONENTS Quick Widgets Qml QuickControls2 REQUIRED)
qt5_add_resources(RESOURCES resources/qml.qrc)

#Find VTK
find_package(VTK)
include(${VTK_USE_FILE})

#########
# BUILD #
#########
set(SOURCES
    app/main.cpp
    app/MainWindow.cpp
    src/QmlOpenGLWindowInteractor.cpp
    src/QmlVTKOpenGLRenderWindowInteractor.cpp
)

#Include QObject class header files here
set(HEADERS
    include/QmlOpenGLWindowInteractor.h
    include/QmlVTKOpenGLRenderWindowInteractor.h
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:interface>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/app
)

########
# LINK #
########
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_11)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/RelWithDebInfo"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin/MinSizeRel"
)

target_link_libraries(${CMAKE_PROJECT_NAME} 
    PUBLIC
        Qt5::Quick Qt5::Widgets Qt5::Qml Qt5::QuickControls2 ${VTK_LIBRARIES}
)

##############
# POST BUILD #
##############

#Qt Deployment

#Set path to windeployqt.exe
find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS "${QT5_INSTALL_PREFIX}/bin")
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>"
        --qmldir ${CMAKE_SOURCE_DIR}/resources
)

if(VTK_FOUND)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
        file(GLOB VTK_MOD_PATHS "${VTK_INSTALL_PREFIX}/bin/*.dll")
        foreach(VTK_MOD_PATH IN LISTS VTK_MOD_PATHS)
            add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${VTK_MOD_PATH}"
                "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>"
            )
        endforeach()
    endif()
endif()

##################
# Copy Resources #
##################
file(GLOB REVTK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources/ironProt.vtk")
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${REVTK_PATH}" 
    "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>"
)
