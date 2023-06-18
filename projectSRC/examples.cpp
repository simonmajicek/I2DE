#include "examples.h"

void randomWalker() {
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay display;
	display.create();
	IPointF walkerLoc = IPointF(display.res.x / 2, display.res.y / 2);
	display.setTitle("Random Walker");

	display.bindResize([&] {
		al_draw_filled_rectangle(0, 0, display.res.x, display.res.y, al_map_rgba(25, 25, 25, 1));
		walkerLoc = IPointF(display.res.x / 2, display.res.y / 2);
		});

	scene.bindInit([] {al_clear_to_color(al_map_rgb(25, 25, 25));});
	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		walkerLoc.x += rand() % 3 - 1;
		walkerLoc.y += rand() % 3 - 1;
		});

	scene.bindRender([&] {
		al_draw_filled_rectangle(0, 0, display.res.x, display.res.y, al_map_rgba(0, 0, 0, 1));
		al_draw_filled_circle(walkerLoc.x, walkerLoc.y, 2.0f, al_map_rgb(180, 0, 180));
		al_flip_display();
		});

	scene.run();
}

void drawWithPixels() {
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	scene.setFPS(1.0f / 120.0f);
	IDisplay display;
	display.create();
	display.setTitle("Draw With Pixels");

	IGraphic* bitmap = new IGraphic();
	bitmap->loadBitmap("assets/examples/bird.png");
	bitmap->loc = IPointF(bitmap->halfRes.x, bitmap->halfRes.y);		//posunu na levy horni roh okna
	display.changeResolution(IPoint(bitmap->res.x*2, bitmap->res.y));
	IPoint brushLoc;
	ALLEGRO_COLOR color;

	scene.bindUpdate([&] {scene.breakLoop = !display.update();	});
	scene.bindInit([=] {al_clear_to_color(al_map_rgb(0, 25, 25));});

	scene.bindRender([&] {
		for(unsigned int i = 0; i < 50; i++){
			brushLoc.x = rand() % bitmap->res.x;
			brushLoc.y = rand() % bitmap->res.y;
			color = al_get_pixel(bitmap->bitmap, brushLoc.x, brushLoc.y);
			al_draw_filled_circle(bitmap->res.x + brushLoc.x, brushLoc.y, 5.0f, color);
		}
		bitmap->render();
		al_flip_display();
		});

	scene.run();
}

void showClock() {
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay display;
	display.create(ALLEGRO_RESIZABLE);
	display.setTitle("Clock");
	display.changeResolution(IPoint(600, 600));
	display.setPosition(IPoint(0, 0));
	IFont clockFace;
	clockFace.loadFont("assets/examples/arial.ttf", 40);
	clockFace.color = al_map_rgb(235, 235, 235);
	clockFace.flag = ALLEGRO_ALIGN_CENTER;
	zelpWindowsOS::SystemTime aTime;
	IPoint center;
	int radius;
	std::string clockText;

	display.bindResize([&] {
		center = IPoint(display.res.x / 2, display.res.y / 2);
		radius = (display.res.y / 2) * 0.95;
		clockFace.loc = IPoint(display.res.x / 2, (display.res.y / 2) - clockFace.getSize() * 0.5);
		});

	scene.bindInit([&] {
		center = IPoint(display.res.x / 2, display.res.y / 2);
		radius = (display.res.y / 2) * 0.95;
		clockFace.loc = IPoint(display.res.x / 2, (display.res.y / 2) - clockFace.getSize() * 0.5);
		al_clear_to_color(al_map_rgb(15, 15, 15));
		});

	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		aTime.update();
		clockText = std::to_string(aTime.getHour()) + ":" + std::to_string(aTime.getMinute()) + ":" + std::to_string(aTime.getSecond());
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));
		clockFace.render(clockText);
		al_draw_arc(center.x, center.y, radius, degreeToRad(270), mapRange(aTime.getSecond(), 0, 60, 0, degreeToRad(360)), al_map_rgb(180, 60, 180), 12.0f);
		al_draw_arc(center.x, center.y, radius * 0.93, degreeToRad(270), mapRange(aTime.getMinute(), 0, 60, 0, degreeToRad(360)), al_map_rgb(60, 180, 180), 12.0f);
		al_draw_arc(center.x, center.y, radius * 0.86, degreeToRad(270), mapRange(aTime.getHour(), 0, 24, 0, degreeToRad(360)), al_map_rgb(240, 180, 60), 12.0f);
		al_flip_display();
		});

	scene.run();
}

