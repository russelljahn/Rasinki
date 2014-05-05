
#include "Time.h"

double Time::time = 0;
double Time::deltaTime = 0;
clock_t Time::timeProgramStarted = 0;
double Time::timeLastFrame = 0;

void Time::Start() {
	timeProgramStarted = clock();
}

void Time::Update() {
	double currentTime = ((double)(clock()-timeProgramStarted))/CLOCKS_PER_SEC;
	Time::deltaTime = currentTime - Time::timeLastFrame;

	Time::timeLastFrame = Time::time;
	time = currentTime;
}

void Time::Reset() {
	Time::time = 0;
	Time::deltaTime = 0;
	Time::timeProgramStarted = clock();
	Time::timeLastFrame = 0;
}
