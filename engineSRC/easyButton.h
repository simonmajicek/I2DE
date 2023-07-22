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
	ALLEGRO_COLOR fontColor;
	ALLEGRO_FONT* font;
	unsigned int fontSize;
	std::string text;
	std::function<void()> pressCallback = { NULL };
	EasyButton(zelpMath::IPoint loc, zelpMath::IPoint res);
	~EasyButton();
	void bindPress(std::function<void()> func);
	void setColor(ALLEGRO_COLOR colorIdle, ALLEGRO_COLOR colorFocus, ALLEGRO_COLOR colorPress);
	bool loadFont(std::string path, unsigned int size = 32);
	virtual void update(zelpMath::IPointF point, bool LMB);
	virtual void render();
	virtual void renderWithText();
};