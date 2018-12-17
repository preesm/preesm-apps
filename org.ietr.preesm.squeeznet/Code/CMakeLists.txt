cmake_minimum_required(VERSION 2.8)

# *******************************************
# ************* CMake Content ***************
# *******************************************
# This CMake create a workspace containing the following projects
# 
# Programs
#  - squeezenet_c

# IDE dependent config
if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	MESSAGE("Add definition for ${CMAKE_GENERATOR}")
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

# Add definition for relative path into project
add_definitions( -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")


project(squeezenet-c)

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

set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
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


Find_Package(SDL2 REQUIRED)

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
# ************ SDL2TTF LIBRARY **************
# ******************************************

# Set variables before finding SDL2TTF Library
# Helps to find where SDL2TTF libraries are saved (win32 only)
if(WIN32)
    # find the SDL2_ttf-x.y.z folder in the lib directory.
	file(GLOB SDL2TTFDIR "${LIBS_DIR}/SDL2_ttf-[\\.|0-9]*")
	set(ENV{SDL2TTFDIR} ${SDL2TTFDIR})
endif()


Find_Package(SDL2TTF REQUIRED)

if(NOT SDL2TTF_FOUND)
  MESSAGE(FATAL_ERROR "SDL2TTF not found !")
endif()

if (WIN32)
	file(GLOB
		SDL2TTF_DLL
		${SDL2TTFDIR}/bin/*.dll
		${SDL2TTFDIR}/lib/*.dll
	)
	
	MESSAGE("Copy SDL2_ttf DLLs into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
		file(COPY ${SDL2TTF_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	else()
		file(COPY ${SDL2TTF_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
		file(COPY ${SDL2TTF_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
	endif()
endif()

# *******************************************
# ************ SDL2IMAGE LIBRARY **************
# ******************************************

# Set variables before finding SDL2TTF Library
# Helps to find where SDL2TTF libraries are saved (win32 only)
if(WIN32)
	# find the SDL2_image-x.y.z folder in the lib directory.
	file(GLOB SDL2IMAGEDIR "${LIBS_DIR}/SDL2_image-[\\.|0-9]*")
	set(ENV{SDL2IMAGEDIR} ${SDL2IMAGEDIR})
endif()


find_package(SDL2_image REQUIRED)

if(NOT SDL2IMAGE_FOUND)
	MESSAGE(FATAL_ERROR "SDL2IMAGE not found !")
endif()

if (WIN32)
	file(GLOB
			SDL2IMAGE_DLL
			${SDL2IMAGEDIR}/bin/*.dll
			${SDL2IMAGEDIR}/lib/*.dll
			)

	MESSAGE("Copy SDL2_image DLLs into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
		file(COPY ${SDL2IMAGE_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	else()
		file(COPY ${SDL2IMAGE_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
		file(COPY ${SDL2IMAGE_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
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

if(NOT THREADS_FOUND)
	MESSAGE(FATAL_ERROR "Pthread not found !")
endif()

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
# ************ OpenMP LIBRARY ***************
# *******************************************
OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
  FIND_PACKAGE(OpenMP)
  IF(OPENMP_FOUND)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  ENDIF()
ENDIF()

# *******************************************
# ************ squeezenet-c.exe  *************
# *******************************************

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${THREADS_PTHREADS_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIR})

file(
	GLOB_RECURSE
	source_files
	./src/*.c
    ./generated/*.c
)

file(
	GLOB_RECURSE
	header_files
	./include/*.h
    ./generated/*.h
)

list(REMOVE_ITEM 
     source_files
     "${CMAKE_CURRENT_SOURCE_DIR}/./src/main-sequential.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/./src/convolution-sequential.c"
    )

list(REMOVE_ITEM 
     header_files
     "${CMAKE_CURRENT_SOURCE_DIR}/./include/convolution-sequential.h"
    )

add_executable(squeezenet-c ${source_files} ${header_files})
target_link_libraries(squeezenet-c ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2IMAGE_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} m)

list(REMOVE_ITEM 
     source_files
     "${CMAKE_CURRENT_SOURCE_DIR}/./generated/*.c"
    )

list(REMOVE_ITEM 
     header_files
     "${CMAKE_CURRENT_SOURCE_DIR}/./generated/*.h"
    )

list(APPEND
     source_files
     "${CMAKE_CURRENT_SOURCE_DIR}/./src/main-sequential.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/./src/convolution-sequential.c"
    )

list(APPEND 
     header_files
     "${CMAKE_CURRENT_SOURCE_DIR}/./include/convolution-sequential.h"
    )

add_executable(squeezenet-c-sequential ${source_files} ${header_files})
target_link_libraries(squeezenet-c-sequential ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2IMAGE_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} m)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")


