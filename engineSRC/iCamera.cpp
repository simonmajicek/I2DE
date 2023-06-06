#include "iCamera.h"

ICamera::ICamera(){	
	al_identity_transform(&this->view);
}
ICamera::~ICamera(){}

void ICamera::update() {
	this->actualZoom = this->view.m[0][0];
	al_use_transform(&this->view);
}

void ICamera::setLoc2D(IPointF location) {
	this->view.m[3][0] = location.x;
	this->view.m[3][1] = location.y;
}

void ICamera::move2D(IPointF move) {
	al_translate_transform(&this->view, move.x, move.y);
}

void ICamera::rotate2DPivot(IPointF pivot, float angleRad) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_rotate_transform(&this->view, angleRad);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera::zoom2DInPivot(IPointF pivot) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_scale_transform(&this->view, this->zoomSpeedIn, this->zoomSpeedIn);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera::zoom2DOutPivot(IPointF pivot) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_scale_transform(&this->view, this->zoomSpeedOut, this->zoomSpeedOut);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera::resetRotate2DPivot(IPointF pivot) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_rotate_transform(&this->view, -this->view.m[0][1]);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera::resetZoom2DPivot(IPointF pivot) {
	al_translate_transform(&this->view, -pivot.x, -pivot.y);
	al_scale_transform(&this->view, 1.0f/this->view.m[0][0], 1.0f/this->view.m[1][1]);
	al_translate_transform(&this->view, pivot.x, pivot.y);
}

void ICamera::reset() {al_identity_transform(&this->view);}

IPointF ICamera::WorldToScreen(IPointF fWorld){
	IPointF tmp;
	tmp.x = ((fWorld.x * this->actualZoom) + this->view.m[3][0]);
	tmp.y = ((fWorld.y * this->actualZoom) + this->view.m[3][1]);
	return tmp;
}

IPointF ICamera::ScreenToWorld(IPointF nScreen){
	IPointF tmp;
	tmp.x = (nScreen.x - this->view.m[3][0]) / this->actualZoom;
	tmp.y = (nScreen.y - this->view.m[3][1]) / this->actualZoom;
	return tmp;
}

IPointF ICamera::WorldToScreenPointRatio(IPointF fWorld){
	IPointF tmp;
	tmp.x = ((fWorld.x - 0.0f) * (this->actualZoom));
	tmp.y = ((fWorld.y - 0.0f) * (this->actualZoom));
	return tmp;
}

IPointF ICamera::ScreenToWorldPointRatio(IPointF nScreen){
	IPointF tmp;
	tmp.x = (nScreen.x - 0.0f) / this->actualZoom;
	tmp.y = (nScreen.y - 0.0f) / this->actualZoom;
	return tmp;
}

