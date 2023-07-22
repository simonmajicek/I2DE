#include "iKeyboard.h"

IKeyboard::IKeyboard() {
	this->isKeyPress = new bool[this->numberOfKey];
	this->keyTimer = new uint64_t[this->numberOfKey];
	this->keyChar = new char[this->numberOfKey];
	for (int i = 0; i < this->numberOfKey; i++) {
		this->isKeyPress[i] = false;
		this->keyTimer[i] = 0;
		this->keyChar[i] = '0';
	}

	this->event_queue = al_create_event_queue();
	al_register_event_source(this->event_queue, al_get_keyboard_event_source());

	this->initKeyChar();
}

IKeyboard::~IKeyboard() {
	delete this->isKeyPress;
	delete this->keyTimer;
	delete this->keyChar;
	this->isKeyPress = NULL;
	this->keyTimer = NULL;
	this->keyChar = NULL;

	al_destroy_event_queue(this->event_queue);
}

void IKeyboard::update() {
	this->updateCount++;

	ALLEGRO_EVENT events;
	while (al_get_next_event(event_queue, &events)) {
		if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_A:	this->setKey(KEY_A, true); break;
			case ALLEGRO_KEY_B:	this->setKey(KEY_B, true); break;
			case ALLEGRO_KEY_C:	this->setKey(KEY_C, true); break;
			case ALLEGRO_KEY_D:	this->setKey(KEY_D, true); break;
			case ALLEGRO_KEY_E:	this->setKey(KEY_E, true); break;
			case ALLEGRO_KEY_F:	this->setKey(KEY_F, true); break;
			case ALLEGRO_KEY_G:	this->setKey(KEY_G, true); break;
			case ALLEGRO_KEY_H:	this->setKey(KEY_H, true); break;
			case ALLEGRO_KEY_I:	this->setKey(KEY_I, true); break;
			case ALLEGRO_KEY_J:	this->setKey(KEY_J, true); break;
			case ALLEGRO_KEY_K:	this->setKey(KEY_K, true); break;
			case ALLEGRO_KEY_L:	this->setKey(KEY_L, true); break;
			case ALLEGRO_KEY_M:	this->setKey(KEY_M, true); break;
			case ALLEGRO_KEY_N:	this->setKey(KEY_N, true); break;
			case ALLEGRO_KEY_O:	this->setKey(KEY_O, true); break;
			case ALLEGRO_KEY_P:	this->setKey(KEY_P, true); break;
			case ALLEGRO_KEY_Q:	this->setKey(KEY_Q, true); break;
			case ALLEGRO_KEY_R:	this->setKey(KEY_R, true); break;
			case ALLEGRO_KEY_S:	this->setKey(KEY_S, true); break;
			case ALLEGRO_KEY_T:	this->setKey(KEY_T, true); break;
			case ALLEGRO_KEY_U:	this->setKey(KEY_U, true); break;
			case ALLEGRO_KEY_V:	this->setKey(KEY_V, true); break;
			case ALLEGRO_KEY_W:	this->setKey(KEY_W, true); break;
			case ALLEGRO_KEY_X:	this->setKey(KEY_X, true); break;
			case ALLEGRO_KEY_Y:	this->setKey(KEY_Y, true); break;
			case ALLEGRO_KEY_Z:	this->setKey(KEY_Z, true); break;
			case ALLEGRO_KEY_0:	this->setKey(KEY_Normal0, true); break;
			case ALLEGRO_KEY_1:	this->setKey(KEY_Normal1, true); break;
			case ALLEGRO_KEY_2:	this->setKey(KEY_Normal2, true); break;
			case ALLEGRO_KEY_3:	this->setKey(KEY_Normal3, true); break;
			case ALLEGRO_KEY_4:	this->setKey(KEY_Normal4, true); break;
			case ALLEGRO_KEY_5:	this->setKey(KEY_Normal5, true); break;
			case ALLEGRO_KEY_6:	this->setKey(KEY_Normal6, true); break;
			case ALLEGRO_KEY_7:	this->setKey(KEY_Normal7, true); break;
			case ALLEGRO_KEY_8:	this->setKey(KEY_Normal8, true); break;
			case ALLEGRO_KEY_9:	this->setKey(KEY_Normal9, true); break;
			case ALLEGRO_KEY_PAD_0:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_1:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_2:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_3:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_4:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_5:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_6:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_7:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_8:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PAD_9:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_ESCAPE:this->setKey(KEY_ESC, true); break;
			case ALLEGRO_KEY_ALT:	this->setKey(KEY_ALT, true); break;
			case ALLEGRO_KEY_ENTER:	this->setKey(KEY_ENTER, true); break;
			case ALLEGRO_KEY_SPACE:	this->setKey(KEY_SPACE, true); break;
			case ALLEGRO_KEY_LEFT:	this->setKey(KEY_ARROW_LEFT, true); break;
			case ALLEGRO_KEY_RIGHT:	this->setKey(KEY_ARROW_RIGHT, true); break;
			case ALLEGRO_KEY_UP:	this->setKey(KEY_ARROW_UP, true); break;
			case ALLEGRO_KEY_DOWN:	this->setKey(KEY_ARROW_DOWN, true); break;
			case ALLEGRO_KEY_PGUP:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_PGDN:	this->setKey(KEY_Pad0, true); break;
			case ALLEGRO_KEY_BACKSPACE:	this->setKey(KEY_BACKSPACE, true); break;
			case ALLEGRO_KEY_TILDE:	/*this->setKey(KEY_Pad0, true);*/ break;
			case ALLEGRO_KEY_MINUS:	this->setKey(KEY_MINUS, true); break;
			case ALLEGRO_KEY_PAD_MINUS:	this->setKey(KEY_MINUS, true); break;
			case ALLEGRO_KEY_SEMICOLON:	this->setKey(KEY_SEMICOLON, true); break;
			}
			if (this->keyDownCallback) { this->keyDownCallback(); }
		}
		else if (events.type == ALLEGRO_EVENT_KEY_UP) {
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_A:	this->setKey(KEY_A, false); break;
			case ALLEGRO_KEY_B:	this->setKey(KEY_B, false); break;
			case ALLEGRO_KEY_C:	this->setKey(KEY_C, false); break;
			case ALLEGRO_KEY_D:	this->setKey(KEY_D, false); break;
			case ALLEGRO_KEY_E:	this->setKey(KEY_E, false); break;
			case ALLEGRO_KEY_F:	this->setKey(KEY_F, false); break;
			case ALLEGRO_KEY_G:	this->setKey(KEY_G, false); break;
			case ALLEGRO_KEY_H:	this->setKey(KEY_H, false); break;
			case ALLEGRO_KEY_I:	this->setKey(KEY_I, false); break;
			case ALLEGRO_KEY_J:	this->setKey(KEY_J, false); break;
			case ALLEGRO_KEY_K:	this->setKey(KEY_K, false); break;
			case ALLEGRO_KEY_L:	this->setKey(KEY_L, false); break;
			case ALLEGRO_KEY_M:	this->setKey(KEY_M, false); break;
			case ALLEGRO_KEY_N:	this->setKey(KEY_N, false); break;
			case ALLEGRO_KEY_O:	this->setKey(KEY_O, false); break;
			case ALLEGRO_KEY_P:	this->setKey(KEY_P, false); break;
			case ALLEGRO_KEY_Q:	this->setKey(KEY_Q, false); break;
			case ALLEGRO_KEY_R:	this->setKey(KEY_R, false); break;
			case ALLEGRO_KEY_S:	this->setKey(KEY_S, false); break;
			case ALLEGRO_KEY_T:	this->setKey(KEY_T, false); break;
			case ALLEGRO_KEY_U:	this->setKey(KEY_U, false); break;
			case ALLEGRO_KEY_V:	this->setKey(KEY_V, false); break;
			case ALLEGRO_KEY_W:	this->setKey(KEY_W, false); break;
			case ALLEGRO_KEY_X:	this->setKey(KEY_X, false); break;
			case ALLEGRO_KEY_Y:	this->setKey(KEY_Y, false); break;
			case ALLEGRO_KEY_Z:	this->setKey(KEY_Z, false); break;
			case ALLEGRO_KEY_0:	this->setKey(KEY_Normal0, false); break;
			case ALLEGRO_KEY_1:	this->setKey(KEY_Normal1, false); break;
			case ALLEGRO_KEY_2:	this->setKey(KEY_Normal2, false); break;
			case ALLEGRO_KEY_3:	this->setKey(KEY_Normal3, false); break;
			case ALLEGRO_KEY_4:	this->setKey(KEY_Normal4, false); break;
			case ALLEGRO_KEY_5:	this->setKey(KEY_Normal5, false); break;
			case ALLEGRO_KEY_6:	this->setKey(KEY_Normal6, false); break;
			case ALLEGRO_KEY_7:	this->setKey(KEY_Normal7, false); break;
			case ALLEGRO_KEY_8:	this->setKey(KEY_Normal8, false); break;
			case ALLEGRO_KEY_9:	this->setKey(KEY_Normal9, false); break;
			case ALLEGRO_KEY_PAD_0:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_1:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_2:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_3:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_4:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_5:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_6:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_7:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_8:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PAD_9:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_ESCAPE:this->setKey(KEY_ESC, false); break;
			case ALLEGRO_KEY_ALT:	this->setKey(KEY_ALT, false); break;
			case ALLEGRO_KEY_ENTER:	this->setKey(KEY_ENTER, false); break;
			case ALLEGRO_KEY_SPACE:	this->setKey(KEY_SPACE, false); break;
			case ALLEGRO_KEY_LEFT:	this->setKey(KEY_ARROW_LEFT, false); break;
			case ALLEGRO_KEY_RIGHT:	this->setKey(KEY_ARROW_RIGHT, false); break;
			case ALLEGRO_KEY_UP:	this->setKey(KEY_ARROW_UP, false); break;
			case ALLEGRO_KEY_DOWN:	this->setKey(KEY_ARROW_DOWN, false); break;
			case ALLEGRO_KEY_PGUP:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_PGDN:	this->setKey(KEY_Pad0, false); break;
			case ALLEGRO_KEY_BACKSPACE:	this->setKey(KEY_BACKSPACE, false); break;
			case ALLEGRO_KEY_TILDE:	/*this->setKey(KEY_Pad0, true);*/ break;
			case ALLEGRO_KEY_MINUS:	this->setKey(KEY_MINUS, false); break;
			case ALLEGRO_KEY_PAD_MINUS:	this->setKey(KEY_MINUS, false); break;
			case ALLEGRO_KEY_SEMICOLON:	this->setKey(KEY_SEMICOLON, false); break;
			}
		}
		if (this->keyUpCallback) { this->keyUpCallback(); }
	}
}

