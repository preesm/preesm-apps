cmake_minimum_required(VERSION 3.1)

project(Sift)

# Add definition for relative path into project
add_definitions( -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
set(DEBUG 0)

set(CMAKE_VERBOSE_MAKEFILE off)

if(${DEBUG})
  MESSAGE("Generate Debug project")
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
  set(CMAKE_C_FLAGS_DEBUG "-std=gnu11 -g -pg -Wall -DSIFT_DEBUG")
else()
  MESSAGE("Generate Release project")
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
  set(CMAKE_C_FLAGS_RELEASE "-std=gnu11 -Wall -O2")
endif()




# find_library(papi_LIBRARY papi)
# if (papi_LIBRARY)
#    MESSAGE("PAPI Lib found")
# else()
#    MESSAGE(FATAL_ERROR "PAPI lib NOT found")
# endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(
	GLOB_RECURSE
	source_files
	./
	./generated/*.c
	./src/*.c
	./src/x86/*.c
)

add_executable(extract ${source_files} ${header_files})
target_include_directories(extract PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/generated PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/x86)
target_link_libraries(extract Threads::Threads m) # ${papi_LIBRARY})