void showClockToDesktopWallpaper() {
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	scene.setFPS(1.0f);
	IFont clockFace;
	clockFace.loadFont("assets/examples/arial.ttf", 40);
	clockFace.color = al_map_rgb(235, 235, 235);
	clockFace.flag = ALLEGRO_ALIGN_CENTER;
	zelpWindowsOS::SystemTime aTime;
	IPoint center;
	int radius;
	std::string clockText;
	ALLEGRO_BITMAP* canvas = al_create_bitmap(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_target_bitmap(canvas);

	scene.bindInit([&] {
		center = IPoint(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		radius = (WINDOW_HEIGHT / 2) * 0.95;
		clockFace.loc = IPoint(WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 2) - clockFace.getSize() * 0.5);
		al_clear_to_color(al_map_rgb(15, 15, 15));
		});

	scene.bindUpdate([&] {
		//scene.breakLoop = !display.update();
		aTime.update();
		clockText = std::to_string(aTime.getHour()) + ":" + std::to_string(aTime.getMinute()) + ":" + std::to_string(aTime.getSecond());
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));
		clockFace.render(clockText);
		al_draw_arc(center.x, center.y, radius, degreeToRad(270), mapRange(aTime.getSecond(), 0, 60, 0, degreeToRad(360)), al_map_rgb(180, 60, 180), 12.0f);
		al_draw_arc(center.x, center.y, radius * 0.93, degreeToRad(270), mapRange(aTime.getMinute(), 0, 60, 0, degreeToRad(360)), al_map_rgb(60, 180, 180), 12.0f);
		al_draw_arc(center.x, center.y, radius * 0.86, degreeToRad(270), mapRange(aTime.getHour(), 0, 24, 0, degreeToRad(360)), al_map_rgb(240, 180, 60), 12.0f);
		al_flip_display();

		//saveBitmapToFile(canvas, "clock.png");
		zelpWindowsOS::saveToDesktopWallpaper(canvas);
		});

	scene.run();
}

