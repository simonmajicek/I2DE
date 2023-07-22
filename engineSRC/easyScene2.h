#pragma once
#include "easyScene.h"
#include "iCamera2D.h"
#include "iDisplay.h"
#include "iCursor.h"
#include "iKeyboard.h"
#include "easyCam2D.h"
using namespace zelpMath;

//scena, ktera ma vlastni display, klavesnici, atd... + basic camera control - hodi se vice pro box2d
class EasyScene2 : public EasyScene{
protected:
	ALLEGRO_COLOR displayClearColor;
public:
	EasyCam2D eCam2D;
	IDisplay* display;
	ICursor* cursor;
	IKeyboard* keyboard;
	bool multipleScene;		
public:		
	EasyScene2(bool multipleScene = false);	//pukud dam true, musim manualne init a delete IDisplay, ICursor a Keyboard v SceneManager
	~EasyScene2();
	void preUpdate();
	void update();				//vraci cislo sceny
	void postUpdate();
	void preRender();
	void render();
	void postRender();
};


