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
//StringMap &SettingsMap::operator[](std::string group) { return groups[group].table; }

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

	g = groups[group].table;

	if (g[item] != "")
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
	groups[group].table[item] = value;
	
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
	group g;
	
	instream.open(filename, std::ifstream::in);
	
	while (std::getline(instream, line))
	{
		switch (IniFileCheckLine(line)) 
		{
			case INI_SECTION:
				section = line.substr(1,(line.length() - 2));
				g.table.clear();
				g.filename = filename;
				groups[section] = g;
				break;

			case INI_ITEM:
				item = IniFileSplitLine(line);
				g.table = groups[section].table;
				g.table[item[0]] = item[1];
				groups[section].table = g.table;
				break;
 
			default:
				break;
		}
	}

	instream.close();

	return 0;
}

int SettingsMap::SaveIni() 
{
	std::map< std::string, group >::iterator it;
	std::string section, filename;
	StringMap table;
	StringMap::iterator itx;

	for (it = groups.begin(); it != groups.end(); it++)
	{
		section = "[" + it->first + "]";
		table = it->second.table;
		filename = it->second.filename;

		std::cout << section <<  " in " << filename << " (" << table.size() << " items)" << std::endl;

		for (itx = table.begin(); itx != table.end(); itx++)
		{
			std::cout << itx->first << "=" << itx->second << std::endl;
		}

		std::cout << std::endl;
	}

	return 0;
}

int SettingsMap::SaveIni(GroupMap groups) 
{
	

	return 0;
}