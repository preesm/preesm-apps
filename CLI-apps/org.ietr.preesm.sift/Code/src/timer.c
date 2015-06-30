#include "timer.h"

#ifdef _WIN32
int
gettimeofday(struct timeval* tv, int t) {
    union {
        long long ns100;
        FILETIME ft;
    } now;

    GetSystemTimeAsFileTime(&now.ft);
    tv->tv_usec = (long) ((now.ns100 / 10LL) % 1000000LL);
    tv->tv_sec = (long) ((now.ns100 - 116444736000000000LL) / 10000000LL);
    return (0);
}// gettimeofday()
#endif//_WIN32

void
start_timer(Timer* tmr) {
#ifdef _WIN32
    QueryPerformanceCounter((LARGE_INTEGER*)&tmr->start_time);
#else//_WIN32
    gettimeofday(&tmr->start_time, 0);
#endif//_WIN32
}// start_timer()

void
stop_timer(Timer* tmr) {
#ifdef _WIN32
    QueryPerformanceCounter((LARGE_INTEGER*)&tmr->finish_time);
#else//_WIN32
    gettimeofday(&tmr->finish_time, 0);
#endif//_WIN32
}// stop_timer()

float
get_timer_interval(Timer* tmr) {
    float interval = 0.0f;
#ifdef _WIN32
    static int freq_set = 0;
    static double freq  = 0.0;
    if (freq_set == 0) {
        LARGE_INTEGER tmp;
        QueryPerformanceFrequency((LARGE_INTEGER*)&tmp);
        freq = (double)tmp.QuadPart/1000.0;
    }// if (freq_set == 0)
    interval = (float)((double)(tmr->finish_time.QuadPart
                                - tmr->start_time.QuadPart)
                       / freq);
#else
    // time difference in milli-seconds
    interval = (1000.0f*( tmr->finish_time.tv_sec - tmr->start_time.tv_sec)
                +(0.001f*(tmr->finish_time.tv_usec - tmr->start_time.tv_usec)));
#endif//_WIN32
    return interval;
}// get_timer_interval()
