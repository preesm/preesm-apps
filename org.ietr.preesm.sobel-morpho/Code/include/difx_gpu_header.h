// autogenerated header for PiSDF graph: /org.ietr.preesm.sobel-morpho/Algo/difx_gpu.pi
#ifndef PREESM_REFINEMENT_OF_DIFX_GPU
#define PREESM_REFINEMENT_OF_DIFX_GPU

#include <cuComplex.h>
#include <cufft.h>
#include "cuda_runtime_api.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint-gcc.h>
#include <stdlib.h>

#define COMPLEX cuComplex
#define MAKECOMPLEX(x, y)  make_cuFloatComplex(x,y)
#define HALF2FLOAT2(x)    x
#define HALF2FLOAT(x)     x

#define MAX_ANTENNAS 20
#define MAX_ANTENNA_NAME 20
#define MAX_ANTENNA_FILE_NAME 50

__host__ __device__ static __inline__ int
sampIdx(int antenna, int pol, int sample, int stride) {
    const int num_pols = 2;

    return (antenna * num_pols + pol) * stride + sample;
}

__host__ __device__ static __inline__ int
antIdx(int antenna, int pol, int channel, int stride) {
    const int num_pols = 2;

    return (antenna * num_pols + pol) * stride + channel;
}

__host__ __device__ static __inline__ int
accumIdx(int baseline, int product, int channel, int stride) {
    const int num_products = 4;

    return (baseline * num_products + product) * stride + channel;
}

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line) {
    if (code != cudaSuccess) {
        fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
        exit(code);
    }
}

#define CudaCheckError()  __cudaCheckError( __FILE__, __LINE__ )
inline void __cudaCheckError(const char *file, const int line) {
    enum cudaError err = cudaGetLastError();
    if (cudaSuccess != err) {
        fprintf(stderr, "cudaCheckError() failed at %s:%i : %s\n",
                file, line - 1, cudaGetErrorString(err));
        exit(err);
    }
}


#ifdef __cplusplus
extern "C" {
#endif
void init_2bitLevels();

void readData(int NBIT, int NPOL, int CFACTOR, int NFFTS, int NANT, int NCHAN, int *  subintbytes, FILE* *  antStream, int *  numantennas, int8_t *  inputData);

void openAntFiles(int NANT, int *  numantennas, char* *  antFiles, FILE* *  antStream);

void loadCfg(int NANT, int *  nbit, int *  nPol, int *  iscomplex, int *  numchannels, int *  numantennas, double *  lo, double *  bandwidth, int *  numffts, char* *  antFiles, double *  delays, int *  samplegranularity, int *  nbaselines, int *  fftsamples, int *  subintsamples, double *  sampletime, int *  subintbytes);

void calculateDelaysAndPhases(int NANT, int NFFTS, double *  delays, double *  lo, double *  sampletime, int *  fftsamples, int *  numchannels, int *  samplegranularity, float *  rotationPhaseInfo, int *  sampleShifts, float *  fractionalSampleDelays);

void deviceSetup(int *  fftsamples, int *  nPol, int *  numantennas, int *  numffts, int *  nbit, int *  subintsamples, int *  iscomplex, int *  numchannels, int *  subintbytes, cufftHandle *  plan);

#ifdef __cplusplus
}
#endif



__global__ void calculateDelaysAndPhasesGPU(int NANT, int NFFTS, double *  delays, double *  lo, double *  sampletime, int *  fftsamples, int *  numchannels, int *  samplegranularity, float *  rotationPhaseInfo, int *  sampleShifts, int *  fractionalSampleDelays, uint8_t *  packedData, uint8_t *  inputData);

__global__ void unpackData(int NANT, int NFFTS, int CFACTOR, int NCHAN, int NPOL, int NBIT, int SUBINTSAMP, int8_t *  packedData, float *  rotationPhaseInfo, int *  sampleShifts, int *  fftsamples, COMPLEX *  unpackedData);

__global__ void unpackData2(int NANT, int NFFTS, int CFACTOR, int NCHAN, int NPOL, int NBIT, int SUBINTSAMP, int8_t *packedData,
            float *rotationPhaseInfo, int *sampleShifts, int *fftsamples, COMPLEX *unpackedData);

void doFFT(int SUBINTSAMP, int NANT, int NPOL, COMPLEX *  unpackedData, cufftHandle *  plan, COMPLEX *  channelisedData);

__global__ void fracSampleCorrection(int NANT, int NFFTS, int SUBINTSAMP, int NPOL, COMPLEX *  channelisedData, float *  fractionalSampleDelays, int *  numchannels, int *  fftsamples, int *  numffts, int *  subintsamples, COMPLEX *  channelisedData_out);

__global__ void fracSampleCorrection1D(int NANT, int NFFTS, int SUBINTSAMP, int NPOL, COMPLEX *channelisedData,
                                       float *fractionalSampleDelays, int *numchannels, int *fftsamples, int *numffts,
                                       int *subintsamples, COMPLEX *channelisedData_out);

__global__ void CCAH(int NPOL, int SUBINTSAMP, int NANT, int NBASELINE, int NCHAN, int PARAACCUM, COMPLEX *  channelisedData, int *  numantennas, int *  numffts, int *  numchannels, int *  fftsamples, COMPLEX *  baselineData);

void saveVisibilities(int NBASELINE, int NCHAN, int PARAACCUM, COMPLEX *  baselineData, int *  nbaselines, int *  numchannels, double *  bandwidth);

#endif //PREESM_REFINEMENT_OF_DIFX_GPU
