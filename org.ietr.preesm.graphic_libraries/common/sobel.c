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

/* === Include(s) === */

#include "sobel.h"
#include <string.h>
#include <math.h>

/* === Function(s) definition === */

void sobel_raw(int width, int height, unsigned char *input, char *gx, char *gy) {
    for (int j = 1; j < height - 1; ++j) {
        const int previousLine = (j - 1) * width;
        const int currentLine = j * width;
        const int nextLine = (j + 1) * width;

        /* == Set left border to zero == */
        gx[currentLine] = 0;
        gy[currentLine] = 0;

        /* == Set right border to zero == */
        gx[currentLine + width - 1] = 0;
        gy[currentLine + width - 1] = 0;

        /* == Compute sobel x / y component == */
        for (int i = 1; i < width - 1; ++i) {
            /*
             *      | -1 0 1 |
             * gx = | -2 0 2 | * input
             *      | -1 0 1 |
             *
             */
            gx[currentLine + i] = (char) ((-input[previousLine + (i - 1)] + input[previousLine + (i + 1)]) +
                                          (-2 * input[currentLine + (i - 1)] + 2 * input[currentLine + (i + 1)]) +
                                          (-input[nextLine + (i - 1)] + input[nextLine + (i + 1)]));
            /*
             *      | -1 -2 -1 |
             * gy = |  0  0  0 | * input
             *      |  1  2  1 |
             *
             */
            gy[currentLine + i] = (char) (
                    (-input[previousLine + (i - 1)] - 2 * input[previousLine + i] - input[previousLine + (i + 1)]) +
                    (input[nextLine + (i - 1)] + 2 * input[nextLine + i] + input[nextLine + (i + 1)]));
        }
    }
    /* == Set the first line to zero == */
    memset(gx, 0, (unsigned long) width);
    memset(gy, 0, (unsigned long) width);

    /* == Set the last line to zero == */
    memset(gx + (height - 1) * width, 0, (unsigned long) width);
    memset(gy + (height - 1) * width, 0, (unsigned long) width);
}


void sobel(int width, int height, unsigned char *input, unsigned char *output) {
    for (int j = 1; j < height - 1; ++j) {
        const int previousLine = (j - 1) * width;
        const int currentLine = j * width;
        const int nextLine = (j + 1) * width;

        /* == Set left border to zero == */
        output[currentLine] = 0;

        /* == Set right border to zero == */
        output[currentLine + width - 1] = 0;

        /* == Compute sobel x / y component == */
        for (int i = 1; i < width - 1; ++i) {
            /*
             *      | -1 0 1 |
             * gx = | -2 0 2 | * input
             *      | -1 0 1 |
             *
             */
            char gx =
                    (char) ((-input[previousLine + (i - 1)] + input[previousLine + (i + 1)]) +
                            (-2 * input[currentLine + (i - 1)] + 2 * input[currentLine + (i + 1)]) +
                            (-input[nextLine + (i - 1)] + input[nextLine + (i + 1)]));
            /*
             *      | -1 -2 -1 |
             * gy = |  0  0  0 | * input
             *      |  1  2  1 |
             *
             */
            char gy = (char) (
                    (-input[previousLine + (i - 1)] - 2 * input[previousLine + i] - input[previousLine + (i + 1)]) +
                    (input[nextLine + (i - 1)] + 2 * input[nextLine + i] + input[nextLine + (i + 1)]));

            /* == Compute output pixel == */
            output[currentLine + i] = (unsigned char) sqrt((gx * gx) + (gy * gy));
        }
    }
    /* == Set the first line to zero == */
    memset(output, 0, (unsigned long) width);

    /* == Set the last line to zero == */
    memset(output + (height - 1) * width, 0, (unsigned long) width);
}
