cmake_minimum_required(VERSION 3.1)

project(Sift)

# Add definition for relative path into project
add_definitions( -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
set(DEBUG 0)

set(IMG_FILE "img1.pgm")
set(IMG_URL "https://nasext-vaader.insa-rennes.fr/ietr-vaader/preesm/assets/${IMG_FILE}")

set(PTHREAD_ARCHIVE "pthread-3.0.0.zip")
set(PTHREAD_URL "https://vaader-data.insa-rennes.fr/data/preesm/assets/${PTHREAD_ARCHIVE}")

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

# *******************************************
# *********** LIBRARIES and Dat *************
# *******************************************

set(DAT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data/")

if (NOT EXISTS ${DAT_DIR}${IMG_FILE})
  MESSAGE("Downloading ${IMG_FILE}")
    file(DOWNLOAD "${IMG_URL}" "${DAT_DIR}${IMG_FILE}"
          EXPECTED_MD5 f78d3dcfb13493a10303a6d8a4756e94
          SHOW_PROGRESS)
endif ()




# find_library(papi_LIBRARY papi)
# if (papi_LIBRARY)
#    MESSAGE("PAPI Lib found")
# else()
#    MESSAGE(FATAL_ERROR "PAPI lib NOT found")
# endif()


# *******************************************
# ************ Pthread LIBRARY **************
# *******************************************
if (WIN32)
  if (MSVC)
    set(THREADS_USE_PTHREADS_WIN32 true)
    # pthread included AFTER Sdl to avoid unnecessary warnings

    file(GLOB PTHREADDIR "${LIBS_DIR}/pthread-[\\.|0-9]*")

    # if SDL lib folder exists
    if(PTHREADDIR MATCHES "$^")

      message("Downloading PThread library from ${PTHREAD_URL}")
      file(DOWNLOAD ${PTHREAD_URL} "${LIBS_DIR}/${PTHREAD_ARCHIVE}")

      message("Extracting PThread library")
      file(ARCHIVE_EXTRACT
          INPUT "${LIBS_DIR}/${PTHREAD_ARCHIVE}"
          DESTINATION ${LIBS_DIR})
      file(REMOVE ${LIBS_DIR}/${PTHREAD_ARCHIVE})

    endif ()

    file(GLOB PTHREADDIR "${LIBS_DIR}/pthread-[\\.|0-9]*")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PTHREADDIR})
    Find_Package ( Threads REQUIRED )
    set(THREADS_PTHREADS_INCLUDE_DIR "${PTHREADDIR}/include")
  else ()
    set(THREADS_PTHREADS_INCLUDE_DIR "")
  endif ()
else()
  Find_Package ( Threads )
endif()

if(NOT THREADS_FOUND)
  MESSAGE(FATAL_ERROR "Pthread not found !")
endif()

if (MSVC)
  file(GLOB
      PTHREADS_DLL
      ${CMAKE_PREFIX_PATH}/lib/*.dll
      )

  MESSAGE("Copy Pthreads DLLs into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

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
