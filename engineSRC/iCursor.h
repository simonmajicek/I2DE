#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
using namespace zelpMath;

enum {
	MB_FREE = 1,			//MB = Mouse Button
	MB_PRESS = 2,
	MB_HOLD = 4,
	MB_NOT_FREE = 6			//2 = 01, 4 = 001, 6 = 011 (neni KEY_FREE)
};

enum {
	LMB = 0,
	MMB,
	RMB
};

enum {
	MOUSE_SCROLLING_DOWN = -1,
	MOUSE_SCROLLING_NEUTRAL = 0,
	MOUSE_SCROLLING_UP = 1
};

struct ICursor {
protected:
	const short unsigned int numberOfButtons = { 3 };
	uint64_t updateCount = { 0 };
	bool* isMouseButtonPress;							//pole tlacitek
	uint64_t* mouseButtonTimer;							//pole tlacitek
	ALLEGRO_EVENT_QUEUE* event_queue;
public:
	IPointF loc = { IPointF(0, 0) };					//Location v pixelech okna
	IPointF prevLoc = { IPointF(0, 0) };				//slouzi pro vypocet "cursor pan", pan pro originLoc nas nezajima
	IPointF originLoc = { IPointF(0, 0) };				//location in world
	short int scrolling = { MOUSE_SCROLLING_NEUTRAL };	//-1, 0, 1 smer scrollovani
public:
	ICursor();
	~ICursor();
	void update();
	short unsigned int getMouseButtonState(short unsigned int mouseButton);
	bool isMouseButtonLikeState(short unsigned int mouseButton, short unsigned state);
	void setMouseButton(short unsigned int mouseButton, bool mouseButtonIsPress);
	void resetCursorEvents();

	//nejaka "fasada", metody pro ulehceni psani
	void setLoc(IPointF loc);
	void setOriginLoc(IPointF originLoc);
	IPointF getPan();
	bool getLMB();
	bool getMMB();
	bool getRMB();
	void setLMB(bool press);
	void setMMB(bool press);
	void setRMB(bool press);
};




