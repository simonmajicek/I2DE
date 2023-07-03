#pragma once
#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"

struct EasyTextfield {
public : 
	zelpMath::IPoint loc;
	zelpMath::IPoint res;
	ALLEGRO_COLOR colorIdle;
	ALLEGRO_COLOR colorFocus;
	ALLEGRO_COLOR fontColor;
	ALLEGRO_FONT* font;
	unsigned int fontSize;
	std::string text;
	bool focus;
	EasyTextfield(zelpMath::IPoint loc, zelpMath::IPoint res);
	bool loadFont(std::string path, unsigned int size = 32);
	virtual void update(zelpMath::IPointF point, bool LMB);
	virtual void render();
};