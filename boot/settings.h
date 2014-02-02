#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <iostream>

//typedef std::map< const std::string, std::string > StringMap;

class SettingsSystem {

private:
	enum IniLineType { INI_NOMATCH, INI_SECTION, INI_ITEM };
	
	struct setting {
		char* item;
		char* file;
		char* encyptionType;
	};
	
	std::map< setting, char* > settings;
	//std::map< std::string, StringMap > IniSections;

	IniLineType SettingsSystem::IniFileCheckLine(std::string line);
	std::vector<std::string> SettingsSystem::IniFileSplitLine(std::string line);

public
	:SettingsSystem();
	~SettingsSystem();
	
	char* &operator[](char* i);
	
	//char* GetValue(char* i);
	//int SetValue(char* i, char* v);

	int LoadIni(std::string filename);
	int SaveIni(std::string filename);

};

#endif