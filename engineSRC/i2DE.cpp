#include "i2DE.h"

I2DE* I2DE::single = NULL;

I2DE* I2DE::getInstance(){
	if (!single){
		single = new I2DE();
		return single;
	}
	return single;
}

I2DE::I2DE(){
	srand(time(NULL));
}

I2DE::~I2DE(){}

bool I2DE::initEngine() {
	if (!al_init()) {
		al_show_native_message_box(NULL, "Error", "Failed to initialize allegro!", "", "", ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_primitives_addon()) {
		al_show_native_message_box(NULL, "Error", "Failed to initialize primitives!", "", "", ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_install_audio()) {
		al_show_native_message_box(NULL, "Error", "Failed to initialize audio!", "", "", ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_acodec_addon()) {
		al_show_native_message_box(NULL, "Error", "Failed to initialize audio codecs!", "", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(NULL, "Error", "Failed to initialize image!", "", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_init_ttf_addon()) {
		al_show_native_message_box(NULL, "Error", "Failed to initialize ttf!", "", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_install_keyboard()) {
		al_show_native_message_box(NULL, "Error", "Failed to install keyboard!", "", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	if (!al_install_mouse()) {
		al_show_native_message_box(NULL, "Error", "Failed to install mouse!", "", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}
	
	al_init_font_addon(); //Vraci void

	return true;
}