//c++
#include <ctime>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <valarray>
#include <thread>
#include <functional>
#include <complex>

//allegro
#define ALLEGRO_UNSTABLE
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/timer.h>
#include <allegro5/mouse.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_memfile.h>

//#define DEBUG_ON
#define BOX2D_ENGINE_ON
//#define STEAM_SDK_ON	

#ifdef BOX2D_ENGINE_ON
	#include <Box2D/Box2D.h>
#endif

#ifdef STEAM_SDK_ON
	#include "..//..//steamHeaderFiles/steam_api.h"
#endif









