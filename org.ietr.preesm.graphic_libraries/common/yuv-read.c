/*
 * Copyright or © or Copr. IETR/INSA - Rennes (2013 - 2019) :
 *
 * Antoine Morvan <antoine.morvan@insa-rennes.fr> (2018)
 * Clément Guy <clement.guy@insa-rennes.fr> (2014)
 * Florian Arrestier <florian.arrestier@insa-rennes.fr> (2017-2019)
 * Hugo Miomandre <hugo.miomandre@insa-rennes.fr> (2017)
 * Julien Heulot <julien.heulot@insa-rennes.fr> (2013 - 2015)
 * Yaset Oliva <yaset.oliva@insa-rennes.fr> (2013 - 2014)
 * Karol Desnos <karol.desnos@insa-rennes.fr> (2013-2020)
 * Maxime Pelcat <karol.desnos@insa-rennes.fr> (2013-2020)
 *
 * This software is governed by the CeCILL  license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "yuv-read.h"
#include "clock.h"


/* === Static variable(s) === */

static FILE *ptfile = NULL;

/* === Function(s) definition === */

void initReadYUV(int width, int height) {
    if ((ptfile = fopen(VIDEO_PATH, "rb")) == NULL) {
        fprintf(stderr, "ERROR: failed to open file: %s\n", VIDEO_PATH);
#ifdef _WIN32
        system("PAUSE");
#endif
        exit(1);
    }

#ifdef VERBOSE
    fprintf(stderr, "INFO: Opened file: %s\n", VIDEO_PATH);
#endif

    /* == Get file size == */
    fseek(ptfile, 0, SEEK_END);
    long size = ftell(ptfile);
    rewind(ptfile);
    long expectedSize = VIDEO_FRAME_COUNT * (width * height + (width * height) / 2);
    if (size < expectedSize) {
        fprintf(stderr, "ERROR: read size[%ld] of yuv file does not match with expected size: %ld.\n", size,
                expectedSize);
        fprintf(stderr, "INFO: note that video format is expected to be 4:2:0.\n");
#ifdef _WIN32
        system("PAUSE");
#endif
        exit(1);
    }

    /* == Set initial clock == */
    startTiming(0);
}

void readYComponent(int width, int height, unsigned char *y, unsigned char *u, unsigned char *v) {
    static int uvInitialized = 0;
    if (ftell(ptfile) / (width * height + width * height / 2) >= VIDEO_FRAME_COUNT) {
        rewind(ptfile);
        unsigned int time = stopTiming(0);
        fprintf(stderr, "INFO: read %d frames in %u us --> %f fps\n", VIDEO_FRAME_COUNT, time,
                ((float) (VIDEO_FRAME_COUNT) / (float) (time)) * 1000000.f);
        startTiming(0);
    }

    fread(y, sizeof(char), (size_t) (width * height) * sizeof(char), ptfile);

    // u and v values are ignored since the output is in black and white
    fseek(ptfile, width * height / 2, SEEK_CUR);

    if (uvInitialized == 0) {
        const size_t chromaCount = ((size_t) (width * height / 4));
        /* == Both black and white have u and v equal to 128 in YUV representation == */
        memset(u, 128, chromaCount);
        memset(v, 128, chromaCount);
        uvInitialized++;
    }
}

void readYUV(int width, int height, unsigned char *y, unsigned char *u, unsigned char *v) {
    if (ftell(ptfile) / (width * height + width * height / 2) >= VIDEO_FRAME_COUNT) {
        rewind(ptfile);
        unsigned int time = stopTiming(0);
        fprintf(stderr, "INFO: read %d frames in %u us --> %f fps\n", VIDEO_FRAME_COUNT, time,
                ((float) (VIDEO_FRAME_COUNT) / (float) (time)) * 1000000.f);
        startTiming(0);
    }

    size_t res = fread(y, sizeof(char), (size_t) (width * height) * sizeof(char), ptfile);
    res += fread(u, sizeof(char), (size_t) (width * height / 4), ptfile);
    res += fread(v, sizeof(char), (size_t) (width * height / 4), ptfile);
    if (res == 0) {
        printf("Error while read file\n");
        exit(1);
    }
}
