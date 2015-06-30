#include "sift.h"

/**********************************************
 * Difference of Gaussians (DoG)
 * Only diff neighboring scales in same octave
 * Do not diff across two octaves
 *
 * Parameters
 * dog: output, Ox(S-1) images in floating point
 * scaleSpace: input, OxS images in floating pt
 * O: number of octaves
 * S: scales per octave
 * octavesW: output, width of each octave
 * octavesH: output, height of each octave
 **********************************************/

void DoG(float *dog_in,
         float *scale_space_in,
         int *O, int S,
         int* octavesW, int* octavesH){

    // comon variables
    int i, j, ii, jj;
    float* scaleSpace[MAX_O][MAX_S];
    float* dog[MAX_O][MAX_S-1];
    int posSS=0, posDoG=0, octaveSize=0;

#ifdef TIMING_DOG
    Timer timer;
    start_timer(&timer);
#endif

    for(i = 0; i < *O; i++){
		octaveSize=octavesH[i]*octavesW[i];//*sizeof(float);
        for(j = 0; j < S; j++){
			scaleSpace[i][j] =scale_space_in + posSS;
			posSS+=octaveSize;
		}
		for(j = 0; j < S-1; j++){
			dog[i][j] =dog_in + posDoG;
			posDoG+=octaveSize;
		}
    }



    for(i = 0; i < *O; i++){
        for(j = 0; j < S-1; j++){
            for(ii = 0; ii < octavesH[i]; ii++){
                for(jj = 0; jj < octavesW[i]; jj++){
                    // dog = upper scale - lower scale
                    dog
                        [i]
                        [j]
                        [ii*octavesW[i]+jj]
                        =
                        scaleSpace
                        [i]
                        [j+1]
                        [ii*octavesW[i]+jj]
                        -
                        scaleSpace
                        [i]
                        [j]
                        [ii*octavesW[i]+jj];
                }
            }
        }
    }

    //fprintf(stderr,"fin DoG\n");
#ifdef TIMING_DOG
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}
