#include "sift.h"

void splitOctaves(unsigned char *octave0, unsigned char *octave1,
		unsigned char *octave2, unsigned char *octave3,
		unsigned char *octave4, unsigned char *octave5,
		unsigned char *octave6, unsigned char *octave7,
		unsigned char *octaves_in, int *O, int *octavesW, int *octavesH){
	int i;
    int out_offset=0,cpy_size=0,posO=0;
    unsigned char* octaves[MAX_O];
#ifdef TIMING_splitOctaves
    Timer timer;
    start_timer(&timer);
#endif

    octaves[0]=octaves_in;
    for(i = 1; i < *O; i++){
		posO+=octavesH[i-1]*octavesW[i-1];
		octaves[i]=octaves_in+posO;
    }

    cpy_size=octavesH[0]*octavesW[0];
    memcpy(octave0,octaves[0],cpy_size*sizeof(unsigned char));

    memcpy(octave1,octaves[0],cpy_size*sizeof(unsigned char));

    memcpy(octave2,octaves[0],cpy_size*sizeof(unsigned char));

    memcpy(octave3,octaves[0],cpy_size*sizeof(unsigned char));

    memcpy(octave4,octaves[0],cpy_size*sizeof(unsigned char));

	cpy_size=octavesH[1]*octavesW[1];
    memcpy(octave5,octaves[1],cpy_size*sizeof(unsigned char));

	cpy_size=octavesH[1]*octavesW[1]+octavesH[2]*octavesW[2];
    memcpy(octave6,octaves[1],cpy_size*sizeof(unsigned char));

	cpy_size=0;
    for(i=2; i<*O;i++)
			cpy_size+=octavesH[i]*octavesW[i];
    memcpy(octave7,octaves[2],cpy_size*sizeof(unsigned char));

#ifdef TIMING_splitOctaves
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif

}
