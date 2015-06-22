#pragma one

// note: windows timer uses the QueryPerformanceCounter as std::chrono is inefficient in small time durations
// limited usage timer functions
// this version cannot call the same macro function again within the same scope
// TIMER_INIT - initialise the variables for the timer
// TIMER_START - 

#if _MSC_VER
#include "windows.h"
/** Use to init the clock */
#define TIMER_INIT \
    _LARGE_INTEGER frequency; \
    _LARGE_INTEGER t1,t2; \
    double elapsedTime; \
    QueryPerformanceFrequency(&frequency);

/** Use to start the performance timer */
#define TIMER_START QueryPerformanceCounter(&t1);

/** Use to stop the performance timer and output the result to the standard stream. Less verbose than \c TIMER_STOP_VERBOSE */
#define TIMER_STOP \
    QueryPerformanceCounter(&t2); \
    elapsedTime=(float)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart; \
    std::wcout << elapsedTime<<L" sec" << std::endl;
#define TIMER_STOP(LOOPS) \
    QueryPerformanceCounter(&t2); \
    elapsedTime=(float)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart; \
    std::wcout << elapsedTime<<L" sec" << std::endl; \
	std::wcout << elapsedTime/LOOPS << L" sec" << std::endl;

#define TIMER_INIT(t1,t2) \
    _LARGE_INTEGER frequency; \
    _LARGE_INTEGER t1,t2; \
    double elapsedTime; \
    QueryPerformanceFrequency(&frequency);

#define TIMER_START(t1,t2) QueryPerformanceCounter(&t1);

/** Use to stop the performance timer and output the result to the standard stream. Less verbose than \c TIMER_STOP_VERBOSE */
#define TIMER_STOP(t1,t2) \
    QueryPerformanceCounter(&t2); \
    elapsedTime=(float)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart; \
    std::wcout << elapsedTime<<L" sec" << std::endl;
#define TIMER_STOP(t1,t2,LOOPS) \
    QueryPerformanceCounter(&t2); \
    elapsedTime=(float)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart; \
    std::wcout << elapsedTime<<L" sec" << std::endl; \
	std::wcout << elapsedTime/LOOPS << L" sec" << std::endl;
#else
#include <chrono>
#define TIMER_INIT(t1__,t2__) \
	std::chrono::time_point<std::chrono::high_resolution_clock> t1__, t2__;

#define TIMER_START(t1__,t2__) \
	t1__ = std::chrono::high_resolution_clock::now();

#define TIMER_STOP(t1__,t2__,LOOPS) \
	t2__ = std::chrono::high_resolution_clock::now(); \
	std::cout << (double)std::chrono::duration_cast<std::chrono::microseconds>(t2__-t1__).count()/1000000.0 << " secs." << std::endl; \
	std::cout << (double)std::chrono::duration_cast<std::chrono::microseconds>(t2__-t1__).count()/1000000.0/LOOPS << " secs.  per item in loop" << std::endl;
/*
#include "sys/time.h"
#define TIMER_INIT(t1__,t2__) \
timeval t1__, t2__;
unsigned long long elapsedTime__;

#define TIMER_START(t1__,t2__) gettimeofday(&t1__, NULL);

//#define TIMER_STOP \
//	gettimeofday(&t2__, NULL); \
//    std::cout << (t2__.tv_usec - t1__.tv_usec) / 1000.0 << " usec.\n";
//elapsedTime__ = (t2__.tv_sec - t1__.tv_sec) * 1000.0;      // sec to ms \
//elapsedTime__ += (t2__.tv_usec - t1__.tv_usec) / 1000.0;   // us to ms \

#define TIMER_STOP(t1__,t2__,LOOPS) \
gettimeofday(&t2__, NULL); \
elapsedTime__ = (unsigned long long)(t2__.tv_usec - t1__.tv_usec); \
std::cout << elapsedTime__/1000  << " msec\n"; \
std::cout << elapsedTime__/1000/LOOPS << " msec per item in loop\n";
*/
#endif