void simpleSnake() {
#define BOARD_SIZE 40
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay display;
	display.create();
	display.setTitle("Snake");
	display.changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
	scene.setFPS(1.0f / 10.0f);
	struct Food {
		IPoint loc = { IPoint(200, 200) };
		unsigned int size = { BOARD_SIZE };
		void render() {al_draw_filled_rectangle(loc.x, loc.y, loc.x + size - 2, loc.y + size - 2, al_map_rgb(240, 20, 20));}
	};

	struct Snake {
		IPoint loc = {IPoint(0, 0)};
		unsigned int size = { BOARD_SIZE };
		unsigned int dir = {3};
		IKeyboard keyboard;
		std::vector<IPoint> tail;
		void render() {
			al_draw_filled_rectangle(loc.x, loc.y, loc.x + size - 2, loc.y + size - 2, al_map_rgb(240, 240, 240));
			for (auto o : tail) {al_draw_filled_rectangle(o.x, o.y, o.x + size - 2, o.y + size - 2, al_map_rgb(240, 240, 240));}
		}
		bool eat(Food food) { if ((food.loc.x == loc.x) && (food.loc.y == loc.y)) { return true; } return false; }
		void testEdges() {
			if (loc.x < 0) {loc.x = WINDOW_WIDTH - BOARD_SIZE;}
			if (loc.x > WINDOW_WIDTH) {loc.x = 0;}
			if (loc.y < 0) {loc.y = WINDOW_HEIGHT - BOARD_SIZE;}
			if (loc.y > WINDOW_HEIGHT) {loc.y = 0;}
		}
		void update() {
			keyboard.update();

			if (tail.size() > 0) {
				for (unsigned int i = 0; i < tail.size() - 1; i++) {tail.at(i) = tail.at(i + 1);}
				tail.at(tail.size() - 1) = loc;
			}

			switch (dir) {
			case 0: {loc.y -= BOARD_SIZE;  break; }
			case 1: {loc.x -= BOARD_SIZE;  break; }
			case 2: {loc.y += BOARD_SIZE;  break; }
			case 3: {loc.x += BOARD_SIZE;  break; }
			}

			testEdges();
		}
		bool eatHimself() {
			for (auto o : tail) {if ((loc.x == o.x) && (loc.y == o.y)) { return true; }}
			return false;
		}

	};

	Snake snake;

	snake.keyboard.bindKeyDown([&] {
		if (snake.keyboard.isKeyLikeState(KEY_W, KEY_NOT_FREE) && (snake.dir != 2)) { snake.dir = 0; }
		if (snake.keyboard.isKeyLikeState(KEY_A, KEY_NOT_FREE) && (snake.dir != 3)) { snake.dir = 1; }
		if (snake.keyboard.isKeyLikeState(KEY_S, KEY_NOT_FREE) && (snake.dir != 0)) { snake.dir = 2; }
		if (snake.keyboard.isKeyLikeState(KEY_D, KEY_NOT_FREE) && (snake.dir != 1)) { snake.dir = 3; }
		if (snake.keyboard.isKeyLikeState(KEY_ESC, KEY_NOT_FREE)) { scene.breakLoop = true; }
		});

	Food food;

	scene.bindInit([&] {al_clear_to_color(al_map_rgb(25, 25, 25));});

	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		snake.update();
		if (snake.eatHimself()) { scene.breakLoop = true; }
		if (snake.eat(food)) {
			snake.tail.push_back(snake.loc);
			unsigned int col = WINDOW_WIDTH / BOARD_SIZE;
			unsigned int row = WINDOW_HEIGHT / BOARD_SIZE;
			food.loc = IPoint((rand() % col) * BOARD_SIZE, (rand() % row) * BOARD_SIZE);
		}
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));
		snake.render();
		food.render();
		al_flip_display();
		});

	scene.run();
}



void simpleSnakeOSWallpaper() {
#define BOARD_SIZE 40
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	ALLEGRO_BITMAP* canvas = al_create_bitmap(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_target_bitmap(canvas);
	scene.setFPS(1.0f / 10.0f);
	struct Food {
		IPoint loc = { IPoint(200, 200) };
		unsigned int size = { BOARD_SIZE };
		void render() { al_draw_filled_rectangle(loc.x, loc.y, loc.x + size - 2, loc.y + size - 2, al_map_rgb(240, 20, 20)); }
	};

	struct Snake {
		IPoint loc = { IPoint(0, 0) };
		unsigned int size = { BOARD_SIZE };
		unsigned int dir = { 3 };
		IKeyboard keyboard;
		std::vector<IPoint> tail;
		void render() {
			al_draw_filled_rectangle(loc.x, loc.y, loc.x + size - 2, loc.y + size - 2, al_map_rgb(240, 240, 240));
			for (auto o : tail) { al_draw_filled_rectangle(o.x, o.y, o.x + size - 2, o.y + size - 2, al_map_rgb(240, 240, 240)); }
		}
		bool eat(Food food) { if ((food.loc.x == loc.x) && (food.loc.y == loc.y)) { return true; } return false; }
		void testEdges() {
			if (loc.x < 0) { loc.x = WINDOW_WIDTH - BOARD_SIZE; }
			if (loc.x > WINDOW_WIDTH) { loc.x = 0; }
			if (loc.y < 0) { loc.y = WINDOW_HEIGHT - BOARD_SIZE; }
			if (loc.y > WINDOW_HEIGHT) { loc.y = 0; }
		}
		void update() {
			keyboard.update();

			if (tail.size() > 0) {
				for (unsigned int i = 0; i < tail.size() - 1; i++) { tail.at(i) = tail.at(i + 1); }
				tail.at(tail.size() - 1) = loc;
			}

			switch (dir) {
			case 0: {loc.y -= BOARD_SIZE;  break; }
			case 1: {loc.x -= BOARD_SIZE;  break; }
			case 2: {loc.y += BOARD_SIZE;  break; }
			case 3: {loc.x += BOARD_SIZE;  break; }
			}

			testEdges();
		}
		bool eatHimself() {
			for (auto o : tail) { if ((loc.x == o.x) && (loc.y == o.y)) { return true; } }
			return false;
		}

	};

	Snake snake;

	snake.keyboard.bindKeyDown([&] {
		if (snake.keyboard.isKeyLikeState(KEY_W, KEY_NOT_FREE) && (snake.dir != 2)) { snake.dir = 0; }
		if (snake.keyboard.isKeyLikeState(KEY_A, KEY_NOT_FREE) && (snake.dir != 3)) { snake.dir = 1; }
		if (snake.keyboard.isKeyLikeState(KEY_S, KEY_NOT_FREE) && (snake.dir != 0)) { snake.dir = 2; }
		if (snake.keyboard.isKeyLikeState(KEY_D, KEY_NOT_FREE) && (snake.dir != 1)) { snake.dir = 3; }
		if (snake.keyboard.isKeyLikeState(KEY_ESC, KEY_NOT_FREE)) { scene.breakLoop = true; }
		});

	Food food;

	scene.bindInit([&] {al_clear_to_color(al_map_rgb(25, 25, 25)); });

	scene.bindUpdate([&] {
		snake.update();
		if (snake.eatHimself()) { scene.breakLoop = true; }
		if (snake.eat(food)) {
			snake.tail.push_back(snake.loc);
			unsigned int col = WINDOW_WIDTH / BOARD_SIZE;
			unsigned int row = WINDOW_HEIGHT / BOARD_SIZE;
			food.loc = IPoint((rand() % col) * BOARD_SIZE, (rand() % row) * BOARD_SIZE);
		}
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));
		snake.render();
		food.render();
		al_flip_display();
		zelpWindowsOS::saveToDesktopWallpaper(canvas);
		});

	scene.run();
}

