/*
	============================================================================
	Name        : hello_world.h
	Author      : dgageot
	Version     : 1.0
	Copyright   : CECILL-C, IETR, INSA Rennes
	Description : Prototype for the hello world application.
	============================================================================
*/

#ifndef	HELLO_WORLD_H
#define	HELLO_WORLD_H

#include "preesm.h"

/**
 * Generate a given amount of tokens.
 * Output stream is a sequence of natural value {0, 1, ..., nbTokens-1} bounded in a byte.
 * @param nbTokens Number of tokens to produce.
 * @param output Output stream (outputs nbTokens bytes).
 */
void generateTokens(int nbTokens, OUT uchar* output);

/**
 * Print the value of input tokens and move the value on the output.
 * @param input Input stream (expects 1 byte).
 * @param output Output stream (outputs 1 byte).
 */
void helloWorld(uchar* input, uchar* output);

/**
 * Verify that the input sequence is valid i.e. values are ordered naturally.
 * @param nbTokens Number of tokens produced.
 * @param input Input stream (expects nbTokens bytes).
 */
void verifyTokens(int nbTokens, IN uchar* input);

#endif /* HELLO_WORLD_H */
