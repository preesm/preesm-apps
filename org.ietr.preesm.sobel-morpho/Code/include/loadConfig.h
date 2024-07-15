#ifndef GCORR_COMMON_H
#define GCORR_COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "preesm.h"

#define MAX_ANTENNAS 20
#define MAX_ANTENNA_NAME 20
#define MAX_ANTENNA_FILE_NAME 50

#define CONFIG_FILE_PATH "./dat/test4.conf"

/**
 * Parses the config file and sets a bunch of necessary parameters
 * @param configfilename the data array to be allocated
 * @param nbit the number of bits per sample (set in this function)
 * @param nPol the number of polarisations in the data (1 or 2, set in this function)
 * @param iscomplex whether the data is complex (true) or real (false).  Set in this function.
 * @param nchan the number of channels to be produced in the correlation (set in this function).
 * @param nant the number of antennas (set in this function).
 * @param lo the local oscillator frequency in Hz (set in this function).
 * @param bandwidth the bandwidth in Hz (set in this function).
 * @param numffts the number of FFTs that will be processed in one subintegration (set in this function)
 * @param antenna the name of each antenna (set in this function)
 * @param antFiles the filename for each antenna's raw data (set in this function)
 * @param delays the polynomial delay for each antenna: 2nd order, in seconds, time unit in FFT intervals, +ve delay value goes in the opposite direction to wallclock time [same sense as DiFX delays].  (set in this function)
 * @param antfileoffsets the offset of the start time of each antenna's file from the nominal start of this subintegration (in seconds, set in this function).
 */
void parseConfig(OUT int *nBit, OUT int *nPol, OUT int *isComplex, OUT int *nChan, OUT int *nant, OUT double *lo, OUT double *bandwidth, OUT int *numFFT, OUT char** antenna, OUT char** antFiles, OUT double **delays, OUT double *antFileOffsets);

/**
 * Reads the config file and outputs everything in console
 * @param configfilename the data array to be allocated
 * @param nbit the number of bits per sample (set in this function)
 * @param nPol the number of polarisations in the data (1 or 2, set in this function)
 * @param iscomplex whether the data is complex (true) or real (false).  Set in this function.
 * @param nchan the number of channels to be produced in the correlation (set in this function).
 * @param nant the number of antennas (set in this function).
 * @param lo the local oscillator frequency in Hz (set in this function).
 * @param bandwidth the bandwidth in Hz (set in this function).
 * @param numffts the number of FFTs that will be processed in one subintegration (set in this function)
 * @param antenna the name of each antenna (set in this function)
 * @param antFiles the filename for each antenna's raw data (set in this function)
 * @param delays the polynomial delay for each antenna: 2nd order, in seconds, time unit in FFT intervals, +ve delay value goes in the opposite direction to wallclock time [same sense as DiFX delays].  (set in this function)
 * @param antfileoffsets the offset of the start time of each antenna's file from the nominal start of this subintegration (in seconds, set in this function).
 */
void readConfig(IN int *nbit, IN int *nPol, IN int *iscomplex, IN int *nchan, IN int *nant, IN double *lo, IN double *bandwidth, IN int *numffts, IN char **antenna, IN char **antFiles, IN double **delays, IN double *antfileoffsets);

void initMem(char ** antenna, char ** antFiles, double ** delays);


/**
 * Allocates the space for the raw (packed, quantised) voltage data.
 * @param data the data array to be allocated
 * @param numantenna the number of antennas
 * @param numchannels the number of channels to be produced in the correlation
 * @param numffts the number of FFTs that will be processed in one subintegration
 * @param nbit the number of bits per sample
 * @param nPol the number of polarisations
 * @param iscomplex true for complex data, false for real data
 * @param subintbytes the number of bytes allocated in total (set in this function)
 */
//void allocDataHost(uint8_t ***data, int numantenna, int numchannels, int numffts, int nbit, int nPol, bool iscomplex, int &subintbytes);

/**
 * Read data from file into CPU memory
 * @param bytestoread the number of bytes to read in from the file for each antenna.
 * @param antStream the file streams for each antenna
 * @param inputdata the buffers to fill with data from the file
 * @return 0 for success, positive for an error.
 */
//int readdata(int bytestoread, vector<std::ifstream*> &antStream, uint8_t **inputdata);

#endif

