#pragma once
#include "allStaticLib.h"

struct I2DE{
private :
	static I2DE*single;
	I2DE();
public :
	~I2DE();
	static I2DE* getInstance();
	static bool initEngine();
};

