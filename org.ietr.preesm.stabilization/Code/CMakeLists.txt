cmake_minimum_required(VERSION 3.18)

# *******************************************
# ************* CMake Content ***************
# *******************************************
# This CMake create a workspace containing the following projects
#
# Programs
#  - stabilization

set(DEBUG 0)

set(VIDEO1_MP4 "JaguarAndCroco720x404-375f.mp4")
set(VIDEO1_YUV "JaguarAndCroco360x202-375f.yuv")
set(VIDEO1_MP4_URL "https://nasext-vaader.insa-rennes.fr/ietr-vaader/preesm/assets/${VIDEO1_MP4}")

set(VIDEO2_MP4 "GivingScholarlyFallowdeer_1280x720-415f.webm")
set(VIDEO2_YUV "GivingScholarlyFallowdeer_1280x720-415f.yuv")
set(VIDEO2_MP4_URL "https://nasext-vaader.insa-rennes.fr/ietr-vaader/preesm/assets/${VIDEO2_MP4}")

set(TTF_NAME "DejaVuSans.ttf")
set(TTF_URL "https://preesm.github.io/assets/downloads/${TTF_NAME}")

set(SDL2_VERSION "2.30.3")
set(SDL2_MINGW_ARCHIVE "SDL2-devel-${SDL2_VERSION}-mingw.zip")
set(SDL2_VC_ARCHIVE "SDL2-devel-${SDL2_VERSION}-VC.zip")
set(SDL2_MINGW_URL "https://github.com/libsdl-org/SDL/releases/download/release-${SDL2_VERSION}/${SDL2_MINGW_ARCHIVE}")
set(SDL2_VC_URL "https://github.com/libsdl-org/SDL/releases/download/release-${SDL2_VERSION}/${SDL2_VC_ARCHIVE}")

set(SDL2_TTF_VERSION "2.22.0")
set(SDL2_TTF_MINGW_ARCHIVE "SDL2_ttf-devel-${SDL2_TTF_VERSION}-mingw.zip")
set(SDL2_TTF_VC_ARCHIVE "SDL2_ttf-devel-${SDL2_TTF_VERSION}-VC.zip")
set(SDL2_TTF_MINGW_URL "https://github.com/libsdl-org/SDL_ttf/releases/download/release-${SDL2_TTF_VERSION}/${SDL2_TTF_MINGW_ARCHIVE}")
set(SDL2_TTF_VC_URL "https://github.com/libsdl-org/SDL_ttf/releases/download/release-${SDL2_TTF_VERSION}/${SDL2_TTF_VC_ARCHIVE}")

set(PTHREAD_ARCHIVE "pthread-3.0.0.zip")
set(PTHREAD_URL "https://vaader-data.insa-rennes.fr/data/preesm/assets/${PTHREAD_ARCHIVE}")

if(WIN32)
	set(FFMPEG_FOLDER "ffmpeg-master-latest-win64-gpl")
	set(FFMPEG_ARCHIVE "${FFMPEG_FOLDER}.zip")
	set(FFMPEG_URL "https://github.com/BtbN/FFmpeg-Builds/releases/download/latest/${FFMPEG_ARCHIVE}")
	set(FFMPEG_EXTRACT "${FFMPEG_FOLDER}/bin/ffmpeg.exe")
elseif(UNIX AND NOT APPLE)
	set(FFMPEG_FOLDER "ffmpeg-master-latest-linux64-gpl")
	set(FFMPEG_ARCHIVE "${FFMPEG_FOLDER}.tar.xz")
	set(FFMPEG_URL "https://github.com/BtbN/FFmpeg-Builds/releases/download/latest/${FFMPEG_ARCHIVE}")
	set(FFMPEG_EXTRACT "${FFMPEG_FOLDER}/bin/ffmpeg")
elseif(APPLE)
	set(FFMPEG_FOLDER "")	#EMPTY
	set(FFMPEG_ARCHIVE "ffmpeg.zip")
	set(FFMPEG_URL "https://evermeet.cx/ffmpeg/getrelease/zip")
	set(FFMPEG_EXTRACT "ffmpeg")
