//
// Created by emichel on 01/05/24.
//

#ifndef TESTS_DIFX_KERNEL_H
#define TESTS_DIFX_KERNEL_H

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>
#include <ipps.h>
#include <ippvm.h>
#include <ippcore.h>
#include "vectordefs.h"
#include <math.h>

// Structure definition
typedef struct {
    // internal arrays
    f64 * subtoff;
    f64 * subtval;
    f64 * subxoff;
    f64 * subxval;
    f64 * subphase;
    f32 * subarg;
    f32 * subsin;
    f32 * subcos;

    f64 * steptoff;
    f64 * steptval;
    f64 * stepxoff;
    f64 * stepxval;
    f64 * stepphase;
    f32 * steparg;
    f32 * stepsin;
    f32 * stepcos;
    cf32 * stepcplx;
    cf32 * complexrotator;

    f32 * subfracsamparg;
    f32 * subfracsampsin;
    f32 * subfracsampcos;
    f32 * subchannelfreqs;

    f32 * stepfracsamparg;
    f32 * stepfracsampsin;
    f32 * stepfracsampcos;
    cf32 * stepfracsampcplx;
    f32 * stepchannelfreqs;
    cf32 * fracsamprotator;

    // FFTs
    u8 * fftbuffer;
    vecFFTSpecC_cf32 * pFFTSpecC;
} FxKernel;

static cf32 lut2bit[256][4]; /**< Look up table for two bit data, will contain the 4 time samples corresponding to a given byte */

void initLUT2bitReal();

void init_FxKernel(int *nant, int *nchan, int *nbit, double *lo, double *bw, struct timespec *starttime,
              char *starttimestring, int *fftchannels, double *sampletime, int *stridesize,
              int *substridesize, int *fractionalLoFreq, cf32 ***unpacked, cf32 ***channelised, cf32 ***conjchannels,
              cf32 ***visibilities, int *nbaselines, int *baselineCount);

void unpack(u8 * inputdata, cf32 ** unpacked, int offset, int nbit, int fftchannels);

void getStationDelay(int antenna, int fftindex, double *meandelay, double *a, double *b, double **delays);

void unpackReal2bit(u8 *inputdata, cf32 **unpacked, int offset, int nsamp);

void fringerotate(FxKernel *kernel, cf32 ** unpacked, f64 a, f64 b, int substridesize, int stridesize, double lo, int fftchannels, double fractionalLoFreq);

void dofft(FxKernel *kernel, cf32 ** unpacked, cf32 ** channelised);

void fracSampleCorrect(FxKernel *kernel, cf32 ** channelised, f64 fracdelay, int stridesize, int nchan);

void conjChannels(cf32 ** channelised, cf32 ** conjchannels, int nchan);

void saveVisibilities(int *nbaselines, int *nchan, cf32 *** visibilities, double *bw);

void startTiming(struct timespec *starttime, char *starttimestring);

void saveLog(long long *diff_ms, char *starttimestring);

void endTiming(struct timespec *starttime, long long *diff_ms, struct timespec *endtime);

void processAntennas(FxKernel *kernel, int *nant, int *numffts,
                     int *fftchannels, double *antFileOffsets, double *sampletime, int *antValid, u8 ** inputData, cf32 *** unpacked,
                     cf32 ***channelised, cf32 *** conjchannels, double **delays, int *nbit, int *substridesize, int *stridesize,
                     int *fractionalLoFreq, double *lo, int *nchan);

void processNormalize(int i, int *baselineCount,  cf32 *** visibilities, int *nchan, cf32 *** visibilities_out, struct timespec *endtime);

void processBaseline(int *nant, int *antValid, cf32 ***channelised, cf32 *** conjchannels, cf32 *** visibilities, int *nchan,
                     int *baselineCount);

void processAntennasAndBaseline(int *nant, int numffts, int *fftchannels, double *antFileOffsets,
                                double *sampletime, u8 ** inputData, cf32 *** unpacked, cf32 ***channelised,
                                cf32 *** conjchannels, double **delays, int *nbit, int *substridesize, int *stridesize,
                                int *fractionalLoFreq, double *lo, int *nchan, cf32 *** visibilities, int *baselineCount, double *bw,
                                cf32 *** visibilities_out, int *baselineCount_out);

void resetBeforeProcess(int *nbaselines, cf32 *** visibilities, int *nchan, int *baselineCount);

#endif //TESTS_DIFX_KERNEL_H
