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
#ifndef PREESM_SDL_YUV_DISPLAY
#define PREESM_SDL_YUV_DISPLAY

/* === Include(s) === */

#include "yuv-information.h"

/* === Defines for input / output ports === */

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

/* === Define(s) === */

#define NB_DISPLAY 1
#define FPS_MEAN 50
#define ENERGY_MEAN FPS_MEAN
#define FPS_LIMIT 30.f

/* === Function(s) declaration === */

/**
 * @brief Function called to display one of the YUV frame of the window.
 * @remark The size of the displayed frame must correspond to the one declared
 *         when initializing the display.
 * @remark This function add the average (see FPS_MEAN define) Frame per seconds value on top of the video.
 * @param id  Identifier of the display on which the frame should be displayed.
 * @param y   Pointer to the Y component of the frame to display.
 * @param u   Pointer to the U component of the frame to display.
 * @param v   Pointer to the V component of the frame to display.
 */
void yuvDisplay(int id, IN unsigned char *y, IN unsigned char *u, IN unsigned char *v);

/**
 * @brief Function called to display one of the YUV frame of the window.
 *        This function is similar to @refitem yuvDisplay but adds the number of slice used for computation.
 * @remark The size of the displayed frame must correspond to the one declared
 *         when initializing the display.
 * @remark This function add the average (see FPS_MEAN define) Frame per seconds value on top of the video.
 * @param id      Identifier of the display on which the frame should be displayed.
 * @param nbSlice
 * @param y       Pointer to the Y component of the frame to display.
 * @param u       Pointer to the U component of the frame to display.
 * @param v       Pointer to the V component of the frame to display.
 */
void yuvDisplayWithNbSlice(int id, int nbSlice, IN unsigned char *y, IN unsigned char *u, IN unsigned char *v);

/**
* Initialize a new display with a parameterizable resolution and open a
* display window (if not already opened).
* The resolution of the new display must be compatible with the one
* defined with the pre-processor variables.
* A single window can contain several display. In such case, the total width
* of the displays must not exceed DISPLAY_W and the maximum height of a
* display must not exceed DISPLAY_H. Displays will be placed side by side
* in ascending id. All displays must have the same width in the current
* implementation.
*
* @param id
*        The ID of the initialized display.
* @param width
*        the width of the initialized display
* @param height
*        the height of the initialized display
*/
void yuvDisplayInit(int id, int width, int height, int displayWidth, int displayHeight);

/**
 * @brief Clean up everything related to SDL.
 */
void yuvFinalize();

#endif // PREESM_SDL_YUV_DISPLAY
