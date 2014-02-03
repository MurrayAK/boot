#include "settingsmap.h"

/**
* Constructors
* @param filename: loads in settings from a file
* TODO: add support for additional filetypes, such as XML
*/
SettingsMap::SettingsMap() {  }

SettingsMap::SettingsMap(std::string filename) { LoadIni(filename); }

/**
* Destructor
*/
SettingsMap::~SettingsMap() 
{
	//DESTROY "ITEMS", "GROUPS", SELF?
}

/**
* Operator Overloads [], =
*/
StringMap &SettingsMap::operator[](std::string group) { return groups[group]; }

//StringMap &SettingsMap::operator=(const SettingsMap& group) {}

/**
* GetValue
* returns the value of the requested item from "items" 
* @param item: item value to return
*/
std::string SettingsMap::GetValue(std::string item)
{
	std::string v = "";

	if (items[item] != "") 
		v = items[item];

	return v;
}

/**
* GetValue
* returns the value of the requested item from items in "group"
* @param item: item value to return
* @param group: group to lookup item in
*/
std::string SettingsMap::GetValue(std::string item, std::string group)
{
	StringMap g;
	std::string v = "";

	if (!groups[group].empty())
		g = groups[group];

	v = g[item];

	return v;
}

/**
* SetValue
* sets the value for item in "items"
* @param item: item to set
* @param value: value to set item too
*/
int SettingsMap::SetValue(std::string item, std::string value)
{
	items[item] = value;

	return 0;
}

/**
* SetValue
* sets the value for item in group(items) in groups
* @param item: item to set
* @param value: value to set item too
* @param group: the group the item belongs too
*/
int SettingsMap::SetValue(std::string item, std::string value, std::string group)
{
	groups[group][item] = value;

	return 0;
}

// indentifies if line refers to a section or key value pair or newline
// function receives line and outputs 1 or 2 or 0 respectively
// 
SettingsMap::IniLineType SettingsMap::IniFileCheckLine(std::string line)
{
	std::regex a ("^\\[[a-zA-Z]+\\.?[a-zA-Z]+\\]+");
	std::regex b (".*=.*");

	if (std::regex_match(line, a)) 
		return INI_SECTION;

	if (std::regex_match(line, b)) 
		return INI_ITEM;

	return INI_NOMATCH;
}

// gets ini filename
// function receives filename and outputs file contents to hashtable
//
std::vector<std::string> SettingsMap::IniFileSplitLine(std::string line) 
{
	char *s = new char[line.length() + 1];
	std::strcpy(s, line.c_str());
	std::vector<std::string> auxVec;
	char *p = std::strtok(s, "=");

	while (p != 0) {
		auxVec.push_back(p);
		p = strtok(NULL, "=");
	}

	delete[] s;
	
	return auxVec;
}

int SettingsMap::LoadIni(std::string filename) 
{
	std::ifstream instream;
	std::string line, section;
	std::vector<std::string> item;
	StringMap table;
	
	instream.open(filename, std::ifstream::in);
	
	while (std::getline(instream, line))
	{
		switch (IniFileCheckLine(line)) 
		{
			case INI_SECTION:
				section = line.substr(1,(line.length() - 2));
				table.clear();
				groups[section] = table;
				break;

			case INI_ITEM:
				item = IniFileSplitLine(line);
				table = groups[section];
				table[item[0]] = item[1];
				groups[section] = table;
				break;
 
			default:
				break;
		}
	}

	instream.close();

	return 0;
}

int SettingsMap::SaveIni(std::string filename) {

	// loop through each group (section) in groups (sections)
	// write section > item > value to file

	return 0;
}