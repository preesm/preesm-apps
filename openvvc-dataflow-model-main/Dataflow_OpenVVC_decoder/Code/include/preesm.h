/*
	============================================================================
	Name        : preesm.h
	Author      : kdesnos
	Version     : 1.0
	Copyright   : CECILL-C, IETR, INSA Rennes
	Description : Usefull declarations for all headers used in preesm.
	============================================================================
*/

#ifndef PREESM_H
#define PREESM_H
#include <stdint.h>
#include <ovdmx.h>
#include <slicedec.h>
#include <dec_structures.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "ovdefs.h"
#include "ovdmx.h"
#include "ovframe.h"
#include "ovutils.h"
#include "ovversion.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "overror.h"
#include "ovmem.h"
#include "mempool.h"
#include "mempool_internal.h"
#include "ovunits.h"

#include "nvcl.h"
#include "ovdec.h"
#include "ctudec.h"
#include "decinit.h"
#include "slicedec.h"
#include "dec_structures.h"
#include "ovdec_internal.h"
#include "post_proc.h"
/* FIXME
 * To be removed includes
 */
#include "ovdpb.h"
#include "ovthreads.h"
#include "ovio.h"
#include "ovannexb.h"

#define IN
#define OUT
//#define PREESM_VERBOSE
//#define _PREESM_PAPIFY_MONITOR

//#define PREESM_LOOP_SIZE (1)



typedef unsigned char uchar;
typedef int TCoeff;
typedef int16_t TMatrixCoeff;
typedef struct OVVCHdl{
    OVVCDmx *dmx;
    OVVCDec *dec;
    /* TODO decide whether or not file pointer must be given
       to dmx or not  it is only given to the hadle so when can
       close the file later since we opened it from here*/
    OVIO *io;
}OVVCHdl;
#endif