void imageSand() {
//close enought - verze, ktera funguje lepe je archivovana na GDRIVE
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define BRUSH_SIZE 60
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay* display;
	ICursor* cursor;

	IGraphic* bitmap = new IGraphic();
	bitmap->loadBitmap("assets/examples/birdSmall.png");
	bitmap->loc = IPointF(bitmap->halfRes.x, bitmap->halfRes.y);		//posunu na levy horni roh okna

	struct GrainOfSand {
		IPoint loc;
		IPoint originLoc;
		ALLEGRO_COLOR color;
		GrainOfSand() {};
		GrainOfSand(int x, int y, ALLEGRO_COLOR) { loc = IPoint(x, y); this->color = color; }
		void render() { al_draw_pixel(loc.x, loc.y, color); }
		void update(int cursorX, int cursorY, bool hold) {
			if (loc.x < originLoc.x) { loc.x += 1; }
			if (loc.x > originLoc.x) { loc.x -= 1; }
			if (loc.y < originLoc.y) { loc.y += 1; }
			if (loc.y > originLoc.y) { loc.y -= 1; }
			//je uvnitr stetce?
			if(hold){
				int dist = (loc.x - cursorX) * (loc.x - cursorX) + (loc.y - cursorY) * (loc.y - cursorY);
				if (dist < (BRUSH_SIZE*8)) {
					//ziskat vector rozdilu
					int tmpX = loc.x - cursorX;
					int tmpY = loc.y - cursorY;
					//umistit zrnko pisku
					loc.x -= tmpX * 4;
					loc.y -= tmpY * 4;
				}
			}
		}
	};

	int sandSize = bitmap->res.x * bitmap->res.y;
	GrainOfSand *sand = new GrainOfSand[sandSize];
	
	scene.bindInit([&] {
		IPoint grainOffset = IPoint((WINDOW_WIDTH / 2) - bitmap->halfRes.x, (WINDOW_HEIGHT / 2) - bitmap->halfRes.y);
		unsigned int index = 0;
		for (unsigned int y = 0; y < bitmap->res.y; y++) {
			for (unsigned int x = 0; x < bitmap->res.x; x++) {
				sand[index].loc = IPoint(grainOffset.x + x, grainOffset.y + y);
				sand[index].originLoc = sand[index].loc;
				sand[index].color = al_get_pixel(bitmap->bitmap, x, y);
				index++;
			}
		}
		//jakmile se spusti eventy, tak se zpomali al_get_pixel, proto inicializuji az tady
		display = new IDisplay();
		display->create();
		display->setTitle("Image is Sand");
		display->changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
		cursor = new ICursor();
		al_clear_to_color(al_map_rgb(0, 25, 25)); 
		});

	scene.bindUpdate([&] {
		scene.breakLoop = !display->update();	
		cursor->update();
		for (unsigned int i = 0; i < sandSize; i++) { sand[i].update(cursor->loc.x, cursor->loc.y, cursor->getLMB()); }
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(0, 25, 25));
		for (unsigned int i = 0; i < sandSize; i++) {	sand[i].render();}
		//if (cursor->getLMB()) { al_draw_circle(cursor->loc.x, cursor->loc.y, BRUSH_SIZE, al_map_rgb(180, 0, 180), 3); }
		al_flip_display();
		});

	scene.run();
}

