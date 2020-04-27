/*
	============================================================================
	Name        : hello_world.c
	Author      : dgageot
	Version     : 1.0
	Copyright   : CECILL-C, IETR, INSA Rennes
	Description : Source for the hello world application.
	============================================================================
*/

#include "hello_world.h"
#include <stdlib.h>
#include <stdio.h>

void generateTokens(int nbTokens, uchar* output) {
	int i = 0;
	// Write a natural sequence in the output stream for nbTokens values.
	for (i = 0; i < nbTokens; ++i) {
		output[i] = i;
	}
}

void helloWorld(uchar* input, uchar* output) {
	printf("Tokens %d\n\r", *input);
	// Copy input token to output.
	*output = *input;
}

void verifyTokens(int nbTokens, uchar* input) {
	int i = 0;
	// Verify that the input sequence is well ordered i.e. it is a natural sequence.
	for (i = 0; i < nbTokens; ++i) {
		if (input[i] != i) {
			// ERROR! The sequence is not natural at all, warn and exit the program.
			fprintf(stderr, "Invalid tokens order!\n\r");
			exit(0);
		}
	}
	printf("Valid tokens order!\n\r");
}
