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

std::string Settings::getValue(std::string item) 
{
	if (item == "") return "";
	if (this->tableName == "") return "";

	stringmap table = this->database[this->tableName];
	stringmap::iterator i = table.find(item);
	
	if (i != table.end()) 
		return table.at(item);
	
	return "";
}

bool Settings::setValue(std::string item, std::string value)
{
	if (this->tableName == "") return false;

	if (item != "" && value != "")
	{ 
		this->database[this->tableName][item] = value;

		return true;
	}
	
	return false;
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