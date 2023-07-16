#include "iCamera3D.h"

ICamera3D::ICamera3D(float focusRatio) {
	//We save Allegro's projection so we can restore it for drawing text.
	//tohle jsou defaultni hodnoty pro projection matici pro 3D
	//pouzit this->defaultProjection = *al_get_current_projection_transform(); v konstruktoru neni bezpecne
	this->defaultProjection.m[0][0] = 0.00333333;
	this->defaultProjection.m[0][1] = 0;
	this->defaultProjection.m[0][2] = 0;
	this->defaultProjection.m[0][3] = 0;
	this->defaultProjection.m[1][0] = 0;
	this->defaultProjection.m[1][1] = -0.0033333;
	this->defaultProjection.m[1][2] = 0;
	this->defaultProjection.m[1][3] = 0;
	this->defaultProjection.m[2][0] = 0;
	this->defaultProjection.m[2][1] = 0;
	this->defaultProjection.m[2][2] = 1;
	this->defaultProjection.m[2][3] = 0;
	this->defaultProjection.m[3][0] = -1;
	this->defaultProjection.m[3][1] = 1;
	this->defaultProjection.m[3][2] = 0;
	this->defaultProjection.m[3][3] = 1;

	//--------------------------------------------------------------------------------
	this->focusRatio = focusRatio;
	this->fieldOfView = zelpMath::radToDegree(60);

	this->xaxis.x = 1;
	this->yaxis.y = 1;
	this->zaxis.z = 1;
	this->position.y = 2;

	this->useProjection();
}
ICamera3D::~ICamera3D() {}

void ICamera3D::update() {
	//this->projectionBackup = *al_get_current_projection_transform();

	this->useProjection();		//nechat, diky tomu jde focus

	al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
	al_clear_depth_buffer(1);

	al_build_camera_transform(&this->projection,
		this->position.x, this->position.y, this->position.z,
		this->position.x - this->zaxis.x,
		this->position.y - this->zaxis.y,
		this->position.z - this->zaxis.z,
		this->yaxis.x, this->yaxis.y, this->yaxis.z);
	al_use_transform(&this->projection);
	//draw somethinbg in 3D
}

void ICamera3D::rotateAroundAxis(IPointF3D axis, double radians){
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

void ICamera3D::moveAlongDirection(double right, double forward) {
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

void ICamera3D::moveAlongGround(double right, double forward) {
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

void ICamera3D::setFocusRatio(float focusRatio) {this->focusRatio = focusRatio;}

void ICamera3D::useProjection() {
	al_identity_transform(&this->projection);
	al_translate_transform_3d(&this->projection, 0, 0, -1);
	this->focus = tan(this->fieldOfView / 2);
	al_perspective_transform(&this->projection, -this->focusRatio * this->focus, this->focus, 1, this->focus * this->focusRatio, -this->focus, 1000.0f);
	al_use_projection_transform(&this->projection);
}

void ICamera3D::defaultCamera() {
	al_identity_transform(&this->projection);
	al_use_transform(&this->projection);
	al_use_projection_transform(&this->defaultProjection);
	al_set_render_state(ALLEGRO_DEPTH_TEST, 0);

}