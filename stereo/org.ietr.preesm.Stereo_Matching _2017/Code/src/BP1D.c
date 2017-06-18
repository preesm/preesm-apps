#include <stdlib.h>
#include "image.h"
#include "costMatrix.h"
#include "BP1D.h"
#include "bp1d_node.h"


node_type min2(node_type val1, node_type val2)
{
    return val1<val2?(val1):(val2);
}

node_type min3(node_type val1, node_type val2, node_type val3)
{
    return min2(min2(val1,val2),val3);
}

// BP_ComputeFi computes the forward pass
// forward messages are stored in the Fi table of node structure
void BP_ComputeFi(phib_type *Phi_B, fi_type *Fi, unsigned int width, unsigned ndisp, int phi0)
{
    short x, dd;
    node_type MR_MR, B_MR;
    node_type ML_B, B_B, MR_B;

    int halfdispartity = (ndisp-1)/2;
    int width_phib = (width-(halfdispartity + 1));

    for (dd=0; dd < ndisp + 2; dd++)						// initialisation of the Fi first colomn to 0
    {
        Fi[dd].M = 0;
        Fi[dd].B  = 0;
    }

    for (x=1; x < width_phib; x++)						// initialisation of the Fi first lign and last lign
    {
        Fi[x*(ndisp + 2) + ndisp + 1].M = F_BIG;		// normalement inutile	=> pas d'après les tests !
        Fi[x*(ndisp + 2) + ndisp + 1].B = F_BIG;		// normalement inutile	=> pas d'après les tests !
        Fi[x*(ndisp + 2)].M				= F_BIG;		// normalement inutile	=> pas d'après les tests !
        Fi[x*(ndisp + 2)].B				= F_BIG;		// peut être inutile ?
    }


    for (x=1; x < width_phib; x++)

    {
        // compute Fi for the disparity d = 0
        // Fi->ML
        MR_MR	= Fi[(x-1)*(ndisp+2) + 2].M	+ phi0;
        B_MR	= Fi[(x-1)*(ndisp+2) + 2].B	+ Phi_B[(x-1)*(ndisp+1) + 1];
        Fi[x*(ndisp+2)+1].M  = min2 (MR_MR , B_MR);

        // Fi->B
        MR_B	= Fi[(x-1)*(ndisp+2)+1].M		+ phi0 ;
        B_B		= Fi[(x-1)*(ndisp+2)+1].B		+ Phi_B[(x-1)*(ndisp+1)];
        ML_B	= Fi[(x-1)*(ndisp+2)].B		+ phi0;
        Fi[x*(ndisp+2)+1].B  = min3( ML_B , B_B , MR_B);

        for (dd=0; dd < halfdispartity; dd++)
        {
            // compute Fi even disparities (d = dd*2) using previous Fi and Phi_B
            // values for d = 0 and d = 2 are required to compute d = 1
            // Fi->ML
            MR_MR	= Fi[(x-1)*(ndisp+2) + dd*2 + 4].M	+ phi0;
            B_MR	= Fi[(x-1)*(ndisp+2) + dd*2 + 4].B	+ Phi_B[(x-1)*(ndisp+1) + dd*2 + 3];
            Fi[x*(ndisp+2) + dd*2 + 3].M  = min2 (MR_MR , B_MR);

            // Fi->B
            MR_B	= Fi[(x-1)*(ndisp+2) + 2*dd + 3].M 	+ phi0;
            B_B		= Fi[(x-1)*(ndisp+2) + 2*dd + 3].B	+ Phi_B[(x-1)*(ndisp+1) + 2*dd + 2];
            ML_B	= Fi[(x-1)*(ndisp+2) + 2*dd + 2].B	+ phi0;
            Fi[x*(ndisp+2) + 2*dd + 3].B  = min3( ML_B , B_B , MR_B);


            // compute Fi for odd disparities (d = 2*dd + 1) using previous Fi and Phi_B
            // Fi->ML
            MR_MR	= Fi[x*(ndisp+2) + (dd * 2 + 1) + 2].M	+ phi0;
            B_MR = Fi[x*(ndisp + 2) + (dd * 2 + 1) + 2].B		+ Phi_B[x*(ndisp + 1) + (dd * 2 + 1) + 1];
            Fi[x*(ndisp + 2) + (dd * 2 + 1) + 1].M = min2(MR_MR, B_MR);

            // Fi->B
            MR_B = Fi[(x - 1)*(ndisp + 2) + (dd * 2 + 1) + 1].M	+ phi0;
            B_B = Fi[(x - 1)*(ndisp + 2)	+ (dd * 2 + 1) + 1].B	+ Phi_B[(x - 1)*(ndisp + 1) + (2 * dd) + 1];
            ML_B = Fi[x*(ndisp + 2)		+ (dd * 2 + 1)].B		+ phi0;
            Fi[x*(ndisp + 2) + (dd * 2 + 1) + 1].B = min3(ML_B, B_B, MR_B);
        }
    }
}


