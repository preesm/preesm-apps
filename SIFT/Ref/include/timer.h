/*	Copyright (c) 2013, Robert Wang, email: robertwgh (at) gmail.com
	All rights reserved. https://sourceforge.net/p/ezsift

	Part of "timer.h" code referred to code here: https://sites.google.com/site/5kk73gpu2011/

	Revision history:
		September, 15, 2013: initial version.
*/

#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#include <sys/time.h>


struct Timer
{
	struct timeval start_time;
	struct timeval finish_time;
};



struct Timer * CreateTimer()
{
  return (struct Timer *) malloc(sizeof(struct Timer));
}

void start(struct Timer * tmr)
{
  gettimeofday(&(tmr->start_time), NULL);
}

void stop(struct Timer * tmr)
{
  gettimeofday(&(tmr->finish_time), NULL);
}

float get_time(struct Timer * tmr)
{
	double interval = 0.0;
	interval = (double) (1000.0 * (tmr->finish_time.tv_sec - tmr->start_time.tv_sec)
		+(0.001 * (tmr->finish_time.tv_usec - tmr->start_time.tv_usec)));
	return interval;
}

double stop_get(struct Timer * tmr)
{
	double interval;
	stop(tmr);
	interval = get_time(tmr);

	return interval;
}

// Stop the timer, get the time interval, then start the timer again.
double stop_get_start(struct Timer * tmr)
{
	double interval;
	stop(tmr);
	interval = get_time(tmr);
	start(tmr);

	return interval;
}


#endif//_TIMER_H_
