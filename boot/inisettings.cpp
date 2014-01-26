#include "IniSettings.h"

IniSettings::IniSettings() {  }
IniSettings::IniSettings(std::string filename) { LoadIni(filename); }

IniSettings::~IniSettings() {  }

StringMap &IniSettings::operator[](std::string section) { return IniSections[section]; }

// opens file with name filename
// function tests operation and outputs filestream
//
std::ifstream openFile(std::string filename) 
{
	std::ifstream instream;
	instream.open(filename, std::ifstream::in);

	//if (instream.fail()) 
	//	std::cerr << "File Error: " << strerror(errno) << std::endl;
	
	//if (instream.is_open()) 
	//	std::cout << "File "+ filename +" is open" << std::endl;

	return instream;
}

// indentifies if line refers to a section or key value pair or newline
// function receives line and outputs 1 or 2 or 0 respectively
// 
IniSettings::IniLineType IniSettings::IniFileCheckLine(std::string line) 
{
	std::regex a ("^\\[[a-zA-Z]+\\.?[a-zA-Z]+\\]+");
	std::regex b (".*=.*");

	if (std::regex_match(line, a)) 
		return INI_SECTION;

	if (std::regex_match(line, b)) 
		return INI_ITEM;

	return INI_LINE;
}

// gets ini filename
// function receives filename and outputs file contents to hashtable
//
std::vector<std::string> IniSettings::IniFileSplitLine(std::string line) 
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

int IniSettings::LoadIni(std::string filename) 
{
	std::ifstream instream = openFile(filename);
	std::string line, section;
	std::vector<std::string> item;
	StringMap table;
	
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

// gets section from ini file with filename
// function receives filename and section to look in file for and outputs hashtable(section)
//
int IniSettings::LoadIni(std::string filename, std::string section) 
{
	std::ifstream instream = openFile(filename);
	std::string line;
 
	while (std::getline(instream, line)) 
		std::cout << line << std::endl;
	
	instream.close();
	
	return 0;
}

int IniSettings::SaveIni(std::string filename) {

	// loop through each section and through items in memory
	// write section > item > value to file

	return 0;
}