#include "iFpsCounter.h"

void IFpsCounter::update(){
	new_time = al_get_time();
	new_seconds = (new_time - old_time);
	old_time = new_time;
}

int IFpsCounter::getFps(){
	old_seconds = new_seconds;
	return ((int)(1.0/old_seconds));
}


