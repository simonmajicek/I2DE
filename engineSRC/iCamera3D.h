#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
using namespace zelpMath;

struct ICamera3D {
private:
	const float zoomSpeedIn = { 1.05f };
	const float zoomSpeedOut = { 0.95f };
	double f;
	double dw = {800}; //al_get_display_width(display)
	double dh = {800}; //al_get_display_hight(display)
public:
	float fieldOfView = { 1.0f };
	IPointF3D position;
	IPointF3D xaxis;	//eye; /* This represent the direction looking to the right. */
	IPointF3D zaxis;	//view; /* This is the direction towards the viewer ('backwards'). */
	IPointF3D yaxis;	//up; /* This is the up direction. */
	ALLEGRO_TRANSFORM view;
	ALLEGRO_TRANSFORM projection;
	ALLEGRO_TRANSFORM camera;
	float actualZoom;		//slouzi pro prevod World<--->Screen souradnic
	float alpha;
	float beta;
public:
	ICamera3D();
	~ICamera3D();
	void update();
	void cameraRotateAroundAxis(IPointF3D axis, double radians);
	void cameraMoveAlongDirection(double right, double forward);
	IPointF3D getGroundForwardVector();
	IPointF3D getGroundRightVector();
	void cameraMoveAlongGround(double right, double forward);
	double getPitch();
	double getYaw();
	double getRoll();
	//old----------------------------------------------------
	void setLoc3D(IPointF3D location);
	void moveFront(float move);
	void moveSide(float move);
	void rotate(float dx, float dy);
	//void rotate2DPivot(IPointF pivot, float angleRad);
	//void zoom2DInPivot(IPointF pivot);
	//void zoom2DOutPivot(IPointF pivot);
	//void resetRotate2DPivot(IPointF pivot);
	//void resetZoom2DPivot(IPointF pivot);
	void reset();										//reset Zoom/Rotate nefunguje na 100% - nejlepsi je to resetovat uplne a zoom/rotate nastavit od znova
	//zatim nefunguje, pokud CameraRotation != 0
	IPointF WorldToScreen(IPointF fWorld);
	IPointF ScreenToWorld(IPointF nScreen);
	IPointF WorldToScreenPointRatio(IPointF fWorld);	//pro prevod meritka, camera ma souradnici 00
	IPointF ScreenToWorldPointRatio(IPointF nScreen);	//pro prevod meritka, camera ma souradnici 00
};



