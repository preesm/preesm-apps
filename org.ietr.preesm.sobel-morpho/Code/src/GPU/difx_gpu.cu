//
// Created by emichel on 05/07/24.
//

#include "difx_gpu_header.h"

__constant__ float kLevels_2bit[4];

void init_2bitLevels() {
    static const float HiMag = 3.3359;  // Optimal value
    const float lut4level[4] = {-HiMag, -1.0, 1.0, HiMag};
    gpuErrchk(cudaMemcpyToSymbol(kLevels_2bit, lut4level, 4 * sizeof(float), 0, cudaMemcpyHostToDevice));
}

// Rotate inplace a complex number by theta (radians)
__device__ static __inline__ void cuRotatePhase(COMPLEX &x, float theta) {
    float cs, sn;
    sincosf(theta, &sn, &cs);

#ifdef USEHALF
    float2 y = __half22float2(x);
  float px = y.x * cs - y.y * sn;
  float py = y.x * sn + y.y * cs;
#else
    float px = x.x * cs - x.y * sn;
    float py = x.x * sn + x.y * cs;
#endif
    x = MAKECOMPLEX(px, py);
    return;
}

// Rotate a complex number by theta (radians)
__device__ static __inline__ void cuRotatePhase3(float x, COMPLEX &y, float sinA, float cosA) {
    y = MAKECOMPLEX(x * cosA, x * sinA);
    return;
}

// Rotate a complex number by theta (radians)
__device__ static __inline__ void cuRotatePhase4(cuComplex x, COMPLEX &y, float sinA, float cosA) {
    y = MAKECOMPLEX(x.x * cosA - x.y * sinA, x.x * sinA + x.y * cosA);
    return;
}


void loadCfg(int NANT, int *nbit, int *nPol, int *iscomplex, int *numchannels, int *numantennas, double *lo,
             double *bandwidth, int *numffts, char **antFiles, double *delays, int *samplegranularity,
             int *nbaselines, int *fftsamples, int *subintsamples, double *sampletime, int *subintbytes) {
    char *configFileName = "./dat/test4_tested.conf";
    FILE *fconfig = fopen(configFileName, "r");

    for (int i = 0; i < MAX_ANTENNAS; i++) {
        antFiles[i] = (char *)malloc(MAX_ANTENNA_FILE_NAME * sizeof(char));
    }

    if (fconfig == NULL) {
        printf("Error Opening File %s\n", configFileName);
        return;
    }

    char line[1024];
    int antToRead = 0;
    int iant = 0;

    // Set some defaults
    *nPol = 2;
    *iscomplex = 0;
    *nbit = 2;

    // Read the config file
    while (fgets(line, 1024, fconfig)) {
        char keyword[1024];
        char *token = strtok(line, " \n");
        if (!token) {
            fprintf(stderr, "Error: Could not parse \"%s\"\n", line);
            exit(1);
        }
        strcpy(keyword, token);
        if (antToRead) {
            char thisfile[1024];
            sscanf(keyword, "%s", thisfile);
            //strcpy(antenna[iant], keyword);
            token = strtok(NULL, " \n");
            strcpy(antFiles[iant], token);
            token = strtok(NULL, " \n");
            for (int i = 0; i < 3; i++) {
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for antenna %d\n", iant);
                    exit(1);
                }
                sscanf(token, "%lf", &((delays)[4 * iant + i])); // TODO CHECK
                token = strtok(NULL, " \n");
            }
            if (token == NULL) {
                fprintf(stderr, "Error: Insufficient data for antenna %d\n", iant);
                exit(1);
            }
            sscanf(token, "%lf", &((delays)[4 * iant + 3])); // Error checking needed
            iant++;
            antToRead--;
        } else {
            if (strcasecmp(keyword, "COMPLEX") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for COMPLEX\n");
                    exit(1);
                }
                sscanf(token, "%d", iscomplex); // Should error check
            } else if (strcasecmp(keyword, "NBIT") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for NBIT\n");
                    exit(1);
                }
                sscanf(token, "%d", nbit); // Should error check
            } else if (strcasecmp(keyword, "NPOL") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for NPOL\n");
                    exit(1);
                }
                sscanf(token, "%d", nPol); // Should error check
            } else if (strcasecmp(keyword, "NCHAN") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for NCHAN\n");
                    exit(1);
                }
                sscanf(token, "%d", numchannels); // Should error check
            } else if (strcasecmp(keyword, "LO") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for LO\n");
                    exit(1);
                }
                sscanf(token, "%lf", lo); // Should error check
            } else if (strcasecmp(keyword, "BANDWIDTH") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for BANDWIDTH\n");
                    exit(1);
                }
                sscanf(token, "%lf", bandwidth); // Should error check
            } else if (strcasecmp(keyword, "NUMFFTS") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for NUMFFTS\n");
                    exit(1);
                }
                sscanf(token, "%d", numffts); // Should error check
            } else if (strcasecmp(keyword, "NANT") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for NANT\n");
                    exit(1);
                }
                sscanf(token, "%d", numantennas); // Should error check
                antToRead = *numantennas;
                iant = 0;
            } else {
                fprintf(stderr, "Error: Unknown keyword \"%s\"\n", keyword);
            }
        }
    }
    fclose(fconfig);

    // Check that the number of FFTs is a valid number
    if (*numffts % 8) {
        printf("Error: numffts must be divisible by 8");
        exit(1);
    }

