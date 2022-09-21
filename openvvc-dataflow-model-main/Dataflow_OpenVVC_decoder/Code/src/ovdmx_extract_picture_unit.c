#include "ovdmx_extract_picture_unit.h"
void extract_picture(OVVCHdl *in_ovvc_hdl1, OVPictureUnit **pu1, int *ret, int *in_ret4 , int *index)
{

	static OVPictureUnit * previousPu = NULL;
	if (previousPu != NULL) {
		ov_free_pu(&previousPu);
	}
//#if 0
 //  ovdmx_read_stream(dmx);
 //  #else
	    OVVCDmx *const dmx = in_ovvc_hdl1->dmx;
	    static	int nb_boucle1 =0;
	    if (in_ret4[0]>=0){
	    	nb_boucle1++;
	    ret[0] = ovdmx_extract_picture_unit(dmx, pu1);
	    previousPu = *pu1;
	    	}

//#endif

}
