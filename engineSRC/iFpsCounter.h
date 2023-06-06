#pragma once
#include "allStaticLib.h"

struct IFpsCounter{
private:
	double old_time = { 0 };
	double new_time = { 0 };
	double new_seconds = { 0 };
	double old_seconds = { 0 };
public:
	void update();
	int getFps();
};


