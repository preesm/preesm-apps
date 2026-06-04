//
// Created by hmiomand on 25/02/2020.
//

#include "PSNR.h"
#include "yuvRead.h"

extern int counter;
extern char videoFiles[NB_VIDEO][200];

double globMSE = 0;
int totalIter = 0;

void computeGlobPSNR()
{
    globMSE /= totalIter;

    double avgPsnrValue = 10 * log10(255 * 255 / globMSE);

    printf("avgPsnr = %lf\n", avgPsnrValue);
}

void compute_PSNR(int WIDTH, int HEIGHT, unsigned char* reference, unsigned char* modified)
{
    static int once = 0;

    if (once == 0)
    {
        once = 1;
        atexit(computeGlobPSNR);
    }


	static int iter = 0;
    static double worstPsnr = INFINITY;
    static double avgPsnr = 0;

	double psnr_value = 0;
	double max_value = 255;

    double mse = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			mse += (reference[i*WIDTH + j] - modified[i*WIDTH + j]) * (reference[i*WIDTH + j] - modified[i*WIDTH + j]);
		}
	}

	mse /= (WIDTH*HEIGHT);

    globMSE += mse;

    psnr_value = 10 * log10(max_value * max_value / mse);

    avgPsnr+= psnr_value;

    if (psnr_value < worstPsnr)
        worstPsnr = psnr_value;

    if (iter % 10 == 0)
        printf("%d: worst psnr = %f\n", iter, worstPsnr);

    //printf("%d: PSNR = %lf\n", iter, psnr_value);

    if (iter >= 300){
        char fileName[300] = {"\0"};
        strcat(fileName, videoFiles[counter]);
        strcat(fileName, PSNR_FILE_EXT);
        FILE * psnr_file = fopen( fileName, "w");
        //fwrite(&worst_psnr, sizeof(worst_psnr), 1, psnr_file);
        fprintf(psnr_file, "%lf", worstPsnr);
        fclose(psnr_file);


//        printf("avgPsnr = %lf\n", avgPsnr/totalIter);

        iter = 0;
        initReadYUV(352/*width*/, 288/*height*/); // yuvRead_0
//        exit(EXIT_SUCCESS);
    }
    else
        iter++;

    totalIter++;
}