short unsigned int IKeyboard::getKeyState(short unsigned int key) {
	if (this->isKeyPress[key]) {
		if (this->keyTimer[key] == this->updateCount) {return KEY_PRESS;}
		return KEY_HOLD;
	}
	return KEY_FREE;
}

void IKeyboard::setKey(short unsigned int key, bool keyIsPress) {
	this->isKeyPress[key] = keyIsPress;
	if (keyIsPress) {this->keyTimer[key] = this->updateCount;}
}

bool IKeyboard::isKeyLikeState(short unsigned int key, short unsigned state) {
	if (this->getKeyState(key) & state) {return true;}
	return false;
}

char IKeyboard::getKeyCharacter(short unsigned int key){return this->keyChar[key];};

void IKeyboard::initKeyChar() {
	keyChar[KEY_A] = 'a';
	keyChar[KEY_B] = 'b';
	keyChar[KEY_C] = 'c';
	keyChar[KEY_D] = 'd';
	keyChar[KEY_E] = 'e';
	keyChar[KEY_F] = 'f';
	keyChar[KEY_G] = 'g';
	keyChar[KEY_H] = 'h';
	keyChar[KEY_I] = 'i';
	keyChar[KEY_J] = 'j';
	keyChar[KEY_K] = 'k';
	keyChar[KEY_L] = 'l';
	keyChar[KEY_M] = 'm';
	keyChar[KEY_N] = 'n';
	keyChar[KEY_O] = 'o';
	keyChar[KEY_P] = 'p';
	keyChar[KEY_Q] = 'q';
	keyChar[KEY_R] = 'r';
	keyChar[KEY_S] = 's';
	keyChar[KEY_T] = 't';
	keyChar[KEY_U] = 'u';
	keyChar[KEY_V] = 'v';
	keyChar[KEY_W] = 'w';
	keyChar[KEY_X] = 'x';
	keyChar[KEY_Y] = 'y';
	keyChar[KEY_Z] = 'z';
	keyChar[KEY_Normal0] = '0';
	keyChar[KEY_Normal1] = '1';
	keyChar[KEY_Normal2] = '2';
	keyChar[KEY_Normal3] = '3';
	keyChar[KEY_Normal4] = '4';
	keyChar[KEY_Normal5] = '5';
	keyChar[KEY_Normal6] = '6';
	keyChar[KEY_Normal7] = '7';
	keyChar[KEY_Normal8] = '8';
	keyChar[KEY_Normal9] = '9';
	keyChar[KEY_Pad0] = '0';
	keyChar[KEY_Pad1] = '1';
	keyChar[KEY_Pad2] = '2';
	keyChar[KEY_Pad3] = '3';
	keyChar[KEY_Pad4] = '4';
	keyChar[KEY_Pad5] = '5';
	keyChar[KEY_Pad6] = '6';
	keyChar[KEY_Pad7] = '7';
	keyChar[KEY_Pad8] = '8';
	keyChar[KEY_Pad9] = '9';
	keyChar[KEY_ESC] = '-';
	keyChar[KEY_ALT] = '-';
	keyChar[KEY_ENTER] = '-';
	keyChar[KEY_SPACE] = ' ';
	keyChar[KEY_ARROW_UP] = '-';
	keyChar[KEY_ARROW_DOWN] = '.';
	keyChar[KEY_ARROW_LEFT] = '[';
	keyChar[KEY_ARROW_RIGHT] = ']';
	keyChar[KEY_BACKSPACE] = '-';
	keyChar[KEY_MINUS] = '-';
	keyChar[KEY_SEMICOLON] = ';';
}


void IKeyboard::bindKeyDown(std::function<void()> func) { this->keyDownCallback = func; }
void IKeyboard::bindKeyUp(std::function<void()> func) { this->keyUpCallback = func; }
void IKeyboard::resetKeyboardEvents() {
	for (int i = 0; i < this->numberOfKey; i++) {this->isKeyPress[i] = false;}
}