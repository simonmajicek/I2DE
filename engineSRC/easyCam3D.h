#pragma once
#include "allStaticLib.h"
#include "iCamera3D.h"
#include "iCursor.h"
#include "iKeyboard.h"

struct EasyCam3D {
public:
	ICamera3D* camera;
	ICursor* cursor;
	IKeyboard* keyboard;
	const float mouseLookSpeed = { 0.03f };
	const float moveSpeed = { 0.03f };
public:
	EasyCam3D();
	~EasyCam3D();
	void update();
};