#include "sift.h"


void downsample(unsigned char* target,
                int targetW, int targetH,
                unsigned char* src,
                int srcW, int srcH);

/*******************************************
 * buildOB:
 * Build Octave Base by downsampling
 *
 * Parameters
 * img: input, source image (original)
 * octaves[MAX_O]: output, generated octaves
 * O: input, number of octaves to generate
 * S: input, scales per octave
 * octavesW: output, width of each octave
 * octavesH: output, height of each octave
 ******************************************/

void buildOB(unsigned char* img,
             unsigned char* octaves_in,
             int *O, int S,
             int* octavesW, int* octavesH){

    // common variables
    int i;
    unsigned char* octaves[MAX_O]; // tableau de pointeurs temporaire pour coller à la structure du code source de base
    int posO=0;

#ifdef TIMING_BOB
    Timer timer;
    start_timer(&timer);
#endif

    // attribution des pointeurs
    octaves[0]=octaves_in;
    for(i = 1; i < *O; i++){
		posO+=octavesH[i-1]*octavesW[i-1];
		octaves[i]=octaves_in+posO;
    }

    // octave 0 is the original image
    memcpy(octaves[0], img,
           octavesW[0] * octavesH[0] *
           sizeof(unsigned char));
    // downsample for octave 1 to O
    for(i = 1; i < *O; i++){
        downsample(octaves[i],
                   octavesW[i], octavesH[i],
                   octaves[i-1],
                   octavesW[i-1], octavesH[i-1]);
    }
#ifdef TIMING_BOB
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

/*******************************************
 * downsample:
 * Down Sample by Averaging
 *
 * Parameters
 * target: output, downsampled image
 * targetW: input, width of downsampled image
 * targetH: input, height of downsampled image
 * src: input, source image
 * srcW: input, width of source image
 * srcH: input, height of source image
 ******************************************/

void downsample(unsigned char* target,
                int targetW, int targetH,
                unsigned char* src,
                int srcW, int srcH){

    // common variables
    int i, j;

    for(i = 0; i < targetH; i++){
        for(j = 0; j < targetW; j++){
            // downsample by averaging 4 pixels
            target[i*targetW+j] = (unsigned char)
                ( (int)
                  ((int)src[i*2*srcW+j*2] +
                   (int)src[i*2*srcW+j*2+1] +
                   (int)src[(i*2+1)*srcW+j*2] +
                   (int)src[(i*2+1)*srcW+j*2+1])
                  / 4 );
        }
    }

}
