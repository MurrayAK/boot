#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>
#include <iostream>

typedef std::map< const std::string, std::string > stringmap;

class Settings {

private:
	std::map< std::string, stringmap > database;

public:
	Settings();	
	~Settings();
	
	stringmap &operator[](std::string table);
	
	int LoadIni(std::string filename);
	int SaveIni(std::string filename);

};

#endif