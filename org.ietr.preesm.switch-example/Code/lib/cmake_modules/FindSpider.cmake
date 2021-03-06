SET(SPIDER_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
)

FIND_PATH(SPIDER_INCLUDE_DIR spider.h
	HINTS
	$ENV{SPIDERDIR}
	PATH_SUFFIXES include
	PATHS ${SPIDER_SEARCH_PATHS}
)

#MESSAGE("SPIDER_INCLUDE_DIR : ${SPIDER_INCLUDE_DIR}")
FIND_LIBRARY(SPIDER_LIBRARY
	NAMES Spider
	HINTS
	$ENV{SPIDERDIR}
	PATH_SUFFIXES lib
	PATHS ${SPIDER_SEARCH_PATHS}
)
#MESSAGE("SPIDER_LIBRARY : ${SPIDER_LIBRARY}")


INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SPIDER REQUIRED_VARS SPIDER_LIBRARY SPIDER_INCLUDE_DIR)
