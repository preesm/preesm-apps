/**
* Computing the energy of a process measured by the scripts from amercat on the odroid board.
* This program reads a .csvfile with power measurements @10 samples per second, computes the energy and returns it on the console
* @author mpelcat
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_MEASURES 3600 // Maximum duration of measurements in seconds
#define SAMPLING_FREQ 10 // Sampling frequency of the power information in herz

float measures[MAX_MEASURES*SAMPLING_FREQ][3]; // Table correxponding to the energies of the A7, A15 and memory on the odroid board

int fill_table(FILE * pFile){
    const char delimiters[] = " ,\n";
    char line [100];
    char* token;
    char* running;
    int vindex = 0; // vertical index

    while ( fgets (line, 100, pFile) != NULL ){
        int hindex = 0; // horizontal index
        running = strdup (line);
        while((token = strsep (&running, delimiters)) != NULL){
            if(strlen(token) != 0){
                if(hindex > 2){
                    printf("Problem detected in csv file at line %d", vindex);
                }else{
	            measures[vindex][hindex] = strtof(token, NULL);
                    hindex++;
                }
            }
        }
        if(hindex > 0){
	    vindex++;
	}
        if(hindex > MAX_MEASURES){
            printf("Too many lines in the file");
        }
    }

    return(vindex);
}

float sum_table(int nblines){
    int index = 0;
    float energy = 0.f;
    for(index = 0; index < nblines; index++){
        // Ading the powers of A7, A15 and memory
        float power_sample = measures[index][0] + 
          measures[index][1] + measures[index][2]; 
        energy += power_sample / SAMPLING_FREQ;  
    }
    return energy;
}

int main(int argc, char *argv[]){
    if((argc < 2) || (argc > 2)){
        printf("Incorrect number of arguments : %d != 1 expected\n", argc-1);
        printf("Enter a cvs file to read\n");
    }
    else{
        FILE * pFile;
        pFile = fopen (argv[1],"r");
        if (pFile!=NULL)
        {
            int nblines = fill_table(pFile);
            float energy = sum_table(nblines);
            printf("%f\n", energy);
            fclose (pFile);
            
        }
        else{
            printf("Could not open file %s\n", argv[1]);
        }
    }

    return 0;
}
