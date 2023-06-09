#include "processControl.h"

void processControl() {
	zelpWindowsOS::hideConsole();
	EasyScene scene;
	IDisplay display;
	IKeyboard keyboard;
	ICursor cursor;
	display.create();
	display.setTitle("Process Control!");
	display.changeResolution(IPoint(WINDOW_WIDTH, WINDOW_HEIGHT));
	display.setPosition(IPoint(0, 0));
	scene.setFPS(1.0f / 20.0f);

	IPoint center = IPoint(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - 20);
	float radius = (display.getResY() / 2.0f) * 0.65;

	ITimer timer;
	timer.setSpeed(60.0f);	//kazdou minutu
	ITimer secTimer;
	secTimer.setSpeed(1.0f);

	int sec = 60;
	int maxTimeOnInternet = 60;
	bool countdownRunning = false;

	EasyButton buttonStart(IPoint(90, 350), IPoint(100, 40));
	buttonStart.setColor(al_map_rgb(40, 120, 40), al_map_rgb(40, 160, 40), al_map_rgb(40, 200, 40));
	buttonStart.bindPress([&] {
		if(maxTimeOnInternet>0){
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
	countdownFont.loc = IPoint(center.x, center.y - 40);
	countdownFont.flag = ALLEGRO_ALIGN_CENTRE;
	countdownFont.color = al_map_rgb(40, 40, 40);

	scene.bindInit([&] {al_clear_to_color(al_map_rgb(25, 25, 25)); });

	scene.bindUpdate([&] {
		//scene.breakLoop = !display.update();
		cursor.update();
		buttonStart.update(cursor.loc, cursor.getLMB());
		buttonStop.update(cursor.loc, cursor.getLMB());
		if (secTimer.update()) {
			sec--;
			if (sec <= 0) {
				sec = 60;
				if (countdownRunning) {
					maxTimeOnInternet--;
					if (maxTimeOnInternet < 0) {
						countdownRunning = false;
					}
				}
			}
		}

		if(!countdownRunning){	//chceme procesy zabit pouze, pokud cas nebezi
			if (timer.update()) {
				system("taskkill /f /im firefox.exe");
				system("taskkill /f /im steam.exe");
				system("taskkill /f /im hoi4.exe");
				system("taskkill /f /im chrome.exe");
			}
		}
		});

	scene.bindRender([&] {
		if (!countdownRunning) {al_clear_to_color(al_map_rgb(45, 15, 15));}
		else { al_clear_to_color(al_map_rgb(15, 45, 15)); }
		buttonStart.render();
		buttonStop.render();
		countdownFont.render(std::to_string(maxTimeOnInternet));
		al_draw_arc(center.x, center.y, radius, degreeToRad(270), mapRange(maxTimeOnInternet, 0, 60, 0, degreeToRad(360)), al_map_rgb(100, 100, 100), 12.0f);
		al_draw_arc(center.x, center.y, radius*0.85, degreeToRad(270), mapRange(sec, 0, 60, 0, degreeToRad(360)), al_map_rgb(140, 120, 80), 12.0f);

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
			if (str == "killingProcess.exe") // put the name of your process you want to kill
			{
				findProcess = true;
			}
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);

		if (!findProcess) {
			//spust program
			system("start C:\\shit\\dont_delete\\killingProcess\\killingProcess.exe");
		}
		Sleep(60000);	//kazdou minutu
	}
}