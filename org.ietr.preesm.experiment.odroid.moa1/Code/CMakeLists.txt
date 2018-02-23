cmake_minimum_required(VERSION 2.6)

# *******************************************
# ************* CMake Content ***************
# *******************************************
# This CMake create a workspace containing the following projects
# 
# Programs
#  - test_moa

# IDE dependent config
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 9 2008")
	MESSAGE("Add definition for ${CMAKE_GENERATOR}")
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

project(test_moa)
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_C_FLAGS "-std=c99 -O3") 

# *******************************************
# ************ Pthread LIBRARY **************
# *******************************************
if (WIN32)
  set(THREADS_USE_PTHREADS_WIN32 true)
# pthread included AFTER Sdl to avoid unnecessary warnings
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake_modules/")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/lib/pthread-2.8.0/")
endif()

find_package ( Threads REQUIRED )

if(NOT THREADS_FOUND)
	MESSAGE(FATAL_ERROR "Pthread not found !")
endif()

find_library(M_LIBRARY REQUIRED)

# *******************************************
# ************* test_moa  ***************
# *******************************************
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${THREADS_PTHREADS_INCLUDE_DIR} ${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR})
file(
	GLOB_RECURSE
	source_files
	./src/*.c
	./src/*.h
	./generated/*.c
	./include/*.h
)

add_executable( test_moa ${source_files} ${header_files})
target_link_libraries(test_moa ${CMAKE_THREAD_LIBS_INIT} ${SDL_LIBRARY} ${SDL_IMAGE} m)
