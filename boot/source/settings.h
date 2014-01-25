#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>
#include <direct.h>

typedef std::map< const std::string, std::string > stringmap;

class Settings {

private:
	

public:
	std::map< std::string, stringmap > database;
	Settings();	
	~Settings();
	
	stringmap &operator[](std::string table);
	
	int Settings::checkLine(std::string line);
	std::vector<std::string> Settings::splitLine(std::string lineTosplit);

	int LoadIni(std::string filename);
	int LoadIni(std::string filename, std::string section);
	int SaveIni(std::string filename);

};

#endif