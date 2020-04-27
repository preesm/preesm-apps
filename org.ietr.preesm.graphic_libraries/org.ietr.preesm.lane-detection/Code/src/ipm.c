/*
 * Copyright or © or Copr. IETR/INSA - Rennes (2013 - 2019) :
 *
 * Antoine Morvan <antoine.morvan@insa-rennes.fr> (2018)
 * Zhijin Zhang <zhzhang@insa-rennes.fr> (2018)
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
#include <string.h>
#include "ipm.h"

void ipm(int width, int height, int x11, int x12, int x21, int x22, int y1,
         int y2, unsigned char *input, unsigned char *output) {
    const int frame_w1 = x12 - x11;
    const int frame_w2 = x22 - x21;
    const int frame_h = y2 - y1;

    /* == Set everything to zero for starter == */
    memset(output, 0, (size_t) (width * height) * sizeof(char));

    /* == Compute the forward ipm == */
    int k = 0;
    for (int j = 0; j < height; j++) {
        const int x_set = (x11 + (j * (x21 - x11)) / height) +
                          ((y1 + (j * frame_h) / height) * width);
        const int frame_w = frame_w1 + (j * (frame_w2 - frame_w1)) / height;
        for (int i = 0; i < width; i++) {
            output[k++] = input[x_set + (i * frame_w) / width];
        }
    }
}

void ipmReverse(int width, int height, int x11, int x12, int x21, int x22, int y1,
                int y2, unsigned char *input, unsigned char *output) {
    const int frame_w1 = x12 - x11;
    const int frame_w2 = x22 - x21;
    const int frame_h = y2 - y1;

    /* == Set everything to zero for starter == */
    memset(output, 0, (size_t) (width * height) * sizeof(char));

    /* == Compute the reverse ipm == */
    int k = 0;
    for (int j = 0; j < height; j++) {
        const int x_set = (x11 + (j * (x21 - x11)) / height) +
                          ((y1 + (j * frame_h) / height) * width);
        const int frame_w = frame_w1 + (j * (frame_w2 - frame_w1)) / height;
        for (int i = 0; i < width; i++) {
            output[x_set + (i * frame_w) / width] = input[k++];
        }
    }
}
