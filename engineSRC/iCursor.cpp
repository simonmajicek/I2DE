#include "iCursor.h"


ICursor::ICursor() {
	std::vector<ALLEGRO_BITMAP*> cursorBitmapVector;
	this->isMouseButtonPress = new bool[this->numberOfButtons];
	this->mouseButtonTimer = new uint64_t[this->numberOfButtons];
	for (int i = 0; i < this->numberOfButtons; i++) {
		this->isMouseButtonPress[i] = false;
		this->mouseButtonTimer[i] = 0;
	}

	this->event_queue = al_create_event_queue();
	al_register_event_source(this->event_queue, al_get_mouse_event_source());
}

ICursor::~ICursor() {
	al_destroy_event_queue(this->event_queue);
}

void ICursor::update() {
	this->updateCount++;
	this->scrolling = 0;
	//pro panning
	this->prevLoc = this->loc;
	ALLEGRO_EVENT events;
	while (al_get_next_event(event_queue, &events)) {
		if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
			this->setLoc(IPointF(events.mouse.x, events.mouse.y));
			if (events.mouse.dz > 0) { this->scrolling = 1; }
			if (events.mouse.dz < 0) { this->scrolling = -1; }
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (events.mouse.button == 1) {
				this->setLMB(true);
			}
			if (events.mouse.button == 2) {
				this->setRMB(true);
			}
			if (events.mouse.button == 3) {
				this->setMMB(true);
			}
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (events.mouse.button == 1) {
				this->setLMB(false);
			}
			if (events.mouse.button == 2) {
				this->setRMB(false);
			}
			if (events.mouse.button == 3) {
				this->setMMB(false);
			}
		}
	}
}

short unsigned int ICursor::getMouseButtonState(short unsigned int mouseButton) {
	if (this->isMouseButtonPress[mouseButton]) {
		if (this->mouseButtonTimer[mouseButton] == this->updateCount) {return MB_PRESS;}
		return MB_HOLD;
	}
	return MB_FREE;
}

bool ICursor::isMouseButtonLikeState(short unsigned int mouseButton, short unsigned state) {
	if (this->getMouseButtonState(mouseButton) & state) {return true;}
	return false;
}

void ICursor::setMouseButton(short unsigned int mouseButton, bool mouseButtonIsPress) {
	this->isMouseButtonPress[mouseButton] = mouseButtonIsPress;
	if (mouseButtonIsPress) {
		this->mouseButtonTimer[mouseButton] = this->updateCount;
	}
}

void ICursor::resetCursorEvents() {
	for (int i = 0; i < this->numberOfButtons; i++) {
		this->isMouseButtonPress[i] = false;
		this->mouseButtonTimer[i] = this->updateCount;
	}
}

void ICursor::setLoc(IPointF loc) {this->loc = loc;}
void ICursor::setOriginLoc(IPointF originLoc) {this->originLoc = originLoc;}
IPointF ICursor::getPan() { return (this->prevLoc - this->loc); }
bool ICursor::getLMB(){return this->isMouseButtonPress[LMB];};
bool ICursor::getMMB(){return this->isMouseButtonPress[MMB];};
bool ICursor::getRMB(){return this->isMouseButtonPress[RMB];};
void ICursor::setLMB(bool press){this->setMouseButton(LMB, press);};
void ICursor::setMMB(bool press){this->setMouseButton(MMB, press);};
void ICursor::setRMB(bool press){this->setMouseButton(RMB, press);};
