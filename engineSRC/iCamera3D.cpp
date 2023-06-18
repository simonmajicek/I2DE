#include "iCamera3D.h"

ICamera3D::ICamera3D() {
	this->xaxis.x = 1;
	this->yaxis.y = 1;
	this->zaxis.z = 1;
	this->position.y = 2;
	this->fieldOfView = 60 * INDEX_PI / 180;

	al_identity_transform(&this->projection);
	al_translate_transform_3d(&this->projection, 0, 0, -1);
	this->f = tan(this->fieldOfView / 2);
	al_perspective_transform(&this->projection, -1 * this->dw / this->dh * this->f, this->f, 1, this->f * this->dw / this->dh, -this->f, 1000);
	al_use_projection_transform(&this->projection);
}
ICamera3D::~ICamera3D() {}

void ICamera3D::update() {
	/* We save Allegro's projection so we can restore it for drawing text. */
	ALLEGRO_TRANSFORM projection = *al_get_current_projection_transform();
	ALLEGRO_TRANSFORM t;
	//ALLEGRO_COLOR back = al_color_name("black");
	//ALLEGRO_COLOR front = al_color_name("white");
	int th;
	double pitch, yaw, roll;
	this->reset();

	al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
	al_clear_depth_buffer(1);


	al_build_camera_transform(&t,
		this->position.x, this->position.y, this->position.z,
		this->position.x - this->zaxis.x,
		this->position.y - this->zaxis.y,
		this->position.z - this->zaxis.z,
		this->yaxis.x, this->yaxis.y, this->yaxis.z);
	al_use_transform(&t);
	//draw somethinbg in 3D
	/*
	//restpre
	al_identity_transform(&t);
	al_use_transform(&t);
	al_use_projection_transform(&projection);
	al_set_render_state(ALLEGRO_DEPTH_TEST, 0);

	//draw text
	th = al_get_font_line_height(ex.font);
	al_draw_textf(ex.font, front, 0, th * 0, 0,
		"look: %+3.1f/%+3.1f/%+3.1f (change with left mouse button and drag)",
		-c->zaxis.x, -c->zaxis.y, -c->zaxis.z);
	pitch = get_pitch(c) * 180 / pi;
	yaw = get_yaw(c) * 180 / pi;
	roll = get_roll(c) * 180 / pi;
	al_draw_textf(ex.font, front, 0, th * 1, 0,
		"pitch: %+4.0f yaw: %+4.0f roll: %+4.0f", pitch, yaw, roll);
	al_draw_textf(ex.font, front, 0, th * 2, 0,
		"vertical field of view: %3.1f (change with Z/X)",
		c->vertical_field_of_view * 180 / pi);
	al_draw_textf(ex.font, front, 0, th * 3, 0, "move with WASD or cursor");
	al_draw_textf(ex.font, front, 0, th * 4, 0, "control style: %s (space to change)",
		ex.controls_names[ex.controls]);
		*/

	//old*-----------------------------------------------
	//this->actualZoom = this->view.m[0][0];
	//al_use_transform(&this->view);
}

void ICamera3D::cameraRotateAroundAxis(IPointF3D axis, double radians){
	ALLEGRO_TRANSFORM t;
	al_identity_transform(&t);
	al_rotate_transform_3d(&t, axis.x, axis.y, axis.z, radians);
	al_transform_coordinates_3d(&t, &this->yaxis.x, &this->yaxis.y, &this->yaxis.z);
	al_transform_coordinates_3d(&t, &this->zaxis.x, &this->zaxis.y, &this->zaxis.z);

	/* Make sure the axes remain orthogonal to each other. */
	this->zaxis = vectorNormalize(this->zaxis);
	this->xaxis = vectorCrossProduct(this->yaxis, this->zaxis);
	this->xaxis = vectorNormalize(this->xaxis);
	this->yaxis = vectorCrossProduct(this->zaxis, this->xaxis);
}

void ICamera3D::cameraMoveAlongDirection(double right, double forward) {
	vectorAdd(&this->position, vectorMul(this->xaxis, right));
	vectorAdd(&this->position, vectorMul(this->zaxis, -forward));
}

