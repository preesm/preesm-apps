//
// Created by emichel on 29/04/24.
//

#import "loadConfig.h"

void parseConfig(int *nBit,  int *nPol,  int *isComplex,  int *nChan,  int *nant,
                  double *lo,  double *bandwidth,  int *numFFT,  char** antenna,  char** antFiles,  double **delays,  double *antFileOffsets) {
    FILE *fconfig = fopen(CONFIG_FILE_PATH, "r");

    if(fconfig == NULL) {
        printf("Error Opening File %s", CONFIG_FILE_PATH);
        return;
    }

    initMem(antenna, antFiles, delays);

    char line[1024];
    int antToRead = 0;
    int iant = 0;

    // Set some defaults
    *nPol = 2;
    *isComplex = 0;
    *nBit = 2;

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
            strcpy(antenna[iant], keyword);
            token = strtok(NULL, " \n");
            strcpy(antFiles[iant], token);
            token = strtok(NULL, " \n");
            for (int i = 0; i < 3; i++) {
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for antenna %d\n", iant);
                    exit(1);
                }
                sscanf(token, "%lf", &delays[iant][i]); // Corrected allocation and access
                token = strtok(NULL, " \n");
            }
            if (token == NULL) {
                fprintf(stderr, "Error: Insufficient data for antenna %d\n", iant);
                exit(1);
            }
            sscanf(token, "%lf", &antFileOffsets[iant]); // Error checking needed
            iant++;
            antToRead--;
        } else {
            if (strcasecmp(keyword, "COMPLEX") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for COMPLEX\n");
                    exit(1);
                }
                sscanf(token, "%d", isComplex); // Should error check
            } else if (strcasecmp(keyword, "NBIT") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for NBIT\n");
                    exit(1);
                }
                sscanf(token, "%d", nBit); // Should error check
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
                sscanf(token, "%d", nChan); // Should error check
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
                sscanf(token, "%d", numFFT); // Should error check
            } else if (strcasecmp(keyword, "NANT") == 0) {
                token = strtok(NULL, " \n");
                if (token == NULL) {
                    fprintf(stderr, "Error: Insufficient data for NANT\n");
                    exit(1);
                }
                sscanf(token, "%d", nant); // Should error check
                antToRead = *nant;
                iant = 0;
            } else {
                fprintf(stderr, "Error: Unknown keyword \"%s\"\n", keyword);
            }
        }
    }
    fclose(fconfig);
}


void readConfig(int *nbit, int *nPol, int *iscomplex, int *nchan, int *nant, double *lo, double *bandwidth, 
                int *numffts, char **antenna, char **antFiles, double **delays, double *antfileoffsets) {
    /*
    printf("NBIT: %d\n", *nbit);
    printf("NPOL: %d\n", *nPol);
    printf("COMPLEX: %s\n", *iscomplex ? "true" : "false");
    printf("NCHAN: %d\n", *nchan);
    printf("NANT: %d\n", *nant);
    printf("LO: %lf\n", *lo);
    printf("BANDWIDTH: %lf\n", *bandwidth);
    printf("NUMFFTS: %d\n", *numffts);

    // Print antenna names
    printf("Antenna names:\n");
    for (int i = 0; i < *nant; i++) {
        printf("%s\n", antenna[i]);
    }

    // Print antenna files
    printf("Antenna files:\n");
    for (int i = 0; i < *nant; i++) {
        printf("%s\n", antFiles[i]);
    }

    // Print delays
    printf("Delays:\n");
    for (int i = 0; i < *nant; i++) {
        printf("Antenna %d:\n", i);
        for (int j = 0; j < 3; j++) {
            printf("%e ", delays[i][j]);
        }
        printf("\n");
    }

    // Print antfileoffsets
    printf("Antenna file offsets:\n");
    for (int i = 0; i < *nant; i++) {
        printf("%e\n", antfileoffsets[i]);
    }
     */
}

void initMem(char ** antenna, char ** antFiles, double ** delays) {
    for (int i = 0; i < MAX_ANTENNAS; i++) {
        antenna[i] = (char *) malloc(MAX_ANTENNA_NAME * sizeof(char));
        antFiles[i] = (char *)malloc(MAX_ANTENNA_FILE_NAME * sizeof(char));
        delays[i] = (double *)malloc(3*sizeof(double));
    }
}