#ifndef __TIME_CLASS_H__
#define __TIME_CLASS_H__

#include <ctime>

/* 
	Manager that keeps track of time-related thingies.
*/
class Time {

	public:
		static double time;
		static double deltaTime;

		static void Start();
		static void Update();
		static void Reset();


	private:
		static clock_t timeProgramStarted;
		static double timeLastFrame;
};

#endif