IPointF3D ICamera3D::getGroundForwardVector() {
	IPointF3D move = vectorMul(this->zaxis, -1);
	move.y = 0;
	return vectorNormalize(move);
}

IPointF3D ICamera3D::getGroundRightVector() {
	IPointF3D move = this->xaxis;
	move.y = 0;
	return vectorNormalize(move);
}

void ICamera3D::cameraMoveAlongGround(double right, double forward) {
	IPointF3D f = this->getGroundForwardVector();
	IPointF3D r = this->getGroundRightVector();
	this->position.x += f.x * forward + r.x * right;
	this->position.z += f.z * forward + r.z * right;
}

double ICamera3D::getPitch() {
	IPointF3D f = this->getGroundForwardVector();
	return asin(vectorDotProduct(f, this->yaxis));
}

double ICamera3D::getYaw() {
	return atan2(this->zaxis.x, this->zaxis.z);
}

double ICamera3D::getRoll() {
	IPointF3D r = this->getGroundRightVector();
	return asin(vectorDotProduct(r, this->yaxis));
}

//Old-----------------------------------------------------------------------------
void ICamera3D::setLoc3D(IPointF3D location) {
	this->view.m[3][0] = location.x;
	this->view.m[3][1] = location.y;
	this->view.m[3][2] = location.z;
}

void ICamera3D::moveFront(float move) {
	//al_translate_transform(&this->view, move.x, move.y);
}

void ICamera3D::moveSide(float move) {
	//al_translate_transform(&this->view, move.x, move.y);
}

void ICamera3D::rotate(float dx, float dy) {

}

/*
void ICamera3D::rotate2DPivot(IPointF pivot, float angleRad) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_rotate_transform(&this->view, angleRad);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera3D::zoom2DInPivot(IPointF pivot) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_scale_transform(&this->view, this->zoomSpeedIn, this->zoomSpeedIn);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera3D::zoom2DOutPivot(IPointF pivot) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_scale_transform(&this->view, this->zoomSpeedOut, this->zoomSpeedOut);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera3D::resetRotate2DPivot(IPointF pivot) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_rotate_transform(&this->view, -this->view.m[0][1]);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera3D::resetZoom2DPivot(IPointF pivot) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_scale_transform(&this->view, 1.0f / this->view.m[0][0], 1.0f / this->view.m[1][1]);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}
*/
void ICamera3D::reset() {
	al_identity_transform(&this->projection);
	al_translate_transform_3d(&this->projection, 0, 0, -1);
	this->f = tan(this->fieldOfView / 2);
	al_perspective_transform(&this->projection, -1 * this->dw / this->dh * this->f, this->f, 1, this->f * this->dw / this->dh, -this->f, 1000);
	al_use_projection_transform(&this->projection);
}

IPointF ICamera3D::WorldToScreen(IPointF fWorld) {
	IPointF tmp;
	tmp.x = ((fWorld.x * this->actualZoom) + this->view.m[3][0]);
	tmp.y = ((fWorld.y * this->actualZoom) + this->view.m[3][1]);
	return tmp;
}

IPointF ICamera3D::ScreenToWorld(IPointF nScreen) {
	IPointF tmp;
	tmp.x = (nScreen.x - this->view.m[3][0]) / this->actualZoom;
	tmp.y = (nScreen.y - this->view.m[3][1]) / this->actualZoom;
	return tmp;
}

IPointF ICamera3D::WorldToScreenPointRatio(IPointF fWorld) {
	IPointF tmp;
	tmp.x = ((fWorld.x - 0.0f) * (this->actualZoom));
	tmp.y = ((fWorld.y - 0.0f) * (this->actualZoom));
	return tmp;
}

IPointF ICamera3D::ScreenToWorldPointRatio(IPointF nScreen) {
	IPointF tmp;
	tmp.x = (nScreen.x - 0.0f) / this->actualZoom;
	tmp.y = (nScreen.y - 0.0f) / this->actualZoom;
	return tmp;
}
