/*
	============================================================================
	Name        : mi.c
	Author      : ggautier
	Version     : 1.0
	Copyright   : CECILL-C
	Description : code for the MI based cost.
	============================================================================
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "mi.h"
#include "filter_u16.h"

/*
 * WHEN set, saves intermediate step inside files
 * (./out/histo must exist)
 */
#define DEBUG

//#define PROFILING

/**
 * \brief compute a cost map for all disparity.
 * \param size : size of buffers
 * \param iml : left image (must be size height*width)
 * \param imr : right image (must be size height*width)
 * \param thres : saturation value, 20 is a good value (depend on snr of image)
 * \param out : output buffer to store image (must be xsize*ysize*dsize long)
 */



/*!
 * \brief compute cost for a disparity level d.
 * \param imgr : right image (gray).
 * \param imgl : left image (gray).
 * \param mi : input mi matrix.
 * \param C : output cost image.
 * \param d : disparity level.
 */
void mi_cost_d(int height,
               int width,
               int ndisp,
               IN const uint8_t * rgray,
               IN const uint8_t * lgray,
               IN uint8_t * d,
               IN uint8_t *mi,
               OUT uint8_t *CostOUT)
{

    int i,j;
#ifdef PROFILING
    clock_t begin,end;
    float time_spent;
    begin = clock();
#endif
    uint32_t X=width,Y=height;

    for(i=0;i<Y;i++)
    {
        for(j=0;j<X;j++)
        {
            if((j-*d>0))
            {
                CostOUT[i*X+j]=mi[rgray[i*X+j]*256+lgray[i*X+j-*d]];
            }
            else /*border consideration*/
            {
                CostOUT[i*X+j]=mi[rgray[i*X+j]*256+lgray[i*X+j]];
            }
        }
    }
#ifdef PROFILING
    end = clock();
    time_spent = (float) (end - begin) * 1000. / ((float) (CLOCKS_PER_SEC));

    printf("disparity level %2d - cost construction time : %.2f ms\n",d, time_spent);
#endif
}


/*!
 * \brief compute mi matrix.
 * \param mi : output mi matrix.
 * \param imgr : right image (gray).
 * \param imgl : left image (gray).
 * \param disparity_map : input disparity map.
 */
