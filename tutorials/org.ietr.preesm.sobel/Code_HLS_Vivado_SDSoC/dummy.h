#ifndef DUMMY_H
#define DUMMY_H

#include "preesm.h"

// Dummy function to replace display operations using SDL library
/*
 * The function can be used to save some output frame (or the whole video)
 * 
 * */
void dummy(int id, IN unsigned char *y, IN unsigned char *u, IN unsigned char *v);

#endif
