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
#ifndef PREESM_READ_YUV_H
#define PREESM_READ_YUV_H

#include "yuv-information.h"

/* === Defines for input / output ports === */

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

/**
 * Initialize the readYUV actor.
 * Open the YUV file at the given PATH and check its size.
 *
 * @param width
 *        The width of the opened YUV file
 * @param height
 *        The heigth of the opened YUV file
 */
void initReadYUV(int width, int height);

/**
 * Read a new frame from the YUV file and take only the Y component.
 * U and V are given the value 128 since in the YUV representation, black
 * is (0, 128, 128) and white is (255, 128, 128).
 *
 * @param width
 *        The width of the opened YUV file
 * @param height
 *        The heigth of the opened YUV file
 * param y
 *       Destination of the Y component read from the file
 * param u
 *       Destination of the U component read from the file
 * param v
 *       Destination of the V component read from the file
 */
void readYComponent(int width, int height, OUT unsigned char *y, OUT unsigned char *u, OUT unsigned char *v);

#endif // PREESM_READ_YUV_H
