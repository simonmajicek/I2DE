#include "easyTextfield.h"

EasyTextfield::EasyTextfield(zelpMath::IPoint loc, zelpMath::IPoint res) {
	this->loc = loc;
	this->res = res;
	this->fontColor = al_map_rgb(0, 0, 0);
	this->colorIdle = al_map_rgb(90, 90, 90);
	this->colorFocus = al_map_rgb(200, 200, 200);
	this->focus = false;
}

bool EasyTextfield::loadFont(std::string path, unsigned int size) {
	this->font = al_load_ttf_font(path.c_str(), size, 0);
	if (!this->font) { zelpMath::debugLog("Could load font : " + path);	return NULL; }
	this->fontSize = size;
	return true;
}

void EasyTextfield::update(zelpMath::IPointF point, bool LMB) {
	bool isPointInside = false;
	//coding war crime
	if (this->loc.x < point.x) {
		if ((this->loc.x + this->res.x) > point.x) {
			if (this->loc.y < point.y) {
				if ((this->loc.y + this->res.y) > point.y) {
					isPointInside = true;
				}
			}
		}
	}
	if (isPointInside && LMB) {
		this->focus = true;
	}
}

void EasyTextfield::render() {
	ALLEGRO_COLOR showColor = (focus) ? this->colorFocus : this->colorIdle;
	al_draw_filled_rectangle(this->loc.x, this->loc.y, this->loc.x + this->res.x, this->loc.y + this->res.y, showColor);
	if (this->font) {
		al_draw_text(this->font, this->fontColor, this->loc.x + 10, this->loc.y + (this->res.y / 2.0) - (this->fontSize / 2.0), ALLEGRO_ALIGN_LEFT, text.c_str());
	}
}