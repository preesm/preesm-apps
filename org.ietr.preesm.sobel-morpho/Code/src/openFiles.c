//
// Created by emichel on 01/05/24.
//

#include "openFiles.h"

void openFiles(int *numantennas, char **antFiles, FILE **antStream) {
    for (int i = 0; i < *numantennas; i++) {
        antStream[i] = fopen(antFiles[i], "rb");
        if (antStream[i] == NULL) {
            fprintf(stderr, "Problem with file %s - does it exist?\n", antFiles[i]);
        }
    }
}

void readdata(int *bytestoread, FILE **antStream, uint8_t **inputdata, int *numStreams, int numantenna) {

    //Allocate inputdata mem

    printf("subintbytes : %d \n", *bytestoread);
    printf("Allocating %d MB per antenna per subint\n", *bytestoread / (1024 * 1024));
    printf("           %d MB total\n", *bytestoread * numantenna / (1024 * 1024));

    for (int a = 0; a < numantenna; a++)
    {
        (inputdata)[a] = (uint8_t *)malloc(*bytestoread);
        if ((inputdata)[a] == NULL)
        {
            fprintf(stderr, "Unable to allocate %d bytes. Quitting\n", *bytestoread);
            exit(1);
        }
    }

    printf("Size of antStream : %d \n", *numStreams);
    for (int i = 0; i < *numStreams; i++) {
        size_t bytesRead = fread(inputdata[i], sizeof(uint8_t), *bytestoread, antStream[i]);
        if (bytesRead != *bytestoread) {
            if (feof(antStream[i])) {
                exit(1);
            } else {
                fprintf(stderr, "Error: Problem reading data (Read %zu bytes)\n", bytesRead);
                exit(1);
            }
        }
    }
}
