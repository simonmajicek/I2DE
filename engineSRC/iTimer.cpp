#include "iTimer.h"

ITimer::ITimer() {}

ITimer::~ITimer() {
	al_destroy_timer(this->timer);
}

void ITimer::run(float speed) {
	if (this->timer) {	//reset timeru
		this->setSpeed(speed);
		this->setTimerCount(0);
	}
	else {
		this->timer = al_create_timer(speed);
		al_start_timer(this->timer);

		this->event_queue = al_create_event_queue();
		al_register_event_source(this->event_queue, al_get_timer_event_source(this->timer));
	}
}

bool ITimer::update() {
	ALLEGRO_EVENT events;
	while (al_get_next_event(event_queue, &events)) {
		if (events.type == ALLEGRO_EVENT_TIMER) {
			if (events.timer.source == this->timer) {return true;}
		}
	}
	return false;
}

void ITimer::setSpeed(float speed) {
	al_set_timer_speed(this->timer, speed);
}

void ITimer::setTimerCount(int64_t count) {
	al_set_timer_count(this->timer, count);
}

int64_t ITimer::getTimerCount(){return al_get_timer_count(this->timer);}
