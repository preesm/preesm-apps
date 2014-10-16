#include "sift.h"

void mergeSS(float* scale_space_in0, float* scale_space_in1,
	float* scale_space_in2, float* scale_space_in3,
	float* scale_space_in4, float* scale_space_in5,
	float* scale_space_in6, float* scale_space_in7,
	float* scale_space_out, int *O, int S, int *octavesW, int *octavesH){
	int i;
    int out_offset=0,cpy_size=0;
#ifdef TIMING_mergeSS
    Timer timer;
    start_timer(&timer);
#endif


    cpy_size=octavesH[0]*octavesW[0];
    memcpy(scale_space_out+out_offset,scale_space_in0,cpy_size*sizeof(float));
    out_offset+=cpy_size;

    memcpy(scale_space_out+out_offset,scale_space_in1,cpy_size*sizeof(float));
    out_offset+=cpy_size;

    memcpy(scale_space_out+out_offset,scale_space_in2,cpy_size*sizeof(float));
    out_offset+=cpy_size;

    memcpy(scale_space_out+out_offset,scale_space_in3,cpy_size*sizeof(float));
    out_offset+=cpy_size;

    memcpy(scale_space_out+out_offset,scale_space_in4,cpy_size*sizeof(float));
    out_offset+=cpy_size;

	cpy_size=3*octavesH[1]*octavesW[1];
    memcpy(scale_space_out+out_offset,scale_space_in5,cpy_size*sizeof(float));
    out_offset+=cpy_size;

	cpy_size=2*octavesH[1]*octavesW[1]+3*octavesH[2]*octavesW[2];
    memcpy(scale_space_out+out_offset,scale_space_in6,cpy_size*sizeof(float));
    out_offset+=cpy_size;

	cpy_size=2*octavesH[2]*octavesW[2];
    for(i=3; i<*O;i++)
			cpy_size+=octavesH[i]*octavesW[i]*S;
    memcpy(scale_space_out+out_offset,scale_space_in7,cpy_size*sizeof(float));

#ifdef TIMING_mergeSS
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif

}
