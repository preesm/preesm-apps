/*
	============================================================================
	Name        : preesm.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C, IETR, INSA Rennes
	Description : Usefull declarations for all headers used in preesm.
	============================================================================
*/

#ifndef MPPA_PREESM_H
#define MPPA_PREESM_H

// The code will only run one time
#define PREESM_LOOP_SIZE 1

// Use all CCs in clusters
#undef PREESM_NB_CORES_CC
#define PREESM_NB_CORES_CC 16

#define IN
#define OUT

typedef unsigned char uchar;

#endif
