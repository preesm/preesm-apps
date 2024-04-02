cmake_minimum_required(VERSION 3.18.4)
# Add definition for relative path into project
add_definitions( -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
project(rfi C)

set(CMAKE_C_STANDARD 11)
# *******************************************
# ************ MPI LIBRARY **************
# *******************************************
find_package(MPI REQUIRED)
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

# *******************************************
# **************** RFI.exe  ****************
# *******************************************
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/generated ${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${THREADS_PTHREADS_INCLUDE_DIR})

file(
        GLOB_RECURSE
        source_files
        ./src/*.c
        ./src/*.h
        ./include/*.h
        ./generated/*.c
        ./generated/*.h
)
add_executable(rfi ${source_files} ${header_files})
        #generated/sub0/sub0.c
        #generated/sub0/sub0.h
        #generated/interface/sub0/snk_out_2.c)
target_link_libraries(rfi
        ${MPI_C_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${CMAKE_EXTRA_LIB}
        ${LIBM_LIBRARIES}
        m
        psrdada
)
