#pragma once
#include "allStaticLib.h"

#define FPS 60
#define MY_PI 3.14159265358979323846

bool operator==(const ALLEGRO_COLOR& first, ALLEGRO_COLOR& second);

//"zelp" like "help" with 'z'
namespace zelpMath { 
	struct IPoint {
		int x;
		int y;
		IPoint(int x = 0, int y = 0) : x(x), y(y) {}
		IPoint& operator=(const IPoint& a) {
			x = a.x;
			y = a.y;
			return *this;
		}
		void infoToConsole() { std::cout << "[" << x << "][" << y << "]" << std::endl; }
	};

	struct IPointF {
		float x;
		float y;
		IPointF(float x = 0, float y = 0) : x(x), y(y) {}
		IPointF& operator=(const IPointF& a) {
			x = a.x;
			y = a.y;
			return *this;
		}
		IPointF operator+(const IPointF& a) const {
			return IPointF(a.x + x, a.y + y);
		}
		IPointF operator-(const IPointF& a) const {
			return IPointF(a.x - x, a.y - y);
		}
		bool operator==(const IPointF& a) const {
			return (x == a.x && y == a.y);
		}
		void infoToConsole() { std::cout << "[" << x << "][" << y << "]" << std::endl; }
	};

	struct IBezier2D {
		IPointF points[4];
		void render(ALLEGRO_COLOR color, float thickness) { al_draw_spline((float*)points, color, thickness); };
		IPointF stupidLerp(float t);
	};

	//basic math
	void getHUE(char* r, char* g, char* b, float angleDeg);
	float lerp(float a, float b, float t);
	float countDistance(IPointF p1, IPointF p2);
	float degreeToRad(float number);
	float radToDegree(float number);
	float angleBetweenTwoPointsRad(float x1, float y1, float x2, float y2);
	float angleBetweenTwoPointsDegree(float x1, float y1, float x2, float y2);
	void rotateAroundPivot(float centerX, float centerY, float angleDeg, float* myX, float* myY);
	void rotateAroundPivotRad(float centerX, float centerY, float angleRad, float* myX, float* myY);

	//vectors
	IPointF getVectorFromTwoPoints(IPointF p1, IPointF p2);
	IPointF vectorFromAngleRad(float angleRad, float size = 1.0f);
	IPointF vectorFromAngleDegree(float angleDegree, float size = 1.0f);
	float vectorMagnitude(IPointF sizeFromThisVector);
	IPointF getNormalizeVector(IPointF vector);
	IPointF changeVectorMagnitude(IPointF vectorMag, float newMagnitude);

	//specific math
	float randomFloat(float lowNumber, float hightNumber);
	float mapRange(float value, float minCurrentRange, float maxCurrentRange, float minTargetRange, float maxTargetRange);
	int elementIndex2Dto1DArray(int x, int y, int widthSize);	//widthSize je velikost X!
	int sizeOfArray(int x, int y);		//volame sizeOfArray(sizeof(array), sizeof(int));

	//bonus function
	void debugLog(std::string text);
	int sizeOfBitmap(ALLEGRO_BITMAP* bitmap);		//width * height
	int sizeOfBitmapByte(ALLEGRO_BITMAP* bitmap);
	void alMatrixToConsole(ALLEGRO_TRANSFORM mat);
	void textureTest();
	void saveBitmapToFile(ALLEGRO_BITMAP* bitmapToSave, std::string name);
}