void stereo_mutual_info(int height,
                        int width,
                        int ndisp,
                        OUT uint8_t* mi,
                        IN const uint8_t * rgray,
                        IN const uint8_t * lgray,
                        IN const uint8_t * disparitymap)
{
    int i=0, j=0;
    int n= (height)*(width);

#ifdef PROFILING
    clock_t begin,end;
    float time_spent;
#endif

    uint16_t gauss[7] ={290 ,  3539 ,  15862 ,  26154 ,  15862  , 3539  , 290};
    uint16_t P [MI_MATRIX_SIZE*2];
    uint16_t PR[MUTUAL_INFO_SIZE*2];
    uint16_t PL[MUTUAL_INFO_SIZE*2];

    uint16_t * H  = P;
    uint16_t * HR = PR + MUTUAL_INFO_SIZE;
    uint16_t * HL = PL + MUTUAL_INFO_SIZE;

    uint16_t * hr = PR;
    uint16_t * hl = PL;
    uint16_t * hrl= P;

    uint16_t * tmp= P  + MI_MATRIX_SIZE;


    memset(PR,0,sizeof(uint16_t)*MUTUAL_INFO_SIZE*2);
    memset(PL,0,sizeof(uint16_t)*MUTUAL_INFO_SIZE*2);
    memset(P ,0,sizeof(uint16_t)*MI_MATRIX_SIZE*2);




    /*Conjoint Probability of intensity correspondence computation*/
#ifdef PROFILING
    begin = clock();
#endif

    mutual_information_proba(height,width,ndisp,P,PR,PL,rgray,lgray, disparitymap);

#ifdef PROFILING
    end = clock();
    time_spent = (float) (end - begin) * 1000. / ((float) (CLOCKS_PER_SEC));

    printf("histogram time : %.2f ms\n", time_spent);
#endif

#ifdef PROFILING
    begin = clock();
#endif
    /*Apply gaussian filter on PL*/
    hfilter_u16(MUTUAL_INFO_SIZE,1,3,PL,HL,gauss);

    /*Apply gaussian filter on PR*/
    hfilter_u16(MUTUAL_INFO_SIZE,1,3,PR,HR,gauss);


    /*Apply 2D gaussian filter on P*/
    hfilter_u16(MUTUAL_INFO_SIZE,MUTUAL_INFO_SIZE,3,P,tmp,gauss);
    vfilter_u16(MUTUAL_INFO_SIZE,MUTUAL_INFO_SIZE,3,tmp,H,gauss);

#ifdef PROFILING
    end = clock();
    time_spent = (float) (end - begin) * 1000. / ((float) (CLOCKS_PER_SEC));

    printf("1st filter application time : %.2f ms\n", time_spent);
#endif

#ifdef PROFILING
    begin = clock();
#endif
    uint16_t coef = (255/logf( 2 * n ))/2; /*multiply by 19. for scaling*/
    /*Logarithm application and normalisation on HL, HR, H*/
    for(i=0;i<MUTUAL_INFO_SIZE;i++)
    {

        HL[i]= HL[i]!=0 ?
               -logf( (float) HL[i] / (float) n ) * coef:
               logf( 2 * n ) * coef;
        HR[i]= HR[i]!=0 ?
               -logf( (float) HR[i] / (float) n ) * coef:
               logf( 2 * n) * coef;
        H[i] = H[i]!=0 ?
               -logf( (float) H[i]  / (float) n ) * coef:
               logf( 2 * n ) * coef;
    }
    for(i=MUTUAL_INFO_SIZE;i<MI_MATRIX_SIZE;i++)
    {
        H[i] = H[i]!=0 ?
               -logf( (float) H[i]  / (float) n ) * coef:
               logf( 2 * n ) * coef;
    }
#ifdef PROFILING
    end = clock();
    time_spent = (float) (end - begin) * 1000. / ((float) (CLOCKS_PER_SEC));

    printf("Logarithm application time : %.2f ms\n", time_spent);
#endif

#ifdef PROFILING
    begin = clock();
#endif

    /*Apply gaussian filter on HL*/
    hfilter_u16(MUTUAL_INFO_SIZE,1,3,HL,hl,gauss);

    /*Apply gaussian filter on HR*/
    hfilter_u16(MUTUAL_INFO_SIZE,1,3,HR,hr,gauss);


    /*Apply 2D gaussian filter on H*/
    hfilter_u16(MUTUAL_INFO_SIZE,MUTUAL_INFO_SIZE,3,H,tmp,gauss);
    vfilter_u16(MUTUAL_INFO_SIZE,MUTUAL_INFO_SIZE,3,tmp,hrl,gauss);

#ifdef PROFILING
    end = clock();
    time_spent = (float) (end - begin) * 1000. / ((float) (CLOCKS_PER_SEC));

    printf("2nd filter application time : %.2f ms\n", time_spent);
#endif

#ifdef PROFILING
    begin = clock();
#endif
    /*computation and scaling of mi matrix in uint8_t*/
    uint16_t min = UINT16_MAX, max = 0;
    for(i=0;i<MUTUAL_INFO_SIZE;i++){
        for(j=0;j<MUTUAL_INFO_SIZE;j++){
            tmp[i*MUTUAL_INFO_SIZE+j]=
                    ( hl[i] + hr[j] < hrl[j*MUTUAL_INFO_SIZE+i])?
                    255:
                    255 - ( hl[i] - hrl[j*MUTUAL_INFO_SIZE+i] + hr[j] );
            max=(tmp[i*MUTUAL_INFO_SIZE+j])>max?(tmp[i*MUTUAL_INFO_SIZE+j]):max;
            min=(tmp[i*MUTUAL_INFO_SIZE+j])<min?(tmp[i*MUTUAL_INFO_SIZE+j]):min;
        }
    }
    for(i=0;i<MI_MATRIX_SIZE;i++){
        mi[i]= (tmp[i]-min)*255 / (max-min);
    }
#ifdef PROFILING
    end = clock();
    time_spent = (float) (end - begin) * 1000. / ((float) (CLOCKS_PER_SEC));

    printf("mi matrix construction time : %.2f ms\n", time_spent);
#endif
}

/*!
 * \brief compute probabilities.
 * \param P : joint probability.
 * \param PR : right image probability.
 * \param PL : left image probability.
 * \param imgr : right image (gray).
 * \param imgl : left image (gray).
 * \param disparity_map : input disparity map.
 */
void mutual_information_proba(int height,
                              int width,
                              int ndisp,
                              uint16_t* P,
                              uint16_t* PL,
                              uint16_t* PR,
                              const uint8_t * rgray,
                              const uint8_t * lgray,
                              const uint8_t * disparitymap)
{

    int i,j,d = 0,addr=0,addr_mi=0;
    uint8_t occlusion[width];
    uint16_t offset = 255,add_int=0;
    for(i=0;i<height;i++)
    {
        memset(occlusion,0,sizeof(uint8_t)*width);
        for(j=0;j<width;j++)
        {
            addr=i*width+j;
            d=(j-d>0)?disparitymap[addr]:0;
            add_int= (occlusion[j-d]==0)?1:0;
            addr_mi= lgray[addr]*MUTUAL_INFO_SIZE+rgray[addr-d];
            P[addr_mi]=(P[addr_mi]<=offset)?P[addr_mi]+add_int:offset;
            occlusion[j-d]=add_int;
        }
    }
    for(i=0;i<MUTUAL_INFO_SIZE;i++)
    {
        for(j=0;j<MUTUAL_INFO_SIZE;j++)
        {
            PL[i]+=P[i*MUTUAL_INFO_SIZE+j];
            PR[j]+=P[i*MUTUAL_INFO_SIZE+j];
        }
    }

    /*Normalisation*/
    for(i=0;i<MI_MATRIX_SIZE;i++)
    {
        P[i]*=128;
    }
}
