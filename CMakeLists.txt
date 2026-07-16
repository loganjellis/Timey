cmake_minimum_required(VERSION 4.0)
project(Timey VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build using a shared library." ON)

add_library(timey "${CMAKE_CURRENT_SOURCE_DIR}/src/timey.c")

if(BUILD_SHARED_LIBS)
	target_compile_definitions(timey PRIVATE TIMEY_EXPORTS PUBLIC TIMEY_DLL)
endif()

target_include_directories(timey PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
