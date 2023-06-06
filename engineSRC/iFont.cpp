#include "iFont.h"

IFont::IFont() {
	color = al_map_rgb(255, 255, 255);
};

IFont::~IFont() {
	al_destroy_font(this->font); 
};

bool IFont::loadFont(std::string path, unsigned int size) {
	this->font = al_load_ttf_font(path.c_str(), size, 0);
	if (!this->font) { debugLog("Could load font : " + path);	return NULL; }
	this->size = size;
	return true;
}

void IFont::render(std::string text) {
	if (this->font) {
		al_draw_text(this->font, this->color, this->loc.x, this->loc.y, this->flag, text.c_str());
	}
}

void IFont::renderUnicode(ALLEGRO_USTR* unicodeText) {
	if (this->font) {
		if (unicodeText) {
			al_draw_ustr(this->font, this->color, this->loc.x, this->loc.y, this->flag, unicodeText);
		}
	}
}