//    int *samplegranularity,
//    int *nbaselines, int *fftsamples, int *subintsamples, double *sampletime, int *subintbytes) {

    *samplegranularity = 8 / (*nbit * *nPol);
    if (*samplegranularity < 1) {
        *samplegranularity = 1;
    }
    *nbaselines = *numantennas * (*numantennas - 1) / 2;

    int cfactor;
    if (*iscomplex) {
        cfactor = 1;
    } else {
        cfactor = 2; // If real data FFT size twice size of number of frequecy channels
    }

    *fftsamples = *numchannels * cfactor;
    *subintsamples = *numffts * *fftsamples;  // Number of time samples - need to factor # channels (pols) also
    printf("Subintsamples = %d\n", *subintsamples);
    *sampletime = 1.0 / *bandwidth;

    if (!(*iscomplex)) *sampletime /= 2.0;

    *subintbytes = *numchannels * cfactor * (*numffts + 1) * *nbit / 8 * *nPol;
}

void
deviceSetup(int *fftsamples, int *nPol, int *numantennas, int *numffts, int *nbit, int *subintsamples, int *iscomplex,
            int *numchannels, int *subintbytes, cufftHandle *plan) {

    if (cufftPlan1d(plan, *fftsamples, CUFFT_C2C, *nPol * *numantennas * *numffts) != CUFFT_SUCCESS) {
        printf("CUFFT error: Plan creation failed");
        exit(0);
    }
}


void readData(int NBIT, int NPOL, int CFACTOR, int NFFTS, int NANT, int NCHAN, int *subintbytes, FILE **antStream,
              int *numantennas, int8_t *inputData) {

    printf("Size subintbytes %d \n", *subintbytes);

    printf("Size antStream : %d \n", *numantennas);
    for (int i = 0; i < *numantennas; i++) {
        size_t bytes_read = fread(&inputData[i * *subintbytes], 1, *subintbytes, antStream[i]);
        if (bytes_read != *subintbytes) {
            if (feof(antStream[i])) {
                printf("2"); // End of file reached
            } else if (ferror(antStream[i])) {
                perror("Error: Problem reading data");
                printf("1"); // Error reading file
            }
        }
    }
    printf("Read Data Success \n"); // Successful read
}

void openAntFiles(int NANT, int *numantennas, char **antFiles, FILE **antStream) {
    for (int i = 0; i < NANT; i++) {
        antStream[i] = fopen(antFiles[i], "rb");
        if (antStream[i] == NULL) {
            fprintf(stderr, "Problem with file %s - does it exist?\n", antFiles[i]);
        }
    }
}

