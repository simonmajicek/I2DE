#pragma once
#include "allStaticLib.h"

struct ITimer {
private:
	ALLEGRO_EVENT_QUEUE* event_queue = {NULL};
	ALLEGRO_TIMER* timer = {NULL};
public:
	ITimer();
	~ITimer();
	void run(float speed = 1.0f);
	bool update();
	void setSpeed(float speed);
	void setTimerCount(int64_t count);
	int64_t getTimerCount();
};




