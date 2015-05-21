#include "sift.h"

void g2d(float* target,
         unsigned char* src,
         int w,
         int h,
         float sigma);


void buildSS0(unsigned char* octaves_in,
             float *scale_space_in,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas){
    int i;
    unsigned char* octaves[MAX_O];
    float* scaleSpace[MAX_O][MAX_S]; // idem que pour les octaves

#ifdef TIMING_BSS0
    Timer timer;
#endif
    octaves[0]=octaves_in;
#ifdef TIMING_BSS0
    start_timer(&timer);
#endif
    scaleSpace[0][0] =scale_space_in;
    g2d(scaleSpace[0][0],
        octaves[0],
        octavesW[0],
        octavesH[0],
        sigmas[0]);
#ifdef TIMING_BSS0
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

void buildSS1(unsigned char* octaves_in,
             float *scale_space_in,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas){
    int i;
    unsigned char* octaves[MAX_O];
    float* scaleSpace[MAX_O][MAX_S];

#ifdef TIMING_BSS1
    Timer timer;
#endif
    octaves[0]=octaves_in;

#ifdef TIMING_BSS1
    start_timer(&timer);
#endif
    scaleSpace[0][1] =scale_space_in;
    g2d(scaleSpace[0][1],
        octaves[0],
        octavesW[0],
        octavesH[0],
        sigmas[1]);
#ifdef TIMING_BSS1
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

void buildSS2(unsigned char* octaves_in,
             float *scale_space_in,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas){
    int i;
    unsigned char* octaves[MAX_O];
    float* scaleSpace[MAX_O][MAX_S];

#ifdef TIMING_BSS2
    Timer timer;
#endif
    octaves[0]=octaves_in;

#ifdef TIMING_BSS2
    start_timer(&timer);
#endif
    scaleSpace[0][2] =scale_space_in;
    g2d(scaleSpace[0][2],
        octaves[0],
        octavesW[0],
        octavesH[0],
        sigmas[2]);
#ifdef TIMING_BSS2
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

void buildSS3(unsigned char* octaves_in,
             float *scale_space_in,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas){
    int i;
    unsigned char* octaves[MAX_O];
    float* scaleSpace[MAX_O][MAX_S];

#ifdef TIMING_BSS3
    Timer timer;
#endif
    octaves[0]=octaves_in;

#ifdef TIMING_BSS3
    start_timer(&timer);
#endif
    scaleSpace[0][3] =scale_space_in;
    g2d(scaleSpace[0][3],
        octaves[0],
        octavesW[0],
        octavesH[0],
        sigmas[3]);
#ifdef TIMING_BSS3
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

void buildSS4(unsigned char* octaves_in,
             float *scale_space_in,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas){
    int i;
    unsigned char* octaves[MAX_O];
    float* scaleSpace[MAX_O][MAX_S];

#ifdef TIMING_BSS4
    Timer timer;
#endif
    octaves[0]=octaves_in;

#ifdef TIMING_BSS4
    start_timer(&timer);
#endif
    scaleSpace[0][4] =scale_space_in;
    g2d(scaleSpace[0][4],
        octaves[0],
        octavesW[0],
        octavesH[0],
        sigmas[4]);
#ifdef TIMING_BSS4
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

void buildSS5(unsigned char* octaves_in,
             float *scale_space_in,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas){
    int i;
    unsigned char* octaves[MAX_O];
    float* scaleSpace[MAX_O][MAX_S];
    int posSS=0;
#ifdef TIMING_BSS5
    Timer timer;
    start_timer(&timer);
#endif
    octaves[1]=octaves_in;
    for(i = 0; i < 3; i++){
        scaleSpace[1][i] =scale_space_in + posSS;
        posSS+=octavesH[1]*octavesW[1];
        g2d(scaleSpace[1][i],
            octaves[1],
            octavesW[1],
            octavesH[1],
            sigmas[i]);
    }
#ifdef TIMING_BSS5
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

void buildSS6(unsigned char* octaves_in,
             float *scale_space_in,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas){
    int i;
    unsigned char* octaves[MAX_O];
    float* scaleSpace[MAX_O][MAX_S];
    int posSS=0;
#ifdef TIMING_BSS6
    Timer timer;
    start_timer(&timer);
#endif
    octaves[1]=octaves_in;
    for(i = 3; i < S; i++){
        scaleSpace[1][i] =scale_space_in + posSS;
        posSS+=octavesH[1]*octavesW[1];
        g2d(scaleSpace[1][i],
            octaves[1],
            octavesW[1],
            octavesH[1],
            sigmas[i]);
    }
    octaves[2]=octaves_in+octavesH[1]*octavesW[1];
    for(i = 0; i < 3; i++){
        scaleSpace[2][i] =scale_space_in + posSS;
        posSS+=octavesH[2]*octavesW[2];
        g2d(scaleSpace[2][i],
            octaves[2],
            octavesW[2],
            octavesH[2],
            sigmas[i]);
    }
#ifdef TIMING_BSS6
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

void buildSS7(unsigned char* octaves_in,
             float *scale_space_in,
             int *O, int S,
             int* octavesW, int* octavesH,
             float *sigmas){
    int i,j;
    unsigned char* octaves[MAX_O];
    float* scaleSpace[MAX_O][MAX_S];
    int posO=0,posSS=0;
#ifdef TIMING_BSS7
    Timer timer;
    start_timer(&timer);
#endif
    octaves[2]=octaves_in;
    for(i = 3; i < *O; i++){
		posO+=octavesH[i-1]*octavesW[i-1];
		octaves[i]=octaves_in+posO;
    }

    for(i = 3; i < S; i++){
        scaleSpace[2][i] =scale_space_in + posSS;
        posSS+=octavesH[2]*octavesW[2];
        g2d(scaleSpace[2][i],
            octaves[2],
            octavesW[2],
            octavesH[2],
            sigmas[i]);
    }

    for(i = 3; i < *O; i++){
        for(j = 0; j < S; j++){
			scaleSpace[i][j] =scale_space_in + posSS;
			posSS+=octavesH[i]*octavesW[i];
			g2d(scaleSpace[i][j],
                octaves[i],
                octavesW[i],
                octavesH[i],
                sigmas[j]);
		}
    }
#ifdef TIMING_BSS7
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
}

void g2d(float* target,
         unsigned char* src,
         int w,
         int h,
         float sigma){

    // common variables
    int i, j;
    float tmp;
    float norm = 0.0f; // variable for normalization

    /*******************************
     * gR:
     * radius of the gaussian window
     * gW:
     * width of the gaussian window
     * gW = gR * 2 + 1
     * if gR == 2, the gW == 5
     * which is a 5x5 window
     *******************************/
    int gR;
    int gW;

    // 1D gaussian coeficients
    float coef1d[300];

    // pad the source image with boarders,
    // which has the width of gR
    unsigned char srcPadded[(IMG_WIDTH+145*2)*(IMG_HEIGHT+145*2)];

    // intermediate 1D gaussian result
    float intermediate[(IMG_WIDTH+145*2)*(IMG_HEIGHT+145*2)];

    // derive gR and gW
    if(sigma*4.0f > 1.0f){
        gR = (int)(sigma * 4.0f);
    }else{
        gR = 1;
    }
    gW = gR * 2 + 1;

    // allocate memory for gaussian coefficients
    /*coef1d = (float *)malloc( gW * sizeof(float) );

    // allocat ememory for padded source image
    // srcPadded has the type of (unsigned char)
    srcPadded =
        (unsigned char *)
        malloc(
            (w+gR*2)*(h+gR*2)*
            sizeof(unsigned char));

    // Allocat ememory for intermediate image.
    // Intermediate has the same size of srcPadded.
    // intermediate has the type of (float)
    intermediate =
        (float *)
        malloc((w+gR*2)*(h+gR*2)*sizeof(float));*/

    /****************************************
     * Compute Gaussian Coefficients
     ***************************************/

    norm = 0.0f;
    for(i = 0; i < gW; i++){
        tmp = (float)((float)i - (float)gR) / sigma;
        coef1d[i] = exp( -1.0f * tmp * tmp / 2.0f );
        norm = norm + coef1d[i];
    }
    for(i = 0; i < gW; i++){
        coef1d[i] = coef1d[i] / norm;
    }


    /****************************************
     * Padding "0" and copy src to srcPadded
     * Padding "0" to intermediate
     * Input 1 : src, size (w)x(h)
     * Input 2 : intermediate, size (w+gR*2)x(h+gR*2)
     * Output 1 : srcPadded, size (w+gR*2)x(h+gR*2)
     * Output 2 : intermediate, size (w+gR*2)x(h+gR*2)
     ***************************************/
    for(i = 0; i < h+gR*2; i++){
        for(j = 0; j < w+gR*2; j++){
            if( i < gR || i > h+gR-1
                || j < gR || j > w+gR-1 ){
                // padding srcPadded
                srcPadded[i*(w+gR*2)+j] = 0;
                // padding intermediate
                intermediate[i*(w+gR*2)+j] = 0.0f;
            }else{
                // copy the src to srcPadded
                srcPadded[i*(w+gR*2)+j] =
                    src[(i-gR)*w+(j-gR)];
            }
        }
    }

    /**********************************************
     * Horizontal 1D Gaussian
     * Input: srcPadded, size: (w+gR*2)x(h+gR*2)
     * Output: intermediate, size: (w+gR*2)x(h+gR*2)
     *********************************************/
    for(i = gR; i < h+gR; i++){
        for(j = gR; j < w+gR; j++){
            float accu = 0.0f;
            int ii;
            for(ii = (-1 * gR); ii < (gR + 1); ii++){
                // convolute with gaussian window
                // note: srcPadded is unsigned char
                accu +=
                    coef1d[ii + gR] *
                    (float)srcPadded[i*(w+gR*2)+j+ii];
            }
            intermediate[i*(w+gR*2)+j] = accu;
        }
    }

    /**********************************************
     * Vertical 1D Gaussian
     * Input: intermediate, size: (w+gR*2)x(h+gR*2)
     * Output: target, size: (w)x(h)
     *********************************************/
    for(i = gR; i < h+gR; i++){
        for(j = gR; j < w+gR; j++){
            float accu = 0.0f;
            int ii;
            for(ii = (-1 * gR); ii < (gR + 1); ii++){
                // convolute with gaussian window
                accu +=
                    coef1d[ii + gR] *
                    (float)
                    intermediate[(i+ii)*(w+gR*2)+j];
            }
            target[(i-gR)*w+(j-gR)] = accu;
        }
    }

    /**********************************************
     * Free the allocated memory
     * Input: intermediate, size: (w+gR*2)x(h+gR*2)
     * Output: target, size: (w)x(h)
     *********************************************/
    /*free(coef1d);
    free(srcPadded);
    free(intermediate);*/

}