void bezierTest() {
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	ICursor cursor;
	IDisplay display;
	display.create();
	display.setTitle("IBezier Struct Test");
	display.changeResolution(IPoint(600, 600));

	IBezier2D bezier;
	bezier.points[0] = { 10, 300 };
	bezier.points[1] = { 100, 20 };
	bezier.points[2] = { 400, 400 };
	bezier.points[3] = { 590, 300 };

	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		cursor.update();
		if (cursor.getLMB()) {bezier.points[1] = cursor.loc;}
		if (cursor.getRMB()) {bezier.points[2] = cursor.loc;}
		});
	
	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));
		
		bezier.render(al_map_rgb(40, 180, 20), 3);
		al_draw_filled_circle(bezier.points[1].x, bezier.points[1].y, 5, al_map_rgb(40, 240, 40));
		al_draw_filled_circle(bezier.points[2].x, bezier.points[2].y, 5, al_map_rgb(40, 240, 40));
		for (float t = 0; t <= 1; t += 0.02f) {
			IPointF renderPoint = bezier.stupidLerp(t);
			al_draw_filled_circle(renderPoint.x, renderPoint.y, 3, al_map_rgb(240, 240, 240));
		}

		al_flip_display();
		});

	scene.run();
}

void mandelbrot() {
	//dle videa https://youtu.be/6z7GQewK-Ks a https://youtu.be/fAsaSkmbF5s
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	scene.setFPS(0.1f);
	IDisplay* display;
	ICursor cursor;
	IKeyboard keyboard;

	int maxIteration = 50;
	float zoomValue = -2.5;
	float maxValue = 0.5;
	//constanty muzu menit dle http://paulbourke.net/fractals/juliaset/
	float ca = -0.70176;
	float cb = -0.3842;
	IPointF offset;
	float angleOffset = 180.0f;			//meni paletu barev

	keyboard.bindKeyDown([&] {
		if (keyboard.isKeyLikeState(KEY_W, KEY_PRESS)) {offset.y -= 1;}
		if (keyboard.isKeyLikeState(KEY_A, KEY_PRESS)) { offset.x -= 1; }
		if (keyboard.isKeyLikeState(KEY_S, KEY_PRESS)) { offset.y += 1; }
		if (keyboard.isKeyLikeState(KEY_D, KEY_PRESS)) { offset.x += 1; }
		if (keyboard.isKeyLikeState(KEY_ESC, KEY_PRESS)) { scene.breakLoop = true; }
		
		});

	scene.bindInit([&] {
		display = new IDisplay();
		display->create();
		display->setTitle("Mandelbrot");
		display->changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));	
		al_clear_to_color(al_map_rgb(0, 0, 0));
	});

	scene.bindUpdate([&] {
		scene.breakLoop = !display->update();
		cursor.update();
		if (cursor.scrolling == 1) { zoomValue += 0.05f; }
		if (cursor.scrolling == -1) { zoomValue -= 0.05f; }
		ca = zelpMath::mapRange(cursor.loc.x, 0, WINDOW_WIDTH, -1.0, 1.0);
		cb = zelpMath::mapRange(cursor.loc.y, 0, WINDOW_HEIGHT, -1.0, 1.0);
		//angleOffset = zelpMath::mapRange(cursor.loc.x, 0, WINDOW_WIDTH, 0.0, 360.0);
		keyboard.update();
		if (keyboard.isKeyLikeState(KEY_W, KEY_HOLD)) { offset.y -= 10; }
		if (keyboard.isKeyLikeState(KEY_A, KEY_HOLD)) { offset.x -= 10; }
		if (keyboard.isKeyLikeState(KEY_S, KEY_HOLD)) { offset.y += 10; }
		if (keyboard.isKeyLikeState(KEY_D, KEY_HOLD)) { offset.x += 10; }
		});

	scene.bindRender([&] {
		//al_clear_to_color(al_map_rgb(160, 160, 160));
		char red, green, blue;
		float a, b;
		for (int x = 0; x < WINDOW_WIDTH; x++) {
			for (int y = 0; y < WINDOW_HEIGHT; y++) {
				a = zelpMath::mapRange(x+offset.x, 0, WINDOW_WIDTH, zoomValue, -zoomValue);
				b = zelpMath::mapRange(y+offset.y, 0, WINDOW_HEIGHT, zoomValue, -zoomValue);

				int bright = 0;
				float z = 0;
				int iterationValue = 0;
				for (unsigned int n = 0; n <= maxIteration; n++) {
					float aa = a * a;
					float bb = b * b;
					if (std::abs(aa + bb) > 4) { break; }
					float twoab = 2.0 * a * b;

					a = aa - bb + ca;
					b = twoab + cb;
					iterationValue = n;
				}
				bright = zelpMath::mapRange(iterationValue, 0, maxIteration, 0, 360);
				zelpMath::getHUE(&red, &green, &blue, bright + angleOffset);
				al_draw_pixel(x, y, al_map_rgb(red, green, blue));
			}
		}

		al_flip_display();
		});

	scene.run();
}

