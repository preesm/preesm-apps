#include <math.h>
#include "sift.h"

int current_octave = 0;
float* grad_buffer = NULL;

void
keypoint_orientation(SiftKeypoint* key, float *scaleImage,
                     float sigma, int octaveW, int octaveH);

// Calculate the orientations of all the keypoints
void
orientation(int *keyN,
                 float *scale_space_in,
                 int* octavesW, int* octavesH,float *sigmas,
                 float* struct_x, float* struct_y,
                 int* struct_o, float* struct_s,
                 int * struct_int_x, int * struct_int_y, int * struct_int_o,
                 int * struct_int_s, float *struct_float_ori, int *O, int S){
    int i,j;
    SiftKeypoint tmp;
    float* scaleSpace[MAX_O][MAX_S];
    int posSS=0, octaveSize=0;
#ifdef TIMING_ori
    Timer timer;
    start_timer(&timer);
#endif
    for(i = 0; i < *O; i++){
		octaveSize=octavesH[i]*octavesW[i];//*sizeof(float);
		for(j = 0; j < S-1; j++){
			scaleSpace[i][j] =scale_space_in + posSS;
			posSS+=octaveSize;
		}
    }

    //fprintf(stderr,"ori - keyN : %d\n",*keyN);
    for (i=0;i<*keyN;i++) {
        int octave  = struct_o[i];
        float scale = struct_s[i];
        float* scaleImage = scaleSpace[octave][(int)scale];
        float sigma = sigmas[(int)scale];
        int octW = octavesW[octave];
        int octH = octavesH[octave];
        tmp.o=octave;
        tmp.s=scale;
        tmp.x=struct_x[i];
        tmp.y=struct_y[i];
        keypoint_orientation(&tmp, scaleImage, sigma, octW, octH);
        struct_float_ori[i]=tmp.ori;
        struct_int_x[i]= (int)(tmp.x)*(octavesW[0]/octavesW[tmp.o]);
        struct_int_y[i]= (int)(tmp.y)*(octavesH[0]/octavesH[tmp.o]);
        struct_int_s[i]= (int) tmp.s;
        struct_int_o[i]= tmp.o;
    }

#ifdef TIMING_ori
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}// orientation()

void
keypoint_orientation(SiftKeypoint* key, float *scaleImage,
                     float sigma, int octaveW, int octaveH) {
    float PI = 3.1415926f;
    float ori_hist[ORI_BINS] = {0.0f};
    int bin = ORI_BINS;
    int x = (int)(key->x);
    int y = (int)(key->y);
    float radius = 1.5f * sigma;

    int i, j;
    float maxBin = 0.0f;
	int maxOri = 0;
    for(i = -1 * (int)(radius); i < (int)(radius) + 1; ++i){
        for(j = -1 * (int)(radius); j < (int)(radius) + 1; ++j){
            // compute magnitude and orientation
            int index = (y + i) * octaveW + (x + j);
            int voteIndex;
            float mag, ori, weight;
            float dx = scaleImage[index+1] - scaleImage[index-1];
            float dy = scaleImage[index-octaveW] - scaleImage[index+octaveW];
            if(dx == 0.0f && dy == 0.0f){
                continue;
            }
            mag = sqrt(dx*dx + dy*dy);
            ori = atan2(dy, dx);
            // voting to histo bins
            // weight for smoothing
            weight = exp( -1.0f * (i*i+j*j) / (2.0f*sigma*sigma) );
            // oriHisto represent orientations from - PI to PI.
            // (index == 0) means - PI
            // (index == bin-1) means PI
            voteIndex = (int)(bin * ((ori + PI) / (2.0f * PI)) );
            // avoid exceeding the boundary of the histogram
            if(voteIndex < 0 ){
                voteIndex = 0;
            } else if(voteIndex > (ORI_BINS - 1) ){
                voteIndex = (ORI_BINS - 1);
            }
            // weight the vote with Gaussian smoothing
            ori_hist[voteIndex] += weight * mag;
            // update the major orientation
            if(ori_hist[voteIndex] > maxBin){
                maxBin = ori_hist[voteIndex];
                maxOri = voteIndex;
            }
        }// for j
    }// for i
    // ((maxOri*10) - 180) * PI/180
    key->ori = maxOri*PI/18 - PI;
    key->mag = maxBin;
}// keypoint_orientation()
