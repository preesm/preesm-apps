# ezSIFT: An easy-to-use stanalone SIFT library.


## Old version

Original URL: https://sourceforge.net/projects/ezsift/

Created on 9/16/2013.
Modified on 3/27/2015: re-organized the projects, use git to manage the code and project. 
The latest code can be pulled from here:
[git clone git://git.code.sf.net/p/ezsift/code ezsift-code](git clone git://git.code.sf.net/p/ezsift/code ezsift-code)


## New versions

Two versions have been recoded by Alexandre Honorat in 2018. 
In the root folder, just type ```make``` to compile naive sequential and parallel versions (with OpenMP) for Linux.
This generates two binaries for each versions:
- build/feature-extract, to detect keypoints on one image (in pgm format)
- build/image_match, to detect keypoints on two images and match them

The maximum number of detected keypoints is set in include/ezsift.h .

