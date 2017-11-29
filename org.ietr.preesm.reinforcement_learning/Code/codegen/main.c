/**
 * @file main.c
 * @generated by CPrinter
 * @date Wed Nov 29 22:55:58 CET 2017
 *  
 */


#include "x86.h"

// Declare computation thread functions
void *computationThread_Core0(void *arg);

pthread_barrier_t iter_barrier;
int stopThreads;


int main(void)
{

  // Declaring thread pointers
  pthread_t threadCore0;

  #ifdef VERBOSE
  printf("Launched main\n");
  #endif

  // Creating a synchronization barrier
  stopThreads = 0;
  pthread_barrier_init(&iter_barrier, NULL, 1);

  communicationInit();

  // Creating threads
  pthread_create(&threadCore0, NULL, computationThread_Core0, NULL);

  // Waiting for thread terminations
  pthread_join(threadCore0,NULL);

  #ifdef VERBOSE
    printf("Press any key to stop application\n");
  #endif

  // Waiting for the user to end the procedure
  getchar();
  exit(0);
}

