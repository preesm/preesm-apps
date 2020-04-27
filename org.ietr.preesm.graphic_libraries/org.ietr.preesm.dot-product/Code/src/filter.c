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
#include <stddef.h>
#include "filter.h"

void filter(int width, int height, int filterSize, int borderSize,
            char *coefficients, unsigned char *norm, unsigned char *input,
            unsigned char *output) {
    // apply the filter
    for (int j = borderSize; j < height - borderSize; ++j) {
        const int currentLine = j * width;
        for (int i = borderSize; i < width - borderSize; i++) {
            output[currentLine + i] = 0;
            for (int k = -filterSize / 2; k < filterSize / 2; ++k) {
                const int lineWithOffset = (j + k) * width;
                for (int l = -filterSize / 2; l < filterSize / 2; ++l) {
                    output[currentLine + i] += input[lineWithOffset + i + l] * coefficients[k * filterSize + l];
                }
            }
            output[currentLine + i] /= (*norm);
        }

        /* == Set borders to zero == */
        memset(output + (j * width), 0, (size_t) borderSize * sizeof(char));
        memset(output + (j * width) + (width - borderSize), 0, (size_t) borderSize * sizeof(char));
    }

    /* == Set borders to zero == */
    memset(output, 0, ((size_t) (borderSize * width) * sizeof(char)));
    memset(output + (height - 2 * borderSize) * width, 0, ((size_t) (borderSize * width) * sizeof(char)));
}
