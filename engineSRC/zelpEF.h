#pragma once
#include "allStaticLib.h"
//"zelp" like "help" with 'z'

namespace zelpEF {
	//easing Funcion EF - vice na https://www.youtube.com/watch?v=mr5xkf6zSzk
	//t [0, 1]; N > 0 
	float EFFlip(float t);
	float EFSquare(float x);
	float EFScale(float x, float t);						//x - vysledek jine funce
	float EFReverseScale(float x, float t);			//x - vysledek jine funkce
	float EFMix(float x, float y, float blend);	//blend[0, 1], x/y - vysledek jine funkce
	float EFSmoothStep(int N, float t);
	float EFArch2(float t);
	float EFSmoothStartArch3(float t);
	float EFSmoothStopArch3(float t);
	float EFSmoothStart(int N, float t);
	float EFSmoothStop(int N, float t);

	float mapRangeWithEasingFuncion(float value, float minCurrentRange, float maxCurrentRange, float minTargetRange, float maxTargetRange, std::function<float(float)> func);
	float mapRangeWithEasingFuncion(float value, float minCurrentRange, float maxCurrentRange, float minTargetRange, float maxTargetRange, std::function<float(float, float)> func, int N);

}