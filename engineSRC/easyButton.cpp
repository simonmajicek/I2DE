#include "easyButton.h"

EasyButton::EasyButton(zelpMath::IPoint loc, zelpMath::IPoint res) {
	this->loc = loc;
	this->res = res;
}

void EasyButton::bindPress(std::function<void()> func) { this->pressCallback = func; }

void EasyButton::setColor(ALLEGRO_COLOR colorIdle, ALLEGRO_COLOR colorFocus, ALLEGRO_COLOR colorPress) {
	this->colorIdle = colorIdle;
	this->colorFocus = colorFocus;
	this->colorPress = colorPress;
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
