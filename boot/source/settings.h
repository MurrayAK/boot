#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>
#include <map>

typedef std::map< const std::string, std::string > stringmap;

class Settings {

private:
	std::map< std::string, stringmap > database;
	//stringmap table;
	std::string tableName;

public:
	Settings();	
	~Settings();
	
	stringmap &operator[](std::string tableName);

	std::string getValue(std::string item);
	bool setValue(std::string item, std::string value);
	
	int loadini(std::string filename);
	int saveini(std::string filename);

};

#endif