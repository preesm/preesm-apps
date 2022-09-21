#include "tile_decoding.h"
void slice(OVVCHdl *in_ovvc_hdl3, int *in_ret , int *out_ret , OVPictureUnit **in_pu , int *i2 ,OVPictureUnit **out_pu, int iter2, int *number,OVSliceDec **in_sldec , int tiles_number){
if (in_ret[0]>=0)  {
	int i5= i2[0];
//	if(i<iter2){

		OVVCDec *const dec =  in_ovvc_hdl3->dec;
	  OVNALUnit * nalu= (*in_pu)->nalus[i5];
	    	    enum OVNALUType nalu_type = nalu->type;
	if(nalu_type== OVNALU_TRAIL || nalu_type== OVNALU_STSA || nalu_type== OVNALU_RADL || nalu_type== OVNALU_RASL || nalu_type== OVNALU_IDR_W_RADL
			|| nalu_type== OVNALU_IDR_N_LP || nalu_type== OVNALU_CRA || nalu_type== OVNALU_GDR ){


         int i=number[0];


        	int thread_idx = i % in_sldec[0]->nb_entry_th;
            out_ret[0] = slicedec_decode_rect_entry(in_sldec[0], in_sldec[0]->ctudec_list[thread_idx], in_sldec[0]->active_params, i);

            if(i==tiles_number-1){
                slicedec_finish_decoding(in_sldec[0]);
            out_ret[0]=0;}
    	       }

	//else {out_ret[0]=in_ret[0];}

    // }
}
else {out_ret[0]=in_ret[0];}
*out_pu=*in_pu;
}
