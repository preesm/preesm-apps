/*
	============================================================================
	Name        : communication.h
	Author      : kdesnos
	Version     : 2.0
	Copyright   : CECILL-C
	Description : Communication primitive for Preesm Codegen.
                  Currently, primitives were tested only for x86, shared_mem
                  communications.
	============================================================================
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/**
* Initialize the semaphores used for inter-core synchronization.
*/
void communicationInit();

/**
* Non-blocking function called by the sender to signal that a buffer is ready
* to be sent.
* 
* @param[in] senderID
*        the ID of the sender core
* @param[in] coreID
*        the ID of the receiver core
*/
void sendStart(int senderID, int receveirID);

/**
* Blocking function (not for shared_mem communication) called by the sender to
* signal that communication is completed.
*/
void sendEnd();

/**
* Non-blocking function called by the receiver begin receiving the
* data. (not implemented with shared memory communications).
*/
void receiveStart();

/**
* Blocking function called by the sender to wait for the received data 
* availability.
*
* @param[in] senderID
*        the ID of the sender core
* @param[in] coreID
*        the ID of the receiver core
*/
void receiveEnd(int senderID, int receveirID);

#endif
