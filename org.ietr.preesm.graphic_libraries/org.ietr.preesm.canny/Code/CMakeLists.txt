#  Copyright or © or Copr. IETR/INSA - Rennes (2013 - 2019) :
# 
#  Antoine Morvan <antoine.morvan@insa-rennes.fr> (2018)
#  Clément Guy <clement.guy@insa-rennes.fr> (2014)
#  Florian Arrestier <florian.arrestier@insa-rennes.fr> (2017-2019)
#  Hugo Miomandre <hugo.miomandre@insa-rennes.fr> (2017)
#  Julien Heulot <julien.heulot@insa-rennes.fr> (2013 - 2015)
#  Yaset Oliva <yaset.oliva@insa-rennes.fr> (2013 - 2014)
# 
#  Spider is a dataflow based runtime used to execute dynamic PiSDF
#  applications. The Preesm tool may be used to design PiSDF applications.
# 
#  This software is governed by the CeCILL  license under French law and
#  abiding by the rules of distribution of free software.  You can  use,
#  modify and/ or redistribute the software under the terms of the CeCILL
#  license as circulated by CEA, CNRS and INRIA at the following URL
#  "http://www.cecill.info".
# 
#  As a counterpart to the access to the source code and  rights to copy,
#  modify and redistribute granted by the license, users are provided only
#  with a limited warranty  and the software's author,  the holder of the
#  economic rights,  and the successive licensors  have only  limited
#  liability.
# 
#  In this respect, the user's attention is drawn to the risks associated
#  with loading,  using,  modifying and/or developing or reproducing the
#  software by the user in light of its specific status of free software,
#  that may mean  that it is complicated to manipulate,  and  that  also
#  therefore means  that it is reserved for developers  and  experienced
#  professionals having in-depth computer knowledge. Users are therefore
#  encouraged to load and test the software's suitability as regards their
#  requirements in conditions enabling the security of their systems and/or
#  data to be ensured and,  more generally, to use and operate it in the
#  same conditions as regards security.
# 
#  The fact that you are presently reading this means that you have had
#  knowledge of the CeCILL license and that you accept its terms.

cmake_minimum_required(VERSION 3.1)

# *******************************************
# ************* CMake Content ***************
# *******************************************
# This CMake create a workspace containing the following projects
# 
# Programs
#  - preesm-canny
#  - preesm-canny-sequential

project(preesm-canny
        LANGUAGES C)

# Add definition for relative path into project
add_definitions(-DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Defines the CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_BINDIR and many other useful macros.
# See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

# Encourage user to specify a build type (e.g. Release, Debug, etc.), otherwise set it to Release.
if (NOT CMAKE_CONFIGURATION_TYPES)
    if (NOT CMAKE_BUILD_TYPE)
        message(STATUS "Setting build type to 'Release' as none was specified.")
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
    endif ()
endif ()

# Control where libraries and executables are placed during the build.
# With the following settings executables are placed in <the top level of the
# build tree>/bin and libraries/archives in <top level of the build tree>/lib.
# This is particularly useful to run ctests on libraries built on Windows
# machines: tests, which are executables, are placed in the same folders of
# dlls, which are treated as executables as well, so that they can properly
# find the libraries to run. This is a because of missing RPATH on Windows.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/${CMAKE_BUILD_TYPE}")

# Compiler specific settings
if (MSVC)
    message("Add definition _CRT_SECURE_NO_WARNINGS flag for MSVC compiler.")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> CONFIGURATIONS "Debug" "RelWithDebInfo" DESTINATION "${CMAKE_INSTALL_BINDIR}")
else ()
    set(CANNY_WARNING_FLAGS "-Wall -Wextra -pedantic-errors -Wconversion -Wformat")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -pg -O0 ${CANNY_WARNING_FLAGS}")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG ${CANNY_WARNING_FLAGS}")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message(STATUS "Using Link Time Optimization (-flto) on GNU platforms.")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")
    endif ()
    if (${CMAKE_GENERATOR} MATCHES "MinGW Makefiles")
        # To prevent a redefinition conflict
        message(STATUS "Add definition _TIMESPEC_DEFINED")
        add_definitions(-D_TIMESPEC_DEFINED)
    endif ()
endif ()

# CMake cross compilation to mingw
if (${CROSS_COMPILE_MINGW})
    set(CMAKE_SYSTEM_NAME Windows)
    set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

    # cross compilers to use for C and C++
    set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
    set(CMAKE_Fortran_COMPILER ${TOOLCHAIN_PREFIX}-gfortran)
    set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

    # target environment on the build host system
    #   set 1st to dir with the cross compiler's C/C++ headers/libs
    set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

    # modify default behavior of FIND_XXX() commands to
    # search for headers/libs in the target environment and
    # search for programs in the build host environment
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif ()

# Disable C and C++ compiler extensions.
# C/CXX_EXTENSIONS are ON by default to allow the compilers to use extended
# variants of the C/CXX language.
# However, this could expose cross-platform bugs in user code or in the headers
# of third-party dependencies and thus it is strongly suggested to turn
# extensions off.
set(CMAKE_C_EXTENSIONS OFF)

# Setting C standard to C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# We use
# - FindThreads
# - FindSDL2
# - FindSDL2TTF
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# Find Threads
include(FindThreads)

# Find SDL2
include(FindSDL2)

# Find SDL2TTF
include(FindSDL2TTF)

# ****************************************************************
# *************** parallel generated preesm-canny ****************
# ****************************************************************

# Add the files
file(
        GLOB_RECURSE
        CANNY_SRC
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/generated/*.c
        ${CMAKE_SOURCE_DIR}/generated/*.h
)

list(
        REMOVE_ITEM
        CANNY_SRC
        ${CMAKE_SOURCE_DIR}/src/main-sequential.c
)


# Set the include directories to use <> instead of ""
include_directories(
        ${PTHREADDIR}/include
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/generated
        ${SDL2_INCLUDE_DIR}
        ${SDL2TTF_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME} ${CANNY_SRC})
target_link_libraries(${PROJECT_NAME} ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} m)

# ********************************************************
# *************** sequential preesm-canny ****************
# ********************************************************

# Add the files
file(
        GLOB_RECURSE
        CANNY_SEQ_SRC
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/generated/*.h
)

add_executable(${PROJECT_NAME}-sequential ${CANNY_SEQ_SRC})
target_link_libraries(${PROJECT_NAME}-sequential ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} m)
