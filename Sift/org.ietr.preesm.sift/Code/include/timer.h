#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>

#ifdef _WIN32
#include <windows.h>
#if !defined(_WINSOCK2API_) && !defined(_WINSOCKAPI_)
/*struct timeval {
    long tv_sec;
    long tv_usec;
};*/
#endif
#else//_WIN32
#include <sys/time.h>
#endif//_WIN32

typedef struct Timer_t {
#ifdef _WIN32
    LARGE_INTEGER start_time;
    LARGE_INTEGER finish_time;
#else//_WIN32
    struct timeval start_time;
    struct timeval finish_time;
#endif//_WIN32
} Timer;

void start_timer(Timer *tmr);
void stop_timer(Timer *tmr);
float get_timer_interval(Timer *tmr);

#endif//_TIMER_H_