endif()



# IDE dependent config
if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
	MESSAGE("Add definition for ${CMAKE_GENERATOR}")
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif()

# Add definition for relative path into project
add_definitions( -DPROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

project(stabilization-sequential)
project(stabilization)

# If running CMake through a script/cli
if (CMAKE_BUILD_TYPE MATCHES "$^" OR NOT DEFINED CMAKE_BUILD_TYPE)
	message("Set the DEBUG variable in CMakeLists.txt for Debug/Release selection if running outside of IDE")
	if(${DEBUG})
		set(CMAKE_BUILD_TYPE Debug)
	else ()
		set(CMAKE_BUILD_TYPE Release)
	endif ()
	message("Configuring project in ${CMAKE_BUILD_TYPE} mode")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
endif ()

if(NOT DEFINED MSVC)

	if(CMAKE_BUILD_TYPE MATCHES Debug)
		MESSAGE("Generate Debug project")
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -pg -Wall")
	else()
		MESSAGE("Generate Release project")
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")
	endif()
	#add libmath during non visual studio builds
	set(CMAKE_EXTRA_LIB m)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

set(DAT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dat/")
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake_modules/")

# *******************************************
# *********** LIBRARIES and Dat *************
# *******************************************

MESSAGE("Download dat content.")

# MP4 into FFMPEG
if (NOT EXISTS ${DAT_DIR}${VIDEO1_YUV} OR NOT EXISTS ${DAT_DIR}${VIDEO2_YUV})

	if (NOT EXISTS ${DAT_DIR}${VIDEO1_MP4})
		# Download video
		MESSAGE("Downloading ${VIDEO1_MP4}")
		file(DOWNLOAD "${VIDEO1_MP4_URL}" "${DAT_DIR}${VIDEO1_MP4}"
					#EXPECTED_MD5 1F8B8C41D97A300BBA88F8D1DB57ECA3
					SHOW_PROGRESS)
	endif ()

	if (NOT EXISTS ${DAT_DIR}${VIDEO2_MP4})
		# Download video
		MESSAGE("Downloading ${VIDEO2_MP4}")
		file(DOWNLOAD "${VIDEO2_MP4_URL}" "${DAT_DIR}${VIDEO2_MP4}"
					#EXPECTED_MD5 1F8B8C41D97A300BBA88F8D1DB57ECA3
					SHOW_PROGRESS)
	endif ()

	MESSAGE("Downloading ${FFMPEG_ARCHIVE}")
	if (NOT EXISTS ${DAT_DIR}${FFMPEG_ARCHIVE})
		file(DOWNLOAD "${FFMPEG_URL}" "${DAT_DIR}${FFMPEG_ARCHIVE}"
					SHOW_PROGRESS)
	endif()

	MESSAGE("Extracting ${FFMPEG_ARCHIVE}")
	file(ARCHIVE_EXTRACT
				INPUT "${DAT_DIR}${FFMPEG_ARCHIVE}"
				DESTINATION ${DAT_DIR}
				PATTERNS ${FFMPEG_EXTRACT}
				VERBOSE)

	MESSAGE("Converting ${VIDEO1_MP4} into ${VIDEO1_YUV}")
	execute_process(COMMAND ${DAT_DIR}${FFMPEG_EXTRACT} -i ${DAT_DIR}${VIDEO1_MP4} -vf scale=360:202 -c:v rawvideo -pix_fmt yuv420p ${DAT_DIR}${VIDEO1_YUV})

	MESSAGE("Converting ${VIDEO2_MP4} into ${VIDEO2_YUV}")
	execute_process(COMMAND ${DAT_DIR}${FFMPEG_EXTRACT} -i ${DAT_DIR}${VIDEO2_MP4} -c:v rawvideo -pix_fmt yuv420p ${DAT_DIR}${VIDEO2_YUV})

	file(REMOVE ${DAT_DIR}${FFMPEG_ARCHIVE})

	if(NOT APPLE)
		file(REMOVE_RECURSE ${DAT_DIR}${FFMPEG_FOLDER})
	else()
		file(REMOVE "${DAT_DIR}${FFMPEG_ARCHIVE}")
	endif()
endif()


# Downloading/Extracting video file
if(NOT EXISTS ${DAT_DIR}${VIDEO_YUV})
	if(NOT EXISTS ${DAT_DIR}${VIDEO_ARCHIVE})
		MESSAGE("Downloading ${VIDEO_ARCHIVE}")
		file(DOWNLOAD ${VIDEO_URL} "${DAT_DIR}${VIDEO_ARCHIVE}"
				EXPECTED_MD5 F439EA28BC5CE433CA9DB19FB487852D
				SHOW_PROGRESS)
	endif()
	MESSAGE("Extracting ${VIDEO_YUV}")
	file(ARCHIVE_EXTRACT
			INPUT "${DAT_DIR}${VIDEO_ARCHIVE}"
			DESTINATION ${DAT_DIR}
			VERBOSE)

	MESSAGE("Removing ${VIDEO_ARCHIVE}")
	file(REMOVE ${DAT_DIR}${VIDEO_ARCHIVE})
endif()

# Downloading font file
if(NOT EXISTS ${DAT_DIR}${TTF_NAME})
	MESSAGE("Downloading ${TTF_NAME}")
	file(DOWNLOAD ${TTF_URL} "${DAT_DIR}${TTF_NAME}"
			EXPECTED_MD5 BE189A7E2711CDF2A7F6275C60CBC7E2)
endif()


# *******************************************
# ************** SDL2 LIBRARY ***************
# *******************************************
# Set variables before finding SDL Library
# Helps to find where SDL libraries are saved (win32 only)
if(WIN32)

	# find the SDL2-x.y.z folder in the lib directory.
	file(GLOB SDL2DIR "${LIBS_DIR}/SDL2-[\\.|0-9]*")
	set(ENV{SDL2DIR} ${SDL2DIR})

	# if SDL lib folder exists
	if(SDL2DIR MATCHES "$^")

		if (MSVC)
			set(SDL2_URL ${SDL2_VC_URL})
			set(SDL2_ARCHIVE ${SDL2_VC_ARCHIVE})
		else ()
			set(SDL2_URL ${SDL2_MINGW_URL})
			set(SDL2_ARCHIVE ${SDL2_MINGW_ARCHIVE})
		endif ()

		message("Downloading SDL2 library from ${SDL2_URL}")
		file(DOWNLOAD ${SDL2_URL} "${LIBS_DIR}/${SDL2_ARCHIVE}")

		message("Extracting SDL2 library")
		file(ARCHIVE_EXTRACT
				INPUT "${LIBS_DIR}/${SDL2_ARCHIVE}"
				DESTINATION ${LIBS_DIR})
		file(REMOVE ${LIBS_DIR}/${SDL2_ARCHIVE})

		file(GLOB SDL2DIR "${LIBS_DIR}/SDL2-[\\.|0-9]*")
		set(ENV{SDL2DIR} ${SDL2DIR})

		# Moving files
		if (MSVC)
			file(COPY "${SDL2DIR}/lib/x64/" DESTINATION "${SDL2DIR}/lib/")
		else ()
			file(COPY "${SDL2DIR}/x86_64-w64-mingw32/bin/" DESTINATION "${SDL2DIR}/bin/")
			file(COPY "${SDL2DIR}/x86_64-w64-mingw32/lib/" DESTINATION "${SDL2DIR}/lib/")

			file(COPY "${SDL2DIR}/x86_64-w64-mingw32/include/SDL2/" DESTINATION "${SDL2DIR}/include/"
					FILES_MATCHING PATTERN "*.h")
		endif ()

		# Cleaning/Removing unused files
		# MinGW
		file(REMOVE_RECURSE "${SDL2DIR}/i686-w64-mingw32")
		file(REMOVE_RECURSE "${SDL2DIR}/x86_64-w64-mingw32")
		file(REMOVE_RECURSE "${SDL2DIR}/test")

		# MSVC
		file(REMOVE_RECURSE "${SDL2DIR}/lib/x86")
		file(REMOVE_RECURSE "${SDL2DIR}/lib/x64")

	endif ()

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

	MESSAGE("Copy SDL2 DLLs into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	file(COPY ${SDL2_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
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


	# if SDL lib folder exists
	if(SDL2TTFDIR MATCHES "$^")

		if (MSVC)
			set(SDL2_TTF_URL ${SDL2_TTF_VC_URL})
			set(SDL2_TTF_ARCHIVE ${SDL2_TTF_VC_ARCHIVE})
		else ()
			set(SDL2_TTF_URL ${SDL2_TTF_MINGW_URL})
			set(SDL2_TTF_ARCHIVE ${SDL2_TTF_MINGW_ARCHIVE})
		endif ()

		message("Downloading SDL2 library from ${SDL2_TTF_URL}")
		file(DOWNLOAD ${SDL2_TTF_URL} "${LIBS_DIR}/${SDL2_TTF_ARCHIVE}")

		message("Extracting SDL2_TTF library")
		file(ARCHIVE_EXTRACT
				INPUT "${LIBS_DIR}/${SDL2_TTF_ARCHIVE}"
				DESTINATION ${LIBS_DIR})
		file(REMOVE ${LIBS_DIR}/${SDL2_TTF_ARCHIVE})

		file(GLOB SDL2TTFDIR "${LIBS_DIR}/SDL2_ttf-[\\.|0-9]*")
		set(ENV{SDL2TTFDIR} ${SDL2TTFDIR})

		# Moving files
		if (MSVC)
			file(COPY "${SDL2TTFDIR}/lib/x64/" DESTINATION "${SDL2TTFDIR}/lib/")
		else ()
			file(COPY "${SDL2TTFDIR}/x86_64-w64-mingw32/bin/" DESTINATION "${SDL2TTFDIR}/bin/")
			file(COPY "${SDL2TTFDIR}/x86_64-w64-mingw32/lib/" DESTINATION "${SDL2TTFDIR}/lib/")

			file(COPY "${SDL2TTFDIR}/x86_64-w64-mingw32/include/SDL2/" DESTINATION "${SDL2TTFDIR}/include/"
					FILES_MATCHING PATTERN "*.h")
		endif ()

		# Cleaning/Removing unused files
		# MinGW
		file(REMOVE_RECURSE "${SDL2TTFDIR}/i686-w64-mingw32")
		file(REMOVE_RECURSE "${SDL2TTFDIR}/x86_64-w64-mingw32")
		file(REMOVE_RECURSE "${SDL2TTFDIR}/test")

		# MSVC
		file(REMOVE_RECURSE "${SDL2TTFDIR}/lib/x86")
		file(REMOVE_RECURSE "${SDL2TTFDIR}/lib/x64")

	endif ()

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
	file(COPY ${SDL2TTF_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

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

# *******************************************
# ************ stabilization.exe  ************
# *******************************************
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

list(REMOVE_ITEM
	 source_files
	 "${CMAKE_CURRENT_SOURCE_DIR}/./src/main-sequential.c"
	)

add_executable( stabilization ${source_files} ${header_files})
target_link_libraries(stabilization ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_EXTRA_LIB})

file(
		GLOB_RECURSE
		source_files
		./src/*.c
		./src/*.h
		./include/*.h
)

list(REMOVE_ITEM
	 source_files
	 "${CMAKE_CURRENT_SOURCE_DIR}/./generated/main.c"
	)

add_executable( stabilization-sequential ${source_files} ${header_files})
target_link_libraries(stabilization-sequential ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_EXTRA_LIB})