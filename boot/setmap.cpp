#include "setmap.h"

#include <regex>
#include <fstream>
#include <iostream>

/** ------------------------------------------------------------------------------------- */

/** Constructor */
SettingsMap::SettingsMap() {  }

/** Destructor */
SettingsMap::~SettingsMap() { /*FREE MEMORY?*/ }

/**
* GetValue
* returns the value of the requested item from memory
* @param item: item value to return
*/
std::string SettingsMap::GetValue(std::string str)
{
	std::vector< std::string > itemParts;
	std::string item, value = "";
	
	itemParts = SplitItemString(str);
	
	item = std::to_string( GetNamespaceID( itemParts[0] ) )
		   +":"+ 
		   itemParts[1];

	if (settings[item].data != "") 
		value = settings[item].data;

	return value;
}

/**
* SetValue
* sets the value for an item in memory
* @param str: namespace.item to set
* @param value: value to set item too
*/
int SettingsMap::SetValue(std::string str, std::string value)
{
	std::vector< std::string > itemParts;
	std::string item = "";
	
	itemParts = SplitItemString(str);
		
	if (namespaces.count( itemParts[0] ) == 0)
		namespaces[ itemParts[0] ] = (namespaces.size() + 1);

	item = std::to_string( GetNamespaceID( itemParts[0] ) )
		   +":"+ 
		   itemParts[1];
	
	settings[item].data = value;
	settings[item].filename = "";

	return 0;
}

/**
* GetNamespaceID
* returns the id of the namespace-string provided from 'namespaces' table
* @param ns: namespace to get id for
*/
int SettingsMap::GetNamespaceID(std::string ns)
{
	int id = 0;

	if (std::to_string(namespaces[ns]) != "")
		id = namespaces[ns];
	
	return id;
}

/**
* SplitItemString
* splits a string into 'namespace and 'item' parts
* if string has no . (dots) in it, it returns the item name as namespace
* @param str: string to split
*/
std::vector< std::string > SettingsMap::SplitItemString(std::string str)
{
	std::string ns, item = "";
	std::vector< std::string > split;
	std::vector< std::string > strParts = Tokenize(str, ".");
	
	if (strParts.size() == 1)
		ns = strParts[0];
	else 
	{
		std::vector< std::string >::iterator x;

		for (x = strParts.begin(); x < strParts.end() - 1; x++)
		{
			if (ns != "") ns = ns +".";
			ns = ns + *x;
		}
	}

	split.push_back(ns);
	split.push_back( strParts.back() );

	return split;
}

/**
* Tokenize
* splits a string into parts baed on the provided delimiter and returns the vector
* @param str: string to split
* @param delimiter: the char that seperates the parts
*/
std::vector<std::string> SettingsMap::Tokenize(std::string str, const char *delimiter)
{
	char *s = new char[str.length() + 1];
	std::strcpy(s, str.c_str());
	std::vector<std::string> vec;
	char *p = std::strtok(s, delimiter);

	while (p != 0) {
		vec.push_back(p);
		p = strtok(NULL, delimiter);
	}

	delete[] s;
	
	return vec;
}

/**
* IniFileCheckLine
* returns the ini line type of the specified line string
* @param line: the ini file line to check line type of
*/
SettingsMap::IniLineType SettingsMap::IniFileCheckLine(std::string line)
{	
	std::regex r;
	
	if ( std::regex_search(line, r = "^\\;") ) 
		return INI_COMMENT;

	else if ( std::regex_match(line, r = "[^\\n\\=]+\\={1,1}[^\\n\\=]+") )
		return INI_ITEM;

	else if ( std::regex_match(line, r = "^\\[[a-zA-Z0-9]+(\\.?[a-zA-Z0-9]+){1,3}\\]+") ) 
		return INI_SECTION;

	return INI_NOMATCH;
}

/**
* LoadIni
* scans every line in the specified ini file and
* loads in all the items into the correct namespaces
* @param filename: the file path/name to load
*/
int SettingsMap::LoadIni(std::string filename) 
{
	std::ifstream instream;
	std::string line, section, item;
	std::vector<std::string> itemvec;
	
	instream.open(filename, std::ifstream::in);
	
	while (std::getline(instream, line))
	{
		switch (IniFileCheckLine(line)) 
		{
			case INI_SECTION:
				section = line.substr(1,(line.length() - 2));
								
				if (namespaces.count(section) == 0)
					namespaces[section] = (namespaces.size() + 1);

				break;

			case INI_ITEM:
				itemvec = Tokenize(line, "=");
				
				item = std::to_string( GetNamespaceID(section) )
					   +":"+ 
					   itemvec[0];
				
				settings[item].data = itemvec[1];
				settings[item].filename = filename;
				break;
			
			case INI_COMMENT:
				break;

			default:
				break;
		}
	}

	instream.close();

	return 0;
}

/**
* SaveIni
* TODO: Desired functionality undetermined at this time.
*/
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