__global__ void
calculateDelaysAndPhasesGPU(int NANT, int NFFTS, double *delays, double *lo, double *sampletime, int *fftsamples,
                            int *numchannels, int *samplegranularity, float *rotationPhaseInfo, int *sampleShifts,
                            int *fractionalSampleDelays, uint8_t *packedData, uint8_t *inputData) {
    size_t ifft = threadIdx.x + blockIdx.x * blockDim.x;
    size_t iant = blockIdx.y;
    int numffts = blockDim.x * gridDim.x;
    double meandelay, deltadelay, netdelaysamples_f, startphase;
    double d0, d1, d2, a, b;
    double *interpolator = &(delays[iant * 4]);
    double filestartoffset = delays[iant * 4 + 3];
    float fractionaldelay;
    int netdelaysamples;

    // evaluate the delay for the given FFT of the given antenna

    // calculate values at the beginning, middle, and end of this FFT
    d0 = interpolator[0] * ifft * ifft + interpolator[1] * ifft + interpolator[2];
    d1 = interpolator[0] * (ifft + 0.5) * (ifft + 0.5) + interpolator[1] * (ifft + 0.5) + interpolator[2];
    d2 = interpolator[0] * (ifft + 1.0) * (ifft + 1.0) + interpolator[1] * (ifft + 1.0) + interpolator[2];

    // use these to calculate a linear interpolator across the FFT, as well as a mean value
    a = d2 - d0; //this is the delay gradient across this FFT
    b = d0 + (d1 - (a * 0.5 + d0)) / 3.0; //this is the delay at the start of the FFT
    meandelay = a * 0.5 + b; //this is the delay in the middle of the FFT
    deltadelay = a / *fftsamples; // this is the change in delay per sample across this FFT window

    netdelaysamples_f = (meandelay - filestartoffset) / *sampletime;
    netdelaysamples = __double2int_rn(netdelaysamples_f / *samplegranularity) * *samplegranularity;

    // Save the integer number of sample shifts
    sampleShifts[iant * numffts + ifft] = netdelaysamples;

    // Save the fractional delay
    fractionaldelay = (float) (-(netdelaysamples_f - netdelaysamples) * 2 * M_PI /
                               *fftsamples);  // radians per FFT channel
    fractionalSampleDelays[iant * numffts + ifft] = fractionaldelay;

    // set the fringe rotation phase for the first sample of a given FFT of a given antenna
    startphase = b * *lo;
    rotationPhaseInfo[iant * numffts * 2 + ifft * 2] = (float) (startphase - int(startphase)) * 2 * M_PI;
    rotationPhaseInfo[iant * numffts * 2 + ifft * 2 + 1] = (float) (deltadelay * *lo) * 2 * M_PI;
}

__global__ void
unpackData(int NANT, int NFFTS, int CFACTOR, int NCHAN, int NPOL, int NBIT, int SUBINTSAMP, int8_t *packedData,
           float *rotationPhaseInfo, int *sampleShifts, int *fftsamples, COMPLEX *unpackedData) {
    if(threadIdx.x < *fftsamples/2 && blockIdx.x < NFFTS) {
        for (int i = 0; i < NANT; i++) {
            // static const float HiMag = 3.3359;  // Optimal value
            // const float levels_2bit[4] = {-HiMag, -1.0, 1.0, HiMag};
            const size_t isample = 2 * threadIdx.x;
            const size_t ifft = blockIdx.x;
            const size_t osample = isample + ifft * *fftsamples;
            int subintsamples = *fftsamples * NFFTS;

            // Try to Fix
            size_t idx = ((osample - sampleShifts[ifft + i * NFFTS]) /
                          2); // FIXME: may lead to memory access outside src[] bounds, see with 'cuda-memcheck ./benchmark_gxkernel'
            // And of try to fix

            int8_t src_i = packedData[idx + i * (NCHAN * CFACTOR * (NFFTS + 1) * NBIT / 8 *
                                                 NPOL)]; // Here I am just loading src into local memory to
            // reduce the number of reads from global memory

            // I have just changed the order of the writes made to dest
            // In theory this should reduce the number of write operations made
            // I have also implemented the use of constant memory for the levels_2bit
            // array

            float samp0 = kLevels_2bit[src_i & 0x3];
            float samp1 = kLevels_2bit[(src_i >> 4) & 0x3];
            float samp2 = kLevels_2bit[(src_i >> 2) & 0x3];
            float samp3 = kLevels_2bit[(src_i >> 6) & 0x3];

            // phase and slope for this FFT
            float p0 = rotationPhaseInfo[ifft * 2 + i * NFFTS * 2];
            float p1 = rotationPhaseInfo[ifft * 2 + 1 + i * NFFTS * 2];
            float theta0 = -p0 - isample * p1;
            float theta1 = -p0 - (isample + 1) * p1;

            float sinT0, cosT0, sinT1, cosT1;
            sincosf(theta0, &sinT0, &cosT0);
            sincosf(theta1, &sinT1, &cosT1);
            cuRotatePhase3(samp0, unpackedData[(osample + 2 * i * SUBINTSAMP)], sinT0, cosT0);
            cuRotatePhase3(samp1, unpackedData[(osample + 1 + 2 * i * SUBINTSAMP)], sinT1, cosT1);
            cuRotatePhase3(samp2, unpackedData[(subintsamples + osample + 2 * i * SUBINTSAMP)], sinT0, cosT0);
            cuRotatePhase3(samp3, unpackedData[(subintsamples + osample + 1 + 2 * i * SUBINTSAMP)], sinT1, cosT1);
        }
    }
}

