#ifndef BP1D_H_
#define BP1D_H_

#include <stdint.h>
#include "bp1d_node.h"

void BP_ComputeFi(IN phib_type *phiB, OUT fi_type *Fi, unsigned int width, unsigned ndisp, int Phi0);
void BP_Compute_Energy(IN phib_type *phiB, IN fi_type *Fi, unsigned char *disparity_map, unsigned int width, unsigned int ndisp, int Phi0);

#endif
