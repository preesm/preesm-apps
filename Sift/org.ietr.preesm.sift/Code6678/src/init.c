#include "sift.h"


void init(int w, int h, int S, int* O, int* octavesW, int* octavesH,
	float* sigmas){
	float sigma0 = 1.6f;
	int i;
#ifdef TIMING_INIT
    Timer timer;
    start_timer(&timer);
#endif

	*O = (int)(log( (w < h) ? (float)w : (float)h)/log(2.0f))-2;

    octavesW[0] = w;
	octavesH[0] = h;
    for(i = 1; i < *O; i++){
		octavesW[i] = octavesW[i-1]/2;
        octavesH[i] = octavesH[i-1]/2;
    }
    for(i = 0; i < S; i++){
       sigmas[i] = sigma0 * pow(sqrt(2.0f), (float)i/(float)(S-3) );
    }

#ifdef TIMING_INIT
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}