void
doFFT(int SUBINTSAMP, int NANT, int NPOL, COMPLEX *unpackedData, cufftHandle *plan, COMPLEX *channelisedData) {
    if (cufftExecC2C(*plan, unpackedData, channelisedData, CUFFT_FORWARD) != CUFFT_SUCCESS) {
        printf("CUFFT error: ExecC2C Forward failed");
    }
}

__global__ void fracSampleCorrection_old(int NANT, int NFFTS, int SUBINTSAMP, int NPOL, COMPLEX *channelisedData,
                                     float *fractionalSampleDelays, int *numchannels, int *fftsamples, int *numffts,
                                     int *subintsamples, COMPLEX *channelisedData_out) {
    size_t ichan = threadIdx.x + blockIdx.x * blockDim.x;
    size_t ifft = blockIdx.y;
    size_t iant = blockIdx.z;

    // phase and slope for this FFT
    float dslope = fractionalSampleDelays[iant * *numffts + ifft];
    float theta = ichan * dslope;
    cuRotatePhase(channelisedData[sampIdx(iant, 0, ichan + ifft * *fftsamples, *subintsamples)], theta);
    cuRotatePhase(channelisedData[sampIdx(iant, 1, ichan + ifft * *fftsamples, *subintsamples)], theta);

    memcpy(&channelisedData_out[sampIdx(iant, 0, ichan + ifft * *fftsamples, *subintsamples)], &channelisedData[sampIdx(iant, 0, ichan + ifft * *fftsamples, *subintsamples)], sizeof(cuComplex));
    memcpy(&channelisedData_out[sampIdx(iant, 1, ichan + ifft * *fftsamples, *subintsamples)], &channelisedData[sampIdx(iant, 1, ichan + ifft * *fftsamples, *subintsamples)], sizeof(cuComplex));
}

__global__ void fracSampleCorrection(int NANT, int NFFTS, int SUBINTSAMP, int NPOL, COMPLEX *channelisedData,
                                     float *fractionalSampleDelays, int *numchannels, int *fftsamples, int *numffts,
                                     int *subintsamples, COMPLEX *channelisedData_out) {
    if(threadIdx.x < *numchannels && blockIdx.x < NFFTS*NANT) { // NUMCHAN et NUMFFTS*NUMANTENNAS
        size_t ichan = threadIdx.x;
        size_t combinedIndex = blockIdx.x;
        size_t ifft = combinedIndex % *numffts;
        size_t iant = combinedIndex / *numffts;

        // phase and slope for this FFT
        float dslope = fractionalSampleDelays[iant * *numffts + ifft];
        float theta = ichan * dslope;
        cuRotatePhase(channelisedData[sampIdx(iant, 0, ichan + ifft * *fftsamples, SUBINTSAMP)], theta);
        cuRotatePhase(channelisedData[sampIdx(iant, 1, ichan + ifft * *fftsamples, SUBINTSAMP)], theta);

        memcpy(&channelisedData_out[sampIdx(iant, 0, ichan + ifft * *fftsamples, *subintsamples)], &channelisedData[sampIdx(iant, 0, ichan + ifft * *fftsamples, *subintsamples)], sizeof(cuComplex));
        memcpy(&channelisedData_out[sampIdx(iant, 1, ichan + ifft * *fftsamples, *subintsamples)], &channelisedData[sampIdx(iant, 1, ichan + ifft * *fftsamples, *subintsamples)], sizeof(cuComplex));
    }
}


