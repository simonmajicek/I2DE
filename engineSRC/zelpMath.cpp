#include "zelpMath.h"

bool operator==(const ALLEGRO_COLOR& first, ALLEGRO_COLOR& second) {
	if (first.a == second.a)
		if (first.r == second.r)
			if (first.g == second.g)
				if (first.b == second.b)
					return true;
	return false;
}

namespace zelpMath {
	IPointF IBezier2D::stupidLerp(float t) {
		//teorie : https://youtu.be/enNfb6p3j_g
		//teorie : https://devforum.roblox.com/t/how-to-tweenlerp-a-bezier-curve/1174077
		IPointF p0, p1, p2, tmp1, tmp2;
		p0.x = zelpMath::lerp(this->points[0].x, this->points[1].x, t);
		p0.y = zelpMath::lerp(this->points[0].y, this->points[1].y, t);
		p1.x = zelpMath::lerp(this->points[1].x, this->points[2].x, t);
		p1.y = zelpMath::lerp(this->points[1].y, this->points[2].y, t);
		p2.x = zelpMath::lerp(this->points[2].x, this->points[3].x, t);
		p2.y = zelpMath::lerp(this->points[2].y, this->points[3].y, t);
		tmp1 = IPointF(zelpMath::lerp(p0.x, p1.x, t), zelpMath::lerp(p0.y, p1.y, t));
		tmp2 = IPointF(zelpMath::lerp(p1.x, p2.x, t), zelpMath::lerp(p1.y, p2.y, t));
		//-------------------------------------------------------------------
		return IPointF(zelpMath::lerp(tmp1.x, tmp2.x, t), zelpMath::lerp(tmp1.y, tmp2.y, t));
	}

