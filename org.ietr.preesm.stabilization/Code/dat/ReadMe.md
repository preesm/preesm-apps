# Resource location
This readme lists the binary resources that are (commonly) needed to run the project.

* [`arial.ttf`](http://www.font-police.com/classique/sans-serif/arial.ttf): Font used in order to display fps information of the application.
* Video to stabilize:
  - A good source of shaky video: https://www.reddit.com/r/ImageStabilization/
    - Make sure the camera movement are only vertical and horizontal translations as the proposed algorithm does not correct camera rotations.
	- Our personal favorites: 
	  - http://i.imgur.com/WMqwno7.mp4
	  - https://gfycat.com/fr/gifs/detail/GivingScholarlyFallowdeer
  - Convert the video into the yuv format using [ffmpeg] (https://ffmpeg.org):
    `ffmpeg -i <inputVideo.avi> -vf scale=<outputWidth>:<outputHeight> -c:v rawvideo -pix_fmt yuv420p <outputVideo.yuv>` 
  -	Make sure you set the appropriate video parameters in applicationParameters.h (parameters for our favorite video (resized) are already given)