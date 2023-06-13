#include "cerberus.h"

void runCerberus() {
	zelpWindowsOS::hideConsole();
	//zelpWindowsOS::showConsole();
	EasyScene scene;
	IDisplay display;
	ICursor cursor;
	//display.create(ALLEGRO_NOFRAME);
	display.create();
	display.setTitle("Cerberus Watcher!");
	display.changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
	display.setPosition(IPoint(0, 0));
	display.loadIcon("assets/cerberus.png");
	scene.setFPS(1.0f / 20.0f);
	
	//nacist jmena procesu ze souboru
	IFileLoader file;
	file.loadFile("assets/taskList.txt");
	

	IGraphic cerberusBitmap;
	cerberusBitmap.loadBitmap("assets/cerberus.png");

	IPoint centerOne = IPoint(WINDOW_WIDTH /4, WINDOW_HEIGHT/2 - 20);
	IPoint centerTwo = IPoint((WINDOW_WIDTH /4) + (WINDOW_WIDTH / 2), WINDOW_HEIGHT / 2 - 20);
	
	IPoint halfScreen = IPoint(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	float radius = (display.getResY() / 2.0f) * 0.65;

	ITimer secTimer;
	secTimer.run(1.0f);
	ITimer minuteTimer;
	minuteTimer.run(60.0f);

	int secKillingProcess = 3600;
	int secExercise = 3600;
	bool countdownRunning = false;

	EasyButton buttonStart(IPoint(90, 350), IPoint(100, 40));
	buttonStart.setColor(al_map_rgb(40, 120, 40), al_map_rgb(40, 160, 40), al_map_rgb(40, 200, 40));
	buttonStart.bindPress([&] {
		if(secKillingProcess>0){
			countdownRunning = true;
		}
		cursor.setLMB(false);
		});

	EasyButton buttonStop(IPoint(210, 350), IPoint(100, 40));
	buttonStop.setColor(al_map_rgb(120, 40, 40), al_map_rgb(160, 40, 40), al_map_rgb(200, 40, 40));
	buttonStop.bindPress([&] {
		countdownRunning = false;
		cursor.setLMB(false);
		});

	IFont countdownFont;
	countdownFont.loadFont("assets/arial.ttf", 80);
	countdownFont.loc = IPoint(centerOne.x, centerOne.y - 40);
	countdownFont.flag = ALLEGRO_ALIGN_CENTRE;
	countdownFont.color = al_map_rgb(40, 40, 40);

	scene.bindInit([&] {al_clear_to_color(al_map_rgb(25, 25, 25)); });

	scene.bindUpdate([&] {
		//scene.breakLoop = !display.update();
		cursor.update();
		buttonStart.update(cursor.loc, cursor.getLMB());
		buttonStop.update(cursor.loc, cursor.getLMB());
		if (secTimer.update()) {
			//kiling process
			if (countdownRunning) {
				secKillingProcess--;
			}
			if (secKillingProcess <= 0) {
				countdownRunning = false;
			}

			//exercise60minutes
			secExercise--;
			if (secExercise <= 0) {
				secExercise = 3600;
				//vyskoci hlaska, at si jdu zacvicit
				al_show_native_message_box(NULL, "CVICIT", "JDI SE PROTAHNOUT!", "", "", ALLEGRO_MESSAGEBOX_ERROR);
			}
		}

		//system(taskkill) je dost narocny process, proto spoustim pouze kazdou minutu
		if((!countdownRunning) && minuteTimer.update() ){	//chceme procesy zabit pouze, pokud cas nebezi
			std::string order = "";
			for (unsigned int i = 0; i < file.getLinesNumber(); i++) {
				order = "taskkill /f /im " + file.getLine(i);
				system(order.c_str());
				//taskList.push_back(file.getLine());
				//std::cout << file.getLine(i) << std::endl;
			}
			//system("taskkill /f /im firefox.exe");
			//system("taskkill /f /im steam.exe");
			//system("taskkill /f /im hoi4.exe");
			//system("taskkill /f /im chrome.exe");
		}
		});

	scene.bindRender([&] {
		if (!countdownRunning) {al_clear_to_color(al_map_rgb(45, 15, 15));}
		else { al_clear_to_color(al_map_rgb(15, 45, 15)); }
		//"logo" - ale neni moje
		al_draw_tinted_scaled_bitmap(cerberusBitmap.bitmap, al_map_rgba(50, 50, 50, 200),
			0, 0, cerberusBitmap.res.x, cerberusBitmap.res.y,
			0, 0, halfScreen.x, WINDOW_HEIGHT, 0);
		al_draw_tinted_scaled_bitmap(cerberusBitmap.bitmap, al_map_rgba(50, 50, 50, 200),
			0, 0, cerberusBitmap.res.x, cerberusBitmap.res.y,
			halfScreen.x, 0, halfScreen.x, WINDOW_HEIGHT, 0);


		buttonStart.render();
		buttonStop.render();
		//pro killingProcess
		countdownFont.loc = IPoint(centerOne.x, centerOne.y - 40);
		countdownFont.render(std::to_string(secKillingProcess));
		al_draw_arc(centerOne.x, centerOne.y, radius, degreeToRad(270), mapRange(secKillingProcess, 0, 3600, 0, degreeToRad(360)), al_map_rgb(100, 100, 100), 12.0f);
		//pro exercise60minutes
		countdownFont.loc = IPoint(centerTwo.x, centerTwo.y - 40); 
		countdownFont.render(std::to_string(secExercise));
		al_draw_arc(centerTwo.x, centerTwo.y, radius, degreeToRad(270), mapRange(secExercise, 0, 3600, 0, degreeToRad(360)), al_map_rgb(100, 120, 140), 12.0f);

		al_draw_line(halfScreen.x, 0, halfScreen.x, WINDOW_HEIGHT, al_map_rgb(128, 128, 128), 3.0f);
		al_flip_display();
		});

	scene.run();
}

void runProcessControl() {
	using namespace std;
	zelpWindowsOS::hideConsole();
	//programing war crime
	while (true) {
		HANDLE hProcessSnap;
		HANDLE hProcess;
		PROCESSENTRY32 pe32;
		DWORD dwPriorityClass;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE) { return; }

		// Set the size of the structure before using it.
		pe32.dwSize = sizeof(PROCESSENTRY32);

		// Retrieve information about the first process,
		// and exit if unsuccessful
		if (!Process32First(hProcessSnap, &pe32)) {
			CloseHandle(hProcessSnap);  // clean the snapshot object
			return;
		}
		bool findProcess = false;
		// Now walk the snapshot of processes 
		do {
			wstring name = wstring(pe32.szExeFile);
			string str(name.begin(), name.end());
			if (str == "cerberus_watching.exe") // put the name of your process you want to kill
			{
				findProcess = true;
			}
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);

		if (!findProcess) {
			//spust program
			system("start C:\\shit\\dont_delete\\cerberus_watching\\cerberus_watching.exe");
		}
		Sleep(60000);	//kazdou minutu
	}
}
