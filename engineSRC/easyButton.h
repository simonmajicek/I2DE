#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"

struct EasyButton {
	zelpMath::IPoint loc;
	zelpMath::IPoint res;
	ALLEGRO_COLOR colorIdle;
	ALLEGRO_COLOR colorFocus;
	ALLEGRO_COLOR colorPress;
	ALLEGRO_COLOR showColor;
	std::function<void()> pressCallback = { NULL };
	EasyButton(zelpMath::IPoint loc, zelpMath::IPoint res);
	void bindPress(std::function<void()> func);
	void setColor(ALLEGRO_COLOR colorIdle, ALLEGRO_COLOR colorFocus, ALLEGRO_COLOR colorPress);
	void update(zelpMath::IPointF point, bool LMB);
	void render();
};