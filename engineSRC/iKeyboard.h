#pragma once
#include "allStaticLib.h"

enum {
	KEY_FREE = 1,				
	KEY_PRESS = 2,
	KEY_HOLD = 4,
	KEY_UNPRESS = 6,
	KEY_NOT_FREE = 6			//2 = 01, 4 = 001, 6 = 011 (neni KEY_FREE)
};

enum {
	KEY_A = 0,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_Normal0,
	KEY_Normal1,
	KEY_Normal2,
	KEY_Normal3,
	KEY_Normal4,
	KEY_Normal5,
	KEY_Normal6,
	KEY_Normal7,
	KEY_Normal8,
	KEY_Normal9,
	KEY_Pad0,
	KEY_Pad1,
	KEY_Pad2,
	KEY_Pad3,
	KEY_Pad4,
	KEY_Pad5,
	KEY_Pad6,
	KEY_Pad7,
	KEY_Pad8,
	KEY_Pad9,
	KEY_ESC,
	KEY_ALT,
	KEY_ENTER,
	KEY_SPACE,
	KEY_ARROW_UP,
	KEY_ARROW_DOWN,
	KEY_ARROW_LEFT,
	KEY_ARROW_RIGHT,
	KEY_BACKSPACE,
	KEY_MINUS,
	KEY_SEMICOLON
};

struct IKeyboard {
private:
	const short unsigned int numberOfKey = { 57 };
	uint64_t updateCount = { 0 };
	bool* isKeyPress;					//pole klaves
	uint64_t* keyTimer;					//pole casu klaves
	char* keyChar;						//pole znaku klaves
	ALLEGRO_EVENT_QUEUE* event_queue;
	//prekvapive se to v urcitych situacich hodi
	std::function<void()> keyDownCallback = { NULL };
	std::function<void()> keyUpCallback = { NULL };
private:
	void initKeyChar();
public:
	IKeyboard();
	~IKeyboard();
	void update();
	short unsigned int getKeyState(short unsigned int key);
	void setKey(short unsigned int key, bool keyIsPress); 
	bool isKeyLikeState(short unsigned int key, short unsigned state);
	char getKeyCharacter(short unsigned int key);
	void bindKeyDown(std::function<void()> func);
	void bindKeyUp(std::function<void()> func);
	void resetKeyboardEvents();
};



