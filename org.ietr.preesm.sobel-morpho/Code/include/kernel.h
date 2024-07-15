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

static long diff = 0L;
static int count = 0;

static cf32 lut2bit[256][4]; /**< Look up table for two bit data, will contain the 4 time samples corresponding to a given byte */

void initLUT2bitReal();

void init_FxKernel(int nant, int *nchan, int *nbit, double *lo, double *bw, struct timespec *starttime,
              char *starttimestring, int *fftchannels, double *sampletime, int *stridesize,
              int *substridesize, int *fractionalLoFreq, int *nbaselines, int numffts, int * iter, int *antIndex);

void init_FxKernelTesting(int nant, int *nchan, int *nbit, double *lo, double *bw, struct timespec *starttime,
                          char *starttimestring, int *fftchannels, double *sampletime, int *stridesize,
                          int *substridesize, int *fractionalLoFreq, int *nbaselines, int numffts, int * iter, int *antIndex,
                          cf32** unpacked);

void unpack(u8 * inputdata, cf32 ** unpacked, int offset, int nbit, int fftchannels);

void getStationDelay(int antenna, int fftindex, double *meandelay, double *a, double *b, double **delays);

void unpackReal2bit(u8 *inputdata, cf32 **unpacked, int offset, int nsamp);

void fringerotate(FxKernel *kernel, cf32 ** unpacked, f64 a, f64 b, int substridesize, int stridesize, double lo, int fftchannels, int fractionalLoFreq);

void dofft(FxKernel *kernel, cf32 ** unpacked, cf32 ** channelised);

void fracSampleCorrect(FxKernel *kernel, cf32 ** channelised, f64 fracdelay, int stridesize, int nchan);

void conjChannels(cf32 ** channelised, cf32 ** conjchannels, int nchan);

void saveVisibilities(int *nbaselines, int *nchan, cf32 *** visibilities, double *bw);

void startTiming(struct timespec *starttime, char *starttimestring);

void saveLog(char *starttimestring, long long *diff_ms);

void endTiming(struct timespec *starttime, struct timespec *endtime, long long *diff_ms);

void processAntennas(FxKernel *kernel, int *nant, int *numffts,
                     int *fftchannels, double *antFileOffsets, double *sampletime, int *antValid, u8 ** inputData,
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

void resetBeforeProcess(int *nbaselines, cf32 *** visibilities, int *nchan, int *baselineCount, int split);

void processBaselinePara(int *nant, int *antValid, cf32 ***channelised, cf32 *** conjchannels, cf32 *** visibilities, int *nchan,
                         int *baselineCount);

void processAntennasAndBaselinePara(int *nant, int numffts, int *fftchannels, double *antFileOffsets,
                                    double *sampletime, u8 ** inputData, cf32 *** unpacked, cf32 ***channelised,
                                    cf32 *** conjchannels, double **delays, int *nbit, int *substridesize, int *stridesize,
                                    int *fractionalLoFreq, double *lo, int *nchan, cf32 *** visibilities, int *baselineCount,
                                    int *iteration, double *bw, cf32 *** visibilities_out, int *baselineCount_out, int split);

void merge(int split, int nbaselines, int numffts, int nant, cf32 ***visibilities, int *baselineCount, int *nChan, int *baselineCount_out, cf32 ***visibilities_out);

void unpackImpl(u8** inputData, int *offset, int *nbit, int *fftchannels, cf32** unpacked);

void unpackImplTesting(u8** inputData, int *offset, int *nbit, int *fftchannels, cf32** unpacked_in, cf32** unpacked);

void fringeRotateImpl(FxKernel *kernel, cf32 ** unpacked, f64 *a, f64 *b, int *substridesize, int *stridesize, double *lo,
                      int *fftchannels, int *fractionalLoFreq, cf32** unpacked_out, FxKernel *kernel_out);

void doFFTImpl(cf32** unpacked, FxKernel * kernel, int *fftchannels, cf32** channelised);

void fracSampleCorrectImpl(FxKernel * kernel, cf32** channelised, double *fractionaldelay, int *stridesize, int *nchan,
                           cf32** channelised_out);

void conjChannelsImpl(cf32** channelised, int *nchan, int *fftchannels, cf32*** conjchannels, cf32*** channelised_out);

void stationDelayAndOffset(int numffts, double ** delays, int *iteration, double *antFileOffsets, double *sampletime, int *fftchannels,
                           int *antIndex, int *antValid, int *offset, double *fracDelay, double *delaya, double* delayb);

void allocKernel(int *substridesize, double *bw, int*stridesize, int* fftchannels, int* numchannels, double *sampletime, FxKernel *kernel);

void processBaselineImpl(int nant, int *antValid, cf32*** channelised, cf32*** conjchannels, int *nchan, cf32 *** visibilities, int *baselineCount_out);

#endif //TESTS_DIFX_KERNEL_H
