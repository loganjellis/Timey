cmake_minimum_required(VERSION 4.0)
project(Timey VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "C:/ProgramData/mingw64/mingw64/bin/gcc.exe")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# option for building shared lib
option(BUILD_SHARED_LIBS "Build using a shared library." ON)

# source
set(LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/timey.c")

# building lib
add_library(timey ${LIB_SRC})

# TIMEY_EXPORTS must be defined when building Timey as a shared lib
target_compile_definitions(timey PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:TIMEY_EXPORTS>)

# include dirs
target_include_directories(timey PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# exe for testing
add_executable(Timey_test "${CMAKE_CURRENT_SOURCE_DIR}/example.c")
target_link_libraries(Timey_test PRIVATE timey)

# installing Timey
install(TARGETS timey
	EXPORT TimeyTargets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT TimeyTargets
	FILE TimeyTargets.cmake
	NAMESPACE Timey::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Timey)

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/TimeyConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/TimeyConfig.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Timey)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/TimeyConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/TimeyConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/TimeyConfigVersion.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Timey)
