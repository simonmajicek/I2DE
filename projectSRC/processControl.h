#pragma once
#include <iostream>
#include <string>
#include<tchar.h>
#include <process.h>
#include <windows.h>
#include <tlhelp32.h>
#include "allStaticLib.h" 
#include "zelpMath.h"
#include "easyScene2.h"
#include "easyButton.h"
#include "iDisplay.h"
#include "easyCam2D.h"
#include "iKeyboard.h"
#include "iCursor.h"
#include "iGraphic.h"
#include "iFont.h"
#include "iFile.h"
#include "ITimer.h"
#include "zelpWindowsOS.h"
#include "zelpMath.h"
using namespace zelpMath;

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

void processControl();
//pokud nenajde processControl v procesech, tak ho spusti
void runProcessControl();