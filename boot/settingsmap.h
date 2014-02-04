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
	enum IniLineType { INI_NOMATCH, INI_SECTION, INI_ITEM };

	typedef std::map< const std::string, std::string > StringMap;

	struct group {
		StringMap table;
		std::string filename;
	};

	typedef std::map< const std::string, group > GroupMap;

	StringMap items;
	GroupMap groups;

	IniLineType SettingsMap::IniFileCheckLine(std::string line);
	std::vector<std::string> SettingsMap::IniFileSplitLine(std::string line);

public
	:SettingsMap();	
	SettingsMap(std::string filename);

	~SettingsMap();
	
	StringMap &operator[](std::string group);
	//StringMap &operator=(const SettingsMap& group);
	
	std::string GetValue(std::string item);
	std::string GetValue(std::string item, std::string group);

	int SetValue(std::string item, std::string value);
	int SetValue(std::string item, std::string value, std::string group);

	int LoadIni(std::string filename);

	int SaveIni();
	int SaveIni(GroupMap groups);

};

#endif