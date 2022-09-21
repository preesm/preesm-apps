//#include"nalu_sps.h"
#include "non_tiles_decoding.h"
void nalu( int * i2  , int *ret8, int *ret9 , OVPictureUnit **pu3, int iter2,OVNVCLReader *rdr,OVNVCLCtx **const nvcl_ctx){
	if (ret8[0]>=0){
		 int i= i2[0];
		if(i<iter2){


			 OVNALUnit * nalu= (*pu3)->nalus[i];
	    	    enum OVNALUType nalu_type = nalu->type;


if(nalu_type== OVNALU_VPS||nalu_type== OVNALU_SPS||nalu_type== OVNALU_PPS
		||nalu_type== OVNALU_PH ||nalu_type== OVNALU_SUFFIX_APS ||nalu_type==OVNALU_PREFIX_APS||nalu_type== OVNALU_PREFIX_SEI ||nalu_type==OVNALU_SUFFIX_SEI||nalu_type==OVNALU_AUD
		)   {
    	        ret9[0]= nvcl_decode_nalu_hls_data(nvcl_ctx[0], nalu);

    	       }

else{
    	        ret9[0]=ret8[0];
    	    }

     }}
	else {ret9[0]=ret8[0];}
}
