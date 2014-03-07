#ifndef SETTINGS_MAP_H
#define SETTINGS_MAP_H

#include <string>
#include <map>
#include <vector>

class SettingsMap {

private:
	enum IniLineType { INI_NOMATCH, INI_SECTION, INI_ITEM, INI_COMMENT };
	
	std::map< const std::string, int > namespaces;
	std::map< const std::string, int > files;

	struct value {
		std::string data;
		std::string filename;
	};
	std::map< const std::string, value > settings;

	int SettingsMap::GetNamespaceID(std::string ns);
	std::vector< std::string > SplitItemString(std::string str);
	
	IniLineType SettingsMap::IniFileCheckLine(std::string line);
	
	std::vector<std::string> SettingsMap::Tokenize(std::string str, const char* delimiter);

public
	:SettingsMap();	
	~SettingsMap();
	
	std::string GetValue(std::string item);
	int SetValue(std::string item, std::string value);

	int LoadIni(std::string filename);
	int SaveIni();

};

#endif