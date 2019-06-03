/*	Copyright (c) 2013, Robert Wang, email: robertwgh (at) gmail.com
	All rights reserved. https://sourceforge.net/p/ezsift

	Description:Detect keypoints and extract descriptors from two input images.
				Then, match features from two images using brute-force method.

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

using namespace std;

#define USE_FIX_FILENAME 0
int main(int argc, char ** argv)
{
#if USE_FIX_FILENAME
	char * file1 = "img1.pgm";
	char * file2 = "img2.pgm";
#else
	if (argc != 3)
	{
		printf("Please input two image filenames.\n");
		printf("usage: image_match img1 img2\n");
		return -1;
	}
	char file1[255];
	char file2[255];
	memcpy(file1, argv[1], sizeof(char) * strlen(argv[1]));
	file1[strlen(argv[1])] = 0;
	memcpy(file2, argv[2], sizeof(char) * strlen(argv[2]));
	file2[strlen(argv[2])] = 0;
#endif

	struct Timer my_timer;
	start(&my_timer);

	// Read two input images
	ImageObj<unsigned char> * image1 = CreateImage<unsigned char>();
	ImageObj<unsigned char> * image2 = CreateImage<unsigned char>();
	if(read_pgm<unsigned char>(image1, file1) != 0)
	{
		printf("Failed to open input image1!\n");
		return -1;
	}

	if(read_pgm<unsigned char>(image2, file2) != 0)
	{
		printf("Failed to open input image2!\n");
		return -1;
	}
	printf("Image 1 loaded. Image size: %d x %d\n", image1->w, image1->h);
	printf("Image 2 loaded. Image size: %d x %d\n", image2->w, image2->h);

	// Detect keypoints
	struct OrderedList<struct SiftKeypoint> * kpt_list1 = CreateOrdList<struct SiftKeypoint>(SIFT_MAX_KEYPOINTS);
	struct OrderedList<struct SiftKeypoint> * kpt_list2 = CreateOrdList<struct SiftKeypoint>(SIFT_MAX_KEYPOINTS);
	printf("\nSIFT detection on image 1 ...\n");
	sift_cpu(image1, kpt_list1, true);
	printf("# keypoints in image1: %d\n", getSize(kpt_list1));
	
	printf("\nSIFT detection on image 2 ...\n");
	sift_cpu(image2, kpt_list2, true);
	printf("# keypoints in image2: %d\n", getSize(kpt_list2));

	// Save keypoint list, and draw keypoints on images.
	char filename[255];
	sprintf(filename, "s_A_keypoints.ppm");
	draw_keypoints_to_ppm_file(filename, image1, kpt_list1);
	export_kpt_list_to_file("s_A_keypoints.key", kpt_list1, true);

	sprintf(filename, "s_B_keypoints.ppm");
	draw_keypoints_to_ppm_file(filename, image2, kpt_list2);
	export_kpt_list_to_file("s_B_keypoints.key", kpt_list2, true);

	// Match keypoints.
	struct OrderedList<struct MatchPair> * match_list = CreateOrdList<struct MatchPair>(SIFT_MAX_KEYPOINTS);
	match_keypoints(kpt_list1, kpt_list2, match_list);

	// Draw result image.
	sprintf(filename, "s_A_B_matching.ppm");
	draw_match_lines_to_ppm_file(filename, image1, image2, match_list);
	printf("# of matched keypoints: %d\n", getSize(match_list));

	release<unsigned char>(image1);
	release<unsigned char>(image2);
	release<struct SiftKeypoint>(kpt_list1);
	release<struct SiftKeypoint>(kpt_list2);
	release<struct MatchPair>(match_list);
	fprintf(stderr, "\nTotal time: \t%f (ms)\n", stop_get(&my_timer));


	//fprintf(stderr, "Size of a match pair: %zu\n", sizeof(struct MatchPair));
	
	return 0;
}