void escapiWebcamHello() {
#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	scene.setFPS(0.1f);
	IDisplay display;
	display.create();
	display.changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
	display.setTitle("ESCAPI WEBCAM");


	int nCameras = 0;
	int device = 0;
	SimpleCapParams capture;

	nCameras = setupESCAPI();
	if (nCameras == 0) { return; }

	capture.mWidth = WINDOW_WIDTH;
	capture.mHeight = WINDOW_HEIGHT;
	capture.mTargetBuf = new int[WINDOW_WIDTH * WINDOW_HEIGHT];

	if (initCapture(device, &capture) == 0) return;

	unsigned int r = -1;
	unsigned int g = -1;
	unsigned int b = -1;
	int index = 0;

	scene.bindInit([] {al_clear_to_color(al_map_rgb(25, 25, 25)); });
	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(0, 0, 0));

		doCapture(device);
		while (isCaptureDone(device)) {}
		for (int y = 0; y < capture.mHeight; y++) {
			for (int x = 0; x < capture.mWidth; x++) {
				index = y * capture.mWidth + x;
				//get pixel
				r = capture.mTargetBuf[index];
				g = capture.mTargetBuf[index];
				b = capture.mTargetBuf[index];

				//convert pixel to rgb
				r = (r & 0x00ff0000) >> 16;
				g = (g & 0x0000ff00) >> 8;
				b = (b & 0x000000ff) >> 0;
				//draw pixel
				al_draw_pixel(x, y, al_map_rgb(r, g, b));
			}
		}
		al_flip_display();
		});

	scene.run();
}

void unicodeTest() {
	zelpWindowsOS::showConsole();
	EasyScene scene;
	IDisplay display;
	display.create();
	display.setTitle("Unicode Text");
	display.changeResolution(IPoint(600, 600));
	display.setPosition(IPoint(0, 0));
	IFont unicodeFont;
	unicodeFont.loadFont("assets/font/osakaunicode.ttf", 40);
	unicodeFont.color = al_map_rgb(235, 235, 235);
	unicodeFont.flag = ALLEGRO_ALIGN_CENTER;
	FileLoaderUnicode unicodeFile;
	unicodeFile.loadFile("assets/unicodeTest.txt");

	display.bindResize([&] {
		unicodeFont.loc = IPoint(display.res.x / 2, (display.res.y / 2) - unicodeFont.getSize() * 0.5);
		});

	scene.bindInit([&] {
		unicodeFont.loc = IPoint(display.res.x / 2, (display.res.y / 2) - unicodeFont.getSize() * 0.5);
		al_clear_to_color(al_map_rgb(15, 15, 15));
		});

	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));
		unicodeFont.renderUnicode(unicodeFile.getPointerLine(1));
		
		al_flip_display();
		});

	scene.run();
}