// BP_Compute_Energy computes the backward pass = energy for each node of the BVP
// backward messages are stored in the GrandPhi table of node structure
// the energies are stored in the table Energy but it is not required
void BP_Compute_Energy(phib_type *Phi_B, energy_type *Energy, fi_type *Fi, unsigned char *DepthMap, unsigned int width, unsigned int ndisp, int phi0)
{
    short x, dd;
    struct node* GrandPhi;
    node_type ML_ML, B_ML;
    node_type MR_B, B_B, ML_B;
    energy_type Energy_B, Energy_ML, Energy_MR, min;

    int halfdisparity = (ndisp-1)/2;
    //printf("%d\n",halfdisparity);
    int width_phib = (width-(halfdisparity + 1));

    GrandPhi = malloc(sizeof(struct node)*(ndisp+2));

    for (dd=0; dd < ndisp + 1; dd++)						// initialisation of the GrandPhi backward message first colomn to 0
    {
        GrandPhi[dd+1].M	= 0;
        GrandPhi[dd+1].B	= 0;
    }

    GrandPhi[0].M			= F_BIG;
    GrandPhi[0].B			= F_BIG;

    GrandPhi[ndisp+1].M	= F_BIG;
    GrandPhi[ndisp+1].B	= F_BIG;


    for (dd=0; dd < ndisp; dd++)						// compute energies for the last column "width_phib"
    {
        Energy_B	= Phi_B[(width_phib - 1)*(ndisp + 1) + dd]	+ Fi[(width_phib - 1) * (ndisp + 2) + dd].B;
        Energy_ML	= phi0											+ Fi[(width_phib - 1) * (ndisp + 2) + dd].B;
        Energy_MR	= phi0											+ Fi[(width_phib - 1) * (ndisp + 2) + dd].M;
        Energy[(width_phib - 1)* ndisp + dd]  = min3( Energy_B , Energy_ML , Energy_MR);
    }

    for (x=width_phib-2; x>=0; x--)
    {
        for (dd= 0; dd < halfdisparity ; dd++)
        {
            // compute GrandPhi message for odd disparities (d = 2*dd + 1) using previous GrandPhi and Phi_B
            // should start with odd disparities before even ones
            // GrandPhi->MR
            ML_ML	=	GrandPhi[dd*2 + 3].M		+	phi0;
            B_ML	=	GrandPhi[dd*2 + 3].B		+	Phi_B[(x+1)*(ndisp+1) + dd*2 + 2];


            // GrandPhi->B
            MR_B	=	GrandPhi[dd*2 + 1 ].B 		+	phi0;
            B_B		=	GrandPhi[dd*2 + 2 ].B		+	Phi_B[(x+1)*(ndisp+1) + dd*2 + 1];
            ML_B	=	GrandPhi[dd*2 + 2 ].M 		+	phi0;

            GrandPhi[dd * 2 + 2].M = min2(ML_ML, B_ML); // Update : GrandPhi after computing ML_B
            GrandPhi[dd*2 + 2].B  = min3( ML_B , B_B , MR_B);


            Energy_B	=	GrandPhi[dd*2 + 2].B	+ Phi_B[x*(ndisp+1) + dd*2 + 1]	+ Fi[x * (ndisp + 2) + dd*2 + 2].B;
            Energy_ML	= GrandPhi[dd*2 + 2].M		+ phi0								+ Fi[x * (ndisp + 2) + dd*2 + 2].B;
            Energy_MR	= GrandPhi[dd*2 + 2].B		+ phi0								+ Fi[x * (ndisp + 2) + dd*2 + 2].M;
            Energy[x * ndisp + 2*dd + 1]  = min3( Energy_B , Energy_ML , Energy_MR);

            // compute GrandPhi message for even disparities (d = 2*dd) using previous GrandPhi and Phi_B
            // GrandPhi->MR
            ML_ML	=	GrandPhi[dd*2 + 2].M		+	phi0;
            B_ML	=	GrandPhi[dd*2 + 2].B		+	Phi_B[x*(ndisp+1) + dd*2 + 1];


            // GrandPhi->B
            MR_B	= GrandPhi[dd*2].B 			+	phi0;
            B_B		= GrandPhi[dd*2 + 1].B		+	Phi_B[(x+1)*(ndisp+1) + dd*2];
            ML_B	= GrandPhi[dd*2 + 1].M 		+	phi0;

            GrandPhi[dd * 2 + 1].M = min2(ML_ML, B_ML); // Update : GrandPhi after computing ML_B
            GrandPhi[dd*2 + 1].B  = min3( ML_B , B_B , MR_B);

            Energy_B =	GrandPhi[dd*2 + 1].B	+ Phi_B[x*(ndisp+1) + dd*2]		+ Fi[x * (ndisp + 2) + dd*2 + 1].B;
            Energy_ML = GrandPhi[dd*2 + 1].M	+ phi0								+ Fi[x * (ndisp + 2) + dd*2 + 1].B;
            Energy_MR = GrandPhi[dd*2 + 1].B	+ phi0								+ Fi[x * (ndisp + 2) + dd*2 + 1].M;

            Energy[x * ndisp + 2*dd] = min3( Energy_B , Energy_ML , Energy_MR);

        }

        // compute GrandPhi for the last disparity d = 2 * halfdisparity+1
        // 2 * dd + 1 = ndisp
        // GrandPhi->MR

        ML_ML	=	GrandPhi[ndisp + 1].M		+ phi0;
        B_ML	=	GrandPhi[ndisp + 1].B		+ Phi_B[x*(ndisp+1) + ndisp];


        // GrandPhi->B
        MR_B	=	GrandPhi[ndisp - 1].B		+	phi0;
        B_B		=	GrandPhi[ndisp].B			+	Phi_B[(x+1)*(ndisp+1) + ndisp];
        ML_B	=	GrandPhi[ndisp].M 		+	phi0;
        GrandPhi[ndisp].M = min2(ML_ML, B_ML);  // Update : GrandPhi after computing ML_B
        GrandPhi[ndisp].B  = min3( ML_B , B_B , MR_B);

        Energy_B	=	GrandPhi[ndisp].B		+ Phi_B[x*(ndisp+1) + ndisp - 1]	+ Fi[x * (ndisp + 2) + ndisp].B;
        Energy_ML	=	GrandPhi[ndisp].M		+ phi0									+ Fi[x * (ndisp + 2) + ndisp].B;
        Energy_MR	=	GrandPhi[ndisp].B		+ phi0									+ Fi[x * (ndisp + 2) + ndisp].M;
        Energy[x * ndisp + ndisp - 1] = min3( Energy_B , Energy_ML , Energy_MR);


    }

    for (x = width_phib-1; x >= 0; x--)
    {
        min = Energy[x * ndisp];
        DepthMap[x] = 0;
        for (dd= 1; dd < ndisp; dd++)
        {
            if (Energy[x * ndisp + dd] < min)
            {
                min = Energy[x * ndisp + dd];
                DepthMap[x] = dd  ;
                DepthMap[x] = DepthMap[x] ;
            }
        }
    }
    free(GrandPhi);
}



