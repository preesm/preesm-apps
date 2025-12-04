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

set(PTHREAD_ARCHIVE "pthread-2.9.1.zip")
set(PTHREAD_URL "https://preesm.github.io/assets/downloads/${PTHREAD_ARCHIVE}")

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
			${CMAKE_PREFIX_PATH}/dll/*.dll
			)

	MESSAGE("Copy Pthreads DLLs into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	file(COPY ${PTHREADS_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	add_definitions( -DHAVE_STRUCT_TIMESPEC )
endif()
