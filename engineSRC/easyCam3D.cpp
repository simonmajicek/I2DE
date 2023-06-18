#include "easyCam3D.h"

EasyCam3D::EasyCam3D(int controlType) {
	this->cursor = new ICursor();
	this->keyboard = new IKeyboard();
	this->camera = new ICamera3D();
	this->controlType = controlType;
}

EasyCam3D::~EasyCam3D() {
	delete this->camera;
	delete this->cursor;
	delete this->keyboard;

	this->camera = NULL;
	this->cursor = NULL;
	this->keyboard = NULL;
}


void EasyCam3D::update() {
	this->keyboard->update();
	this->camera->update();
	this->cursor->update();

	this->dir = IPointF(0.0f, 0.0f);
	if (this->keyboard->getKeyState(KEY_W) == KEY_HOLD) { this->dir.y = 1; }
	if (this->keyboard->getKeyState(KEY_A) == KEY_HOLD) { this->dir.x = -1; }
	if (this->keyboard->getKeyState(KEY_S) == KEY_HOLD) { this->dir.y = -1; }
	if (this->keyboard->getKeyState(KEY_D) == KEY_HOLD) { this->dir.x = 1; }

	//field of view
	if (this->keyboard->getKeyState(KEY_Z) == KEY_HOLD) {
		double m = zelpMath::radToDegree(20);
		this->camera->fieldOfView -= 0.01;
		if (this->camera->fieldOfView < m) { this->camera->fieldOfView = m; }
	}
	if (this->keyboard->getKeyState(KEY_X) == KEY_HOLD) {
		double m = zelpMath::radToDegree(120);
		this->camera->fieldOfView += 0.01;
		if (this->camera->fieldOfView > m) { this->camera->fieldOfView = m; }
	}

	if (this->controlType == CONTROL_TYPE_FPS) {
		this->controlFPS();
	}
	if (this->controlType == CONTROL_TYPE_AIRPLANE) {
		this->controlAirplane();
	}
	if (this->controlType == CONTROL_TYPE_SPACESHIP) {
		this->controlSpaceship();
	}

	this->camera->update();
	//if (this->keyboard->getKeyState(KEY_R) == KEY_HOLD) { this->camera->restore(); }
}


void EasyCam3D::controlFPS() {
	if (this->camera->position.y > 2) { this->camera->position.y -= 0.1; }
	if (this->camera->position.y < 2) { this->camera->position.y = 2; }/* Move the camera, either freely or along the ground. */
	double roll = this->camera->getRoll();
	this->camera->rotateAroundAxis(this->camera->zaxis, roll / 60);
	this->dirScale = sqrt(this->dir.x * this->dir.x + this->dir.y * this->dir.y);
	if (this->dirScale > 0) {
		this->dir.x /= this->dirScale;
		this->dir.y /= this->dirScale;
		this->camera->moveAlongGround(this->moveSpeed * this->dir.x, moveSpeed * this->dir.y);
	}

	if (this->cursor->getRMB()) {
		IPointF3D up = IPointF3D(0, 1, 0);
		this->camera->rotateAroundAxis(this->camera->xaxis, -this->mouseLookSpeed * this->cursor->getPan().y);
		this->camera->rotateAroundAxis(up, -this->mouseLookSpeed * this->cursor->getPan().x);
	}
}

void EasyCam3D::controlAirplane() {
	this->dirScale = sqrt(this->dir.x * this->dir.x + this->dir.y * this->dir.y);
	if (this->dirScale > 0) {
		this->dir.x /= this->dirScale;
		this->dir.y /= this->dirScale;
		this->camera->moveAlongDirection(this->moveSpeed * this->dir.x, this->moveSpeed * this->dir.y);
	}
	if (this->cursor->getRMB()) {
		this->camera->rotateAroundAxis(this->camera->xaxis, -this->mouseLookSpeed * this->cursor->getPan().y);

		this->camera->rotateAroundAxis(this->camera->zaxis, -this->mouseLookSpeed * this->cursor->getPan().x);
	}
}

void EasyCam3D::controlSpaceship() {
	double roll = this->camera->getRoll();
	this->camera->rotateAroundAxis(this->camera->zaxis, roll / 60);
	this->dirScale = sqrt(this->dir.x * this->dir.x + this->dir.y * this->dir.y);
	if (this->dirScale > 0) {
		this->dir.x /= this->dirScale;
		this->dir.y /= this->dirScale;
		this->camera->moveAlongDirection(this->moveSpeed * this->dir.x, this->moveSpeed * this->dir.y);
	}

	if (this->cursor->getRMB()) {
		IPointF3D up = IPointF3D(0, 1, 0);
		this->camera->rotateAroundAxis(this->camera->xaxis, -this->mouseLookSpeed * this->cursor->getPan().y);
		this->camera->rotateAroundAxis(up, -this->mouseLookSpeed * this->cursor->getPan().x);
	}

}


