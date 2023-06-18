#include "easyCam2D.h"

EasyCam2D::EasyCam2D() {
	this->cursor = new ICursor();
	this->keyboard = new IKeyboard();
	this->camera = new ICamera2D();
}

EasyCam2D::~EasyCam2D() {
	delete this->camera;
	delete this->cursor;
	delete this->keyboard;

	this->camera = NULL;
	this->cursor = NULL;
	this->keyboard = NULL;
}


void EasyCam2D::update() {
	this->keyboard->update();
	this->camera->update();
	this->cursor->update();
	this->cursor->setOriginLoc(this->camera->ScreenToWorld(this->cursor->loc));

	if (this->keyboard->getKeyState(KEY_W) == KEY_HOLD) { this->camera->move2D(IPointF(0.0f, this->moveSpeed)); }
	if (this->keyboard->getKeyState(KEY_A) == KEY_HOLD) { this->camera->move2D(IPointF(this->moveSpeed, 0.0f)); }
	if (this->keyboard->getKeyState(KEY_S) == KEY_HOLD) { this->camera->move2D(IPointF(0.0f, -this->moveSpeed)); }
	if (this->keyboard->getKeyState(KEY_D) == KEY_HOLD) { this->camera->move2D(IPointF(-this->moveSpeed, 0.0f)); }
	if (this->cursor->scrolling == MOUSE_SCROLLING_DOWN) { this->camera->zoom2DOutPivot(this->cursor->loc); }
	if (this->cursor->scrolling == MOUSE_SCROLLING_UP) { this->camera->zoom2DInPivot(this->cursor->loc); }
	if (this->cursor->getMMB()) { this->camera->move2D(this->cursor->getPan());}
}
