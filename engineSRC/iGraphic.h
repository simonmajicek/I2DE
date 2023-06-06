#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
using namespace zelpMath;

//nejzakladnejsi grafika - 1x bitmapa a vsechny operace s sni
struct IGraphic {
public:
	IPointF loc = { IPointF(0.0f, 0.0f) };
	IPoint res;
	IPoint halfRes;
	float size = { 1.0f };
	float angleRad = { 0.0f };
	int bitmapFlags = { 0 };			//dle https://www.allegro.cc/manual/5/al_draw_bitmap
	ALLEGRO_BITMAP* bitmap;
public:
	IGraphic();
	~IGraphic();
	bool loadBitmap(std::string path);
	void render();
	void render2();
	bool isPointInside(IPointF point);				//nefunguje pri rotaci
};


