#ifndef SettingsIni_H
#define SettingsIni_H

#include <string>
#include <map>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>

typedef std::map< const std::string, std::string > StringMap;

class SettingsIni {

private:
	enum IniLineType { INI_NOMATCH, INI_SECTION, INI_ITEM };
	
	std::map< std::string, StringMap > IniSections;

	IniLineType SettingsIni::IniFileCheckLine(std::string line);
	std::vector<std::string> SettingsIni::IniFileSplitLine(std::string line);

public
	:SettingsIni();	
	SettingsIni(std::string filename);	
	~SettingsIni();
	
	StringMap &operator[](std::string section);
	
	int LoadIni(std::string filename);
	int LoadIni(std::string filename, std::string section);

	int SaveIni(std::string filename);

};

#endif