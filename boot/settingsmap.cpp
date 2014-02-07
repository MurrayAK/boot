#include "settingsmap.h"

/**
* Constructors
* @param filename: loads in settings from a file
* TODO: add support for additional filetypes, such as XML
*/
SettingsMap::SettingsMap() {  }

/**
* Destructor
*/
SettingsMap::~SettingsMap() { /*FREE MEMORY?*/ }

/**
* GetValue
* returns the value of the requested item from "items" 
* @param item: item value to return
*/
std::string SettingsMap::GetValue(std::string str)
{
	std::string item, value, ns = "";
	std::vector<std::string> strParts;

	strParts = Tokenize(str, ".");
	
	if (strParts.size() > 1) {
		for (std::vector<std::string>::iterator x = strParts.begin(); x < strParts.end() - 1; x++)
		{
			if (ns != "") ns = ns +".";
			ns = ns + *x;
		}
	} else
		ns = strParts[0];

	//std::cout << ns << std::endl;

	ns = GetNamespaceID(ns);

	item = ns +":"+ strParts.back();

	//std::cout << strParts.back() << std::endl;

	if (settings[str].data != "") 
		value = settings[str].data;
	
	return value;
}

/**
* SetValue
* sets the value for item in "items"
* @param item: item to set
* @param value: value to set item too
*/
int SettingsMap::SetValue(std::string str, std::string value)
{
	std::string item, ns = "";
	std::vector<std::string> strParts;
	strParts = Tokenize(str, ".");
	
	if (strParts.size() > 1) {
		for (std::vector<std::string>::iterator x = strParts.begin(); x < strParts.end() - 1; x++)
		{
			if (ns != "") ns = ns +".";
			ns = ns + *x;
		}
	} else
		ns = strParts[0];
	
	item = ns +":"+ strParts.back();
	
	settings[str].data = value;

	if (GetNamespaceID(ns) == -1) { 
		namespaces[ns] = namespaces.size();
	}

	return 0;
}

int SettingsMap::GetNamespaceID(std::string ns)
{
	int id = -1;

	if (namespaces[ns])
		id = namespaces[ns];
	
	return id;
}

std::string SettingsMap::GetNamespace(int id)
{
	std::string ns = "";

	//if (namespaces[id])
	//	ns = namespaces[ns];
	
	return ns;
}

std::vector<std::string> SettingsMap::Tokenize(std::string str, const char* delimiter) 
{
	char *s = new char[str.length() + 1];
	std::strcpy(s, str.c_str());
	std::vector<std::string> auxVec;
	char *p = std::strtok(s, delimiter);

	while (p != 0) {
		auxVec.push_back(p);
		p = strtok(NULL, delimiter);
	}

	delete[] s;
	
	return auxVec;
}

// indentifies if line refers to a section or key value pair or newline
// function receives line and outputs 1 or 2 or 0 respectively
// 
SettingsMap::IniLineType SettingsMap::IniFileCheckLine(std::string line)
{
	std::regex a ("^\\[[a-zA-Z]+\\.?[a-zA-Z]+\\]+");
	std::regex b (".*=.*");

	// TO DO: SKIP LINES THAT BEGIN WITH ;
	//        THEY ARE COMMENTS NOT SECTIONS OR ITEMS

	if (std::regex_match(line, a)) 
		return INI_SECTION;

	if (std::regex_match(line, b)) 
		return INI_ITEM;

	return INI_NOMATCH;
}

int SettingsMap::LoadIni(std::string filename) 
{
	std::ifstream instream;
	std::string line, section;
	std::vector<std::string> item;
	//group g;
	
	instream.open(filename, std::ifstream::in);
	
	while (std::getline(instream, line))
	{
		switch (IniFileCheckLine(line)) 
		{
			case INI_SECTION:
				section = line.substr(1,(line.length() - 2));
				//g.table.clear();
				//g.filename = filename;
				//groups[section] = g;
				break;

			case INI_ITEM:
				item = Tokenize(line, "=");
				//g.table = groups[section].table;
				//g.table[item[0]] = item[1];
				//groups[section].table = g.table;
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
	//std::map< std::string, group >::iterator it;
	//std::string section, filename;
	//StringMap table;
	//StringMap::iterator itx;

	//for (it = groups.begin(); it != groups.end(); it++)
	//{
	//	section = "[" + it->first + "]";
	//	table = it->second.table;
	//	filename = it->second.filename;

	//	std::cout << section <<  " in " << filename << " (" << table.size() << " items)" << std::endl;

	//	for (itx = table.begin(); itx != table.end(); itx++)
	//	{
	//		std::cout << itx->first << "=" << itx->second << std::endl;
	//	}

	//	std::cout << std::endl;
	//}

	return 0;
}