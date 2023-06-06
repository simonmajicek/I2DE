#pragma once
#include "allStaticLib.h"

//posledni znak v souboru musi byt 2x MAM TAM CHYBU!!!
struct IFileLoader{
private :
	std::vector<std::string> vecOfLineText;
public:		
	IFileLoader() {};
	~IFileLoader();
	bool loadFile(std::string path);
	void showVecOfLineText();
	unsigned int getLinesNumber();
	std::string getLine(unsigned int lineNumber);
};

struct IFileSaver{			//bacha, prepise soubor od zacatku
private :
	ALLEGRO_FILE *aFile;
public:		
	IFileSaver() {};
	~IFileSaver();
	bool openFile(std::string path);
	bool closeFile();	
	void saveLine(std::string text);
	void saveLineUnicode(ALLEGRO_USTR *lineOfText);	
};

struct FileLoaderUnicode {
private:
	std::vector<ALLEGRO_USTR*> vecOfLineText;
public:
	FileLoaderUnicode() {};
	~FileLoaderUnicode();
	bool loadFile(std::string path);
	unsigned int getLinesNumber();
	ALLEGRO_USTR* getPointerLine(unsigned int lineNumber);
};


