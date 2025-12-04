# Download video and font files into dat/
set(VIDEO_MP4 "ShakeNDry_1920x1080_120fps_420_8bit_YUV.mp4")
set(VIDEO_YUV "ShakeNDry_1920x1080_120fps_420_8bit_YUV.yuv")
set(VIDEO_ARCHIVE "ShakeNDry_1920x1080_120fps_420_8bit_YUV.zip")
set(VIDEO_URL "https://vaader-data.insa-rennes.fr/data/preesm/assets/${VIDEO_ARCHIVE}")
set(VIDEO_MP4_URL "https://nasext-vaader.insa-rennes.fr/ietr-vaader/preesm/assets/${VIDEO_MP4}")

set(TTF_NAME "DejaVuSans.ttf")
set(TTF_URL "https://preesm.github.io/assets/downloads/${TTF_NAME}")

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

MESSAGE("Download dat content.")

# MP4 into FFMPEG
if (NOT EXISTS ${DAT_DIR}/${VIDEO_YUV})
	if (NOT EXISTS ${DAT_DIR}/${VIDEO_MP4})
		# Download video
		MESSAGE("Downloading ${VIDEO_MP4}")
		file(DOWNLOAD "${VIDEO_MP4_URL}" "${DAT_DIR}/${VIDEO_MP4}"
					EXPECTED_MD5 1F8B8C41D97A300BBA88F8D1DB57ECA3
					SHOW_PROGRESS)
	endif ()

	MESSAGE("Downloading ${FFMPEG_ARCHIVE}")
	if (NOT EXISTS ${DAT_DIR}/${FFMPEG_ARCHIVE})
		file(DOWNLOAD "${FFMPEG_URL}" "${DAT_DIR}/${FFMPEG_ARCHIVE}"
					SHOW_PROGRESS)
	endif()

	MESSAGE("Extracting ${FFMPEG_ARCHIVE}")
	file(ARCHIVE_EXTRACT
				INPUT "${DAT_DIR}/${FFMPEG_ARCHIVE}"
				DESTINATION ${DAT_DIR}/
				PATTERNS ${FFMPEG_EXTRACT}
				VERBOSE)

	MESSAGE("Converting ${VIDEO_MP4} into ${VIDEO_YUV}")
	MESSAGE("Running command: ${DAT_DIR}/${FFMPEG_EXTRACT} -i ${DAT_DIR}/${VIDEO_MP4} -vf scale=1920:1080 -c:v rawvideo -pix_fmt yuv420p ${DAT_DIR}/${VIDEO_YUV}")
	execute_process(COMMAND ${DAT_DIR}/${FFMPEG_EXTRACT} -i ${DAT_DIR}/${VIDEO_MP4} -vf scale=1920:1080 -c:v rawvideo -pix_fmt yuv420p ${DAT_DIR}/${VIDEO_YUV})

	file(REMOVE ${DAT_DIR}/${FFMPEG_ARCHIVE})

	if(NOT APPLE)
		file(REMOVE_RECURSE ${DAT_DIR}/${FFMPEG_FOLDER})
	else()
		file(REMOVE "${DAT_DIR}/${FFMPEG_ARCHIVE}")
	endif()
endif()


# Downloading/Extracting video file
if(NOT EXISTS ${DAT_DIR}/${VIDEO_YUV})
	if(NOT EXISTS ${DAT_DIR}/${VIDEO_ARCHIVE})
		MESSAGE("Downloading ${VIDEO_ARCHIVE}")
		file(DOWNLOAD ${VIDEO_URL} "${DAT_DIR}/${VIDEO_ARCHIVE}"
				EXPECTED_MD5 F439EA28BC5CE433CA9DB19FB487852D
				SHOW_PROGRESS)
	endif()
	MESSAGE("Extracting ${VIDEO_YUV}")
	file(ARCHIVE_EXTRACT
			INPUT "${DAT_DIR}/${VIDEO_ARCHIVE}"
			DESTINATION ${DAT_DIR}/
			VERBOSE)

	MESSAGE("Removing ${VIDEO_ARCHIVE}")
	file(REMOVE ${DAT_DIR}/${VIDEO_ARCHIVE})
endif()


# Downloading font file
if(NOT EXISTS ${DAT_DIR}/${TTF_NAME})
	MESSAGE("Downloading ${TTF_NAME}")
	file(DOWNLOAD ${TTF_URL} "${DAT_DIR}/${TTF_NAME}"
			EXPECTED_MD5 BE189A7E2711CDF2A7F6275C60CBC7E2)
endif()

