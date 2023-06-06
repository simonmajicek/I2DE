#include "iGraphic.h"

IGraphic::IGraphic() {};
IGraphic::~IGraphic() { al_destroy_bitmap(this->bitmap); };

bool IGraphic::loadBitmap(std::string path) {
	this->bitmap = al_load_bitmap(path.c_str());
	if (!bitmap) { debugLog("Could load bitmap : " + path);	return NULL; }
	this->res.x = al_get_bitmap_width(this->bitmap);
	this->res.y = al_get_bitmap_height(this->bitmap);;
	this->halfRes.x = al_get_bitmap_width(this->bitmap) / 2;;
	this->halfRes.y = al_get_bitmap_height(this->bitmap) / 2;;
	return true;
}

void IGraphic::render() {
	al_draw_scaled_rotated_bitmap(this->bitmap, this->halfRes.x, this->halfRes.y, this->loc.x, this->loc.y, this->size, this->size, this->angleRad, this->bitmapFlags);
}

void IGraphic::render2() {
	al_draw_bitmap(this->bitmap, this->loc.x, this->loc.y, 0);
}

bool IGraphic::isPointInside(IPointF point) {
	//L - left, R - Right, T - Top, B - Botton
	IPointF LT = IPointF(0.0f);
	IPointF RT = IPointF(0.0f);
	IPointF RB = IPointF(0.0f);
	IPointF LB = IPointF(0.0f);

	float halfW = (this->halfRes.x * this->size);
	float halfH = (this->halfRes.y * this->size);

	LT = IPointF(this->loc.x - halfW, this->loc.y - halfH);
	RT = IPointF(this->loc.x + halfW, this->loc.y - halfH);
	RB = IPointF(this->loc.x + halfW, this->loc.y + halfH);
	LB = IPointF(this->loc.x - halfW, this->loc.y + halfH);

	if (LT.x < point.x) {
		if (LT.y < point.y) {
			if (RB.x > point.x) {
				if (RB.y > point.y) {
					return true;
				}
			}
		}
	}

	return false;
}

