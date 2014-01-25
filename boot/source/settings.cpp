#include "settings.h"

Settings::Settings() 
{  

}

Settings::~Settings() 
{  

}

stringmap &Settings::operator[](std::string tableName)
{
	return this->database[this->tableName];
}

int Settings::loadini(std::string filename) {

	//loop through sections and through items
	//check user.ini, if exists grab item
	//check defaults.ini, if it exists grab item instead
	//insert item and value into memory

	return 0;
}

int Settings::saveini(std::string filename) {

	//loop through each section and through items in memory
	//write section > item > value to file

	return 0;
}