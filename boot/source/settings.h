#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>
#include <map>

typedef std::map< const std::string, std::string > stringmap;

class Settings {

private:
	std::map< std::string, stringmap > database;

public:
	Settings();	
	~Settings();
	
	stringmap &operator[](std::string tableName);
	
	int LoadIni(std::string filename);
	int SaveIni(std::string filename);

};

#endif