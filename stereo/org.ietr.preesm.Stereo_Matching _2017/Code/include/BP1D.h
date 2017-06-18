#ifndef BP1D_H_
#define BP1D_H_

#include <stdint.h>
#include "costMatrix.h"


void bp1d_selection(const struct dispMatrix_size* size, const uint8_t* costIn, uint8_t* out, int phi0);


#endif
