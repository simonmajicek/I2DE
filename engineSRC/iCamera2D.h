#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
using namespace zelpMath;

struct ICamera2D{
private :
	const float zoomSpeedIn = { 1.05f };		
	const float zoomSpeedOut = { 0.95f };
public:
	ALLEGRO_TRANSFORM view;
	ALLEGRO_TRANSFORM defaultView;
	float actualZoom;		//slouzi pro prevod World<--->Screen souradnic
public:
	ICamera2D();
	~ICamera2D();
	void update();
	void setLoc2D(IPointF location);
	void move2D(IPointF move);
	void rotate2DPivot(IPointF pivot, float angleRad);
	void zoom2DInPivot(IPointF pivot);
	void zoom2DOutPivot(IPointF pivot);
	void resetRotate2DPivot(IPointF pivot);
	void resetZoom2DPivot(IPointF pivot);
	void reset();										//reset Zoom/Rotate nefunguje na 100% - nejlepsi je to resetovat uplne a zoom/rotate nastavit od znova
	//zatim nefunguje, pokud CameraRotation != 0
	IPointF WorldToScreen(IPointF fWorld);
	IPointF ScreenToWorld(IPointF nScreen);	
	IPointF WorldToScreenPointRatio(IPointF fWorld);	//pro prevod meritka, camera ma souradnici 00
	IPointF ScreenToWorldPointRatio(IPointF nScreen);	//pro prevod meritka, camera ma souradnici 00
	void defaultCamera();	//pro zobrazeni textu atd...
};