__global__ void
CCAH(int NPOL, int SUBINTSAMP, int NANT, int NBASELINE, int NCHAN, int PARAACCUM, COMPLEX *channelisedData,
     int *numantennas, int *numffts, int *numchannels, int *fftsamples, COMPLEX *baselineData) {
    if(blockIdx.x < (1+(NCHAN-1)/128)*NANT*NANT && threadIdx.x < 128) {
        int linear_idx = blockIdx.x * 128 + threadIdx.x;
        // Total number of pairs of antennas
        int total_pairs = NANT * (NANT - 1) / 2;
        int total_elements = total_pairs * NCHAN;

        if (linear_idx >= total_elements) return;

        // Calculate the channel index
        int t = linear_idx % NCHAN;

        // Calculate the pair index
        int pair_idx = linear_idx / NCHAN;

        // Calculate ant1 and ant2 from pair_idx
        int ant1 = 0;
        int ant2 = 0;
        int offset = 0;
        for (ant1 = 0; ant1 < NANT - 1; ++ant1) {
            int remaining_pairs = NANT - ant1 - 1;
            if (pair_idx < offset + remaining_pairs) {
                ant2 = ant1 + 1 + (pair_idx - offset);
                break;
            }
            offset += remaining_pairs;
        }

        // Index into output vector blocks: = (j-i-1) + n-1 + ... + n-i
        int b = ant1 * NANT - ant1 * (ant1 + 1) / 2 - ant1 + ant2 - 1;

        int s = *numffts * *fftsamples;

        const COMPLEX *iv = channelisedData + ant1 * s * 2 + t;
        const COMPLEX *jv = channelisedData + ant2 * s * 2 + t;

        COMPLEX u1 = iv[0];
        COMPLEX v1 = jv[0];
        COMPLEX u2 = iv[s];
        COMPLEX v2 = jv[s];
        cuComplex a1;
        cuComplex a2;
        cuComplex a3;
        cuComplex a4;
        a1.x = (u1.x * v1.x + u1.y * v1.y);
        a1.y = u1.y * v1.x - u1.x * v1.y;
        a2.x = u1.x * v2.x + u1.y * v2.y;
        a2.y = u1.y * v2.x - u1.x * v2.y;
        a3.x = u2.x * v1.x + u2.y * v1.y;
        a3.y = u2.y * v1.x - u2.x * v1.y;
        a4.x = u2.x * v2.x + u2.y * v2.y;
        a4.y = u2.y * v2.x - u2.x * v2.y;

        for (int k = *fftsamples; k < s; k += *fftsamples) {
            u1 = iv[k];
            v1 = jv[k];
            u2 = iv[k + s];
            v2 = jv[k + s];

            a1.x += HALF2FLOAT(u1.x * v1.x + u1.y * v1.y);
            a1.y += HALF2FLOAT(u1.y * v1.x - u1.x * v1.y);
            a2.x += HALF2FLOAT(u1.x * v2.x + u1.y * v2.y);
            a2.y += HALF2FLOAT(u1.y * v2.x - u1.x * v2.y);
            a3.x += HALF2FLOAT(u2.x * v1.x + u2.y * v1.y);
            a3.y += HALF2FLOAT(u2.y * v1.x - u2.x * v1.y);
            a4.x += HALF2FLOAT(u2.x * v2.x + u2.y * v2.y);
            a4.y += HALF2FLOAT(u2.y * v2.x - u2.x * v2.y);
        }

        a1.x /= *numffts;
        a1.y /= *numffts;
        a2.x /= *numffts;
        a2.y /= *numffts;
        a3.x /= *numffts;
        a3.y /= *numffts;
        a4.x /= *numffts;
        a4.y /= *numffts;
        baselineData[4 * b * NCHAN + t] = a1;
        baselineData[(4 * b + 1) * NCHAN + t] = a2;
        baselineData[(4 * b + 2) * NCHAN + t] = a3;
        baselineData[(4 * b + 3) * NCHAN + t] = a4;
    }
}

// Function to compute the phase angle of a cuComplex number
float cuCargf(cuComplex z) {
    return atan2f(cuCimagf(z), cuCrealf(z));
}

