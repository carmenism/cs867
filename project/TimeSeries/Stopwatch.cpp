#include "Stopwatch.h"

Stopwatch::Stopwatch() {
	state = NotStarted;
}

Stopwatch::~Stopwatch() {

}

WORD Stopwatch::getCurrentTime() {
    SYSTEMTIME time;
    GetSystemTime(&time);
    WORD millis = (time.wHour * 60 * 60 * 1000) // 60min/hour 60s/min 1000ms/s
        + (time.wMinute * 60 * 1000) // 60s/min 1000ms/s
        + (time.wSecond * 1000) // 1000ms/s
        + time.wMilliseconds;

    return millis;
}

void Stopwatch::start() {
	state = Started;
    startTime = getCurrentTime();
}

double Stopwatch::stop() {
    double retval = -1;

    if (state == Started) {
        WORD currentTime = getCurrentTime();
        WORD diff = currentTime - startTime;    

        retval = ((double) diff) / 1000.0;
    } 

	state = Stopped;

	return retval;
}