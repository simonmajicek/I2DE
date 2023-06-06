#include "zelpWindowsOS.h"

namespace zelpWindowsOS {
	void hideConsole() { 
		HWND hwnd = GetConsoleWindow();
		ShowWindow(hwnd, false);
	}

	void showConsole() {
		HWND hwnd = GetConsoleWindow();
		ShowWindow(hwnd, true);
	}

	void clearConsole() { system("CLS"); }

	void shutDownPC() {system("shutdown /s /t 0");}

	void saveToDesktopWallpaper(ALLEGRO_BITMAP* wallpaper) {
		//ALLEGRO_BITMAP* wallpaper = al_get_backbuffer(display->display);
		
		al_save_bitmap("../../../../../../../../../../../../../wallpaper/wallpaper.jpg", wallpaper);	//war crime
		std::string path = "C:\\wallpaper\\wallpaper.jpg";
		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)L"C:\\wallpaper\\wallpaper.jpg", SPIF_UPDATEINIFILE);
	}
}