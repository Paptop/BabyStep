# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

FILE(GLOB SRCFILES *.cpp)

add_library(freetype STATIC IMPORTED)
set_target_properties(freetype PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/external/libfreetype.a)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library( # Specifies the name of the library.
        jni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${SRCFILES}
        Pipeline.cpp)

find_library(
             # Sets the name of the path variable.
             log-lib

             # Specifies the name of the NDK library that
             # you want CMake to locate.
             log)


target_include_directories(jni PRIVATE
                            ${PROJECT_SOURCE_DIR}/external/include)

target_link_libraries(jni freetype ${log-lib} GLESv2)