void testingBox2D() {
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
	zelpWindowsOS::showConsole();
	EasyScene2 scene;
	scene.display->changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
	scene.display->setTitle("box2d test001");


	IB2Entity* floor = new IB2Entity(scene.b2world, IPointF(3, 5), b2_staticBody);
	std::vector<IB2Entity*> vecOfDynamic;


	scene.bindInit([&] {
		//floor->addBoxShape(2.0f, 0.2f, 1, 0.95, 0.95);
		std::vector<b2Vec2> vertex;
		vertex.push_back(b2Vec2(-3, -3.0));
		vertex.push_back(b2Vec2(-3, 0.5));
		vertex.push_back(b2Vec2(-2, -0.5));
		vertex.push_back(b2Vec2(-1, 2.5));
		vertex.push_back(b2Vec2(0, 0.5));
		vertex.push_back(b2Vec2(1, -1.5));
		vertex.push_back(b2Vec2(1, -3.5));
		floor->addChainShape(&vertex, 1, 0.95, 0.95);
		});

	scene.bindUpdate([&] {
		if (scene.cursor->getLMB()) {
			IPointF spawnLoc = IB2Entity::cursorOriginToBox2D(scene.cursor->originLoc);
			IB2Entity* box = new IB2Entity(scene.b2world, spawnLoc, b2_dynamicBody);
			box->addBoxShape(0.05f, 0.05f, 1, 0.95, 0.95, 0.05f, 0);
			box->addCircleShape(0.05f, 1, 0.95, 0.95);

			std::vector<b2Vec2> vertex;
			vertex.push_back(b2Vec2(-0.3, -0.3));
			vertex.push_back(b2Vec2(-0.3, 0.3));
			vertex.push_back(b2Vec2(0, 0.36));
			vertex.push_back(b2Vec2(0.3, 0.3));
			vertex.push_back(b2Vec2(0.3, -0.3));
			box->addShape(&vertex, 1, 0.95, 0.95);
			vecOfDynamic.push_back(box);
		}

		});

	scene.bindRender([&] {
		//textureTest();
		floor->renderDebugBox2D();
		for (auto o : vecOfDynamic) {
			o->renderDebugBox2D();
		}
		//otestovat circle render getOriginLoc entity
		});

	scene.run();
}

void testingRecording() {
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay display;
	display.create();
	display.setTitle("Microphone Recording");
	display.changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
	display.setPosition(IPoint(0, 0));
	IMicrophone microphone;
	microphone.init();

	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();



		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));

		microphone.update();
		al_flip_display();
		});

	scene.run();


}

