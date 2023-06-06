#include "easyScene2.h"

EasyScene2::EasyScene2() : EasyScene(){
	this->display = new IDisplay();
	this->display->create();
	this->cursor = new ICursor();
	this->keyboard = new IKeyboard();

	al_set_target_backbuffer(this->display->display);
	this->displayClearColor = al_map_rgb(25, 25, 25);
}

EasyScene2::~EasyScene2(){
	delete this->display;
	delete this->cursor;
	delete this->keyboard;

	this->display = NULL;
	this->cursor = NULL;
	this->keyboard = NULL;
}

void EasyScene2::preUpdate(){
	if (!this->display->update()) { this->breakLoop = true; }
	eCam2D.update();
	this->keyboard->update();
	this->cursor->update();
	this->cursor->setOriginLoc(this->eCam2D.camera->ScreenToWorld(this->cursor->loc));
}

void EasyScene2::update(){
	this->preUpdate();
	if (this->updateCallback) { this->updateCallback(); }
	this->postUpdate();
}

void EasyScene2::postUpdate(){}

void EasyScene2::preRender(){al_clear_to_color(this->displayClearColor);}

void EasyScene2::render(){
	this->preRender();
	if (this->renderCallback) { this->renderCallback(); }
	this->postRender();
}

void EasyScene2::postRender(){
	al_flip_display();
	fpsCounter.update();	
}






