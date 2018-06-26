# Resource location
This readme lists the binary resources that are (commonly) needed to run the project.

* [`akiyo_cif`](http://preesm.sourceforge.net/downloads/akiyo_cif.7z): YUV video processed by the gaussian filter.
* [`DejaVuSans.ttf`](http://preesm.sourceforge.net/downloads/DejaVuSans.ttf): Font used in order to display fps information of the application.
* To test the appliction on other yuv sequences
	* place the sequence in the */dat/* folder
	* change the path and the number of frames specified in */include/readYUV.h*
	* change the parameters DISPLAY_W and DISPLAY_H in */include/displayYUV.h* (optional)
	* change the parameters width and height in */Algo/top_display* (optional)
	* run the workflow (optional)
	* launch the CMake (optional)
	* recompile the application.
* To convert a video into YUV format
> ffmpeg -i inputVideo.avi -vf scale=outputWidth:outputHeight -c:v rawvideo -pix_fmt yuv420p outputVideo.yuv
* To read a YUV file, you can use ffplay in command lines as follows
> ffplay -i video.yuv -video_size width:height