void BP1D_image(const struct dispMatrix_size* size, const uint8_t* costIn, uint8_t* out, int phi0)
{
    int i;
    phib_type*	Phi_B_message;
    fi_type*	Fi;
    energy_type* Energy_values;
    unsigned int ndisp = size->dsize;
    if(size->dsize%2 == 0)
        ndisp = size->dsize-1;

    int halfdisparity = (ndisp-1)/2;
    int width_phib = (size->xsize-(halfdisparity + 1));

    Phi_B_message = malloc(sizeof(phib_type)*( width_phib * (ndisp + 1) ));
    Fi = malloc(sizeof(fi_type)*( width_phib * (ndisp + 2) ));
    Energy_values = malloc(sizeof(energy_type)*( width_phib * ndisp ));

    for (i = 0; i < size->ysize; i++)
    {
        costMatrix_dxy_getLine(size,i,costIn,Phi_B_message);
        BP_ComputeFi(Phi_B_message, Fi, size->xsize, ndisp, phi0);
        BP_Compute_Energy(Phi_B_message, Energy_values, Fi, out + i*size->xsize, size->xsize, ndisp, phi0);
    }

    free(Phi_B_message);
    free(Fi);
    free(Energy_values);
}

void bp1d_selection(const struct dispMatrix_size* size, const uint8_t* costIn, uint8_t* out, int phi0) {
    BP1D_image(size,costIn, out, phi0);
}
