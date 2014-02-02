#include "settings.h"

SettingsSystem::SettingsSystem() {}
SettingsSystem::~SettingsSystem() {}

char* &SettingsSystem::operator[](setting i) 
{ 
	char* v = settings[i];
	
	return;
}

/**
* Indentifies if line refers to a section or key value pair or newline
* function receives line and outputs 1 or 2 or 0 respectively
* @param line to check
* @return ini line type
*/
SettingsSystem::IniLineType SettingsSystem::IniFileCheckLine(std::string line) 
{
	std::regex a ("^\\[[a-zA-Z]+\\.?[a-zA-Z]+\\]+");
	std::regex b (".*=.*");

	if (std::regex_match(line, a)) 
		return INI_SECTION;

	if (std::regex_match(line, b)) 
		return INI_ITEM;

	return INI_NOMATCH;
}

/**
* Gets ini filename
* function receives filename and outputs file contents to hashtable
* @param line to split
* @return array of elements
*/
std::vector<std::string> SettingsSystem::IniFileSplitLine(std::string line) 
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

int SettingsSystem::LoadIni(std::string filename) 
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
				IniSections[section] = table;
				break;

			case INI_ITEM:
				item = IniFileSplitLine(line);
				table = IniSections[section];
				table[item[0]] = item[1];
				IniSections[section] = table;
				break;
 
			default:
				break;
		}
	}

	instream.close();

	return 0;
}

int SettingsSystem::SaveIni(std::string filename) 
{
	
	return 0;
}