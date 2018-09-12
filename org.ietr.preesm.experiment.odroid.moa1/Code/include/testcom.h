/*
	============================================================================
	Name        : testComSources.h
	Author      : mpelcat
	Version     :
	Copyright   : Application specific function prototypes
	Description :
	============================================================================
*/

#ifndef TESTCOMSOURCE_H_
#define TESTCOMSOURCE_H_

#include "preesm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void sensor_init(int size, int N, int stressN);
void sensor2_init(int size, int stressN);
void parallel_init(int size, int stressN);
void gen_int_init(int size, int stressN);
void copy_init(int size, int stressN);
void actuator_init(int size, int N, int stressN);
void circular_init(int size, int stressN);
void circular6_init(int size, int stressN);

void sensor(char* o1, char* o2, char* o3, char* o4, char* o5, char* o6, char* o7, char* o8, char* op, int size, int N, int stressN);
void sensor2(char* o1, int size, int stressN);
void parallel(char* i1, char* o1, int size, int stressN);
void parallel2(char* i1, char* i2, char* o1, int size, int stressN);
void gen_int(char* i1,char* i2,char* o1,char* o2, int size, int stressN);
void copy(char* i1, char* o1, int size, int stressN);
void circular(char* i1, char* i2, char* o1, char* o2, int size, int stressN);
void circular6(char* i1, char* o1, int size, int stressN);
void actuator(char* i1,char* i2,char* i3, char* i4,char* i5,char* i6, char* i7,char* i8,char* ip, int size, int N, int stressN);
#endif
