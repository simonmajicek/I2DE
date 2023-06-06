#include "iDisplay.h"

IDisplay::IDisplay(IPoint res){this->res = res;}
IDisplay::~IDisplay(){al_destroy_display(this->display);}

bool IDisplay::create(short int flags) {
	al_set_new_display_flags(flags);
	this->display = al_create_display(this->res.x, this->res.y);
	if (!this->display) {return false;}
	al_set_target_backbuffer(this->display);
	//osetreni, pokud okno je fullscreen, nastavi hnedka rozliseni
	this->changeResolution(IPoint(al_get_display_width(this->display), al_get_display_height(this->display)));

	this->event_queue = al_create_event_queue();
	al_register_event_source(this->event_queue, al_get_display_event_source(this->display));

	return true;
}

bool IDisplay::update() {
	bool stillOpen = true;

	ALLEGRO_EVENT events;
	while (al_get_next_event(event_queue, &events)) {
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			if (events.display.source == this->display) {stillOpen = false;}
		}
		if (events.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT){if(this->onLostFocus) this->onLostFocus();}
		if (events.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN){if(this->onGetFocus) this->onGetFocus();}

		if (events.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
			this->changeResolution(IPoint(events.display.width, events.display.height));
			if (this->onResize) { this->onResize(); }
		}
	}
	return stillOpen;
}

bool IDisplay::setFullscreen(bool fullscreen) {
	bool help = al_set_display_flag(this->display, ALLEGRO_FULLSCREEN_WINDOW, fullscreen);
	if (help) {
		this->changeResolution(IPoint(al_get_display_width(this->display), al_get_display_height(this->display)));
	}
	else { std::cout << "ERROR : Display : setFullscreen" << std::endl;}
	return help;
}

bool IDisplay::getFullscreen() {
	if (al_get_display_flags(this->display) & ALLEGRO_FULLSCREEN) { return true; }
	if (al_get_display_flags(this->display) & ALLEGRO_FULLSCREEN_WINDOW) { return true; }
	return false;
}

bool IDisplay::changeResolution(IPoint res) {
	this->res = res;
	if (this->res.x < this->minRes.x) {this->res.x = this->minRes.x;}
	if (this->res.y < this->minRes.y) {this->res.y = this->minRes.y;}

	bool help = al_resize_display(this->display, this->res.x, this->res.y);
	if (!help) { std::cout << "ERROR : Display : resize" << std::endl;}
	return help;
}

int IDisplay::getResX() { return al_get_display_width(this->display); };
int IDisplay::getResY() { return al_get_display_height(this->display); };
void IDisplay::bindGetFocus(std::function<void()> func) { this->onGetFocus = func; }
void IDisplay::bindLostFocus(std::function<void()> func) { this->onLostFocus = func; }
void IDisplay::bindResize(std::function<void()> func) { this->onResize = func; }
void IDisplay::setTitle(std::string title) { al_set_window_title(this->display, title.c_str()); }
void IDisplay::setPosition(IPoint windowPosition) { al_set_window_position(this->display, windowPosition.x, windowPosition.x); }
void IDisplay::showCursor() {al_show_mouse_cursor(this->display);}
void IDisplay::hideCursor() { al_hide_mouse_cursor(this->display); }