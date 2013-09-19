#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
	state = NotStarted;
}

double Stopwatch::getCurrentTime() {
    SYSTEMTIME time;
    GetSystemTime(&time);
    WORD millis = (time.wDay * 24 * 60 * 60 * 1000)
        + (time.wHour * 60 * 60 * 1000) 
        + (time.wMinute * 60 * 1000) 
        + (time.wSecond * 1000) 
        + time.wMilliseconds;

    return ((int) millis / 1000.0);
}

void Stopwatch::start()
{
	state = Started;
    startTime = getCurrentTime();
}

double Stopwatch::read()
{
    if (state == Started) {
        return getCurrentTime() - startTime;
    }

	return -1;
}

double Stopwatch::stop()
{
    double retval = -1;

    if (state == Started) {
        retval = getCurrentTime() - startTime;    
    }

	state = Stopped;

	return retval;
}