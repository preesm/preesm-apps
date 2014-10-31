#include "sift.h"
#include "img_io.h"

//#define PRINT_FILE
void switchInt(int* tab, int i, int j);
void switchFloat(float* tab, int i, int j);

void  render(int w, int h, unsigned char* y_input,
             unsigned int* x, unsigned int* y, int *o, int *s, float *ori, int *keyN,
			 unsigned char* y_output, float* sigmas, int n_max){

    // common variables
#ifdef PRINT_FILE
    FILE *skey;
#endif // PRINT_FILE

    int i, j;
    /*******************************
     * cR:
     * radius of the circle
     * cR = sigma * 4 * (2^O)
     *******************************/
    int cR[MAX_SiftKeypoints];

#ifdef TIMING_render
    Timer timer;
    start_timer(&timer);
#endif

    memcpy(y_output,y_input,w*h);


#ifdef PRINT_FILE
    fprintf(stderr,"render - valeur keyN : %d\n\n",*keyN);
    skey = fopen("skey.txt","w");
    fprintf(skey, "%d keypoints\n", *keyN);
#endif // PRINT_FILE

    for(i = 0; i < *keyN; i++){
            // derive circle radius cR
            cR[i] = (int)(sigmas[s[i]]*pow(2,o[i]));
            if(cR[i] <= 1){ // avoid zero radius
                cR[i] = 1;
            }
    }
#ifdef PRINT_FILE
            fprintf(skey, "%d\t%d\t%d\t%f\n", x[i], y[i], s[i], ori[i]);
#endif // PRINT_FILE
    for(i = 0; i < *keyN-1; i++){
        for(j=i+1;j<*keyN; j++){
            if(cR[j]>cR[i]){
                   switchInt(x,i,j);
                   switchInt(y,i,j);
                   switchInt(o,i,j);
                   switchInt(s,i,j);
                   switchInt(cR,i,j);
                   switchFloat(ori,i,j);
            }
        }
    }
    for(i = 0; i < n_max; i++){
        draw_circle(y_output, x[i], y[i], cR[i],w,h);
        draw_orientation(y_output, x[i], y[i], ori[i], cR[i],w,h);
    }
#ifdef PRINT_FILE
    fclose(skey);
#endif // PRINT_FILE

#ifdef TIMING_render
    stop_timer(&timer);
    fprintf(stderr,"Temps %s : %f ms\n",__FUNCTION__,get_timer_interval(&timer));
#endif
#ifdef TIMING
    system("pause");
#endif
}// render()

void switchInt(int* tab, int i, int j){
    int temp;
    temp=tab[i];
    tab[i]=tab[j];
    tab[j]=temp;
}

void switchFloat(float* tab, int i, int j){
    float temp;
    temp=tab[i];
    tab[i]=tab[j];
    tab[j]=temp;
}
