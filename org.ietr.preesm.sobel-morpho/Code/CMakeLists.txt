cmake_minimum_required(VERSION 2.6)

# *******************************************
# ************* CMake Content ***************
# *******************************************
# This CMake create a workspace containing the following projects
# 
# Programs
#  - difx_implem

# IDE dependent config
if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	MESSAGE("Add definition for ${CMAKE_GENERATOR}")
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

# Add definition for relative path into project
add_definitions( -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

project(difx_implem)

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
	#add libmath during non visual studio builds
	set(CMAKE_EXTRA_LIB m)
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

Find_Package (SDL2 REQUIRED )

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


Find_Package (SDL2TTF REQUIRED )

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
		file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
		file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
	endif()
endif()

#************************* GPU VERSION *******************************

#find_package(CUDA REQUIRED)
set(CUDA_DIR /usr/local/cuda)
set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
set(CMAKE_CUDA_ARCHITECTURES native)
if(CMAKE_CUDA_COMPILER)

	project(difx_gpu CXX CUDA)

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -g -Wall ${ADDITIONAL_C_FLAGS}")

	#find_package(CUDA 12.3 REQUIRED)
	find_package(CUDA REQUIRED)
	message(STATUS ">>> Found CUDA ${CUDA_VERSION_STRING} at ${CUDA_TOOLKIT_ROOT_DIR}")

	set(
			CUDA_NVCC_FLAGS
			${CUDA_NVCC_FLAGS};
			-std=c++11 -arch=sm_60 -Xptxas -O3 -restrict -D_FORCE_INLINES -D_DEBUG -lineinfo
	)

#	file(
#			GLOB_RECURSE
#			source_files_GPU
#			./src/GPU/*.cu
#			./generated/*.c
#			./generated/*.cu
#	)
#
#	file(
#			GLOB_RECURSE
#			header_files
#			./include/difx_gpu_header.h
#			./include/preesm.h
#			./generated/*.h
#	)
#
#	message("source_files_GPU : ${source_files_GPU}")
#	#    message("header_files : ${header_files}")
#	cuda_add_executable(difx_gpu ${source_files_GPU})
#	#target_link_libraries(difx_gpu cudart cusolver cufft m) # math, CUDA FFT and SVD
#	target_link_libraries(difx_gpu m cudart cusolver cufft ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_EXTRA_LIB} ${header_files})

	# Include directories
	include_directories(
			${CMAKE_CURRENT_SOURCE_DIR}/include
			${CMAKE_CURRENT_SOURCE_DIR}/generated
	)

	# Source files
	file(GLOB_RECURSE source_files_GPU
			${CMAKE_CURRENT_SOURCE_DIR}/src/GPU/*.cu
			${CMAKE_CURRENT_SOURCE_DIR}/src/GPU/difx_gpu.cu
			${CMAKE_CURRENT_SOURCE_DIR}/generated/*.c
			${CMAKE_CURRENT_SOURCE_DIR}/generated/*.cu
	)

	# Header files
	file(GLOB_RECURSE header_files
			${CMAKE_CURRENT_SOURCE_DIR}/generated/Cluster_difx_gpu_urc_0.h
			${CMAKE_CURRENT_SOURCE_DIR}/include/difx_gpu_header.h
			${CMAKE_CURRENT_SOURCE_DIR}/include/preesm.h
			${CMAKE_CURRENT_SOURCE_DIR}/generated/*.h
	)

	# Message to display source files (optional)
	message("source_files_GPU : ${source_files_GPU}")
	message("header_files : ${header_files}")

	# Add executable
	cuda_add_executable(difx_gpu ${source_files_GPU} ${header_files})

	# Link libraries
	target_link_libraries(difx_gpu
			m
			cudart
			cusolver
			cufft
			${SDL2_LIBRARY}
			${SDL2TTF_LIBRARY}
			${CMAKE_THREAD_LIBS_INIT}
			${CMAKE_EXTRA_LIB}
	)

else()
	message(STATUS "No CUDA compiler found")
endif()

# *******************************************
# **************** IPP  ****************
# *******************************************

set(IPP_DIR /opt/intel/oneapi/ipp/latest/lib/cmake/ipp)

FIND_PACKAGE(IPP REQUIRED)

if (IPP_FOUND)
	add_definitions (-DHAVE_IPP)
	set(IPP_INCLUDE_DIRS /opt/intel/oneapi/ipp/latest/include/)
	set(IPP_LIBRARY_DIRS /opt/intel/oneapi/ipp/latest/lib/)

	include_directories (${IPP_INCLUDE_DIRS})
	include_directories(${IPP_INCLUDE_DIRS})
	link_directories ( ${IPP_LIBRARY_DIRS} )

	find_library(IPP_CORE libippcore.so PATHS /opt/intel/oneapi/ipp/latest/lib/intel64)

endif ()

# *******************************************
# **************** difx_implem.exe  ****************
# *******************************************
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/generated ${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${THREADS_PTHREADS_INCLUDE_DIR})
file(
	GLOB_RECURSE
	source_files
	./src/*.c
	./src/*.h
	./include/*.h
	./generated/*.c
)

add_executable( difx_implem ${source_files} ${header_files})
target_link_libraries(difx_implem ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_EXTRA_LIB} ${IPP_LIBRARIES} ${CMAKE_MATH_LIBRARIES} -lm)
set(CMAKE_C_FLAGS "-std=gnu99")