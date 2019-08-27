cmake_minimum_required(VERSION 2.6)

# *******************************************
# ************* CMake Content ***************
# *******************************************
# This CMake create a workspace containing the following projects
# 
# Programs
#  - sobel

# IDE dependent config
if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	MESSAGE("Add definition for ${CMAKE_GENERATOR}")
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

project(reinforcement-learning)
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Add definition for relative path into project
add_definitions( -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Set to 1 to activate debug compilation (0 for release)
if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	set(DEBUG 1)

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
# ************** SDL2 LIBRARY ***************
# *******************************************
# Set variables before finding SDL Library
# Helps to find where SDL libraries are saved (win32 only)
if(WIN32)
    # find the SDL2-x.y.z folder in the lib directory.
	file(GLOB SDL2DIR "${LIBS_DIR}/SDL2-[\\.|0-9]*")
	set(ENV{SDL2DIR} ${SDL2DIR})
endif()


find_Package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

if(NOT SDL2_FOUND)
  MESSAGE(FATAL_ERROR "SDL not found !")
endif()

if (WIN32)
	file(GLOB
		SDL2_DLL
		${SDL2DIR}/bin/*.dll
		${SDL2DIR}/lib/*.dll
	)
	
	MESSAGE("Copy SDL DLLs into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
		file(COPY ${SDL2_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	else()
		file(COPY ${SDL2_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
		file(COPY ${SDL2_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
	endif()
endif()


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
	Find_Package ( THREADS REQUIRED )
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

# ***********************
# ******** SPIDER *******
# ***********************
# find the spider folder in the libspider directory.
file(GLOB SPIDERDIR "${LIBS_DIR}/spider")
set(ENV{SPIDERDIR} ${SPIDERDIR})
 
Find_Package(Spider REQUIRED)
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
        file(COPY ${SPIDER_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
        file(COPY ${SPIDER_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
    endif()
endif()



# ********************************************
# **************** Sobel.exe  ****************
# ********************************************
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR} ${THREADS_PTHREADS_INCLUDE_DIR} ${SPIDER_INCLUDE_DIR})
file(
	GLOB_RECURSE
	source_files
    ./generated/*.cpp
	./src/*.cpp
)

file(
    GLOB_RECURSE
    header_files
    ./src/*.h
    ./generated/*.h
    ./include/*.h
)

add_executable( reinforcement-learning ${source_files} ${header_files} ${SOURCES})
target_link_libraries(reinforcement-learning ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${SPIDER_LIBRARY})
set(CMAKE_C_FLAGS "-std=gnu99 -lm")
