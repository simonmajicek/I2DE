
#include <iostream>

#include "allStaticLib.h" 
#include "i2DE.h"
#include "zelpMath.h"
#include "examples.h"
#include "simpleTABS.h"
#include "houbaLevel.h"
#include "cerberus.h"
using namespace std;
using namespace zelpMath;

int main() {
	//if (SteamAPI_RestartAppIfNecessary(480)) {return 1;}
#ifdef DEBUGON
	cout << "debugTest" << endl;
#endif // DEBUG
#ifdef STEAM_SDK_ON
	//if (SteamAPI_RestartAppIfNecessary(480)) {return 1;}
#endif

	if (!I2DE::initEngine()) {
		debugLog("I2DE Error");
		return -1;
	}

	//randomWalker();
	//drawWithPixels();
	//showClock();
	//showClockToDesktopWallpaper();
	//simpleSnake();
	//simpleSnakeOSWallpaper();
	//imageSand();
	//bezierTest();
	//mandelbrot();
	//zelpWindowsOS::shutDownPC();
	//escapiWebcamHello();
	//unicodeTest();
	//testingBox2D();
	//simpleTABS();

	//houbaLevel();
	//runProcessControl();
	//runCerberus();
	//testingRecording();
	//calculator();
	//test3Dscene();
	
	//rate, bet min, want win, alreadyLost
	//vypocita, kolik musim vsadit, abych byl zpatky v plusu
	//bruteForceBet();


	return 0;
}