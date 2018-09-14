#include <stdio.h>
#include <stdlib.h>
#include "compare.h"

void compare(int width, int height, unsigned char *input1,
		unsigned char *input2) {
	unsigned char *c1 = input1 + width;
	unsigned char *c2 = input2 + width;
	int i, j;
	int areIdentical = 1;

	for (i = 2; i < height - 2; i++) {
		for (j = 2; j < width - 2; j++) {
			if (c1[j] != c2[j]) {
				areIdentical = 0;
				printf("(%d, %d)\n", j, i - 1);
			}
		}
		c1 += width;
		c2 += width;
	}
	if (areIdentical) {
		printf("Identical\n");
	}
}