	//basic math------------------------------------------------------------------------------
	void getHUE(char* r, char* g, char* b, float angleDeg) { 
		*r = 255.0f * std::cos(degreeToRad(angleDeg));
		*g = 255.0f * std::cos(degreeToRad(angleDeg + 120.0f));
		*b = 256.0f * std::cos(degreeToRad(angleDeg - 120.0f));
	}
	float lerp(float a, float b, float t) { return a + t * (b - a); }
	float countDistance(IPointF p1, IPointF p2) { return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); };
	float degreeToRad(float number) { return (number * (INDEX_PI / (float)180)); };
	float radToDegree(float number) { return (number * ((float)180) / INDEX_PI); };
	float angleBetweenTwoPointsRad(float x1, float y1, float x2, float y2) { return atan2(y1 - y2, x1 - x2); };
	float angleBetweenTwoPointsDegree(float x1, float y1, float x2, float y2) { return radToDegree(atan2(y1 - y2, x1 - x2)); };
	
	void rotateAroundPivot(float centerX, float centerY, float angleDeg, float* myX, float* myY) {
		float s = sin(degreeToRad(angleDeg));
		float c = cos(degreeToRad(angleDeg));
		*myX -= centerX;
		*myY -= centerY;
		float newX = (*myX * c) - (*myY * s);
		float newY = (*myY * s) + (*myY * c);
		*myX = newX + centerX;
		*myY = newY + centerY;
	}

	void rotateAroundPivotRad(float centerX, float centerY, float angleRad, float* myX, float* myY) {
		float s = sin(angleRad);
		float c = cos(angleRad);
		*myX -= centerX;
		*myY -= centerY;
		float newX = (*myX * c) - (*myY * s);
		float newY = (*myY * s) + (*myY * c);
		*myX = newX + centerX;
		*myY = newY + centerY;
	}

	//vectors------------------------------------------------------------------------------------
	IPointF getVectorFromTwoPoints(IPointF p1, IPointF p2) {return IPointF(p2.x - p1.x, p2.y - p1.y);}
	IPointF vectorFromAngleRad(float angleRad, float size) {return changeVectorMagnitude(IPointF(cos(angleRad), sin(angleRad)), size);}
	IPointF vectorFromAngleDegree(float angleDegree, float size) {return vectorFromAngleRad(degreeToRad(angleDegree), size);}
	float vectorMagnitude(IPointF sizeFromThisVector) {return sqrt((sizeFromThisVector.x * sizeFromThisVector.x) + (sizeFromThisVector.y * sizeFromThisVector.y));}
	IPointF getNormalizeVector(IPointF vector) { return IPointF(vector.x / vectorMagnitude(vector), vector.y / vectorMagnitude(vector)); }
	IPointF changeVectorMagnitude(IPointF vectorMag, float newMagnitude) {
		float oldMag = vectorMagnitude(vectorMag);
		if (oldMag == 0) { oldMag = 0.001; }
		vectorMag.x = vectorMag.x * (newMagnitude / oldMag);
		vectorMag.y = vectorMag.y * (newMagnitude / oldMag);
		return vectorMag;
	}

	//vectors3D----------------------------------------------------------------------------------
	float vectorDotProduct(IPointF3D a, IPointF3D b) {return a.x * b.x + a.y * b.y + a.z * b.z;}
	IPointF3D vectorCrossProduct(IPointF3D a, IPointF3D b) {
		IPointF3D v = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
		return v;
	}
	IPointF3D vectorMul(IPointF3D a, float s) {
		IPointF3D v = { a.x * s, a.y * s, a.z * s };
		return v;
	}
	float vectorNorm(IPointF3D a) {return sqrt(vectorDotProduct(a, a));}
	IPointF3D vectorNormalize(IPointF3D a) {
		float s = vectorNorm(a);
		if (s == 0) { return a; }
		return vectorMul(a, 1 / s);
	}
	void vectorAdd(IPointF3D* a, IPointF3D b) {
		a->x += b.x;
		a->y += b.y;
		a->z += b.z;
	}

	//specific math------------------------------------------------------------------------------
	float randomFloat(float lowNumber, float hightNumber) { return lowNumber + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hightNumber - lowNumber))); };
	float mapRange(float value, float minCurrentRange, float maxCurrentRange, float minTargetRange, float maxTargetRange) { return ((value - minCurrentRange) / (maxCurrentRange - minCurrentRange)) * (maxTargetRange - minTargetRange) + minTargetRange; };
	int elementIndex2Dto1DArray(int x, int y, int widthSize) { return x + y * widthSize; };	//widthSize je velikost X!
	int sizeOfArray(int x, int y) { return x / y; };

	//bonus function-----------------------------------------------------------------------------
	void debugLog(std::string text) { std::cout << text << std::endl; };

	int sizeOfBitmap(ALLEGRO_BITMAP* bitmap) {
		int size = 0;
		if (bitmap) { size = al_get_bitmap_height(bitmap) * al_get_bitmap_width(bitmap); }
		return size;
	}

	int sizeOfBitmapByte(ALLEGRO_BITMAP* bitmap) {
		int size = 0;
		if (bitmap) {
			ALLEGRO_LOCKED_REGION* tmpRegion = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
			size = tmpRegion->pixel_size;		//in bytes
			al_unlock_bitmap(bitmap);
			size = al_get_bitmap_height(bitmap) * al_get_bitmap_width(bitmap) * size;
		}
		return size;
	}

	void alMatrixToConsole(ALLEGRO_TRANSFORM mat) {
		std::cout << "-------------------------------" << std::endl;
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				std::cout << "[" << mat.m[i][j] << "]";
			}
			std::cout << std::endl;
		}
		std::cout << "-------------------------------" << std::endl;
	}

	void textureTest() {
		ALLEGRO_BITMAP* bitmapTexture = al_load_bitmap("assets/examples/bird.png");
		ALLEGRO_VERTEX v[] = {{0, 0, 0, 0, 0, al_map_rgb(255, 255, 255)},
							 {0, 5.27, 0, 0, 527, al_map_rgb(255, 255, 255)},
							 {3.95, 5.27, 0, 395, 527, al_map_rgb(255, 255, 255)},
							 {1.80, 0, 0, 395, 0, al_map_rgb(255, 255, 255)} };
		al_draw_prim(v, NULL, bitmapTexture, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
		al_destroy_bitmap(bitmapTexture);
	}

	void saveBitmapToFile(ALLEGRO_BITMAP* bitmapToSave, std::string name) {
		if (!al_save_bitmap(name.c_str(), bitmapToSave)) {
			//debugLog("Bitmap was not save : " + name);
		}
	}
}