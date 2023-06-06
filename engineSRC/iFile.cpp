#include "iFile.h"

IFileLoader::~IFileLoader(){
	this->vecOfLineText.clear();
}

bool IFileLoader::loadFile(std::string path){	
	std::ifstream file(path);
	if(file.is_open()){
		std::string tmpLine;
	    while (std::getline(file, tmpLine)) {
			this->vecOfLineText.push_back(tmpLine);
	    }
	    file.close();
	}
	else{
		std::cout << "Error File Loader Open File! : " << path << std::endl;
	   return false;
	}
	return true;
}

void IFileLoader::showVecOfLineText(){
	for(unsigned int i = 0; i < this->vecOfLineText.size(); i++){
		std::cout << this->vecOfLineText.at(i) << std::endl;
	}
}

unsigned int IFileLoader::getLinesNumber(){return this->vecOfLineText.size();};

std::string IFileLoader::getLine(unsigned int lineNumber){
	if(lineNumber < this->vecOfLineText.size()){
		return this->vecOfLineText.at(lineNumber);
	}
	return NULL;
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

IFileSaver::~IFileSaver(){
	al_fclose(aFile);
}

bool IFileSaver::openFile(std::string path){
	this->aFile = al_fopen(path.c_str(), "w");
	if(!aFile){return false;}
	return true;
}
bool IFileSaver::closeFile(){
	al_fclose(aFile);
	return true;
}

void IFileSaver::saveLine(std::string text){
	al_fwrite(this->aFile, text.c_str(), text.length());
}
void IFileSaver::saveLineUnicode(ALLEGRO_USTR* lineOfText){
	al_fwrite(this->aFile, al_cstr(lineOfText), al_ustr_size(lineOfText));
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

FileLoaderUnicode::~FileLoaderUnicode() {
	for (unsigned int i = 0; i < this->vecOfLineText.size(); i++) {al_ustr_free(this->vecOfLineText.at(i));}
	this->vecOfLineText.clear();
}

bool FileLoaderUnicode::loadFile(std::string path) {
	ALLEGRO_FILE* aFile = al_fopen(path.c_str(), "r");
	if (aFile == NULL) {return false;}

	while (!al_feof(aFile)) {
		ALLEGRO_USTR* tmpUstrText = al_fget_ustr(aFile);
		//kazdy radek ma na konci ENTER character - odstranujeme (krome posledniho radku)
		if (!al_feof(aFile)) {al_ustr_remove_chr(tmpUstrText, al_ustr_offset(tmpUstrText, -1));	}
		this->vecOfLineText.push_back(tmpUstrText);
	}
	al_fclose(aFile);
	return true;
}

unsigned int FileLoaderUnicode::getLinesNumber() {return this->vecOfLineText.size();}
ALLEGRO_USTR* FileLoaderUnicode::getPointerLine(unsigned int lineNumber) {
	if (lineNumber < this->vecOfLineText.size()) {return this->vecOfLineText.at(lineNumber);}
	return NULL;
}
