#include "easyScene.h"


EasyScene::EasyScene() {
	#ifdef BOX2D_ENGINE_ON
		this->b2world = new b2World(b2Vec2(0.0f, -10.0f));
		this->b2world->SetContactListener(&this->myContactListener);
	#endif
}

EasyScene::~EasyScene() {
	#ifdef BOX2D_ENGINE_ON
		delete this->b2world;
	#endif
}

void EasyScene::update(){if(this->updateCallback){this->updateCallback();}}

void EasyScene::render(){ 
	if (this->renderCallback) { this->renderCallback(); }
	fpsCounter.update();
}

void EasyScene::run() {
	if (this->initCallback) { this->initCallback(); }

	double sleep_time = 0;
	double begin_time = 0;
	double diff_time = 0;
	#ifdef BOX2D_ENGINE_ON
		int correctVelocity = 16;
		int correctPosition = 8;
	#endif

	while (!this->breakLoop) {
		begin_time = al_get_time();
		#ifdef BOX2D_ENGINE_ON
				this->b2world->Step(this->timeStep, correctVelocity, correctPosition);
		#endif
		this->update();
		if (this->breakLoop) { break; }
		this->render();

		diff_time = al_get_time() - begin_time;
		sleep_time = this->timeStep - diff_time;
		if (sleep_time > 0) { al_rest(sleep_time); }	//nemusim osetrit zaporne cislo, udela to automaticky ve fci

		while (sleep_time < 0) {
			#ifdef BOX2D_ENGINE_ON
				this->b2world->Step(this->timeStep, correctVelocity, correctPosition);
			#endif
			this->update();
			if (this->breakLoop) { break; }
			sleep_time += this->timeStep;
		}
	}
}

void EasyScene::setFPS(float timeStep) { this->timeStep = timeStep; }
void EasyScene::bindInit(std::function<void()> func) { this->initCallback = func; }
void EasyScene::bindUpdate(std::function<void()> func) { this->updateCallback = func; }
void EasyScene::bindRender(std::function<void()> func) { this->renderCallback = func; }




