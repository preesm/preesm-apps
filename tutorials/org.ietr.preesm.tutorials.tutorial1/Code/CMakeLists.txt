cmake_minimum_required(VERSION 2.6)

# *******************************************
# ************* CMake Content ***************
# *******************************************
# This CMake create a workspace containing the following projects
#
# Programs
#  - introduction

# IDE dependent config
if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	MESSAGE("Add definition for ${CMAKE_GENERATOR}")
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

project(introduction)
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Set to 1 to activate debug compilation (0 for release)
if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	set(DEBUG 0)

	if(${DEBUG})
			MESSAGE("Generate Debug project")
			set(CMAKE_BUILD_TYPE Debug)
			set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
			set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -pg -Wall")
	else()
			MESSAGE("Generate Release project")
			set(CMAKE_BUILD_TYPE Release)
			set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
			set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")
	endif()
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

if(WIN32)
	set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake_modules/")

# *******************************************
# ************ Pthread LIBRARY **************
# *******************************************
if (WIN32)
  set(THREADS_USE_PTHREADS_WIN32 true)
	# pthread included AFTER Sdl to avoid unnecessary warnings
	file(GLOB PTHREADDIR "${LIBS_DIR}/pthread-[\\.|0-9]*")
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PTHREADDIR})
	Find_Package ( THREADS REQUIRED )
else()
	Find_Package ( Threads REQUIRED )
endif()

if(NOT THREADS_FOUND)
	MESSAGE(FATAL_ERROR "Pthread not found !")
endif()


if (WIN32)
	file(GLOB
		PTHREADS_DLL
		${CMAKE_PREFIX_PATH}/lib/*.dll
	)

	MESSAGE("Copy Pthreads DLLs into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
		file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	else()
		file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
		file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
	endif()
endif()

# *******************************************
# ************* Introduction  ***************
# *******************************************
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/generated ${THREADS_PTHREADS_INCLUDE_DIR})
file(
	GLOB_RECURSE
	source_files
	./src/*.c
	./src/*.h
	./generated/*.c
	./generated/*.h
	./include/*.h
)

add_executable( introduction ${source_files} ${header_files})
target_link_libraries(introduction ${CMAKE_THREAD_LIBS_INIT})
set(CMAKE_C_FLAGS "-std=c99")
