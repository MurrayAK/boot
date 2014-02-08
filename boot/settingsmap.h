#ifndef SETTINGSMAP_H
#define SETTINGSMAP_H

#include <string>
#include <map>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>

class SettingsMap {

private:
	struct value {
		std::string data;
		std::string filename;
	};

	std::map< const std::string, value > settings;
	std::map< const std::string, int > namespaces;
	
	int SettingsMap::GetNamespaceID(std::string ns);
	std::vector< std::string > SplitItemString(std::string str);
	std::vector<std::string> SettingsMap::Tokenize(std::string str, const char* delimiter);

	enum IniLineType { INI_NOMATCH, INI_SECTION, INI_ITEM };

	IniLineType SettingsMap::IniFileCheckLine(std::string line);

public
	:SettingsMap();	

	~SettingsMap();
	
	std::string GetValue(std::string item);

	int SetValue(std::string item, std::string value);

	int LoadIni(std::string filename);

	int SaveIni();
	//int SaveIni(GroupMap groups);

};

#endif