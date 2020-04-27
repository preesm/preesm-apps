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
#ifndef SOBEL_H
#define SOBEL_H

#include "preesm.h"

/**
 * @brief Compute the x / y gradient of an image using the sobel filter.
 *        see: https://fr.wikipedia.org/wiki/Filtre_de_Sobel
 * @param width   Width the input image.
 * @param height  Height the input image.
 * @param input   Pointer to the input pixel buffer.
 * @param gx      Pointer to the output x gradient computed with the sobel filter.
 * @param gy      Pointer to the output y gradient computed with the sobel filter.
 */
void sobel_raw(int width, int height, IN unsigned char *input, OUT char *gx, OUT char *gy);

/**
 * @brief Apply the sobel filter on an image.
 *        see: https://fr.wikipedia.org/wiki/Filtre_de_Sobel
 * @param width   Width the input image.
 * @param height  Height the input image.
 * @param input   Pointer to the input pixel buffer.
 * @param output  Pointer to the output image.
 */
void sobel(int width, int height, IN unsigned char *input, OUT unsigned char *output);

#endif