void calculator() {
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay display;
	ICursor cursor;
	display.create();
	display.setTitle("Calculator");
	display.changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
	display.setPosition(IPoint(0, 0));
	//al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	//al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	//al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_SUGGEST);
	//al_set_new_display_flags(ALLEGRO_RESIZABLE);
	IFont displayText;
	displayText.loadFont("assets/examples/arial.ttf", 55);
	displayText.color = al_map_rgb(235, 235, 235);
	displayText.flag = ALLEGRO_ALIGN_RIGHT;
	displayText.loc = IPoint(WINDOW_WIDTH - 15, 50 - displayText.getSize() / 2);
	std::string clockText = "";

	std::vector<EasyButton*> vecOfButtons;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int w = (WINDOW_WIDTH / 4) - 10;
			int h = 100;
			int locX = 5 + (x * (w + 10));
			int locY = 105 + (y * (h + 10));
			EasyButton* button = new EasyButton(IPoint(locX, locY), IPoint(w, h));
			button->setColor(al_map_rgb(20, 20, 20), al_map_rgb(30, 30, 30), al_map_rgb(90, 90, 90));
			button->loadFont("assets/examples/arial.ttf", 40);
			button->fontColor = al_map_rgb(235, 235, 235);
			vecOfButtons.push_back(button);
		}
	}

	vecOfButtons.at(0)->text = "7";
	vecOfButtons.at(0)->bindPress([&] {clockText += "7"; cursor.setLMB(false); });
	vecOfButtons.at(1)->text = "8";
	vecOfButtons.at(1)->bindPress([&] {clockText += "8"; cursor.setLMB(false); });
	vecOfButtons.at(2)->text = "9";
	vecOfButtons.at(2)->bindPress([&] {clockText += "9"; cursor.setLMB(false); });
	vecOfButtons.at(3)->text = "/";
	vecOfButtons.at(3)->bindPress([&] {clockText += "/"; cursor.setLMB(false); });
	vecOfButtons.at(4)->text = "4";
	vecOfButtons.at(4)->bindPress([&] {clockText += "4"; cursor.setLMB(false); });
	vecOfButtons.at(5)->text = "5";
	vecOfButtons.at(5)->bindPress([&] {clockText += "5"; cursor.setLMB(false); });
	vecOfButtons.at(6)->text = "6";
	vecOfButtons.at(6)->bindPress([&] {clockText += "6"; cursor.setLMB(false); });
	vecOfButtons.at(7)->text = "*";
	vecOfButtons.at(7)->bindPress([&] {clockText += "*"; cursor.setLMB(false); });
	vecOfButtons.at(8)->text = "1";
	vecOfButtons.at(8)->bindPress([&] {clockText += "1"; cursor.setLMB(false); });
	vecOfButtons.at(9)->text = "2";
	vecOfButtons.at(9)->bindPress([&] {clockText += "2"; cursor.setLMB(false); });
	vecOfButtons.at(10)->text = "3";
	vecOfButtons.at(10)->bindPress([&] {clockText += "3"; cursor.setLMB(false); });
	vecOfButtons.at(11)->text = "-";
	vecOfButtons.at(11)->bindPress([&] {clockText += "-"; cursor.setLMB(false); });
	vecOfButtons.at(12)->text = "0";
	vecOfButtons.at(12)->bindPress([&] {clockText += "0"; cursor.setLMB(false); });
	vecOfButtons.at(13)->text = "C";
	vecOfButtons.at(13)->bindPress([&] {clockText = ""; cursor.setLMB(false); });
	vecOfButtons.at(14)->text = "=";
	vecOfButtons.at(14)->bindPress([&] {
		clockText = std::to_string(te_interp(clockText.c_str(), 0));
		//printf("Answer is %f\n", answer);
		cursor.setLMB(false); });
	vecOfButtons.at(15)->text = "+";
	vecOfButtons.at(15)->bindPress([&] {clockText += "+"; cursor.setLMB(false); });

	scene.bindInit([&] {al_clear_to_color(al_map_rgb(40, 40, 40)); });

	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		cursor.update();
		for (int i = 0; i < vecOfButtons.size(); i++) {
			vecOfButtons.at(i)->update(cursor.loc, cursor.getLMB());
		}
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));
		//show calculator display
		al_draw_filled_rounded_rectangle(5, 5, WINDOW_WIDTH - 5, 100, 5, 5, al_map_rgb(45, 45, 45));
		displayText.render(clockText);
		for (int i = 0; i < vecOfButtons.size(); i++) {
			vecOfButtons.at(i)->renderWithText();
		}
		al_flip_display();
		});

	scene.run();
}

void test3Dscene() {
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay display;
	display.create();
	display.setTitle("Scene 3D");
	display.changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
	display.setPosition(IPoint(0, 0));
	EasyCam3D easyCam(CONTROL_TYPE_SPACESHIP);
	easyCam.camera->setFocusRatio((float)display.res.y / (float)display.res.y);

	scene.bindUpdate([&] {
		scene.breakLoop = !display.update();
		easyCam.update();
		});

	scene.bindRender([&] {
		al_clear_to_color(al_map_rgb(15, 15, 15));
		textureTest();

		al_flip_display();
		});

	scene.run();
}
