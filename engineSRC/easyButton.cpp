#include "easyButton.h"

EasyButton::EasyButton(zelpMath::IPoint loc, zelpMath::IPoint res) {
	this->loc = loc;
	this->res = res;
	this->fontColor = al_map_rgb(0, 0, 0);
}

void EasyButton::bindPress(std::function<void()> func) { this->pressCallback = func; }

void EasyButton::setColor(ALLEGRO_COLOR colorIdle, ALLEGRO_COLOR colorFocus, ALLEGRO_COLOR colorPress) {
	this->colorIdle = colorIdle;
	this->colorFocus = colorFocus;
	this->colorPress = colorPress;
}

bool EasyButton::loadFont(std::string path, unsigned int size) {
	this->font = al_load_ttf_font(path.c_str(), size, 0);
	if (!this->font) { zelpMath::debugLog("Could load font : " + path);	return NULL; }
	this->fontSize = size;
	return true;
}

void EasyButton::update(zelpMath::IPointF point, bool LMB) {
	this->showColor = this->colorIdle;
	bool isPointInside = false;
	//coding war crime
	if (this->loc.x < point.x) {
		if ((this->loc.x + this->res.x) > point.x) {
			if (this->loc.y < point.y) {
				if ((this->loc.y + this->res.y) > point.y) {
					isPointInside = true;
					this->showColor = this->colorFocus;
				}
			}
		}
	}
	if (isPointInside && LMB) {
		this->showColor = this->colorPress;
		if (this->pressCallback) {
			this->pressCallback();
		}
	}
}

void EasyButton::render() { al_draw_filled_rectangle(this->loc.x, this->loc.y, this->loc.x + this->res.x, this->loc.y + this->res.y, this->showColor); }

void EasyButton::renderWithText() { 
	al_draw_filled_rectangle(this->loc.x, this->loc.y, this->loc.x + this->res.x, this->loc.y + this->res.y, this->showColor); 
	if (this->font) {
		al_draw_text(this->font, this->fontColor, this->loc.x + (this->res.x/2), this->loc.y + (this->res.y / 2) - (this->fontSize/2), ALLEGRO_ALIGN_CENTER, text.c_str());
	}
}