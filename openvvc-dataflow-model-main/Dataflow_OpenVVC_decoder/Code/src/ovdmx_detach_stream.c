
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "ovdec.h"
#include "ovdefs.h"
#include "ovdmx.h"
#include "ovframe.h"
#include "ovutils.h"
#include "ovversion.h"
#include "ovdmx_detach_stream.h"
//void
//void
static uint32_t write_decoded_frame_to_file(OVFrame *const frame, FILE *fp){
  uint8_t component = 0;
  uint32_t ret = 0;
  for(component=0; component<3; component++){
    uint32_t frame_size = frame->height[component] * frame->linesize[component];
    ret +=fwrite(frame->data[component], frame_size, sizeof(uint8_t), fp);
  }
  return ret;
}
void detach (OVVCHdl *ovvc_hdl4 , int *nb_pic2){


	int nb_pic = nb_pic2[0];
	int ret=1;
		FILE *fout;
	OVVCDec *const dec =  ovvc_hdl4->dec;
	fout = fopen("/dev/null", "ab+");

			   if (fout == NULL) {
			     ov_log(NULL, OVLOG_ERROR, "Failed to open output file '%s'.\n", "/dev/null");


			   }
			//  else {
			  //   ov_log(NULL, OVLOG_INFO, "Decoded stream will be written to '%s'.\n", "cac.yuv");

			 //  }
		    while (ret > 0) {
		        OVFrame *frame = NULL;
		        ret = ovdec_drain_picture(dec, &frame);
		        if (frame) {
		            ov_log(NULL, OVLOG_TRACE, "Draining decoder\n");
		            if (fout) {
		                write_decoded_frame_to_file(frame, fout);
		                ++nb_pic;
		            }

		            ov_log(NULL, OVLOG_TRACE, "Draining last pictures with POC: %d\n", frame->poc);
		            ovframe_unref(&frame);
		        }
		    }

		    ov_log(NULL, OVLOG_INFO, "Decoded %d pictures\n", nb_pic);



	ovdmx_detach_stream(ovvc_hdl4->dmx);
	//fclose(fout);

    }
