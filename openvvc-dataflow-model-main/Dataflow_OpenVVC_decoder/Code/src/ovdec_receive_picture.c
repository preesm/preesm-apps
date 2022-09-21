#include "ovdec_receive_picture.h"
static uint32_t write_decoded_frame_to_file(OVFrame *const frame, FILE *fp){
  uint8_t component = 0;
  uint32_t ret = 0;
  for(component=0; component<3; component++){
    uint32_t frame_size = frame->height[component] * frame->linesize[component];
    ret +=fwrite(frame->data[component], frame_size, sizeof(uint8_t), fp);
  }
  return ret;
}
void receive(OVVCHdl *ovvc_hdl3, int *ret2,int *ret5, int *ret4 , int *nb_pic2)
{
ret4[0]=ret5[0];
	 FILE *fout = NULL;
static	int nb_pic =0;
static	int nb_boucle2 =0;
    int nb_pic3;
	OVVCDec *const dec =  ovvc_hdl3->dec;
	OVFrame *frame = NULL;
	if(ret2[0]>=0 && ret5[0]>=0)
	{

	//************recuperer le nom de fichier output**************
	//*********************************************************************************

		   fout = fopen("/dev/null", "ab+");

		   if (fout == NULL) {
		     ov_log(NULL, OVLOG_ERROR, "Failed to open output file '%s'.\n", "/dev/null");


		   }
		   else {
		    // ov_log(NULL, OVLOG_INFO, "Decoded stream will be written to '%s'.\n", "cac.yuv");

		   }
      //  }

//****************************************************************************************
//******************************************************************************************
	  do {
		  frame = NULL;
		  nb_pic3 = ovdec_receive_picture(dec, &frame);
		  nb_boucle2++;

	                /* FIXME use ret instead of frame */
	                if (frame) {
	                    if (fout) {
	                        write_decoded_frame_to_file(frame, fout);
	                        ++nb_pic;
	                    }

	                    ov_log(NULL, OVLOG_TRACE, "Received pic with POC: %d\n", frame->poc);
	                    ovframe_unref(&frame);
	                }
	            } while (nb_pic3 > 0);
	 }

   // ov_log(NULL, OVLOG_INFO, "Decoded %d pictures\n", nb_pic);

nb_pic2[0]=nb_pic;

}
