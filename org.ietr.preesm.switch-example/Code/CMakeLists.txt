cmake_minimum_required(VERSION 2.6)

# *******************************************
# ************* CMake Content ***************
# *******************************************
# This CMake create a workspace containing the following projects
# 
# Programs
#  - dls

# IDE dependent config
if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	MESSAGE("Add definition for ${CMAKE_GENERATOR}")
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

# Add definition for relative path into project
add_definitions( -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

project(switch-example)

# Set to 1 to activate debug compilation (0 for release)
if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	set(DEBUG 0)

	if(${DEBUG})
			MESSAGE("Generate Debug project")
			set(CMAKE_BUILD_TYPE Debug)
			set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -pg -Wall -std=c++11")
	else()
			MESSAGE("Generate Release project")
			set(CMAKE_BUILD_TYPE Release)
			set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
			set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11")
	endif()
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
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
	Find_Package ( Threads )
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
		file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
		file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	endif()
endif()


# *******************************************
# ************ Spider LIBRARY ***************
# *******************************************
 
# find the spider folder in the libspider directory.
file(GLOB SPIDERDIR "${LIBS_DIR}/spider")
set(ENV{SPIDERDIR} ${SPIDERDIR})
 
Find_Package (Spider REQUIRED )
 
if(NOT SPIDER_FOUND)
  MESSAGE(FATAL_ERROR "SPIDER not found !")
endif()
 
if (WIN32)
    file(GLOB
        SPIDER_DLL
        ${SPIDERDIR}/lib/*.dll
    )
     
    MESSAGE("Copy SPIDER DLLs into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
        file(COPY ${SPIDER_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    else()
        file(COPY ${SPIDER_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        file(COPY ${SPIDER_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endif()
endif()


# *******************************************
# **************** dls.exe  ****************
# *******************************************
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/generated 
    ${THREADS_PTHREADS_INCLUDE_DIR} 
    ${SPIDER_INCLUDE_DIR})
file(
	GLOB_RECURSE
	source_files
	./src/*.cpp
	./src/*.h
	./include/*.h
	./generated/*.cpp
	./generated/*.h
)

add_executable(switch-example ${source_files} ${header_files} )
target_link_libraries(switch-example ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_EXTRA_LIB} ${SPIDER_LIBRARY})

