#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
using namespace zelpMath;

struct IDisplay {
private:
	ALLEGRO_EVENT_QUEUE* event_queue;
public:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* icon;
	const IPoint defaultRes = { IPoint(1920, 1080) };
	IPoint minRes = { IPoint(40, 40) };
	IPoint res;
	std::function<void()> onGetFocus = { NULL };
	std::function<void()> onLostFocus = { NULL };
	std::function<void()> onResize = { NULL };
	std::function<void()> onClose = { NULL };
public:
	IDisplay(IPoint res = IPoint(640, 360));
	~IDisplay();
	bool create(short int flags = 0);			//slouzi i pro overeni, zda se okno podarilo vytvorit
	bool update();			//vraci, zda je okno stale otevreno
	bool setFullscreen(bool fullscreen);
	bool getFullscreen();
	bool changeResolution(IPoint res);
	bool loadIcon(std::string path);
	int getResX();
	int getResY();
	void bindGetFocus(std::function<void()> func);
	void bindLostFocus(std::function<void()> func);
	void bindResize(std::function<void()> func);
	void bindClose(std::function<void()> func);
	void setTitle(std::string title);
	void setPosition(IPoint windowLoc);
	void showCursor();
	void hideCursor();
};
