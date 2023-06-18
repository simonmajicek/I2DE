#include "easyCam3D.h"

EasyCam3D::EasyCam3D() {
	this->cursor = new ICursor();
	this->keyboard = new IKeyboard();
	this->camera = new ICamera3D();
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
	this->cursor->setOriginLoc(this->camera->ScreenToWorld(this->cursor->loc));

	double x = 0, y = 0;
	double xy;


	if (this->keyboard->getKeyState(KEY_W) == KEY_HOLD) { y = 1; }
	if (this->keyboard->getKeyState(KEY_A) == KEY_HOLD) { x = -1; }
	if (this->keyboard->getKeyState(KEY_S) == KEY_HOLD) { y = -1; }
	if (this->keyboard->getKeyState(KEY_D) == KEY_HOLD) { x = 1; }

	if (this->keyboard->getKeyState(KEY_Z) == KEY_HOLD) {
		double m = 20 * INDEX_PI / 180;
		this->camera->fieldOfView -= 0.01;
		if (this->camera->fieldOfView < m) { this->camera->fieldOfView = m; }
	}
	if (this->keyboard->getKeyState(KEY_X) == KEY_HOLD) {
		double m = 120 * INDEX_PI / 180;
		this->camera->fieldOfView += 0.01;
		if (this->camera->fieldOfView > m) { this->camera->fieldOfView = m; }
	}
	//FPS STYLE
	if (this->camera->position.y > 2)
		this->camera->position.y -= 0.1;
	if (this->camera->position.y < 2)
		this->camera->position.y = 2;

	//airplane style
	//double roll = get_roll(&ex.camera);
	//camera_rotate_around_axis(&ex.camera, ex.camera.zaxis, roll / 60);


	/* Move the camera, either freely or along the ground. */
	xy = sqrt(x * x + y * y);
	if (xy > 0) {
		x /= xy;
		y /= xy;
			this->camera->cameraMoveAlongGround(moveSpeed * x,
				moveSpeed * y);
		//if (ex.controls == 1 || ex.controls == 2) {
		//	camera_move_along_direction(&ex.camera, ex.movement_speed * x,
		//		ex.movement_speed * y);
		//}
	}
	if (this->cursor->getRMB()) {
		IPointF3D up = IPointF3D(0, 1, 0);
		this->camera->cameraRotateAroundAxis(this->camera->xaxis,
			-this->mouseLookSpeed * this->cursor->getPan().y);
		this->camera->cameraRotateAroundAxis(up,
			-this->mouseLookSpeed * this->cursor->getPan().x);
	}
	/*
	if (ex.button[1]) {
		if (ex.controls == 0 || ex.controls == 2) {
			Vector up = { 0, 1, 0 };
			camera_rotate_around_axis(&ex.camera, ex.camera.xaxis,
				-ex.mouse_look_speed * ex.mouse_dy);
			camera_rotate_around_axis(&ex.camera, up,
				-ex.mouse_look_speed * ex.mouse_dx);
		}
		if (ex.controls == 1) {
			camera_rotate_around_axis(&ex.camera, ex.camera.xaxis,
				-ex.mouse_look_speed * ex.mouse_dy);
			camera_rotate_around_axis(&ex.camera, ex.camera.zaxis,
				-ex.mouse_look_speed * ex.mouse_dx);
		}
	}
	*/


	//if (this->cursor->scrolling == MOUSE_SCROLLING_DOWN) { this->camera->zoom2DOutPivot(this->cursor->loc); }
	//if (this->cursor->scrolling == MOUSE_SCROLLING_UP) { this->camera->zoom2DInPivot(this->cursor->loc); }
	//if (this->cursor->getMMB()) { this->camera->move2D(this->cursor->getPan()); }


	//complete diferent control : 
	/*
	
    double x = 0, y = 0;
    double xy;
    if (ex.key[ALLEGRO_KEY_A] || ex.key[ALLEGRO_KEY_LEFT]) x = -1;
    if (ex.key[ALLEGRO_KEY_S] || ex.key[ALLEGRO_KEY_DOWN]) y = -1;
    if (ex.key[ALLEGRO_KEY_D] || ex.key[ALLEGRO_KEY_RIGHT]) x = 1;
    if (ex.key[ALLEGRO_KEY_W] || ex.key[ALLEGRO_KEY_UP]) y = 1;

    //Change field of view with Z/X.
	if (ex.key[ALLEGRO_KEY_Z]) {
		double m = 20 * pi / 180;
		ex.camera.vertical_field_of_view -= 0.01;
		if (ex.camera.vertical_field_of_view < m)
			ex.camera.vertical_field_of_view = m;
	}
	if (ex.key[ALLEGRO_KEY_X]) {
		double m = 120 * pi / 180;
		ex.camera.vertical_field_of_view += 0.01;
		if (ex.camera.vertical_field_of_view > m)
			ex.camera.vertical_field_of_view = m;
	}

	//In FPS style, always move the camera to height 2.
	if (ex.controls == 0) {
		if (ex.camera.position.y > 2)
			ex.camera.position.y -= 0.1;
		if (ex.camera.position.y < 2)
			ex.camera.position.y = 2;
	}

	// Set the roll (leaning) angle to 0 if not in airplane style.
	if (ex.controls == 0 || ex.controls == 2) {
		double roll = get_roll(&ex.camera);
		camera_rotate_around_axis(&ex.camera, ex.camera.zaxis, roll / 60);
	}

	// Move the camera, either freely or along the ground.
	xy = sqrt(x * x + y * y);
	if (xy > 0) {
		x /= xy;
		y /= xy;
		if (ex.controls == 0) {
			camera_move_along_ground(&ex.camera, ex.movement_speed * x,
				ex.movement_speed * y);
		}
		if (ex.controls == 1 || ex.controls == 2) {
			camera_move_along_direction(&ex.camera, ex.movement_speed * x,
				ex.movement_speed * y);
		}
	}

	// Rotate the camera, either freely or around world up only.
	if (ex.button[1]) {
		if (ex.controls == 0 || ex.controls == 2) {
			Vector up = { 0, 1, 0 };
			camera_rotate_around_axis(&ex.camera, ex.camera.xaxis,
				-ex.mouse_look_speed * ex.mouse_dy);
			camera_rotate_around_axis(&ex.camera, up,
				-ex.mouse_look_speed * ex.mouse_dx);
		}
		if (ex.controls == 1) {
			camera_rotate_around_axis(&ex.camera, ex.camera.xaxis,
				-ex.mouse_look_speed * ex.mouse_dy);
			camera_rotate_around_axis(&ex.camera, ex.camera.zaxis,
				-ex.mouse_look_speed * ex.mouse_dx);
		}
	}
	
	*/



	this->camera->update();
}
