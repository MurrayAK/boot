#include "settings.h"

Settings::Settings() {

}

Settings::~Settings() {

}

int Settings::loadIni(std::string f) {

	//loop through sections and through items

	//insert item and value into memory

	return 0;
}

int Settings::saveIni(std::string f) {

	//loop through each section and through items in memory

	//write section > item > value to file

	return 0;
}

std::string Settings::getValue(std::string i) {

	//check mem, if exists, return

	//check user.ini, if exists return

	//check defaults.ini, if t exists return

	//if all else failed, throw error

	return 0;
}

std::string Settings::setValue(std::string i, std::string v) {

	//save to memory

	//save to ini if flag is true?

	return 0;
}