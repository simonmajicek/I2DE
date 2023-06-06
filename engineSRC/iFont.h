#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
using namespace zelpMath;

struct IFont {
private:
	ALLEGRO_FONT* font = { NULL };
	unsigned int size = { 0 };					//nelze menit velikost za provozu, musi se nacist font znova se spravnou velikosti
public:
	IPoint loc = { IPoint(0.0f, 0.0f) };
	ALLEGRO_COLOR color;
	short int flag = { 0 };
public:
	IFont();
	~IFont();
	bool loadFont(std::string path, unsigned int size = 32);
	void render(std::string text);
	void renderUnicode(ALLEGRO_USTR* unicodeText);
	unsigned int getSize() { return this->size; }
};


