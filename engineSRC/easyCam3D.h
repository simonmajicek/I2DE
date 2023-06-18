#pragma once
#include "allStaticLib.h"
#include "iCamera3D.h"
#include "iCursor.h"
#include "iKeyboard.h"

//clas type
enum {
	CONTROL_TYPE_FPS = 0,
	CONTROL_TYPE_AIRPLANE,
	CONTROL_TYPE_SPACESHIP		//asi nejvice intuitivni?
};

struct EasyCam3D {
private : 
	void controlFPS();
	void controlAirplane();
	void controlSpaceship();
	//tmp var for optimization
	IPointF dir;
	float dirScale; //(x*x + y*y)
public:
	ICamera3D* camera;
	ICursor* cursor;
	IKeyboard* keyboard;
	const float mouseLookSpeed = { 0.03f };
	const float moveSpeed = { 0.03f };
	int controlType = { CONTROL_TYPE_SPACESHIP };
public:
	EasyCam3D(int controlType = CONTROL_TYPE_SPACESHIP);
	~EasyCam3D();
	void update();
};