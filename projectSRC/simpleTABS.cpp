#include "simpleTABS.h"

struct SimpleButton {
	IPointF loc;
	IPointF res;
	IFont* font;
	ALLEGRO_COLOR color;
	std::string buttonText;
	void render() {
		al_draw_filled_rectangle(loc.x, loc.y, loc.x + res.x, loc.y + res.y, color);
		font->loc = IPoint(loc.x + (res.x / 2), loc.y + (res.y / 2) - font->getSize() * 0.5);
		font->render(buttonText);
	}
	bool isPointInside(IPointF p) {
		//WAR CRIME IN CODING :D
		if (p.x > loc.x) {
			if (p.x < (loc.x + res.x)) {
				if (p.y > loc.y) {
					if (p.y < (loc.y + res.y)) {
						return true;
					}
				}
			}
		}
		return false;
	}
};

struct TAB {
	IPointF loc;
	float radius = {10};
	IFont* font;
	ALLEGRO_COLOR color;
	std::string text;
	int value = {-1};
	void render() {
		if(value != -1){
			al_draw_filled_circle(loc.x, loc.y, radius, color);
			text = std::to_string(value);
			font->loc = IPoint(loc.x, loc.y - font->getSize() * 0.5);
			font->render(text);
		}
		else {
			al_draw_filled_circle(loc.x, loc.y, radius, al_map_rgba(0, 0, 0, 20));
		}
	}
	bool isPointInside(IPointF p) {
		float dist = (p.x - loc.x) * (p.x - loc.x) + (p.y - loc.y) * (p.y - loc.y);
		if (dist <= (radius*4)) { return true; }
		return false;
	}
};

struct Axis {
	IPointF loc;
	IPointF res = { IPointF(250, 125) };
	std::vector<TAB*> vecOfTabs;
	void render() {
		al_draw_line(loc.x, loc.y, loc.x, loc.y + res.y, al_map_rgb(0, 0, 0), 3.0f);
		al_draw_line(loc.x + res.x, loc.y, loc.x + res.x, loc.y + res.y, al_map_rgb(0, 0, 0), 3.0f);
		for (unsigned int i = 0; i <= 5; i++) {
			al_draw_line(loc.x, loc.y + (i * (res.y/5)), loc.x + res.x, loc.y + (i * (res.y / 5)), al_map_rgb(0, 0, 0), 1.0f);
		}
		for (auto t : vecOfTabs) {
			t->render();
		}
	}
	void init(IFont* font) {
		for (unsigned int y = 0; y <= 5; y++) {
			for (unsigned int x = 1; x < 9; x++) {
				TAB* t = new TAB;
				t->font = font;
				t->color = al_map_rgb(0, 0, 0);
				t->loc = IPointF(loc.x + (x * (res.x / 9)), loc.y + (y * (res.y / 5)));
				vecOfTabs.push_back(t);
			}
		}
	}
};

void simpleTABS() {
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay display;
	ICursor cursor;
	display.create();
	display.setTitle("Simple TABS");
	display.changeResolution(IPoint(1325, 1200));
	display.setPosition(IPoint(0, 0));
	IFont* fontButton = new IFont;
	fontButton->loadFont("assets/examples/arial.ttf", 15);
	fontButton->color = al_map_rgb(20, 20, 20);
	fontButton->flag = ALLEGRO_ALIGN_CENTER;

	IFont* fontTAB = new IFont;
	fontTAB->loadFont("assets/examples/arial.ttf", 16);
	fontTAB->color = al_map_rgb(0, 0, 0);
	fontTAB->flag = ALLEGRO_ALIGN_CENTER;

	SimpleButton addButton;
	addButton.color = al_map_rgb(200, 200, 200);
	addButton.loc = IPointF(10, 10);
	addButton.res = IPointF(75, 25);
	addButton.font = fontButton;
	addButton.buttonText = "ADD";

	SimpleButton removeButton;
	removeButton.color = al_map_rgb(200, 200, 200);
	removeButton.loc = IPointF(95, 10);
	removeButton.res = IPointF(75, 25);
	removeButton.font = fontButton;
	removeButton.buttonText = "REMOVE";

	SimpleButton saveButton;
	saveButton.color = al_map_rgb(200, 200, 200);
	saveButton.loc = IPointF(180, 10);
	saveButton.res = IPointF(75, 25);
	saveButton.font = fontButton;
	saveButton.buttonText = "SAVE";

	std::vector<Axis*> vecOfA;
	Axis* test = new Axis;
	test->loc = { 20, 50 };
	test->init(fontTAB);
	vecOfA.push_back(test);

	scene.bindInit([&] {
		al_clear_to_color(al_map_rgb(250, 250, 250));
		});

	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		cursor.update();

		if(addButton.isPointInside(cursor.loc)) {
			addButton.color = al_map_rgb(200, 200, 200);
			if (cursor.getLMB()) {
				cursor.setLMB(false);	
				//hack
				Axis* newest = new Axis;
				Axis* last = vecOfA.at(vecOfA.size()-1);
				if (((vecOfA.size()-1) % 5) == 4) {		//na jednom radku jsou 4x Axis
					newest->loc = { 20, last->loc.y + (last->res.y * 1.5f) };
				}
				else {
					newest->loc = { last->loc.x + last->res.x, last->loc.y };
				}
				newest->init(fontTAB);
				vecOfA.push_back(newest);
			}
		}
		else {addButton.color = al_map_rgb(160, 160, 160);}

		if (removeButton.isPointInside(cursor.loc)) { 
			removeButton.color = al_map_rgb(200, 200, 200); 
			if (cursor.getLMB()) {
				cursor.setLMB(false);		//hack
				if (vecOfA.size() > 1) {
					delete vecOfA.at(vecOfA.size() - 1);
					vecOfA.pop_back();
				}
			}
		}
		else { removeButton.color = al_map_rgb(160, 160, 160); }

		if (saveButton.isPointInside(cursor.loc)) { 
			saveButton.color = al_map_rgb(200, 200, 200);
			if (cursor.getLMB()) {
				cursor.setLMB(false);		//hack
				ALLEGRO_BITMAP* tmp = al_get_backbuffer(display.display);
				saveBitmapToFile(tmp, "tab.png");
			}
		}
		else { saveButton.color = al_map_rgb(160, 160, 160); }

		for(auto a : vecOfA){
			for (auto t : a->vecOfTabs) {
				if (t->isPointInside(cursor.loc)) {
					t->color = al_map_rgb(80, 80, 80);
					if (cursor.getLMB()) { 
						t->value++; 
						cursor.setLMB(false);		//hack
					}
					if (cursor.getRMB()) { 
						t->value--;
						cursor.setRMB(false);		//hack
					}
				}
				else {
					t->color = al_map_rgb(255, 255, 255);
				}
			}
		}
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(250, 250, 250));
		addButton.render();
		removeButton.render();
		saveButton.render();
		for (auto a : vecOfA) {
			a->render();
		}
		al_flip_display();
		});

	scene.run();
}