void
saveVisibilities(int NBASELINE, int NCHAN, int PARAACCUM, COMPLEX *baselineData, int *nbaselines, int *numchannels,
                 double *bandwidth) {
    COMPLEX **vis;
    FILE *fvis = fopen("vis.out", "w");
    if (fvis == NULL) {
        fprintf(stderr, "Error opening file %s\n", "vis.out");
        exit(1);
    }

    // Copy final visibilities back to CPU
    vis = (cuComplex **) malloc(*nbaselines * 4 * sizeof(cuComplex *));
    for (int i = 0; i < *nbaselines * 4; i++) {
        vis[i] = (cuComplex *) malloc(NCHAN * sizeof(cuComplex));
        gpuErrchk(
                cudaMemcpy(vis[i], &baselineData[i * *numchannels], NCHAN * sizeof(cuComplex), cudaMemcpyDeviceToHost));
    }

    printf("Test : %e \n", vis[0][0].x);
    printf("Test : %e \n", vis[0][0].y);

    for (int c = 0; c < NCHAN; c++) {
        fprintf(fvis, "%5d %11.6f", c, (c + 0.5) / NCHAN * *bandwidth / 1e6);
        for (int i = 0; i < *nbaselines * 4; i++) {
            fprintf(fvis, " %11.6f %11.6f %11.6f %10.6f",
                    cuCrealf(vis[i][c]), cuCimagf(vis[i][c]),
                    cuCabsf(vis[i][c]), cuCargf(vis[i][c]));
        }
        fprintf(fvis, "\n");
    }
    fclose(fvis);

    for (int i = 0; i < *nbaselines * 4; i++) {
        free(vis[i]);
    }
    free(vis);
}

void calculateDelaysAndPhases(int NANT, int NFFTS, double *delays, double *lo, double *sampletime, int *fftsamples,
                            int *numchannels, int *samplegranularity, float *rotationPhaseInfo, int *sampleShifts,
                            float *fractionalSampleDelays) {
    for (size_t ifft = 0; ifft < NFFTS; ++ifft) {
        for (size_t iant = 0; iant < NANT; ++iant) {
            double meandelay, deltadelay, netdelaysamples_f, startphase;
            double d0, d1, d2, a, b;
            double *interpolator = &(delays[iant * 4]);
            double filestartoffset = delays[iant * 4 + 3];
            float fractionaldelay;
            int netdelaysamples;

            // Calculate values at the beginning, middle, and end of this FFT
            d0 = interpolator[0] * ifft * ifft + interpolator[1] * ifft + interpolator[2];
            d1 = interpolator[0] * (ifft + 0.5) * (ifft + 0.5) + interpolator[1] * (ifft + 0.5) + interpolator[2];
            d2 = interpolator[0] * (ifft + 1.0) * (ifft + 1.0) + interpolator[1] * (ifft + 1.0) + interpolator[2];

            // Use these to calculate a linear interpolator across the FFT, as well as a mean value
            a = d2 - d0; // This is the delay gradient across this FFT
            b = d0 + (d1 - (a * 0.5 + d0)) / 3.0; // This is the delay at the start of the FFT
            meandelay = a * 0.5 + b; // This is the delay in the middle of the FFT
            deltadelay = a / *fftsamples; // This is the change in delay per sample across this FFT window

            netdelaysamples_f = (meandelay - filestartoffset) / *sampletime;
            netdelaysamples = (int) (netdelaysamples_f / *samplegranularity) * *samplegranularity;

            // Save the integer number of sample shifts
            sampleShifts[iant * NFFTS + ifft] = netdelaysamples;

            // Save the fractional delay
            fractionaldelay = (float) (-(netdelaysamples_f - netdelaysamples) * 2 * M_PI /
                                       *fftsamples);  // Radians per FFT channel
            fractionalSampleDelays[iant * NFFTS + ifft] = fractionaldelay;

            // Set the fringe rotation phase for the first sample of a given FFT of a given antenna
            startphase = b * *lo;
            rotationPhaseInfo[iant * NFFTS * 2 + ifft * 2] = (float) (startphase - (int) startphase) * 2 * M_PI;
            rotationPhaseInfo[iant * NFFTS * 2 + ifft * 2 + 1] = (float) (deltadelay * *lo) * 2 * M_PI;
        }
    }
}

__global__ void channCorrect(int SUBINTSAMP, int NANT, int NPOL, COMPLEX *  chann_fft, COMPLEX *  chann_frac, COMPLEX *  chann_out) {
        int global_index = blockIdx.x * blockDim.x + threadIdx.x;
        if (global_index < 15728640) {
            if (chann_frac[global_index].x == 0.0f || chann_frac[global_index].y == 0.0f) {
                //memcpy(&correct_out[global_index], &fft_out[global_index], sizeof(cuComplex));
                chann_out[global_index] = chann_fft[global_index];
            } else {
                //memcpy(&correct_out[global_index], &frac_out[global_index], sizeof(cuComplex));
                chann_out[global_index] = chann_frac[global_index];
            }
        }
}