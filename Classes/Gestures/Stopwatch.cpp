#include "Stopwatch.h"

void StopWatch::Start() {
	_elapsedSeconds = 0;
	//this->schedule(schedule_selector(StopWatch::UpdateTimer), 0.001f);
}

void StopWatch::UpdateTimer(float dt) {
	_elapsedSeconds += dt;
}

void StopWatch::Stop() {
	//this->unschedule(schedule_selector(StopWatch::UpdateTimer));
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
