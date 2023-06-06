#pragma once
#include "zelpMath.h"
#include "iB2Entity.h"
#include "iB2ContactListener.h"
#include "iFpsCounter.h"
using namespace zelpMath;

//Prazda scena
class EasyScene {
protected:
	float timeStep = {1.0f / FPS};		//pocet updatu za cas
	IFpsCounter fpsCounter;
	//------------------------------------------------------------
	std::function<void()> initCallback = { NULL };
	std::function<void()> updateCallback = { NULL };
	std::function<void()> renderCallback = { NULL };
public:
#ifdef BOX2D_ENGINE_ON
	b2World* b2world;
	IB2ContactListener myContactListener;
#endif
	//-------------------------------------------------------------
	bool breakLoop = { false };
public:
	EasyScene();
	~EasyScene();
	void run();
	virtual void update();		
	virtual void render();
	void setFPS(float timeStep);
	void bindInit(std::function<void()> func);
	void bindUpdate(std::function<void()> func);
	void bindRender(std::function<void()> func);
};



