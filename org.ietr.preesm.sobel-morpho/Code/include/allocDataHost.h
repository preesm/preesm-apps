//
// Created by emichel on 01/05/24.
//

#ifndef TESTS_DIFX_ALLOCDATAHOST_H
#define TESTS_DIFX_ALLOCDATAHOST_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void allocDataHost(int *numchannels, int *numffts, int *nbit, int *nPol, int *iscomplex, int *subintbytes);

void freeMem(char ***antenna, char ***antFiles, int *nant, double **antFileOffsets, FILE ***antStream);

#endif //TESTS_DIFX_ALLOCDATAHOST_H
