#pragma once
#include <Windows.h>
#include "allStaticLib.h"

//pro hrani si s OS Windows
namespace zelpWindowsOS {
	struct SystemTime {
	public:
		std::time_t systemTime;
		std::tm* now;
	public:
		void update() { this->systemTime = std::time(0); localtime_s(this->now, &systemTime); };
		int getSecond() { return this->now->tm_sec; };
		int getMinute() { return this->now->tm_min; };
		int getHour() { return this->now->tm_hour; };
		int getDay() { return this->now->tm_mday; };
		int getMonth() { return this->now->tm_mon; };
		int getYear() { return this->now->tm_year + 1900; };
		void infoToConsole() { std::cout << this->getYear() << ':' << this->getMonth() << ':' << this->getDay() << "   " << this->getHour() << ':' << this->getMinute() << ':' << this->getSecond() << std::endl; };
	};

	//console se da defaultne schovat v LINKER nastaveni projektu!!!!
	void hideConsole();	
	void showConsole();
	void clearConsole();
	void shutDownPC();
	void saveToDesktopWallpaper(ALLEGRO_BITMAP* wallpaper);
}