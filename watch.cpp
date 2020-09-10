#include "watch.h"

// Stopwatch
Stopwatch::Stopwatch() {
	elapsed = 0;
	startTime = 0;
}
Stopwatch::~Stopwatch() {}

void Stopwatch::start() {
	startTime = clock();
}

void Stopwatch::stop() {
	elapsed = clock() - startTime;
}

void Stopwatch::reset() {
	elapsed = 0;
	startTime = 0;
}

void Stopwatch::restart() {
	reset();
	start();
}

clock_t Stopwatch::getElapsed() {
	return elapsed;
}

clock_t Stopwatch::getDay() {
	return elapsed / DAY;;
}

clock_t Stopwatch::getHour() {
	clock_t auxElapsed = elapsed;
	auxElapsed = auxElapsed % DAY;
	return auxElapsed / HOUR;
}

clock_t Stopwatch::getMinute() {
	clock_t auxElapsed = elapsed;
	auxElapsed = auxElapsed % DAY;
	auxElapsed = auxElapsed % HOUR;
	return auxElapsed / MINUTE;
}

clock_t Stopwatch::getSecond() {
	clock_t auxElapsed = elapsed;
	auxElapsed = auxElapsed % DAY;
	auxElapsed = auxElapsed % HOUR;
	auxElapsed = auxElapsed % MINUTE;
	return auxElapsed / SECOND;
}

clock_t Stopwatch::getMillisecond() {
	clock_t auxElapsed = elapsed;
	auxElapsed = auxElapsed % DAY;
	auxElapsed = auxElapsed % HOUR;
	auxElapsed = auxElapsed % MINUTE;
	auxElapsed = auxElapsed % SECOND;
	return auxElapsed;
}

// Timer
Timer::Timer(clock_t interval) {
	startTime = 0;
	this->interval = interval;
}

Timer::~Timer() {}

void Timer::start() {
	startTime = clock();
}

bool Timer::timeout() {
	if (clock() - startTime > interval) {
		startTime = clock();
		return true;
	}
	return false;
}
