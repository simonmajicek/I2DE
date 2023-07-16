#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
using namespace zelpMath;

struct ICamera3D {
private:
	float focus;
	float focusRatio = { 1.0f }; //display width / display height
private:
	void useProjection();	//prepocita a pouzije projekci - hlavne focus
public: 
	float fieldOfView = { 1.0f };
	IPointF3D position;
	IPointF3D xaxis;	//SIDE - This represent the direction looking to the right.
	IPointF3D zaxis;	//EYE - This is the direction towards the viewer
	IPointF3D yaxis;	//UP - This is the up direction.
	ALLEGRO_TRANSFORM projection;
	ALLEGRO_TRANSFORM defaultProjection; //save actual projection (we can do magic like skybox, draw GUI on screen, atd...);
public:
	ICamera3D(float focusRatio = 1.0f);
	~ICamera3D();
	void update();
	void rotateAroundAxis(IPointF3D axis, double radians);
	void moveAlongDirection(double right, double forward);
	IPointF3D getGroundForwardVector();
	IPointF3D getGroundRightVector();
	void moveAlongGround(double right, double forward);
	double getPitch();
	double getYaw();
	double getRoll();
	void setFocusRatio(float focusRatio);
	void defaultCamera();	//jako kkdybychom s kamerou vubec nic nedelali - fajne pro zobrazeni textu na obrazovku, gui, skybox? ...
};



