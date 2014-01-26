#ifndef IniSettings_H
#define IniSettings_H

#include <string>
#include <map>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>

typedef std::map< const std::string, std::string > StringMap;

class IniSettings {

private:
	enum IniLineType { INI_LINE, INI_SECTION, INI_ITEM };
	
	std::map< std::string, StringMap > database;

	IniLineType IniSettings::IniFileCheckLine(std::string line);
	std::vector<std::string> IniSettings::IniFileSplitLine(std::string line);

public
	:IniSettings();	
	IniSettings(std::string filename);	
	~IniSettings();
	
	StringMap &operator[](std::string table);
	
	int LoadIni(std::string filename);
	int LoadIni(std::string filename, std::string section);

	int SaveIni(std::string filename);

};

#endif