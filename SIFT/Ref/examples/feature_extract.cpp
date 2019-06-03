/*	Copyright (c) 2013, Robert Wang, email: robertwgh (at) gmail.com
	All rights reserved. https://sourceforge.net/p/ezsift

	Description: Detect keypoints and extract descriptors from an input image.

	Revision history:
		September, 15, 2013: initial version.
*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "timer.h"

#include "ezsift.h"

#define USE_FIX_FILENAME	0
int main(int argc, char ** argv)
{

#if USE_FIX_FILENAME
	char *file1 = "img1.pgm";
#else
	if (argc != 2)
	{
		printf("Please input an input image name.\n");
		printf("usage: feature_extract img\n");
		return -1;
	}
	char file1[255];
	memcpy(file1, argv[1], sizeof(char) * strlen(argv[1]));
	file1[strlen(argv[1])] = 0;
#endif

	struct Timer my_timer;
	start(&my_timer);
	
	ImageObj<unsigned char> * image = CreateImage<unsigned char>();	
	//if(read_pgm(file1, image->data, image->w, image->h)!=0)
	if(read_pgm<unsigned char>(image, file1)!=0)
	{
		printf("Failed to open input image!\n");
		return -1;
	}
	printf("image size: %d x %d\n", image->w, image->h);

	bool bExtractDescriptor = true;
	
	struct OrderedList<struct SiftKeypoint> * kpt_list = CreateOrdList<struct SiftKeypoint>(SIFT_MAX_KEYPOINTS);

	// Perform SIFT computation on CPU.
	printf("Start SIFT detection ...\n");
	sift_cpu(image, kpt_list, bExtractDescriptor);

	// Generate output image with keypoints drawing
	char filename[255];
	sprintf(filename, "%s_psift_output.ppm", file1);
	draw_keypoints_to_ppm_file(filename, image, kpt_list);

	// Generate keypoints list
	sprintf(filename, "%s_psift_key.key", file1);
	export_kpt_list_to_file(filename, kpt_list, bExtractDescriptor);

	printf("\n");
	printf("Total keypoints number: \t\t %d\n", getSize(kpt_list));

	release<unsigned char>(image);
	release<struct SiftKeypoint>(kpt_list);
	fprintf(stderr, "\nTotal time: \t%f (ms)\n", stop_get(&my_timer));


	//fprintf(stderr, "Size of a keypoint: %zu\n", sizeof(struct SiftKeypoint));
	
	return 0;
}
