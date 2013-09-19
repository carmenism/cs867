class Stopwatch;

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "Windows.h"

class Stopwatch
{
	public:
		enum State {NotStarted, Started, Stopped};
		Stopwatch();

		void start();
		double stop();
	protected:
		WORD startTime;
		State state;
		WORD getCurrentTime();
};

#endif