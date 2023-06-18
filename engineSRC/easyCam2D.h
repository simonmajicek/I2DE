#pragma once
#include "allStaticLib.h"
#include "iCamera2D.h"
#include "iCursor.h"
#include "iKeyboard.h"

struct EasyCam2D {
public : 
	ICamera2D* camera;
	ICursor* cursor;
	IKeyboard* keyboard;
	float moveSpeed = { 1.0f };
public:
	EasyCam2D();
	~EasyCam2D();
	void update();
};