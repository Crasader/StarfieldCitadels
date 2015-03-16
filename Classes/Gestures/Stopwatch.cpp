#include "Stopwatch.h"

void StopWatch::Start() {
	_elapsedSeconds = 0;
	this->schedule(schedule_selector(StopWatch::Update), 0.001);
}

void StopWatch::Update(float dt) {
	_elapsedSeconds += dt;
}

void StopWatch::Stop() {
	this->unschedule(schedule_selector(StopWatch::Update));
}

void StopWatch::Reset() {
	_elapsedSeconds = 0;
}

void StopWatch::Continue() {
	_elapsedSeconds = 0;
}

float StopWatch::GetSeconds() {
   return _elapsedSeconds;
}
