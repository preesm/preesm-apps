//#include "ovdec_submit_picture_unit.h"
#include "slice_selection.h"
int submit(OVVCHdl *in_ovvc_hdl2, OVPictureUnit **in_pu, int *in_ret, int *out_ret ,  int *in, OVPictureUnit **out_pu , int iter2 , OVNVCLReader *out_rdr,  OVNVCLCtx ** out_nvcl_ctx, OVSliceDec **out_sldec)
{
	 OVVCDec *const dec =  in_ovvc_hdl2->dec;
	 //out_nvcl_ctx[0]= &dec->nvcl_ctx;
	 *out_nvcl_ctx= &dec->nvcl_ctx;

	 if(in_ret[0]>=0)
	 {
  int i= in[0];

if(i<iter2){

    	    OVNALUnit * nalu= (*in_pu)->nalus[i];
    	    enum OVNALUType nalu_type = nalu->type;


    	    nvcl_reader_init(out_rdr, nalu->rbsp_data, nalu->rbsp_size);

    	    /* FIXME properly read NAL Unit header */
    	    nvcl_skip_bits(out_rdr, 16);

    		if(nalu_type== OVNALU_TRAIL || nalu_type== OVNALU_STSA|| nalu_type== OVNALU_RADL || nalu_type== OVNALU_RASL || nalu_type== OVNALU_IDR_W_RADL || nalu_type== OVNALU_IDR_N_LP || nalu_type== OVNALU_CRA || nalu_type== OVNALU_GDR )
    		{

    	        out_ret[0]= nvcl_decode_nalu_sh(out_rdr, out_nvcl_ctx[0], nalu_type);

    	        if (out_ret[0]>=0){

    	        	  out_sldec [0]= ovdec_select_subdec(dec);

    	        	            uint32_t nb_sh_bytes = nvcl_nb_bytes_read(out_rdr);
    	        	out_ret[0]= init_vcl_decoder(dec, out_sldec[0],out_nvcl_ctx[0], nalu, nb_sh_bytes);



	            if (out_ret[0]< 0) {
	            	slicedec_finish_decoding(out_sldec[0]);



	            	 if (dec->subdec_list[0]->pic) {
	            	        ovdpb_unref_pic(dec->subdec_list[0]->pic, ~0);
	            	    }

	           }}
    	     }
    	        else {

    	        	out_ret[0]=in_ret[0];


    	            }

    	       }}
	 else {out_ret[0]=in_ret[0];

	 }



	*out_pu=*in_pu;

return 0;

}
