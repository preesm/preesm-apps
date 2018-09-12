/*
	============================================================================
	Name        : testComSources.c
	Author      : mpelcat
	Version     : 1.0
	Copyright   : CECILL-C
	Description : Dummy functions called by the communication tester project
	============================================================================
 */

#include "testcom.h"

#define STRESS_SIZE 5000
int sensorIncrement = 0;
int actuatorIncrement = 0;


void stress(int amount){

	int i = 0;
	volatile float fl = 1000000;

	for(i=0;i<amount;i++){
		fl = sqrtf(fl);
	}
}

void sensor_init(int size, int N, int stressN){

}

void sensor2_init(int size, int stressN){
}

void parallel_init(int size, int stressN){

}

void gen_int_init(int size, int stressN){

}

void copy_init(int size, int stressN){

}

void actuator_init(int size, int N, int stressN){

}

void circular_init(int size, int stressN){

}
void circular6_init(int size, int stressN){

}

void sensor(char* o1, char* o2, char* o3, char* o4, char* o5, char* o6, char* o7, char* o8, char* op, int size, int N, int stressN){
	//printf("sensor");
	// Generating dummy data
	int i = 0;

	for(i=0;i<size*N;i++){
		o8[i] = o7[i] = o6[i] = o5[i] = o4[i] = o3[i] = o2[i] = o1[i] = (i+sensorIncrement) & 0x7f; // %128
	}

	for(i=0;i<size;i++){
		op[i] = i & 0x7f; // %128
	}

	for(i=0;i<stressN;i++)
		stress(STRESS_SIZE);
	sensorIncrement++;
}

// Managing 5*size data
void sensor2(char* o1, int size, int stressN){
	//printf("sensor");
	// Generating dummy data
	int i = 0;

	for(i=0;i<5*size;i++){
		o1[i] = (-i) & 0x7f; // %128
	}
	for(i=0;i<stressN;i++)
		stress(STRESS_SIZE);
}

// Managing 5*size data
void parallel(char* i1, char* o1, int size, int stressN){
	//printf("parallel");
	int i = 0;

	for(i=0;i<5*size;i++){
		o1[i] = i1[i];
	}
	for(i=0;i<stressN;i++)
		stress(STRESS_SIZE);
}

// Managing 5*size data
void parallel2(char* i1, char* i2, char* o1, int size, int stressN){
	//printf("parallel");
	int i = 0;

	for(i=0;i<5*size;i++){
		o1[i] = i1[i];
	}
	for(i=0;i<stressN;i++)
		stress(STRESS_SIZE);
}

// gen_int is 3x longer than others
void gen_int(char* i1,char* i2,char* o1,char* o2, int size, int stressN){
	//printf("gen_int");
	int i = 0;

	for(i=0;i<size;i++){
		o1[i] = i1[i];
		o2[i] = i2[i];
	}
	for(i=0;i<3*stressN;i++)
		stress(STRESS_SIZE);
}

void copy(char* i1, char* o1, int size, int stressN){
	//printf("copy");
	int i = 0;

	for(i=0;i<size;i++){
		o1[i] = i1[i];
	}
	for(i=0;i<stressN;i++)
		stress(STRESS_SIZE);
}

void circular(char* i1, char* i2, char* o1, char* o2, int size, int stressN){
	//printf("circular");
	int i = 0;

	for(i=0;i<size;i++){
		o1[i] = i1[i];
		o2[i] = i2[i];
	}
	for(i=0;i<stressN;i++)
		stress(STRESS_SIZE);
}
void circular6(char* i1, char* o1, int size, int stressN){
	//printf("circular6");
	int i = 0;

	for(i=0;i<size;i++){
		o1[i] = i1[i];
	}
	for(i=0;i<stressN;i++)
		stress(STRESS_SIZE);
}


// Managing 5*size data on ip
void actuator(char* i1,char* i2,char* i3, char* i4,char* i5,char* i6, char* i7,char* i8,char* ip, int size, int N, int stressN){
	//printf("actuator");
	// Testing dummy data
	int i = 0;
	int bSuccess = 1;

	for(i=0;i<size;i++){
		if(i1[i] != (char)((i + actuatorIncrement) & 0x7f)){ // %128
			bSuccess = 0;
			break;
		}
		if(i2[i] != (char)((i + actuatorIncrement) & 0x7f)){
			bSuccess = 0;
			break;
		}
		if(i3[i] != (char)((i + actuatorIncrement) & 0x7f)){
			bSuccess = 0;
			break;
		}
		if(i4[i] != (char)((i + actuatorIncrement) & 0x7f)){
			bSuccess = 0;
			break;
		}
		if(i5[i] != (char)((i + actuatorIncrement) & 0x7f)){
			bSuccess = 0;
			break;
		}
		if(i6[i] != (char)((i + actuatorIncrement) & 0x7f)){
			bSuccess = 0;
			break;
		}
		if(i7[i] != (char)((i + actuatorIncrement) & 0x7f)){
			bSuccess = 0;
			break;
		}
		if(i8[i] != (char)((i + actuatorIncrement) & 0x7f)){
			bSuccess = 0;
			break;
		}
	}

	for(i=0;i<5*size;i++){
		if(ip[i] != (char)((-i) & 0x7f)){
			bSuccess = 0;
			break;
		}
	}

	for(i=0;i<stressN;i++)
		stress(STRESS_SIZE);
	actuatorIncrement++;

	if(bSuccess){
		printf("Actuator received the right data\n");
	}else{
		printf("Failure\n");
		exit(-1);
	}
}


