#pragma once
#include "allStaticLib.h"

struct ITimer {
private:
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
public:
	ITimer(float speed);
	~ITimer();
	bool update();
	void setSpeed(float speed);
	int64_t getTimerCount();
};




