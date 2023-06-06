#include "zelpEF.h"

namespace zelpEF {
	float EFFlip(float t) { return 1.0f - t; };
	float EFSquare(float x) { return x * x; };
	float EFScale(float x, float t) { return x * t; };						//x - vysledek jine funce
	float EFReverseScale(float x, float t) { return (1.0f - t) * x; };			//x - vysledek jine funkce
	float EFMix(float x, float y, float blend) { return x + blend * (y - x); };	//blend[0, 1], x/y - vysledek jine funkce
	float EFSmoothStep(int N, float t) { return EFMix(EFSmoothStart(N, t), EFSmoothStop(N, t), t); };
	float EFArch2(float t) { return t * (1.0f - t); };
	float EFSmoothStartArch3(float t) { return (t * t) * (1.0f - t); };
	float EFSmoothStopArch3(float t) { return t * ((1.0f - t) * (1.0f - t)); };

	float EFSmoothStart(int N, float t) {
		for (int i = 1; i < N; i++) { t = EFSquare(t); }
		return t;
	}

	float EFSmoothStop(int N, float t) {
		float tmp = EFFlip(t);
		for (int i = 1; i < N; i++) { tmp = EFSquare(tmp); }
		return 1.0f - tmp;
	}

	float mapRangeWithEasingFuncion(float value, float minCurrentRange, float maxCurrentRange, float minTargetRange, float maxTargetRange, std::function<float(float)> func) {
		float result = value - minCurrentRange;
		result = result / (maxCurrentRange - minCurrentRange);
		result = func(result);
		result = result * (maxTargetRange - minTargetRange);
		return result + minTargetRange;
	}

	float mapRangeWithEasingFuncion(float value, float minCurrentRange, float maxCurrentRange, float minTargetRange, float maxTargetRange, std::function<float(float, float)> func, int N) {
		float result = value - minCurrentRange;
		result = result / (maxCurrentRange - minCurrentRange);
		result = func(N, result);
		result = result * (maxTargetRange - minTargetRange);
		return result + minTargetRange;
	}
}