#pragma once

#include <time.h>

#define MILLISECOND 1
#define SECOND (1000 * MILLISECOND)
#define MINUTE (60 * SECOND)
#define HOUR (60 * MINUTE)
#define DAY (24 * HOUR)

class Stopwatch {
private:
	clock_t elapsed;

	clock_t startTime;

public:
	Stopwatch();
	~Stopwatch();

	void start();

	void stop();
	void reset();
	void restart();

	clock_t getElapsed();
	clock_t getDay();
	clock_t getHour();
	clock_t getMinute();
	clock_t getSecond();
	clock_t getMillisecond();
};

class Timer {
private:
	clock_t startTime;
	clock_t interval;

public:
	Timer(clock_t);
	~Timer();

	void start();
	bool timeout();
};
